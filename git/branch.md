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

## 二、标签

### 删除本地tag
```sh
git tag -d tag-name
```

### 删除远程tag
```sh
git push origin :refs/tags/tag-name
```
