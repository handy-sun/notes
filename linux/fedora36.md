# **fedora36 基础开发环境配置**

---

系统镜像下载链接:

<https://mirrors.tuna.tsinghua.edu.cn/fedora/releases/36/Server/x86_64/iso/Fedora-Server-dvd-x86_64-36-1.5.iso>

## 1. 将镜像源更新为国内的 </font>

```sh
# 备份之前的repo文件
cd /etc/yum.repos.d/
mkdir bak
mv *.repo bak/
# 下载阿里云的repo文件
wget -O /etc/yum.repos.d/fedora.repo http://mirrors.aliyun.com/repo/fedora.repo
wget -O /etc/yum.repos.d/fedora-updates.repo http://mirrors.aliyun.com/repo/fedora-updates.repo
# 重新建立缓存
dnf makecache
```

## 2. 安装常用的软件组和软件包 </font>

```sh
# 查看目前软件组列表
dnf group list

# 安装软件组: 'C语言开发工具和库', '开发工具', '系统工具'
dnf groupinstall 'C Development Tools and Libraries'
dnf groupinstall 'Development Tools'
dnf groupinstall 'System Tools'

# 安装个人常用的软件包
dnf -y install cmake samba ccache unrar p7zip nmap glibc-static ncurses-static ninja-build trash-cli pigz htop clang clang-tools-extra lldb
```

----------------------
