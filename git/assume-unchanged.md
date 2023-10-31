
# GIT 忽略本地某一文件更改，不提交

比如有一个文件： config.ini 里面有一些本地开发环境参数，不需要提交

```shell
git update-index --assume-unchanged config.ini
```

就看不到config.ini 文件了

如果需要提交config.ini文件了，执行：

```shell
git update-index --no-assume-unchanged config.ini
```

就可以看到config.ini了，这时就可以提交了