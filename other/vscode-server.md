

## 记录一下远程server安装出错 只能手动下载的情况

先到远端的服务器内，在~/.vscode-server 记住Commit ID

可以通过下面的链接下载(其他架构类推)

```shell
## linux-x64
https://update.code.visualstudio.com/commit:${commit_id}/server-linux-x64/stable
## darwin-arm64
https://update.code.visualstudio.com/commit:${commit_id}/server-darwin-arm64/stable
```

2026年了，vscode-server的路径已经是新的了:

```shell
mkdir -p ~/.vscode-server/cli/server
unzip vscode-server-darwin-arm64.zip
mv vscode-server-darwin-arm64 ~/.vscode-server/cli/server/Stable-${commit_id}
```

## 后续:重启vscode后 再重新远程连接依然还会失败?

后来发现其实是 `Remote-SSH` 插件在MacOS下用的bsdtar解压命令(hardcode)，插件开发者未考虑用户环境变量中的tar实际为gnutar,
如果用了gnutar,则会解压失败,后续一系列的安装步骤就都失败了

先把 `Remote-SSH` 插件禁用更新再说。。。