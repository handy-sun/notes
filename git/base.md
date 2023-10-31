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

### 1. 使用合并（merge）策略

- 查看本地分支文件信息，非必要，但建议确认下没有未提交的更改，否则不允许pull
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
    git commit -m "Merge branch ..."
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

## 四、创建ssh公钥

### 1. 在.ssh文件下运行 git Bash，或者输入如下代码跳转到此目录：

```shell
cd ~/.ssh
```

可以看到目录下是否存在id_rsa.pub 或 id_dsa.pub 文件，存在说明已经生成过sshkey。但无论是否存在，可以选择使用以前的sshkey或创建sshkey覆盖之前生成的key。

### 2. 创建一个ssh key

```shell
ssh-keygen -t rsa
```

代码参数含义：
-t 指定密钥类型，默认是 rsa ，可以省略。
-C 设置注释文字，比如邮箱，可以省略。
-f 指定密钥文件存储文件名，省略了生成过程中也可以输入。

参数全省略即为：

```shell
ssh-keygen
```

以上代码省略了 -f 参数，因此，运行上面那条命令后会让你输入一个文件名，用于保存刚才生成的 SSH key 代码，如：

> Generating public/private rsa key pair.
> Enter file in which to save the key (/c/Users/you/.ssh/id_rsa): [Press enter]

当然，可以不输入文件名，使用默认文件名，那么在当前路径下就会生成 id_rsa 和 id_rsa.pub 两个秘钥文件。
接着又会提示输入两次密码（该密码是你push的时候要输入的密码，而不是github管理者的密码），
同样，也可以不输入密码，直接按回车。那么push的时候就不需要输入密码，直接提交到git服务器上了，如：

> Enter passphrase (empty for no passphrase): 
> Enter same passphrase again:

接下来，就会显示如下代码提示，如：

> Your identification has been saved in /c/Users/you/.ssh/id_rsa.
> Your public key has been saved in /c/Users/you/.ssh/id_rsa.pub.The key fingerprint is:01:0f:f4:3b:ca:85:d6:17:a1:7d:f0:68:9d:f0:a2:db your_email@example.com

当你看到上面这段代码，那就说明，你的 SSH key 已经创建成功，将 SSH key 提交给相应的git服务器就可以用ssh地址进行pull,push了
你只需要添加到github的SSH key上就可以了。

### 3. 添加你的ssh key到gitlab或github上面去

(1) 首先需要拷贝 id_rsa.pub 文件的内容：在.ssh文件下执行命令

```shell
cat id_rsa.pub
```
即可显示公钥的内容，按`ctrl+insert`复制密钥内容

(2) 登录你的github账号，从右上角的设置（ Account Settings ）进入自己的个人设置界面，然后点击菜单栏的 SSH key 进入页面添加 SSH key。

(3) 点击 Add SSH key 按钮添加一个 SSH key 。把你复制的 SSH key 代码粘贴到 key 所对应的输入框中，记得 SSH key 代码的前后不要留有空格或者回车。当然，上面的 Title 所对应的输入框你也可以输入一个该 SSH key 显示在 github 上的一个别名。默认的会使用你的邮件名称或用户名@主机名。

以上为ssh key配置简单步骤，如果仍然不能使用，参考
`ssh-remote.md`

