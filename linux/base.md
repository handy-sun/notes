# **linux system**

---

## <font color="#66ccdd" size="4"> 1、用户和用户组。</font>

在使用 CentOS 之前用的更多是Ubuntu，所以在 useradd 和 adduser 两条命令出现歧义，在Ubuntu系统上这是两条命令，而在CentOS上则是同一条命令，adduser 是链接的形式存在

```sh
# ll /usr/sbin/ | grep 'user'
lrwxrwxrwx. 1 root root  7 10月 30 17:09 adduser -> useradd
-rwxr-x---. 1 root root 114064 6月 10 09:16 useradd
```

### 1) 添加用户，创建用户完毕后，必须修改密码否则无法登陆

```sh
useradd dev #创建用户
passwd dev #修改密码

# 更改用户 dev 的密码 。
# 新的 密码：
# 重新输入新的 密码：
# passwd：所有的身份验证令牌已经成功更新。
```

建工作组
```sh
groupadd test             //新建test工作组
```

新建用户同时增加工作组
```sh
useradd -g test phpq        //新建phpq用户并增加到test工作组
#注：：-g 所属组 -d 家目录 -s 所用的SHELL
```

给已有的用户增加工作组
```sh
usermod -G groupname username
#或者：(但此用户依然属于之前的组)
gpasswd -a user group
```

### 2) 从组中移除用户和彻底删除用户
```sh
# 从组中移除用户
gpasswd test -d phpq
# 彻底删除用户（包括/home目录下）
userdel -r stage
```

### 3) 更改属主和同组人

有时候还需要更改文件的属主和所属的组。只有文件的属主有权更改其他属主和所属的组，用户可以把属于自己的文件转让给大家。改变文件属主用chown命令

```sh
chown [-R] <用户名或组><文件或目录>
# 把文件files属主改成zh888用户。
chown zh888 files
# 将files所有目录和子目录下的所有文件或目录的主和组都改成zh888.
chown -R zh888.zh888 files
# 通过在组前面加一个冒号，可以只更改组。现在，gamma 组的成员可以编辑该文件：
chown :gamma mynotes
```

### 4) 设置文件的目录和目录生成掩码

用户可以使用umask命令设置文件默认的生成掩码。默认的生成掩码告诉系统创建一个文件或目录不应该赋予哪些权限。如果用户将umask命令放在环境文件.bash_profile中，就可以控制所有新建的文件和目录的访问权限。

```sh
# a1表示的是不允许属主的权限，a2表示的是不允许同组人的权限，a3代表不允许其他人的权限。
umask [a1a2a3]
# 表示设置不允许同组用户和其他用户有写的权限
umask 022
# 显示当前的默认生成掩码。
umask
```

补充: 查看用户和用户组的方法


用户列表文件：/etc/passwd

用户组列表文件：/etc/group

查看系统中有哪些用户：cut -d : -f 1 /etc/passwd

查看可以登录系统的用户：cat /etc/passwd | grep -v /sbin/nologin | cut -d : -f 1

查看某一用户：w 用户名

查看登录用户：who

查看用户登录历史记录：last


