# git 网站上一些基本配置操作

## 一、本地创建并上传到服务器

1. 本机window系统的话先下载git windows版，安装后在开始菜单里面找到  
`Git --> Git Bash` 进入命令

2. 找到要上传的目录，通过命令 git init 把这个目录变成git可以管理的仓库
```shell
git init
```

3. 把文件添加到版本库中，使用命令 git add .添加到暂存区里面去，不要忘记后面的小数点“.”，意为添加文件夹下的所有文件

```shell
git add （文件名如果后面是.责添加当前目录下所有文件）
```

4. 用命令 git commit告诉Git，把文件提交到仓库。引号内为提交说明
```shell
git commit -m '提交的内容介绍'
```

5. 关联到远程库
```shell
git remote add origin  https://github.com/XXXX/xxxx.git
```

6. 获取远程库与本地同步合并（如果远程库里有文件，必须先执行此命令，否则后续会提交会失败）
```shell
git pull --rebase origin master
```

7. 把本地库的内容推送到远程，使用 git push命令，实际上是把当前分支master推送到远程。执行此命令后会要求输入用户名 密码，验证通过后即开始上传。
```shell
git push -u origin master
```

## 二、Clone 到本地

1. 选择目标路径的上一级文件夹，右键 git bash.
    
2. 此步骤可省略，但不加此步有时可能连接不上服务器。

```shell
# origin 为远程服务器名，一般为origin;master 为分支名
git remote add origin/master 项目地址
```

3. 最后执行clone
```shell
git clone 项目地址
```

## 三、与远端同步

本地已经提交一个未推送到远端的commit

### 3.1 使用合并（merge）策略


- 查看本地分支文件信息，确保没有未提交的更改
```shell
git status
```

- 拉取origin远端的master分支： `git pull origin master`
都是默认的直接执行下边命令：
```shell
git pull
```

- (1) 如果 Git 能够自动合并，那么会弹出一个包含commit信息的提交页面，如果使用vim作为git编辑器，`:wq` 保存后此merge commit生成。
- (2) Git 不能够自动合并，那么会有`CONFLICT`提示, 需要手动解决冲突,所有的冲突都得以解决，然后就可以使用

    ```shell
    git add .
    git commit -m "fixed conflicts"
    ```

- 此时可以推送到远端了

```shell
git push
```


### 2. 使用变基（rebase）策略


```shell
git status
# 不同的就是这一步
git pull --rebase
# 如果有冲突同merge策略的操作
git push
```

## 四、创建 ssh

### 1. 在.ssh文件下运行 git Bash，或者输入如下代码跳转到此目录：

```shell
cd ~/.ssh
```

可以看到目录下是否存在id_rsa.pub 或 id_dsa.pub 文件，存在说明已经生成过sshkey。但无论是否存在，可以选择使用以前的sshkey或创建sshkey覆盖之前生成的key。

### 2. 创建一个ssh key

```shell
ssh-keygen -t rsa -C "your_email@example.com"
```

代码参数含义：
-t  指定密钥类型，默认是 rsa ，可以省略。
-C 设置注释文字，比如邮箱，可以省略。
-f  指定密钥文件存储文件名。

 参数全省略即为：

```shell
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

```shell
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

