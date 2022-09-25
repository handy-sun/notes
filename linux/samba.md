# **配置samba服务映射**

---



## <font color="#66ccdd" size="4"> 通过Samba服务映射，之后在windows上添加网络盘，这样做的好处是可以随时共享文件。</font>

先安装一下samba：`yum install samba`

然后更改samba配置文件(root)：

vi /etc/samba/smb.conf

home目录下"/home/用户名"这个目录就是我想共享映射的目录，在这个文件后面添加以下内容

```ini
[sunq]
        path = /home/sunq
        available = yes
        browsealbe = yes
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

`重启smb`：systemctl restart smb

`开机启动smb进程`：systemctl enable smb

