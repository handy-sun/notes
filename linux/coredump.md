# **coredump配置**

## 1. 设定ulimit -c

a）使用`ulimit -c`命令可查看core文件的生成开关。若结果为`0`，则表示关闭了此功能，不会生成core文件。
b）使用`ulimit -c filesize`命令，可以限制core文件的大小（filesize的单位为kbyte）。若`ulimit -c unlimited`，则表示core文件的大小不受限制。如果生成的信息超过此大小，将会被裁剪，最终生成一个不完整的core文件。在调试此core文件的时候，gdb会提示错误。

## 2. 设定Coredump文件的保存位置与格式

coredump文件`默认存储位置与可执行文件在同一目录下`，文件名为core。

可以通过/proc/sys/kernel/core_pattern进行设置。

%e: 出Core进程对应的可执行文件名

%p: 出Core进程的PID%u 出Core进程的UID

%g: real gid of the process

%h: host name

%s: 造成Core的signal号

%t: 出Core的时间，从1970-01-01 00:00:00开始的秒数


通过以下方式设定格式（root用户）

```bash
echo "core_%e_%p_%s_%t" > /proc/sys/kernel/core_pattern
# 或
sysctl -w kernel.core_pattern=core_%e_%p_%s_%t
```

更改保存位置及永久生效（经测试暂无法永久生效）
```bash
# 可以将core文件统一生成到/var/crash目录下
sysctl -w "kernel.core_pattern=/var/crash/core_%e_%p_%s_%t" >> /etc/sysctl.conf
sysctl -w "kernel.core_uses_pid=1" >> /etc/sysctl.conf
# (查看生效参数，验证设置是否生效)
sysctl -p 
# 快速验证是否能生成core文件
kill -s SIGSEGV $$
```

## 3. 生成成功使用以下方式分析
gdb 崩溃程序名 core文件位置

`注`：由于没有开启程序的调试信息，错误消息只能大概定位到函数级别，如果需要获取更精确错误信息，可在编译程序时加“-g”或“-ggdb3”，其中“-ggdb3”表示产生更多适合GDB的调试信息，3是最高等级。

coredumpctl list 'app-name'

查看某个程序生成的core文件