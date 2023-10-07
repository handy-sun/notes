# 1. 克隆完整的linux系统分区

也叫做硬盘对拷、系统迁移
全部命令都需要root权限
本文以 manjaro 发行版系统为例，其他发行版系统具体细节可能有差异

## 1.1 前提准备



如果是新的硬盘，可使用图形程序 `gparted` 先对新硬盘进行分区。boot和根分区大小都不要小于老硬盘的分区，`gparted` 的好处是简单并且可以给boot分区添加标记

若用命令行操作分区参考 `fdisk`, `mkfs.ext4` 等命令的手册和示例

用 `sudo smartctl --all /dev/sda` 命令看下新硬盘的SMART信息

下载一些工具包方便使用
```shell
pacman -S arch-install-scripts manjaro-tools-base
```

使用 `df -h` 查看当前系统的挂载情况

命令输出:

```shell
文件系统         大小  已用  可用  已用% 挂载点
/dev/sdc3       458G   51G  385G   12% /
/dev/sdc2       511M  368K  511M    1% /boot/efi
/dev/sdc1       466G  234G  232G   51% /run/media/wh/jvm
```

旧硬盘根目录所在的分区是/dev/sdc3，BOOT分区(引导分区)是/dev/sdc2


## 1.2 复制完整的linux系统（主要是根分区和boot分区）

新硬盘划分的是/dev/sdb2，并且准备将根分区拷贝到此扇区。

### 1.2.1 dd命令拷贝整个根分区
```shell
dd if=/dev/sdc3 of=/dev/sdb2
# 下方参数可显示过程
# dd if=/dev/sdc3 of=/dev/sdb2 status=progress
```

如果没有加 `status=progress`, 可以用另一条命令来让他输出中间过程：

```shell
# 每隔5s显示一次过程
watch -n 5 killall -USR1 dd
```

### 1.2.2 拷贝引导分区

上边已得出BOOT分区(引导分区)是/dev/sdc2

先挂载boot分区和新系统分区

```shell
mkdir -p /mnt/new
# 挂载新系统分区到此临时目录下
mount /dev/sdb2 /mnt/new
cp -aur /boot/* /mnt/new/boot  
```

更新硬盘信息

```shell
# 记得在操作之前先卸载挂载
umount /dev/sdb2
e2fsck -f /dev/sdb2
resize2fs /dev/sdb2
```

# 2. chroot和修复grub引导

## 2.1 挂载其他必要的目录

接下来，你需要挂载其他重要的目录，如`/proc`、`/dev`、`/sys`和可能的`/boot`分区。这可以通过以下命令完成

```shell
mount --bind /dev /mnt/new/dev
mount --bind /proc /mnt/new/proc
mount --bind /sys /mnt/new/sys
```

## 2.2 进入chroot环境

现在，你可以进入chroot环境，**manjaro系统推荐使用manjaro-chroot而不是chroot**
这样操作系统能够正确识别并配置引导

```shell
manjaro-chroot /mnt/new
```

在chroot环境中，你的文件系统会被视为根文件系统，因此你可以执行与操作系统安装和配置相关的命令。
下面是修复GRUB引导的一般步骤：

## 2.3 fstab更新新硬盘的uuid

grub引导根据硬盘的UUID来启动系统，必须保证/etc/fstab无误，否则无法进入系统

```shell
# 备份原来的fstab为/etc/fstab.bak当做参考
cp /etc/fstab{,.bak}
# 查看新硬盘的根分区和boot分区的UUID
blkid
# 只更改UUID，其他的不动
vim /etc/fstab
```

## 2.4 安装GRUB

ubuntu系统可以使用下边方式快速修复，而且不适用arch系
重新在新系统配置一遍grub更通用

```shell
sudo add-apt-repository ppa:yannubuntu/boot-repair
sudo apt install -y boot-repair
```

在chroot环境中，使用`grub2-install`命令来安装GRUB引导程序。此时，GRUB将安装到正确的位置。

```shell
grub2-install /dev/sdb
```

其中，`/dev/sdb`代表引导设备，**注意是你的硬盘，而不是分区**。

如果在执行`grub2-install`命令时出现"EFI variables are not supported on this system"的错误提示，这通常表示你的系统不支持EFI引导或者未正确配置。
使用以下命令查看当前系统的启动模式：

```shell
sudo efibootmgr -v
```

将显示当前系统的EFI引导配置。确保它指向正确的EFI引导加载程序。

## 2.5 生成GRUB配置文件

```shell
update-grub
# 等价于旧版grub的这条命令
# grub2-mkconfig -o /boot/grub2/grub.cfg
```

原理就是根据配置文件:/etc/default/grub 生成的 /boot/grub2/grub.cfg 启动脚本，
主要影响grub引导的界面配置、引导选项等，根据自己需要配置


```shell
# 完成上述步骤后，可以使用 exit 命令退出chroot环境
exit
# 最后，卸载之前挂载的目录和分区
umount /mnt/new/dev
umount /mnt/new/proc
umount /mnt/new/sys
umount /mnt/new/boot
umount /mnt/new/
```

至此，完成了修复GRUB引导的过程。

**记住，在执行`grub2-install`命令之前，必须进入chroot环境，以确保引导程序正确安装到根文件系统。**


