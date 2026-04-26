## 1.wsl1 常用命令

设置默认登录用户为root (在wsl安装目录下)

```powershell
#PS C:\Ubuntu_2004> 
.\ubuntu2004.exe config --default-user root
```

卸载已安装好的Linux 发行版

wsl --unregister DISTRO-NAME

## 2.WSL2启动时提示：参考的对象类型不支持尝试的操作

### 2.1 原因

如果Winsock LSP DLL被加载到其进程中，则wsl.exe将显示此错误, 在注册表

`HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\WinSock2\Parameters\AppId_Catalog`

中为wsl.exe创建一个条目。这告诉Windows不要将LSP DLL加载到wsl.exe进程中

### 2.2 解决方法

往注册表进行写入,注意wsl.exe路径要正确，可以直接运行`NoLsp_fix_WSL2.reg`进行注册

```
[HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\WinSock2\Parameters\AppId_Catalog\0408F7A3]
"AppFullPath"="C:\\Windows\\System32\\wsl.exe"
"PermittedLspCategories"=dword:80000000
```

## 3.WSL2桌面环境配置
在子系统 ~/.bashrc 后追加以下内容

```bash
export DISPLAY=$(grep -m 1 nameserver /etc/resolv.conf | awk '{print $2}'):0
export XDG_SESSION_TYPE=x11
```

## 4. WSL2莫名其妙无法联网

管理员方式启动powershell

```powershell
wsl --shutdown
netsh winsock reset
netsh int ip reset all
netsh winhttp reset proxy
ipconfig /flushdns
```

之后重启电脑即可

## 5. WSL2虚拟磁盘空间回收

WSL2 的虚拟磁盘（ext4.vhdx）会自动扩容但不会自动缩容，删除文件后需手动压缩回收空间。

### 5.1 WSL 内部清理

```bash
# 清理包缓存
sudo apt autoremove && sudo apt clean

# 删除临时文件和日志
sudo rm -rf /tmp/*
sudo rm -rf /var/log/*

# 检查缓存占用
du -sh ~/.cache
```

### 5.2 查找 VHDX 文件位置

默认路径：`%LOCALAPPDATA%\Packages\<发行版名称>\LocalState\ext4.vhdx`

在资源管理器中打开 `%LOCALAPPDATA%\Packages`，找类似 `CanonicalGroupLimited.Ubuntu...` 的文件夹。

### 5.3 diskpart 压缩（核心步骤）

管理员 PowerShell：

```powershell
# 关闭所有 WSL 实例
wsl --shutdown

# 启动 diskpart
diskpart
```

在 diskpart 中执行（替换为实际路径）：

```
select vdisk file="C:\Users\<用户名>\AppData\Local\Packages\<发行版>\LocalState\ext4.vhdx"
attach vdisk readonly
compact vdisk
detach vdisk
exit
```

### 5.4 Hyper-V 方式（Windows 11 Pro）

需启用 Hyper-V，先 `wsl --shutdown`，然后：

```powershell
Optimize-VHD -Path "VHDX文件路径" -Mode Full
```

### 5.5 Docker Desktop 用户

Docker 数据通常位于单独的 `data/ext4.vhdx` 中（在 `DockerDesktopResources` 相关目录下）。

压缩前清理 Docker 垃圾：

```powershell
docker system prune -a --volumes
```

然后对 Docker 的 VHDX 文件执行相同的 diskpart 压缩流程。


## 6. 最新线上安装方式

查看所有线上预装的子系统

```powershell
wsl --list --online
```

开始安装

```powershell
wsl --install Ubuntu --location C:\wsl\ubuntu --name ubuntu --no-launch
```

- --location：表示安装到的位置，这里安装到了 D:\wsl\ubuntu 这个位置
- --name：Linux 发行版的名称
- --no-launch: 安装好不立即启动

安装后有个警告

```
wsl: 由于潜在的数据损坏，目前已禁用稀疏 VHD 支持。=========]

要强制发行版使用稀疏 VHD，请运行:

wsl.exe --manage <DistributionName> --set-sparse true --allow-unsafe
```

不开启稀疏 VHD 完全可以正常用 WSL，唯一区别是 .vhdx 文件占磁盘空间更大，而且删除文件后不会自动缩小。
**⚠️强制开启风险：在异常断电或磁盘满的情况下可能损坏 WSL 数据，正常使用一般没问题。**

```powershell
wsl --manage ubuntu --set-sparse true --allow-unsafe
```

