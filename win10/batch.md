## 1. tasklist

tasklist命令是Windows操作系统中的一个命令行工具，用于列出当前正在运行的进程信息。它可以显示进程的名称、进程ID、内存使用情况、CPU占用率等信息

如果需要查看某个特定进程的详细信息，可以在命令后面加上进程ID，如

```batch
tasklist /fi "pid eq 1234"
```

要查看名为 `nginx.exe` 的进程

```batch
tasklist /fi "imagename eq nginx.exe"
```

如果需要将进程列表输出到文件中，可以使用

```batch
tasklist /fo csv > process.csv
```

将进程列表输出到名为process.csv的文件中



要查看运行时间超过5秒的进程，可以使用以下命令

```batch
tasklist /fi "CPUTIME gt 00:00:05"
```

## 2. taskkill


taskkill是Windows系统中的一个命令行工具，用于终止指定的进程。它的语法如下：

```batch
taskkill [/s Computer] [/u Domain\User [/p Password]] [/fi FilterName FilterValue] [/pid ProcessID] [/im ImageName] [/f] [/t]
```

- /s：指定要终止进程的计算机名或IP地址。
- /u：指定要使用的用户帐户。
- /p：指定要使用的用户帐户的密码。
- /fi：指定筛选器名称和筛选器值，以选择要终止的进程。
- /pid：指定要终止的进程的进程ID。
- /im：指定要终止的进程的映像名称。
- /f：强制终止进程。
- /t：终止指定进程及其子进程。


例如，要终止名为nginx.exe的进程，可以使用以下命令：

```batch
taskkill /im nginx.exe /f
```

