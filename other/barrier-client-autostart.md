## macOS Barrier 开机总以服务端模式启动

现象：本机实际要作为 Barrier 客户端连接到另一台机器，但每次开机自启动后，Barrier GUI 总是恢复成服务端模式。

原因一般是 Barrier 的 macOS 偏好设置里保存了上一次选择的模式：

- `groupServerChecked = 1`
- `groupClientChecked = 0`

把它改成客户端模式即可：

```shell
defaults write com.github.Barrier groupClientChecked -bool true
defaults write com.github.Barrier groupServerChecked -bool false
defaults write com.github.Barrier autoStart -bool true

# 按实际服务端 IP 修改
defaults write com.github.Barrier serverHostname -string '192.168.1.29'

# 让 macOS 偏好设置缓存重新加载
killall cfprefsd
```

检查配置：

```shell
defaults read com.github.Barrier groupClientChecked
defaults read com.github.Barrier groupServerChecked
defaults read com.github.Barrier serverHostname
defaults read com.github.Barrier autoStart
```

期望输出类似：

```text
1
0
192.168.1.29
1
```

确认当前进程是否为客户端：

```shell
ps aux | rg -i '[b]arrier|[b]arriers|[b]arrierc'
```

如果看到 `barrierc ... [服务端IP]:24800`，说明当前运行的是客户端；如果看到 `barriers`，则是服务端进程。

登录项可以这样确认：

```shell
osascript -e 'tell application "System Events" to get the name of every login item'
```

里面有 `Barrier` 即表示它会随登录启动。
