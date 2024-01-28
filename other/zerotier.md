## zerotier manjaro 上的安装

官网的脚本只能适用于debian, redhat, suse系的发行版，arch系执行应该是会报错的
不过pacman能安装：

```bash
sudo pacman -S zerotier-one
```

安装过程中会添加相应的用户和用户组

> ...
> Creating group 'zerotier-one' with GID 943.
> Creating user 'zerotier-one' (ZeroTier One user) with UID 943 and GID 943.
>...


```bash
# 设置自启服务并启动（但有问题）
sudo systemctl enable --now zerotier-one.service
# 查看cli是否能连接程序
sudo zerotier-cli status

```

结果

> Error connecting to the ZeroTier service: connection failed
> Please check that the service is running and that TCP port 9993 can be contacted via 127.0.0.1.

看了下端口是被zerotier-one占用的，绑定的也是 0.0.0.0:9993, 不懂为啥状态不对。。。

```bash
# 先停止服务
sudo systemctl stop zerotier-one.service
# 运行程序（后台方式）
sudo zerotier-one -d
sudo zerotier-cli status
```

这次竟然正常了。。

> 200 info a58298793a 1.12.2 OFFLINE

获取当前的连接情况，不是一定要执行

```bash
sudo zerotier-cli listpeers 
```

```
200 listpeers <ztaddr> <path> <latency> <version> <role>
200 listpeers 62f865ae71 50.7.252.138/9993;4606;113536 822 - PLANET
200 listpeers 778cde7190 103.195.103.66/9993;114760;113440 881 - PLANET
200 listpeers cafe04eba9 84.17.53.155/9993;114760;113441 903 - PLANET
200 listpeers cafe9efeb9 104.194.8.134/9993;-1;113293 1467 - PLANET
```

```bash
sudo zerotier-cli join {NETWORK ID}
# sudo zerotier-cli listpeers 会看到多了一行

# allowManaged改为0的理由如下：
# 解决 勾选Authorized后，zerotier自动将路由下发到ubuntu，如果
# zerotier设置的路由为10.0.1.0/24,会导致本来10.0.1.0/24 dev br-lan
# 变成10.0.1.0/24 dev ztxxxxxxxxx,然后你就不能连接路由器了
# 自己尝试后发现这样没法连接本网络下其他zerotier设备了，还是设为1吧，暂未遇到需要设为0的场景
sudo set {NETWORK ID} allowManaged=1

kill -9 {PID}
sudo systemctl restart zerotier-one.service
```

