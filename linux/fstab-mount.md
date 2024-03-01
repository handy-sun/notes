
# fstab 各列含义

\<file system>	\<dir>	\<type>	\<options>	\<dump>	\<pass>


## type


FAT32或FAT16或FAT：填写vfat

NTFS类型可以挂载为ntfs-3g, 其是一个开源的用户空间驱动程序，它允许 Linux 系统通过 FUSE（Filesystem in Userspace）机制来访问和操作 NTFS 文件系统。它提供了对 NTFS 文件系统的完全读写支持，包括文件和目录的创建、修改、删除等操作。


更新：
ntfs-3g 读写效率较低，新内核的已经集成了ntfs3驱动，更高效

## option

挂载时使用的参数，注意有些mount 参数是特定文件系统才有的。一些比较常用的参数有：

- auto - 在启动时或键入了 mount -a 命令时自动挂载。noauto - 只在你的命令下被挂载。
- exec - 允许执行此分区的二进制文件。
- noexec - 不允许执行此文件系统上的二进制文件。
- ro - 以只读模式挂载文件系统。
- rw - 以读写模式挂载文件系统。
- user - 允许任意用户挂载此文件系统，若无显示定义，隐含启用 noexec, nosuid, nodev 参数。
- users - 允许所有 users 组中的用户挂载文件系统.
- nouser - 只能被 root 挂载。
- owner - 允许设备所有者挂载.sync - I/O 同步进行。
- sync - 强制同步写入，即每次写入操作都会立即写入磁盘。
- async - I/O 异步进行。
- dev - 解析文件系统上的块特殊设备。
- nodev - 不解析文件系统上的块特殊设备。
- suid - 允许 suid 操作和设定 sgid 位。这一参数通常用于一些特殊任务，使一般用户运行程序时临时提升权限。
- 
- noauto - 不自动挂载文件系统，需要手动执行挂载命令。
- nosuid - 禁止 suid 操作和设定 sgid 位。
- noatime - 不更新文件系统上 inode 访问记录，可以提升性能(参见 atime 参数)。
- nodiratime - 不更新文件系统上的目录 inode 访问记录，可以提升性能(参见 atime 参数)。
- relatime - 实时更新 inode access 记录。只有在记录中的访问时间早于当前访问才会被更新。（与 noatime 相似，但不会打断如 mutt 或其它程序探测文件在上次访问后是否被修改的进程。），可以提升性能(参见 atime 参数)。
- flush - vfat 的选项，更频繁的刷新数据，复制对话框或进度条在全部数据都写入后才消失。
- defaults - 使用文件系统的默认挂载参数，例如 ext4 的默认参数为:rw, suid, dev, exec, auto, nouser, async.

- auto和 noauto： 这是控制设备是否自动挂载的选项。auto是默认选择的选项，这样，设备会在启动或者你使用mount -a命令时按照fstab的内容自动挂载。如果你不希望这样，就使用noauto选项，如果这样的话，你就只能明确地通过手工来挂载设备。


## dump

通常是第1个数字，表示 dump备份的设置

dump 是一个用来做备份的命令， 可以通过 fstab 指定哪个文件系统必须要进行 dump 备份。

- 0 代表不做 dump 备份
- 1 代表要每天进行 dump 
- 2 代表其他不定日期的 dump 备份动作

通常这个数值不是 0 就是 1。

## pass

通常是第2个数字，表示 fsck 检验扇区的设置

启动的过程中，系统默认会以 fsck 检验我们的 filesystem 是否完整 (clean)。 不过，某些 filesystem 是不需要检验的，例如内存置换空间 (swap) ，或者是特殊文件系统例如 /proc 与 /sys 等等。
所以，可以配置是否要以 fsck 检验该 filesystem 。

- 0 是不要检验
- 1 表示最早检验(一般只有根目录会配置为 1)
- 2 也是要检验。 一般来说，根目录配置为 1 ，其他的要检验的 filesystem 都配置为 2


# mount 其他文件系统


## ntfs

```bash
# 挂载 ntfs, 文件夹权限 750, 文件权限  640
mount -t ntfs3 -o defaults,uid=1000,gid=1000,umask=007,fmask=117,noatime,prealloc /dev/sdb1 /mnt/ntfs
```

*如果开机自动挂载的 ntfs 硬盘出现问题导致系统进入 emergency mode 的话，登录root用户注释掉 `/etc/fstab` 中有问题的行，之后再接着执行下方的流程*

```bash
# 退出救援模式(emergency mode)
exit
# 使用下边命令修复ntfs
ntfsfix -d /dev/sdb1
# 取消 /etc/fstab 有问题行的注释 ...
systemctl daemon-reload
# 测试 fstab 是否能正确挂载
mount -a
```

## cifs

```bash
# arch系安装cifs相关的包
pacman -Ss cifs-utils
# 挂载 windows共享文件夹到linux目录下，这里以一个中间含有空格的用户名为例，没有空格等特殊符号无需单引号，后续发现windows的用户名可以省略中间的空格
# 先不要加 iocharset, codepage 等参数，可能导致挂载失败
sudo mount -t cifs -o user='q s',password=123,uid=1000,gid=1000,dir_mode=0777,file_mode=0666,forceuid,forcegid //10.144.1.12/shared /mnt/v0d8lfn
# 可查看挂载日志中详细的参数项
mount -l | grep cifs
```

### problem1: 无法浏览文件

如果挂载成功，但是不能浏览目录下的文件（如`ls`命令），提示
`reading directory '.': Permission denied`
在windows共享目录的属性中打开 `网络和共享中心` ，选择 `启用共享以便……公用文件夹中的文件`

### problem2: 无法向文件夹拷贝（vers=2.1）

`cannot create regular file ... Permission denied`

添加参数。forceuid 和 forcegid

解决此问题的另一种方法（如果您可以接受安全风险）是使用 CIFS 的 noperm 选项，以允许所有用户读取和写入 CIFS 挂载。

```
sudo mount -t cifs -o noperm //server-address/folder /mount/path/on/client
```
