## nix repl 与 nix eval 的差异

两者都是 Nix 的求值工具，但定位和行为有明显区别。

**nix eval**

- 一次性求值，输出结果后退出
- 默认以文本形式打印结果（JSON/递归属性集等）
- 适合脚本集成、CI 检查、快速查看某个表达式的值
- 常用形式：
  - `nix eval .#nixosConfigurations.host.config.networking.hostName`
  - `nix eval --json .#packages.x86_64-linux.default`
  - `nix eval --expr '1 + 2'`

**nix repl**

- 交互式 REPL，加载后持续等待输入
- 支持 Tab 补全、`:q` 退出、`:t` 查看类型
- 可以逐步探索大型属性集（如 NixOS config 树）
- 加载 flake：`nix repl` 后输入 `:lf .` 或启动时 `nix repl .`
- 加载文件：`:l <path>` 加载任意 .nix 文件
- 在 REPL 中可以持续引用之前加载的绑定，适合调试

**关键差异总结**

- eval 是"命令行一次性求值"，repl 是"交互式探索环境"
- eval 输出可控（`--json`/`--raw`），repl 输出适合人类阅读
- eval 可嵌入脚本，repl 适合手动调试

## 在命令行中求值 let ... in 变量

Nix 文件中 `let ... in` 绑定的变量默认对外不可见——它们是表达式作用域内的局部绑定，不是模块系统的 option，无法通过 `nix eval .#xxx` 的属性路径访问。

**方法一：用 `--expr` 直接求值整个表达式**

```bash
nix eval --expr 'let x = 42; y = x + 1; in { inherit x y; }'
# => { x = 42; y = 43; }
```

**方法二：求值 .nix 文件本身**

如果文件是一个纯表达式（不是 module），直接 eval 文件路径会得到 `in` 之后的值：

```bash
# vars.nix 内容：let profileLevel = { guiBase = true; }; in profileLevel
nix eval --file lib/vars.nix
# => { guiBase = true; }
```

`--file`（`-f`）会求值文件的顶层表达式，`let ... in` 中 `in` 后面的值就是结果。

**方法三：结合 jq 提取特定字段**

```bash
nix eval --json -f lib/vars.nix | jq '.profileLevel.guiBase'
# => true
```

**方法四：在 nix repl 中加载并探索**

```bash
nix repl
:l lib/vars.nix
profileLevel       # 直接访问 let 绑定
profileLevel.guiBase
```

repl 加载文件后，`let` 绑定会成为当前环境的一部分，可以直接按名字引用，还能 Tab 补全。

**与 specialArgs 的关系**

`specialArgs` 传递的值（如 `profileLevel`）本质上也是通过函数参数绑定到模块作用域的。在 flake 的属性树中，它们不作为独立节点存在——你无法 `nix eval .#nixosConfigurations.host.profileLevel` 来访问它，因为它是函数参数，不是 config attribute。

要查看某个 host 实际使用的 `profileLevel`，需要在构建上下文中求值：

```bash
# 如果 mksystem.nix 把 profileLevel 放进了 specialArgs
# 它不在 config 树中，无法通过 config.xxx 访问
# 但可以通过查看 flake inputs 或 lib/vars.nix 的输出来确认
nix eval --json -f lib/vars.nix profileLevel
```
