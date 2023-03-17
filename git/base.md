# git 网站上一些基本配置操作

## 一、本地创建并上传到服务器

1. 本机window系统的话先下载msys git  下载后在开始菜单里面找到  
"Git --> Git Bash" 进入命令

2. 找到要上传的目录，通过命令 git init 把这个目录变成git可以管理的仓库
```
git init
```
3. 把文件添加到版本库中，使用命令 git add .添加到暂存区里面去，不要忘记后面的小数点“.”，意为添加文件夹下的所有文件
```
git add （文件名如果后面是.责添加当前目录下所有文件）
```
4. 用命令 git commit告诉Git，把文件提交到仓库。引号内为提交说明
```
git commit -m '提交的内容介绍'
```

5. 关联到远程库
```
git remote add origin  https://github.com/XXXX/xxxx.git
```

6. 获取远程库与本地同步合并（如果远程库里有文件，必须先执行此命令，否则后续会提交会失败）
```
git pull --rebase origin master
```

7. 把本地库的内容推送到远程，使用 git push命令，实际上是把当前分支master推送到远程。执行此命令后会要求输入用户名 密码，验证通过后即开始上传。
```
git push -u origin master
```

## 二、Clone 到本地

1. 选择目标路径的上一级文件夹，右键 git bash.
    
2. 此步骤可省略，但不加此步有时可能连接不上服务器。
```bash
# origin 为远程服务器名，一般为origin;master 为分支名
git remote add origin/master 项目地址
```

1. 最后执行clone
```
git clone 项目地址
```

## 二（附）、github clone速度太慢的解决办法 
思路：

git clone特别慢是因为github.global.ssl.fastly.net域名被限制了。  
只要找到这个域名对应的ip地址，然后在hosts文件中加上ip–>域名的映射，刷新DNS缓存便可。

实施方法一：
1. 在网站 https://www.ipaddress.com/ 分别搜索：
github.global.ssl.fastly.net
github.com
       得到ip.
2. 打开hosts文件
• Windows上的hosts文件路径在C:\Windows\System32\drivers\etc\hosts
• Linux的hosts文件路径在：sudo vim /etc/hosts
3. 在hosts文件末尾添加两行(对应上面查到的ip)
151.101.185.194 github.global-ssl.fastly.net
140.82.113.4 github.com
4. 保存更新DNS
• Winodws系统的做法：打开CMD，输入ipconfig /flushdns
• Linux的做法：在终端输入sudo /etc/init.d/networking restart
5. 完成，试试git clone这条命令速度如何？

实施方法二：
git clone的浅拷贝
这里推荐大家使用浅拷贝来clone项目，浅拷贝的好处是不用clone项目的完整历史，而只需clone最近的一次提交，但是项目里面的文件都会完整地被下载下来，只是历史不会完全保留，如果你并不关系项目的git历史，那就完全可以使用浅拷贝来完成clone
像这样使用Git bash客户端命令行:
```
git clone --depth=1 https://…
```
来自 <https://blog.csdn.net/qq_15110681/article/details/94415946> 

## 三、更新到本地

### 1.正规流程
```bash
# 查看本地分支文件信息，确保更新时不产生冲突
git status
# 若文件有修改，可以还原到最初状态; 若文件需要更新到服务器上，应该先merge到服务器，再更新到本地
git checkout – [file name] 
# 查看当前分支情况
git branch
# 若分支为本地分支，则需切换到服务器的远程分支
git checkout remote branch
# 若命令执行成功，则更新代码成功！
git pull
```


### 2.快速流程

上面是比较安全的做法，如果你可以确定什么都没有改过只是更新本地代码

```bash
git pull

git branch
# 切换分支aaa
git chechout aaa 
# 创建aaa分支
git branck aaa 
# 本地创建 aaa分支，同时切换到aaa分支。只有提交的时候才会在服务端上创建一个分支
git chechout -b aaa 
```

## 四、创建 ssh

### 1. 在.ssh文件下运行 git Bash，或者输入如下代码跳转到此目录：
```
cd ~/.ssh
```
可以看到目录下是否存在id_rsa.pub 或 id_dsa.pub 文件，存在说明已经生成过sshkey。但无论是否存在，可以选择使用以前的sshkey或创建sshkey覆盖之前生成的key。

### 2. 创建一个ssh key

```
ssh-keygen -t rsa -C "your_email@example.com"
```

代码参数含义：
-t  指定密钥类型，默认是 rsa ，可以省略。
-C 设置注释文字，比如邮箱，可以省略。
-f  指定密钥文件存储文件名。

 参数全省略即为：

