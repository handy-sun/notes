## 一. 分支

### 1.使用以下命令同步远端的分支到本地
```sh
git remote update origin --p
```

### 2.查看所有分支是否包含所要找的远端分支: remote/origin/tdhtest
```sh
git branch -a
```

### 3.拉取远端分支到本地
```sh
git pull origin branch_name
```

### 4.切换分支，注意：切换前记得commit或stash，防止没有add的代码丢失
```sh
git checkout branch_name
```

要删除本地和远端的 Git 分支，可以使用以下命令：

### 5.删除本地分支
```sh
git branch -d branch_name
```

如果分支没有被合并，使用 `-D` 强制删除：
```sh
git branch -D branch_name
```

### 6.删除远端分支
```sh
git push origin --delete branch_name
```

### 7. 清理本地已失效的远程跟踪分支

远程仓库里的分支删除后，本地的 `origin/xxx` 远程跟踪分支不一定会自动消失。
如果 `git branch -a` 里还能看到很多远端已经删掉的分支，可以用 prune 清理。

预览会删除哪些远程跟踪分支，不实际删除：

```sh
git remote prune origin --dry-run
```

实际清理 `origin` 下已失效的远程跟踪分支：

```sh
git remote prune origin
```

或者在拉取远端信息时顺手清理：

```sh
git fetch --prune
```

以后每次 `git fetch` 自动清理：

```sh
git config --global fetch.prune true
```

注意：这些命令删除的是本地的 `origin/xxx` 远程跟踪引用，不会删除本地自己的分支，也不会删除远程仓库里的分支。

## 二、标签

### 删除本地tag
```sh
git tag -d tag-name
```

### 删除远程tag
```sh
git push origin :refs/tags/tag-name
```
