# CentOS 设置相关

## 1、设置CentOS7的静态IP地址

修改虚拟机网卡配置文件，如`/etc/sysconfig/network-scripts/ifcfg-ens33`，注意，文件名不一定是ifcfg-ens33，根据您的实际情况决定。

### 1)修改BOOTPROTO参数，把地址协议改为静态IP方式。
```ini
BOOTPROTO=static  # dhcp-动态分配，static-静态分配（重要)。
```
### 2)修改ONBOOT参数，把开机启动选项ONBOOT设置为yes。
```ini
ONBOOT=yes  # 是否开机引导。
```
### 3)设置DSN服务器的IP，添加以下内容。
```ini
DNS1=114.114.114.114  # 第1个DSN服务器的IP地址。
```
### 4)设置CentOS7的IP地址、子网掩码和网关参数，添加以下内容。
```ini
IPADDR=192.168.226.128  # IP地址（重要）。
NETMARSK=255.255.255.0  # 子网掩码（重要）。或是PREFIX="24"
GATEWAY=192.168.226.2   # 网关（重要）。
```

### 5)重启CentOS7的网络服务
```sh
systemctl restart network
```
