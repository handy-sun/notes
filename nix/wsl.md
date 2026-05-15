## 安装

去 [发布页](https://github.com/nix-community/NixOS-WSL/releases)下载最新的NixOS-WSL发行版

根据 `https://nix-community.github.io/NixOS-WSL/install.html`的说法


可以打开（双击）.wsl 文件进行安装。也可以通过 PowerShell 执行安装：

```powershell
wsl --install --from-file nixos.wsl
```

nixos.wsl 如果在另一个目录中运行该命令，则必须是刚刚下载的文件的路径。

您可以使用 `--name` --name 和 `--location` --location 标志来更改发行版注册名称（默认值：`<distro_name> NixOS`）

和磁盘映像位置（默认值：`<distro_image> %localappdata%\wsl\{some random GUID}`）。有关完整选项列表，请参阅[此处]。


### 1 直接双击安装的

`%localappdata%\wsl\{some random GUID}` 是在这个目录下存储 `ext4.vhdx` 文件。

默认登录用户为nixos, `id`
```
uid=1000(nixos) gid=100(users) groups=100(users),1(wheel)
```

试了下更改默认用户和移动位置


```powershell
wsl --manage NixOS --set-default-user qi
```

*wsl: Failed to start the systemd user session for 'root'. See journalctl for more details.
bash: line 1: /usr/bin/id: No such file or directory*


```powershell
wsl --manage NixOS --move "C:\\sth\\nixos-wsl"
```

*另一个程序正在使用此文件，进程无法访问。
错误代码: Wsl/Service/MoveDistro/ERROR_SHARING_VIOLATION*
（文件夹都已通过此命令创建了）

卸载重装

```powershell
wsl --unregister NixOS
```

```
正在注销。
操作成功完成。
```

### 2 命令行安装

磁盘映像位置使用默认生成

```powershell
wsl --install --from-file nixos.wsl --name nixos --no-launch
# 指定位置 文件夹提前创建好
wsl --install --from-file 'D:\迅雷下载\nixos.wsl' --name nixos --no-launch --location 'C:\wsl\nixos'
```

这个name是wsl识别子系统的关键，和系统内的主机名没有关系

**注意：这个wsl2初始进入时用户名和主机名都是nixos，**

先关闭wsl2, 之后启用强制vhd稀疏（减少空间占用）

```powershell
wsl --shutdown
wsl --manage nixos --set-sparse true --allow-unsafe 
```


#### 2.1 需要先进行 nix-channel update

查看当前channel

```shell
sudo nix-channel --list
```


```
nixos https://channels.nixos.org/nixos-25.11
nixos-wsl https://github.com/nix-community/NixOS-WSL/archive/refs/heads/release-25.11.tar.gz
```

添加清华镜像源(都是不稳定版)

```shell
## 订阅镜像仓库频道
sudo nix-channel --add https://mirrors.ustc.edu.cn/nix-channels/nixpkgs-unstable nixpkgs
## 请注意系统版本
sudo nix-channel --add https://mirrors.ustc.edu.cn/nix-channels/nixos-unstable nixos
```

之后执行

```shell
sudo nix-channel --update
```

### 2.2 首次rebuild

```shell
cp /etc/nixos/configuration.nix{,.bak}
```

在中间部分（imports段落后，wsl.enable属性前）添加内容，
加上必要的软件和开启实验特性

```nix
  nix = {
    enable = true;
    settings = {
      trusted-users = [ "qi" ];
      experimental-features = [
        "nix-command"
        "flakes"
      ];
      substituters = [
        "https://mirrors.ustc.edu.cn/nix-channels/store"
        "https://mirror.sjtu.edu.cn/nix-channels/store"
        "https://cache.garnix.io"
      ];
      trusted-public-keys = [
        "cache.garnix.io:CTFPyKSLcx5RMJKfLo5EEPUObbA78b0YQ2DTCJXqr9g="
      ];
      extra-substituters = [
        "https://cache.numtide.com"
        "https://nix-community.cachix.org"
      ];
      extra-trusted-public-keys = [
        "niks3.numtide.com-1:DTx8wZduET09hRmMtKdQDxNNthLQETkc/yaX7M4qK0g="
        "nix-community.cachix.org-1:mB9FSh9qf2dCimDSUo8Zy7bkq5CX+/rkCWyvRCYg3Fs="
      ];
      auto-optimise-store = true;
      builders-use-substitutes = true;
      accept-flake-config = true;
    };
  };
  networking.resolvconf.enable = false;
```

第二次装nixos-wsl,
遇到了
```
error:
       Failed assertions:
       - networking.resolvconf.enable is true but environment.etc."resolv.conf"
       is also set. Set networking.resolvconf.enable = false if another
       service manages /etc/resolv.conf.
```
所以
networking.resolvconf.enable = false;


开始rebuild

**建议关闭外部主机的tun代理工具，可能会影响网络**

```
sudo nixos-rebuild switch
```

### 2.3 构建自己仓库的配置

注意在非root用户(nixos)的shell下，仓库目录中执行命令

默认用户名 *nixos* 会更改为配置中的用户名

构建完毕最好重启此子系统

```shell
nh os switch . -H myHost
```

#### 卡住问题
目前遇到第一次正式构建仓库中配置，有14.2G, 显示了 `> Activating configuration` 这一步后会卡住，
Ctrl-C , 然后手动boot一下

```sh
sudo nixos-rebuild boot --flake .#myHost
```
