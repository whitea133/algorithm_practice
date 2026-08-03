const templateSelect = document.querySelector("#templateSelect");
const codeInput = document.querySelector("#codeInput");
const lineCount = document.querySelector("#lineCount");
const charCount = document.querySelector("#charCount");
const saveState = document.querySelector("#saveState");
const compareBtn = document.querySelector("#compareBtn");
const clearBtn = document.querySelector("#clearBtn");
const userDiff = document.querySelector("#userDiff");
const refDiff = document.querySelector("#refDiff");
const userSummary = document.querySelector("#userSummary");
const refSummary = document.querySelector("#refSummary");
const aiState = document.querySelector("#aiState");
const aiResult = document.querySelector("#aiResult");

let templates = [];
let saveTimer = null;
let editor = null;

init();

async function init() {
  restoreDraft();
  setupEditor();
  syncEditorMeta();
  compareBtn.addEventListener("click", compareCode);
  clearBtn.addEventListener("click", clearEditor);
  templateSelect.addEventListener("change", saveDraft);
  await loadTemplates();
}

function setupEditor() {
  if (window.CodeMirror) {
    editor = CodeMirror.fromTextArea(codeInput, {
      mode: "text/x-c++src",
      lineNumbers: true,
      indentUnit: 4,
      tabSize: 4,
      indentWithTabs: false,
      lineWrapping: false,
      autoCloseBrackets: true,
      matchBrackets: true,
      extraKeys: {
        Tab(cm) {
          cm.replaceSelection("    ");
        },
      },
    });
    editor.on("change", onInput);
    return;
  }

  codeInput.addEventListener("input", onInput);
  codeInput.addEventListener("keydown", handleTextareaKeys);
}

async function loadTemplates() {
  setBusy(true);
  try {
    const response = await fetch("/api/templates");
    if (!response.ok) throw new Error("模板列表读取失败");
    templates = await response.json();
    templateSelect.replaceChildren(
      ...templates.map((item) => {
        const option = document.createElement("option");
        option.value = item.id;
        option.textContent = item.id;
        return option;
      }),
    );
    const savedTemplate = localStorage.getItem("dictation.template");
    if (savedTemplate && templates.some((item) => item.id === savedTemplate)) {
      templateSelect.value = savedTemplate;
    }
  } catch (error) {
    aiState.textContent = "读取失败";
    aiResult.textContent = error.message;
  } finally {
    setBusy(false);
  }
}

function onInput() {
  syncEditorMeta();
  saveState.textContent = "保存中...";
  clearTimeout(saveTimer);
  saveTimer = setTimeout(saveDraft, 250);
}

function syncEditorMeta() {
  const code = getCode();
  const lines = code.split("\n").length;
  lineCount.textContent = `${lines} 行`;
  charCount.textContent = `${code.length} 字符`;
}

function saveDraft() {
  localStorage.setItem("dictation.code", getCode());
  localStorage.setItem("dictation.template", templateSelect.value);
  saveState.textContent = "已自动保存";
}

function restoreDraft() {
  codeInput.value = localStorage.getItem("dictation.code") || "";
}

function clearEditor() {
  setCode("");
  userDiff.textContent = "";
  refDiff.textContent = "";
  userSummary.textContent = "等待对比";
  refSummary.textContent = "等待对比";
  aiState.textContent = "未开始";
  aiResult.textContent = "已经清空，可以重新默写。";
  onInput();
}

function getCode() {
  return editor ? editor.getValue() : codeInput.value;
}

function setCode(value) {
  if (editor) {
    editor.setValue(value);
  } else {
    codeInput.value = value;
  }
}

function handleTextareaKeys(event) {
  const pairs = {
    "(": ")",
    "[": "]",
    "{": "}",
    "\"": "\"",
    "'": "'",
  };

  if (pairs[event.key]) {
    insertPair(event, pairs[event.key]);
    return;
  }

  if (event.key === "Backspace" && deleteEmptyPair(event, pairs)) {
    return;
  }

  if (event.key !== "Tab") return;
  event.preventDefault();
  const start = codeInput.selectionStart;
  const end = codeInput.selectionEnd;
  codeInput.setRangeText("    ", start, end, "end");
  onInput();
}

