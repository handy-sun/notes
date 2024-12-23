## 软件安装

```sh
pacman -S package 下载并安装package
pacmam -U package.pkg.tar.gz 从安装本地package包
pacman -Syu 更新包列表并且升级所有包(已下载)
pacman -Syu package 更新包列表并且升级所有包(已下载) 如果package包没有下载那么下载并安装package
pacman -Su package 升级所有包(已下载) 如果package包没有下载那么下载并安装package
pacman -Su --ignore package 忽略package包的更新 更新整个系统
pacman -Sy package 刷新本地数据库 如果package没有安装 则下载并安装(保证下载到的软件是最新的)(常用！！！)
```

## 软件查询

```sh
pacman -Ss package 从服务器数据库寻找package包(package关键字即可)(常用！！！)
pacman -Q package 查看本地是否安装了package包(package为完整包名)
pacman -Qi package 列出package包的详情信息(名字 描述 官网 以来 架构等)
pacman -Si package 从数据库中查询package包的详细信息
pacman -Ql package 列出package包的文件(列出的是文件路径)
pacman -Qe >> list.txt # 导出系统中所有手动指定安装的包
pacman -Qo xxd # 查询某个程序属于哪个包

```

## 删除软件

```sh
pacman -R package 只删除package包 不删除依赖
pacman -Rs package 删除package包及其依赖的包
pacman -Rc package 删除package包及依赖package的包(谨慎使用)
pacman -Rsc package 删除package包 package的依赖 依赖package的包(谨慎使用)
pacman -Ru 删除不被任何包依赖的包(非常安全)
pacman -Rn 删除备份的配置文件(.pacsave扩展名)
pacman -Rsn package 删除package包和依赖以及其备份的配置文件(常用！！！)
pacman -Sc 移除缓存不再安装的软件包
pacman -Scc 移除缓存中所有的文件
```
