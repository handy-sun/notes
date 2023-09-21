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