function insertPair(event, closeChar) {
  event.preventDefault();
  const start = codeInput.selectionStart;
  const end = codeInput.selectionEnd;
  const selected = codeInput.value.slice(start, end);

  codeInput.setRangeText(`${event.key}${selected}${closeChar}`, start, end, "end");

  if (!selected) {
    codeInput.setSelectionRange(start + 1, start + 1);
  }

  onInput();
}

function deleteEmptyPair(event, pairs) {
  const start = codeInput.selectionStart;
  const end = codeInput.selectionEnd;
  if (start !== end || start === 0) return false;

  const before = codeInput.value[start - 1];
  const after = codeInput.value[start];
  if (pairs[before] !== after) return false;

  event.preventDefault();
  codeInput.setRangeText("", start - 1, start + 1, "end");
  onInput();
  return true;
}

async function compareCode() {
  if (!templateSelect.value) {
    aiResult.textContent = "没有找到可对比的模板。";
    return;
  }

  setBusy(true);
  aiState.textContent = "分析中";
  aiResult.textContent = "正在对比...";

  try {
    const response = await fetch("/api/compare", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        templateId: templateSelect.value,
        code: getCode(),
      }),
    });
    const payload = await response.json();
    if (!response.ok) throw new Error(payload.error || "对比失败");

    const diff = buildLineDiff(getCode(), payload.reference);
    renderDiff(userDiff, diff.userRows);
    renderDiff(refDiff, diff.refRows);
    userSummary.textContent = `${diff.userIssues} 处需检查`;
    refSummary.textContent = `${diff.refIssues} 处差异`;
    aiState.textContent = payload.analysis ? "已完成" : "本地对比";
    aiResult.textContent = payload.analysis || payload.analysisError || "未配置 DeepSeek，已完成本地逐行对比。";
  } catch (error) {
    aiState.textContent = "失败";
    aiResult.textContent = error.message;
  } finally {
    setBusy(false);
  }
}

function buildLineDiff(userCode, referenceCode) {
  const a = userCode.replace(/\s+$/g, "").split("\n");
  const b = referenceCode.replace(/\s+$/g, "").split("\n");
  const matrix = Array.from({ length: a.length + 1 }, () => Array(b.length + 1).fill(0));

  for (let i = a.length - 1; i >= 0; i -= 1) {
    for (let j = b.length - 1; j >= 0; j -= 1) {
      matrix[i][j] = a[i] === b[j] ? matrix[i + 1][j + 1] + 1 : Math.max(matrix[i + 1][j], matrix[i][j + 1]);
    }
  }

  const userRows = [];
  const refRows = [];
  let i = 0;
  let j = 0;

  while (i < a.length || j < b.length) {
    if (i < a.length && j < b.length && a[i] === b[j]) {
      userRows.push(row("same", i + 1, a[i]));
      refRows.push(row("same", j + 1, b[j]));
      i += 1;
      j += 1;
    } else if (j < b.length && (i === a.length || matrix[i][j + 1] >= matrix[i + 1]?.[j])) {
      userRows.push(row("del", "", ""));
      refRows.push(row("add", j + 1, b[j]));
      j += 1;
    } else {
      userRows.push(row("change", i + 1, a[i]));
      refRows.push(row("del", "", ""));
      i += 1;
    }
  }

  return {
    userRows,
    refRows,
    userIssues: userRows.filter((item) => item.type !== "same").length,
    refIssues: refRows.filter((item) => item.type !== "same").length,
  };
}

function row(type, line, text) {
  return { type, text: `${String(line).padStart(4, " ")} | ${text}` };
}

function renderDiff(target, rows) {
  target.replaceChildren(
    ...rows.map((item) => {
      const span = document.createElement("span");
      span.className = `line ${item.type}`;
      span.textContent = item.text;
      return span;
    }),
  );
}

function setBusy(isBusy) {
  compareBtn.disabled = isBusy;
  templateSelect.disabled = isBusy;
}