```
ssh-keygen
```

以上代码省略了 -f 参数，因此，运行上面那条命令后会让你输入一个文件名，用于保存刚才生成的 SSH key 代码，如：

> Generating public/private rsa key pair.
> Enter file in which to save the key (/c/Users/you/.ssh/id_rsa): [Press enter]

当然，你也可以不输入文件名，使用默认文件名（推荐），那么就会生成 id_rsa 和 id_rsa.pub 两个秘钥文件。
接着又会提示你输入两次密码（该密码是你push文件的时候要输入的密码，而不是github管理者的密码），
当然，你也可以不输入密码，直接按回车。那么push的时候就不需要输入密码，直接提交到github上了，如：

> Enter passphrase (empty for no passphrase): 
> Enter same passphrase again:

接下来，就会显示如下代码提示，如：

> Your identification has been saved in /c/Users/you/.ssh/id_rsa.
> Your public key has been saved in /c/Users/you/.ssh/id_rsa.pub.The key fingerprint is:01:0f:f4:3b:ca:85:d6:17:a1:7d:f0:68:9d:f0:a2:db your_email@example.com

当你看到上面这段代码的收，那就说明，你的 SSH key 已经创建成功，你只需要添加到github的SSH key上就可以了。

### 3. 添加你的ssh key到gitlab或github上面去

(1) 首先你需要拷贝 id_rsa.pub 文件的内容：在.ssh文件下执行命令
```
cat id_rsa.pub
```
即可显示公钥的内容，按`ctrl+insert`复制密钥内容

(2) 登录你的github账号，从又上角的设置（ Account Settings ）进入，然后点击菜单栏的 SSH key 进入页面添加 SSH key。

(3) 点击 Add SSH key 按钮添加一个 SSH key 。把你复制的 SSH key 代码粘贴到 key 所对应的输入框中，记得 SSH key 代码的前后不要留有空格或者回车。当然，上面的 Title 所对应的输入框你也可以输入一个该 SSH key 显示在 github 上的一个别名。默认的会使用你的邮件名称。

以上为ssh key配置简单步骤，参考git添加ssh key步骤。

### 4. 配置ssh

#### (1) 配置git全局配置信息

```bash
cd /home/sunq
vim .gitconfig
--------------------
[user]
name = sooncheer
email = handy-sun@foxmail.com
-------------------
```

可以在该文件中配置user信息，这样一来每个项目中不用再单独(找到项目所在目录下的 .git/文件夹)使用git config user.name 和git config user.email配置用户信息了

可以使用 git config --list 或 git config --edit 该项目中的git配置信息，将会看到我们配置的user信息。

#### (2) 修改ssh配置信息，config文件，在实际使用中gitlab对外的ssh连接端口不一定为22，若为其他端口号，则需要对其进行配置。

```bash
cd /home/sunq/.ssh
#该目录下有我们生产的id_rsa和id_rsa.pub
生成文件config
vim config

配置我们的config信息如下:
# gitee
Host  gitee.com
HostName gitee.com
Port 8177
User sooncheer
IdentityFile /home/sunq/.ssh/gee
IdentitiesOnly yes
```

配置文件参数:

* Host : Host可以看作是一个你要识别的模式，对识别的模式，进行配置对应的的主机名和ssh文件
* HostName : 要登录主机的主机名
* User : 登录名
* Port : ssh连接端口号
* IdentityFile : 指明上面User对应的identityFile路径
* IdentitiesOnly : 指定 ssh 只能使用配置文件指定的 identity 和 certificate 文件或通过 ssh 命令行通过身份验证
--------------------- 
原文：https://blog.csdn.net/FU250/article/details/81537463 

#### (3) 如果添加了SSH公钥仍然无法连接远端服务器，则在config中添加以下信息（可能会与2冲突）

```bash
# gitee
Host gitee.com
HostName gitee.com
PreferredAuthentications publickey
IdentityFile ~/.ssh/gitee_id_rsa
```
参考gitee文档：https://gitee.com/help/articles/4229#article-header1

## 五、GIT 忽略本地某一文件更改，不提交

比如有一个文件： config.ini 里面有一些本地开发环境参数，不需要提交
```
git update-index --assume-unchanged config.ini
```
就看不到config.ini 文件了

如果需要提交config.ini文件了，执行：
```
git update-index --no-assume-unchanged config.ini
```
就可以看到config.ini了，这时就可以提交了

