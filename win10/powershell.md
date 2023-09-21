## 1.打印所有环境变量

使用以下 PowerShell 命令来打印所有环境变量的值：

```powershell
Get-ChildItem Env:
```

这个命令会列出所有环境变量及其对应的值。你可以在 PowerShell 中运行这个命令，它将输出环境变量的详细信息。如果你只想要列出特定环境变量的值，可以使用以下命令打印 PATH 环境变量：

```powershell
$env:PATH
```

## 2.刷新环境变量(目前不好用)

要在PowerShell中刷新环境变量`PATH`的值，您可以使用以下命令：

```powershell
[Environment]::SetEnvironmentVariable("PATH", [System.Environment]::GetEnvironmentVariable("PATH", [System.EnvironmentVariableTarget]::Machine), [System.EnvironmentVariableTarget]::Process)
```

这个命令会将当前进程的`PATH`环境变量重置为系统级别的`PATH`值，实现刷新效果。请确保以管理员权限运行PowerShell，以便修改系统级别的`PATH`变量。

如果您只想刷新当前会话中的`PATH`，而不是永久更改系统级别的`PATH`，可以使用以下命令：

```powershell
$env:PATH = [System.Environment]::GetEnvironmentVariable("PATH", [System.EnvironmentVariableTarget]::Machine)
```

这将仅在当前PowerShell会话中刷新`PATH`变量。请注意，一旦您关闭PowerShell窗口，更改将失

## 3.删除文件(夹)

在PowerShell中执行`rm`命令用于删除文件或文件夹。`rm`是`Remove-Item`的简写。以下是一些示例：

### 3.1. 删除文件：

```powershell
Remove-Item -Path C:\path\to\file.txt
```

### 3.2. 删除文件夹及其内容（递归删除）：

```powershell
Remove-Item -Path C:\path\to\folder -Recurse
```

注意，在执行删除操作时要格外小心，删除的内容不会进入回收站。
