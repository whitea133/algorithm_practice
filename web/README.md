# 代码默写对比网页

这个目录是一个很轻量的本地网页，用来默写 `src/` 里的 C++ 模板并做对比。

## 启动

```bash
cd /Users/whitea133/codeProject/suanFa
cp web/.env.example web/.env
# 把 .env 里的 DEEPSEEK_API_KEY 换成你的真实 Key
npm start
```

然后打开：

```text
http://127.0.0.1:3000
```

不配置 DeepSeek Key 也能用，本地逐行对比仍然会正常工作；配置 Key 后，下方会额外返回 DeepSeek 的语义检查结果。

代码编辑器使用本地的 CodeMirror 文件，放在 `web/vendor/codemirror/`，启动页面时不依赖 CDN。

## API Key 怎么保护

真实 Key 只放在 `web/.env`，根目录 `.gitignore` 已经忽略 `.env` 和 `.env.*`，所以不会被提交到 GitHub。仓库里只保留 `.env.example`，它只有占位符，方便别人知道需要哪些配置项。
