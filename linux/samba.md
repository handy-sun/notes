# **配置samba服务映射**

---



## <font color="#66ccdd" size="4"> 通过Samba服务映射，之后在windows上添加网络盘，这样做的好处是可以随时共享文件。</font>

先安装一下samba：

```sh
yum install samba samba-client samba-common -y
```

然后更改samba配置文件(root)：

vi /etc/samba/smb.conf

home目录下"/home/用户名"这个目录就是我想共享映射的目录，在这个文件后面添加以下内容

```ini
[sunq]
        path = /home/sunq
        available = yes
        browseable = yes
        public = yes
        writable = yes
```

`添加samba用户`，就是共享的那个目录对应的用户：
这里的用户名和密码也是后面网络映射连接需要用到的密码

smbpasswd -a sunq


`然后关闭selinux`：

vi /etc/selinux/config，
修改SELINUX为disabled


`关闭防火墙`：systemctl stop firewalld
`开机禁用防火墙`：systemctl disable firewalld

Firewall防火墙开启Samba端口命令（不行）
```sh
firewall-cmd --permanent --zone=public --add-service=samba
firewall-cmd --reload
```

`重启smb`：systemctl restart smb

`开机启动smb进程`：systemctl enable smb

---

发现Samba不能进入文件夹，提示没有权限，发现这是Centos7的SELinux安全级别太高引起，降低为Permissive 宽容模式即可
编辑：vi /etc/selinux/config
将SELINUX=enforcing改为SELINUX=disabled
然后重启系统生效
用getenforce命令查看,显示Permissive就成功了
