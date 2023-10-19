# **linux system**

---

## 1. 用户和用户组。</font>

### 1.1 useradd 和 adduser 
useradd 和 adduser 两条命令，在Ubuntu系统上这是两条命令，
而在CentOS上则是同一条命令，adduser 是链接的形式存在

```sh
LANG=C ls -l /usr/sbin/ | grep -E 'useradd|adduser'
# ------------------ Ubuntu20.04
lrwxrwxrwx 1 root root         7 Apr 16  2020 addgroup -> adduser*
-rwxr-xr-x 1 root root     37785 Apr 16  2020 adduser*
-rwxr-xr-x 1 root root    147160 Nov 29  2022 useradd*
# ------------------ other
lrwxrwxrwx. 1 root root       7  Jun 24  2021 adduser -> useradd
-rwxr-xr-x. 1 root root   22568  Jun 24  2021 luseradd
-rwxr-xr-x. 1 root root  142760  Jun 24  2021 useradd

```

### 1.2 添加用户

创建用户若没有指定密码，必须修改密码否则无法登陆

```sh
useradd dev
# useradd有可能无法在/home目录下生成相应的目录，此时删除用户，改用adduser
passwd dev

# 更改用户 dev 的密码 。
# 新的 密码：
# 重新输入新的 密码：
# passwd：所有的身份验证令牌已经成功更新。
```

建工作组
```sh
# 新建test工作组
groupadd test
```

新建用户同时增加工作组
```sh
# 新建phpq用户并增加到test工作组
useradd -g test phpq
#注：：-g 所属组 -d 家目录 -s 所用的SHELL
```

给已有的用户增加工作组
```sh
usermod -G groupname username
#或者：(但此用户依然属于之前的组)
gpasswd -a user group
```

推荐的创建用户命令（新建tester用户并添加到prac工作组）
<font bold="true" size="5">
```sh
useradd -g prac -m tester -d /home/tester -s /bin/bash
```
</font>

### 1.3 从组中移除用户和彻底删除用户
```sh
# 从组中移除用户
gpasswd test -d phpq
# 彻底删除用户（包括/home目录下）
userdel -r stage
```

### 1.4 更改属主和同组人

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

### 1.5 设置文件的目录和目录生成掩码

用户可以使用umask命令设置文件默认的生成掩码。默认的生成掩码告诉系统创建一个文件或目录不应该赋予哪些权限。如果用户将umask命令放在环境文件.bash_profile中，就可以控制所有新建的文件和目录的访问权限。

```sh
# a1表示的是不允许属主的权限，a2表示的是不允许同组人的权限，a3代表不允许其他人的权限。
umask [a1a2a3]
# 表示设置不允许同组用户和其他用户有写的权限
umask 022
# 显示当前的默认生成掩码。
umask
```

### 1.6 查看用户和用户组的方法

```sh
# 用户列表文件
cat /etc/passwd
# 用户组列表文件
cat /etc/group
# 查看系统中有哪些用户
cut -d: -f1 /etc/passwd
# 查看可以登录系统的用户
grep -E '*sh$' /etc/passwd
grep -v '/nologin' /etc/passwd | grep -v '/false' | cut -d: -f1
# 查看可以登录系统并设置密码的用户(/etc/shadow文件需要root权限)
sudo grep -v '!\*' /etc/shadow | cut -d: -f1
# 查看某一用户
w 用户名
# 查看登录用户
who
# 查看用户登录历史记录
last
```

在Linux系统中，将用户的shell设置为`/bin/false`的目的是禁止该用户登录到系统。这通常用于创建系统用户，这些用户不需要交互式登录，例如用于运行特定的服务或任务。

当一个用户的shell被设置为`/bin/false`时，当该用户尝试登录时，系统会立即终止登录会话，因为`/bin/false`是一个命令，它会立即退出并返回非零退出状态码，这将导致登录失败。这可以用来提高系统的安全性，因为禁止不必要的用户登录可以减少潜在的安全风险。

另一种类似的方法是将shell设置为`/sbin/nologin`（在部分发行版中可能`/usr/bin/nologin`），其效果类似，也会阻止用户交互式登录。这些设置通常用于系统账户或服务账户，以确保这些账户只能用于特定的系统任务而不允许用户登录。
