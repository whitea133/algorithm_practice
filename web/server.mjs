import http from "node:http";
import { readFile, readdir } from "node:fs/promises";
import path from "node:path";
import { fileURLToPath } from "node:url";

const WEB_DIR = path.dirname(fileURLToPath(import.meta.url));
const ROOT_DIR = path.resolve(WEB_DIR, "..");
const SRC_DIR = path.join(ROOT_DIR, "src");
const VENDOR_DIR = path.join(WEB_DIR, "vendor");
const HOST = process.env.HOST || "127.0.0.1";
const PORT = Number(process.env.PORT || 3000);
const MAX_BODY_BYTES = 200 * 1024;
const STATIC_FILES = new Map([
  ["/", "index.html"],
  ["/index.html", "index.html"],
  ["/style.css", "style.css"],
  ["/app.js", "app.js"],
]);

loadEnv(await readOptionalFile(path.join(WEB_DIR, ".env")));

const server = http.createServer(async (req, res) => {
  try {
    const url = new URL(req.url, `http://${HOST}:${PORT}`);
    if (req.method === "GET" && STATIC_FILES.has(url.pathname)) {
      return serveStatic(res, STATIC_FILES.get(url.pathname));
    }
    if (req.method === "GET" && url.pathname.startsWith("/vendor/")) {
      return serveVendor(res, url.pathname);
    }
    if (req.method === "GET" && url.pathname === "/api/templates") {
      const templates = await listTemplates();
      return sendJson(res, 200, templates.map((id) => ({ id })));
    }
    if (req.method === "POST" && url.pathname === "/api/compare") {
      return compareTemplate(req, res);
    }
    sendJson(res, 404, { error: "Not found" });
  } catch (error) {
    sendJson(res, 500, { error: error.message || "Server error" });
  }
});

server.listen(PORT, HOST, () => {
  console.log(`Code dictation web app: http://${HOST}:${PORT}`);
});

async function serveStatic(res, fileName) {
  const filePath = path.join(WEB_DIR, fileName);
  return sendFile(res, filePath, fileName, "no-store");
}

async function serveVendor(res, pathname) {
  const relativePath = decodeURIComponent(pathname.replace(/^\/vendor\//, ""));
  const filePath = path.resolve(VENDOR_DIR, relativePath);
  if (!filePath.startsWith(`${VENDOR_DIR}${path.sep}`)) {
    return sendJson(res, 403, { error: "Forbidden" });
  }
  return sendFile(res, filePath, relativePath, "public, max-age=31536000, immutable");
}

async function sendFile(res, filePath, fileName, cacheControl) {
  const ext = path.extname(fileName);
  const contentTypes = {
    ".html": "text/html; charset=utf-8",
    ".css": "text/css; charset=utf-8",
    ".js": "text/javascript; charset=utf-8",
  };
  res.writeHead(200, {
    "Content-Type": contentTypes[ext] || "application/octet-stream",
    "Cache-Control": cacheControl,
  });
  res.end(await readFile(filePath));
}

async function compareTemplate(req, res) {
  const body = await readJsonBody(req);
  const templateId = String(body.templateId || "");
  const userCode = String(body.code || "");
  const templates = await listTemplates();

  if (!templates.includes(templateId)) {
    return sendJson(res, 400, { error: "模板不存在或路径不合法" });
  }

  const reference = await readFile(path.join(SRC_DIR, templateId), "utf8");
  const ai = await analyzeWithDeepSeek(templateId, userCode, reference);
  sendJson(res, 200, {
    reference,
    analysis: ai.analysis,
    analysisError: ai.error,
  });
}

async function listTemplates() {
  const files = [];

  async function walk(dir) {
    const entries = await readdir(dir, { withFileTypes: true });
    for (const entry of entries) {
      const fullPath = path.join(dir, entry.name);
      if (entry.isDirectory()) {
        await walk(fullPath);
      } else if (entry.isFile() && entry.name.endsWith(".cpp")) {
        files.push(path.relative(SRC_DIR, fullPath).split(path.sep).join("/"));
      }
    }
  }

  await walk(SRC_DIR);
  return files.sort((a, b) => a.localeCompare(b));
}

async function analyzeWithDeepSeek(templateId, userCode, reference) {
  const apiKey = process.env.DEEPSEEK_API_KEY;
  if (!apiKey) {
    return { analysis: null, error: "未配置 DEEPSEEK_API_KEY，所以这里只显示本地逐行对比。" };
  }

  try {
    const response = await fetch("https://api.deepseek.com/chat/completions", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${apiKey}`,
      },
      body: JSON.stringify({
        model: process.env.DEEPSEEK_MODEL || "deepseek-chat",
        temperature: 0.2,
        messages: [
          {
            role: "system",
            content: "你是算法模板默写批改助手。请只指出会影响正确性、边界条件、复杂度或模板结构的问题；如果没有问题，直接说明正确。",
          },
          {
            role: "user",
            content: [
              `模板文件: ${templateId}`,
              "【标准模板】",
              reference,
              "【学生默写】",
              userCode,
              "请用中文输出：1. 总体结论 2. 关键错误 3. 可忽略差异。",
            ].join("\n"),
          },
        ],
      }),
    });

    const payload = await response.json();
    if (!response.ok) {
      return { analysis: null, error: `DeepSeek 调用失败：${payload.error?.message || response.status}` };
    }
    return { analysis: payload.choices?.[0]?.message?.content || "DeepSeek 没有返回内容。", error: null };
  } catch (error) {
    return { analysis: null, error: `DeepSeek 调用失败：${error.message}` };
  }
}

function readJsonBody(req) {
  return new Promise((resolve, reject) => {
    let size = 0;
    const chunks = [];
    req.on("data", (chunk) => {
      size += chunk.length;
      if (size > MAX_BODY_BYTES) {
        reject(new Error("请求内容太大"));
        req.destroy();
        return;
      }
      chunks.push(chunk);
    });
    req.on("end", () => {
      try {
        resolve(JSON.parse(Buffer.concat(chunks).toString("utf8") || "{}"));
      } catch {
        reject(new Error("JSON 格式错误"));
      }
    });
    req.on("error", reject);
  });
}

function sendJson(res, statusCode, data) {
  res.writeHead(statusCode, {
    "Content-Type": "application/json; charset=utf-8",
    "Cache-Control": "no-store",
  });
  res.end(JSON.stringify(data));
}

async function readOptionalFile(filePath) {
  try {
    return await readFile(filePath, "utf8");
  } catch (error) {
    if (error.code === "ENOENT") return "";
    throw error;
  }
}

function loadEnv(content) {
  for (const line of content.split(/\r?\n/)) {
    const trimmed = line.trim();
    if (!trimmed || trimmed.startsWith("#")) continue;
    const match = trimmed.match(/^([A-Za-z_][A-Za-z0-9_]*)=(.*)$/);
    if (!match) continue;
    const [, key, rawValue] = match;
    if (process.env[key] !== undefined) continue;
    process.env[key] = rawValue.replace(/^["']|["']$/g, "");
  }
}
