# 1. git初始化克隆下来的仓库中的子模块


## 1.1 **克隆主仓库**：首先，克隆主仓库，这将包括子模块的配置信息，但尚未初始化或下载子模块的内容。

   ```bash
   git clone <URL of Main Repository>
   ```

## 1.2 **进入主仓库目录**：进入刚刚克隆的主仓库目录。

   ```bash
   cd <Main Repository Directory>
   ```

## 1.3 **初始化子模块**：使用以下命令初始化子模块。这将会下载子模块的内容并将其初始化。

   ```bash
   git submodule init
   ```

## 1.4 **更新子模块**：运行以下命令来更新子模块内容。

   ```bash
   git submodule update
   ```

   或者，如果你想一次完成初始化和更新，可以使用以下命令：

   ```bash
   git submodule update --init
   ```

如果主仓库中的子模块有更新，在主仓库中使用`git submodule update`来获取最新的子模块内容。

请确保在使用子模块时理解其工作原理，以便在主仓库和子模块之间进行正确的协作和版本控制。

# 2. 其他的初始化方法

```shell
git submodule update --init --recursive
```

是用于初始化和更新Git子模块的命令，其含义如下：

- `git submodule update`：这部分命令是用于更新子模块的内容。当你运行它时，Git会进入每个已配置的子模块目录并尝试更新它们。如果子模块尚未初始化，它将尝试初始化子模块。这是执行主要子模块操作的一部分。

- `--init`：此选项用于初始化尚未初始化的子模块。如果子模块已经初始化，该选项不会产生影响。

- `--recursive`：此选项告诉Git递归地更新子模块中的子模块。这对于具有嵌套子模块结构的仓库非常有用。如果你的子模块中还包含子模块，使用此选项将确保所有嵌套子模块都被正确初始化和更新。

`git submodule update --init --recursive` 的目的是确保主仓库中的所有子模块都被初始化、更新，并且如果子模块中还包含其他子模块，也会被递归地初始化和更新。这是在处理具有复杂子模块结构的仓库时非常有用的命令。

# 3. 在项目中添加子模块

1. 先进入仓库的根目录

2. 加入子模块的仓库地址和其在本仓库的相对路径

```shell
git submodule add <repo_url> <module_path>
```

会生成 `.gitmodules` 文件

3. 添加、提交、推送

```shell
git add .gitmodules <module_path>
git commit -m '...add submodule...'
git push
```

# 4. 重新添加子模块

如果之前项目中的子模块url需要变更，则应该重新添加子模块
，请确保已经备份了重要数据，避免数据丢失。

```shell
git rm .gitmodules
git rm --cached path_to_submodule
rm -rf .git/modules/path_to_submodule
rm -rf path_to_submodule
```

执行以上命令后，子模块已经被完全移除。然后，您可以使用 `git submodule add` 命令重新添加子模块。

```shell
git submodule add new_url path_to_submodule
```

但却提示

```shell
fatal: please make sure that the .gitmodules file is in the working tree
```

尝试创建一个新的 .gitmodules, 再次使用 `git submodule add`

```shell
touch .gitmodules
git submodule add new_url path_to_submodule
```

这次可以看到开始拉新的子模块的库了

