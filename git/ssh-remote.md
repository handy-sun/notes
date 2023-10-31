# git服务器托管网站进一步配置ssh(gitee)

如果一个仓库配置了多个远端，或git服务器托管网站有更为严格的ssh安全设置，则需要配置git服务器托管网站信息

修改ssh配置信息，config文件，在实际使用中gitlab对外的ssh连接端口不一定为22，若为其他端口号，则需要对其进行配置。

`vim ~/.ssh/config`

配置我们的config信息如下(第二行以及之后的内容可以不缩进，此处为了层次分明):

```shell
Host gitee
    HostName gitee.com
    IdentityFile ~/.ssh/id_rsa
    IdentitiesOnly yes
    UserKnownHostsFile ~/.ssh/known_hosts
```

配置文件参数说明

| 参数 | 含义 |
| --- | ----- |
| Host | Host可以看作是一个你要识别的模式，对识别的模式，进行配置对应的的主机名和ssh文件
| HostName | 要登录主机的主机名
| User | 登录名(可不填), 在连接git托管网站时会自动使用git用户
| Port | ssh连接端口号(可不填，默认为22)
| IdentityFile | 指明上面User对应的identityFile路径
| IdentitiesOnly | 指定 ssh 只能使用配置文件指定的 identity 和 certificate 文件或通过 ssh 命令行通过身份验证
| UserKnownHostsFile | 指定known_hosts文件，确保访问的git服务器正确无误
| ForwardAgent | 通常用于跳板式连接或者多级SSH连接的情况(可不设置)


测试是否可以建立ssh连接, 输入命令

```shell
ssh -T git@gitee.com
```

有 `successfully authenticated` 即表示可以建立，其他的内容不用关心

---

参考gitee文档：https://gitee.com/help/articles/4229#article-header1
