# **coredump配置**

## 1. 设定ulimit -c

a）使用`ulimit -c`命令可查看core文件的生成开关。若结果为`0`，则表示关闭了此功能，不会生成core文件。
b）使用`ulimit -c filesize`命令，可以限制core文件的大小（filesize的单位为kbyte）。若`ulimit -c unlimited`，则表示core文件的大小不受限制。如果生成的信息超过此大小，将会被裁剪，最终生成一个不完整的core文件。在调试此core文件的时候，gdb会提示错误。

可以在 `/etc/security/limits.conf` 文件中设置 core dump 文件大小限制。以下是一个示例：
```conf
#<domain>      <type>  <item>         <value>
*               soft    core           1000000
```
此行将限制所有用户生成的 core dump 文件的大小为 1 MB。您可以根据需要调整此值。
要使此更改生效，您需要重新启动系统或注销并重新登录。

## 2. 设定Coredump文件的保存位置与格式

coredump文件`默认存储位置与可执行文件在同一目录下`，文件名为core。

可以通过/proc/sys/kernel/core_pattern进行设置。

**%e**: 出Core进程对应的可执行文件名
**%p**: 出Core进程的PID%u 出Core进程的UID
**%g**: real gid of the process
**%h**: host name
**%s**: 造成Core的signal号
**%t**: 出Core的时间，从1970-01-01 00:00:00开始的秒数


通过以下方式设定格式（root用户）

```bash
echo "core_%e_%p_%s_%t" > /proc/sys/kernel/core_pattern
# 或
sysctl -w kernel.core_pattern=core_%e_%p_%s_%t
```

更改保存位置及永久生效（部分新的linux系统可以生效）
```bash
# 可以将core文件统一生成到/var/crash目录下
sysctl -w "kernel.core_pattern=/var/crash/core_%e_%p_%s_%t" >> /etc/sysctl.conf
sysctl -w "kernel.core_uses_pid=1" >> /etc/sysctl.conf
# 查看生效参数；一定要验证设置，因为可能和你设置的不完全一致
sysctl -p 
# 快速验证是否能生成core文件（如果此时在某种shell环境会退出到其外部环境）
kill -s SIGSEGV $$
```

## 3. gdb分析coredump文件

使用以下命令分析
```shell
gdb 崩溃程序 core文件
# 以下gdb指令常用分析崩溃原因，根据具体场景选用
# 进入gdb, bt(backtrace) 查看程序崩溃时的堆栈信息，
(gdb) bt
# 查看程序崩溃时的变量值：
(gdb) p <var>
# x/nfu 查看内存内容: n 是要显示的内存单元数，f 是显示格式，u 是单位大小
# 以下命令将显示从地址 0x0 开始的前 16 个字节
(gdb) x/16xb 0x<address>
# 查看程序崩溃时的寄存器状态：
(gdb) info registers
# 查看程序崩溃时的汇编代码：
(gdb) disassemble
```

注：由于没有开启程序的调试信息，错误消息只能大概定位到函数级别，如果需要获取更精确错误信息，可在编译程序时加 `-g` 或 `-ggdb3`，其中 `-ggdb3` 表示产生更多适合GDB的调试信息，`3`是最高等级。

## 4. coredumpctl

coredumpctl list 是一个用于列出系统上可用核心转储文件（core dumps）的命令。核心转储文件通常包含了程序崩溃时的内存快照，这对于调试问题非常有用。

这个命令通常在Linux系统中使用，前提是你的系统已经启用了核心转储（core dumping）功能。coredumpctl 是 Systemd 套件的一部分，用于管理系统上的核心转储文件。通过运行 coredumpctl list，你可以查看系统上的核心转储文件列表，以确定哪些程序崩溃并生成了核心转储文件。

*注意，要使用 coredumpctl，通常需要具有管理员或超级用户权限，因为它需要访问系统级的核心转储文件*
```shell
# 查看某个程序生成的core文件
coredumpctl list <executable>
# 将coredump主要信息打印到标准输出
coredumpctl dump <PID>
```

注意 `/var/lib/systemd/coredump/` 下也可能会放置一些 core 文件(可能是压缩后的文件)

## 5. readelf 工具

readelf 是一个用于查看可执行文件和共享库文件的 ELF 格式文件头的工具。它可以用于分析程序崩溃时的内存布局，找出问题所在。

使用 readelf 分析可执行程序文件与coredump结合：
```shell
# 查看可执行程序文件中的程序段：
readelf -S <executable>
# 查看可执行程序文件中的程序符号表：
readelf -s <executable>
# 查看可执行程序文件中的程序动态链接信息：
readelf -d <executable>
```
