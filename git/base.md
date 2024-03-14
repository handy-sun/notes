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

### 0. 附言：密钥类型

目前大部分ssh的server端支持使用 RSA，DSA，ECDSA 和 ED25519 密钥.

- Openssl从2023年中已经不再建议使用 RSA
- GitLab 在 GitLab 11.0 中已弃用 DSA 密钥.
- 如 [Go 实用密码术](https://leanpub.com/gocrypto/read#leanpub-auto-ecdsa) 中所述，与 DSA 相关的安全性问题也适用于 ECDSA.

>提示：现有文档表明 ED25519 更安全. 如果使用 RSA 密钥，则美国国家科学技术研究院出版物 800-57 第 3 部分（PDF）建议密钥大小至少为 2048 位.

### 1. 检视ssh目录：

```shell
test -d ~/.ssh && ls -lh ~/.ssh || mkdir -p ~/.ssh
```

可以看到目录下是否存在id_rsa.pub 或 id_dsa.pub 文件，存在说明已经生成过sshkey。但无论是否存在，可以选择使用以前的sshkey或创建sshkey覆盖之前生成的key。

### 2. 创建一个ssh key

```shell
ssh-keygen -t ed25519 -C "<comment>"
```

代码参数含义：
-t 指定密钥类型，默认是 rsa ，可以省略。
-C 设置注释文字，比如邮箱，可以省略。
-f 指定密钥文件存储文件名，省略了生成过程中也可以输入。

运行上面那条命令后会让你输入一个文件名，用于保存刚才生成的 SSH key 代码，如：

> Generating public/private ed25519 key pair.
> Enter file in which to save the key (/home/you/.ssh/id_ed25519): [Press enter]

当然，可以不输入文件名，使用默认文件名，SSH 密钥存储在用户的主目录中的 `.ssh` 子目录中. 下表包括每种 SSH 密钥算法的默认文件名：

Algorithm | 公钥 | 私钥
-- | -- | --
ED25519（首选） | id_ed25519.pub | id_ed25519
RSA（至少2048位密钥大小） | id_rsa.pub | id_rsa
DSA（已弃用） | id_dsa.pub | id_dsa
ECDSA | id_ecdsa.pub | id_ecdsa

接着又会提示输入两次密码（该密码是你push的时候要输入的密码，而不是github管理者的密码），
同样，也可以不输入密码，直接按回车。那么push的时候就不需要输入密码，直接提交到git服务器上了，如：

> Enter passphrase (empty for no passphrase): 
> Enter same passphrase again:

接下来，就会显示如下代码提示，如：

> Your identification has been saved in /home/you/.ssh/id_ed25519.
> Your public key has been saved in /home/you/.ssh/id_ed25519.pub.The key fingerprint is:01:02:03:04:05:06:07:08:aa:aa:aa:aa:aa:aa:aa:aa your_email@example.com

当你看到上面这段代码，那就说明，你的 SSH key 已经创建成功，将 SSH key 提交给相应的git服务器就可以用ssh地址进行pull,push了
你只需要添加到github的SSH key上就可以了。

#### 附1：RSA SSH keys

您可以使用以下命令创建和配置 RSA 密钥，如果需要，可以使用建议的最小密钥大小`2048`代替：
```shell
ssh-keygen -t rsa -b 2048 -C "email@example.com"
```

#### 附2：RSA keys and OpenSSH from versions 6.5 to 7.8
在 OpenSSH 7.8 之前，RSA 密钥的默认公共密钥指纹基于 MD5，因此不安全.

查看版本
```shell
ssh -V
```

如果 OpenSSH 版本介于 6.5 至 7.8（含）之间，请使用`-o`选项运行ssh-keygen，以更安全的 OpenSSH 格式保存私人 SSH 密钥.

如果已经具有可用于 GitLab 的 RSA SSH 密钥对，请考虑对其进行升级以使用更安全的密码加密格式. 可以使用以下命令进行操作：

```shell
ssh-keygen -o -t rsa -b 4096 -C "email@example.com"
```

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

