## 1.打印所有环境变量

使用以下 PowerShell 命令来打印所有环境变量的值：

```powershell
Get-ChildItem Env:
```

这个命令会列出所有环境变量及其对应的值。你可以在 PowerShell 中运行这个命令，它将输出环境变量的详细信息。如果你只想要列出特定环境变量的值，可以使用以下命令打印 PATH 环境变量：

```powershell
$env:PATH
```

## 2.刷新环境变量(目前无效，验证方式有问题?)

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

## 4 Powershell 运行脚本权限问题

Powershell 脚本运行的几种权限：

- Restricted: 默认设置，不允许任何脚本运行

- AllSigned: 只能运行经过数字证书签名的脚本

- RemoteSigned: 运行本地脚本不需要数字签名，但是运行从网络上下载的脚本必须要有数字签名

- Unrestricted: 允许所有的脚本运行, 但是在运行前会提示是否进行操作

- Bypass: 允许所有的脚本运行, 没有任何的提示和警告。

然后是第二个问题，修改 Powershell 权限设置。

查看当前 PowerShell 的环境配置：

```powershell
Get-ExecutionPolicy
```

改变当前的 PowerShell 环境的权限设置（注意，此命令需要在管理员权限的 powershell 下运行）

```powershell
Set-ExecutionPolicy unrestricted
```

## 5 Powershell 运行脚本用户权限问题

要在 PowerShell 中以普通权限启动脚本或命令，你可以使用以下方法：

1. **使用 `Start-Process` 命令**：你可以使用 `Start-Process` 命令来启动 PowerShell 会话，并指定以普通权限运行。例如：

```powershell
Start-Process powershell.exe -NoProfile -ExecutionPolicy Bypass -NoExit -Verb RunAs
```

   这将以普通权限启动一个新的 PowerShell 会话。

2. **在 PowerShell 中执行命令**：如果你已经在 PowerShell 中，但需要以普通权限执行某个命令，你可以使用 `Start-Process` 命令，如下所示：

```powershell
Start-Process -FilePath "cmd.exe" -ArgumentList "/c YourCommandHere" -Verb RunAs
```

这将以普通权限启动一个新的 CMD 窗口，并在其中运行指定的命令。

请注意，以普通权限启动 PowerShell 或命令将要求你提供管理员凭据（如果系统设置为需要）。