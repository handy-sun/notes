## 1.打印所有环境变量

使用以下 PowerShell 命令来打印所有环境变量的值：

```powershell
Get-ChildItem Env:
```

这个命令会列出所有环境变量及其对应的值。可以在 PowerShell 中运行这个命令，它将输出环境变量的详细信息。
若只想列出特定环境变量的值，可以使用以下命令打印 PATH 环境变量：

```powershell
$env:PATH
# 搭配字符串替换使每行显示一个环境变量 (ps中 `n 表示换行符)
$env:PATH -replace ";", "`n"
```

## 2.刷新环境变量(目前无效，验证方式有问题?)

要在PowerShell中刷新环境变量`PATH`的值，可以使用以下命令：

```powershell
[Environment]::SetEnvironmentVariable("PATH", [System.Environment]::GetEnvironmentVariable("PATH", [System.EnvironmentVariableTarget]::Machine), [System.EnvironmentVariableTarget]::Process)
```

这个命令会将当前进程的`PATH`环境变量重置为系统级别的`PATH`值，实现刷新效果。请确保以管理员权限运行PowerShell，以便修改系统级别的`PATH`变量。

如果只想刷新当前会话中的`PATH`，而不是永久更改系统级别的`PATH`，可以使用以下命令：

```powershell
$env:PATH = [System.Environment]::GetEnvironmentVariable("PATH", [System.EnvironmentVariableTarget]::Machine)
```

这将仅在当前PowerShell会话中刷新`PATH`变量。请注意，一旦关闭PowerShell窗口，更改将失

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

要在 PowerShell 中以普通权限启动脚本或命令，可以使用以下方法：

1. **使用 `Start-Process` 命令**：可以使用 `Start-Process` 命令来启动 PowerShell 会话，并指定以普通权限运行。例如：

    ```powershell
    Start-Process powershell.exe -NoProfile -ExecutionPolicy Bypass -NoExit -Verb RunAs
    ```

   这将以普通权限启动一个新的 PowerShell 会话。

2. **在 PowerShell 中执行命令**：如果已经在 PowerShell 中，但需要以普通权限执行某个命令，可以使用 `Start-Process` 命令，如下所示：

    ```powershell
    Start-Process -FilePath "cmd.exe" -ArgumentList "/c YourCommandHere" -Verb RunAs
    ```

    这将以普通权限启动一个新的 CMD 窗口，并在其中运行指定的命令。

## 6 字符串替换

PowerShell 提供了多种用于字符串替换的函数和方法

1. **Replace 方法：** `Replace` 方法用于替换字符串中的指定子字符串。

   ```powershell
   $originalString = "Hello, world!"
   $newString = $originalString.Replace("world", "PowerShell")
   Write-Host $newString
   ```

   输出:

   ```
   Hello, PowerShell!
   ```

2. **-replace 操作符：** PowerShell 支持 `-replace` 操作符，它允许使用正则表达式进行替换。

   ```powershell
   $originalString = "The quick brown fox jumps over the lazy dog."
   $newString = $originalString -replace "fox", "cat"
   Write-Host $newString
   ```

   输出:

   ```
   The quick brown cat jumps over the lazy dog.
   ```

3. **[Regex]::Replace 方法：** 使用 `System.Text.RegularExpressions.Regex` 类的 `Replace` 方法进行更高级的正则表达式替换。

   ```powershell
   $originalString = "The date is 2023-10-24."
   $pattern = "\d{4}-\d{2}-\d{2}"
   $newString = [System.Text.RegularExpressions.Regex]::Replace($originalString, $pattern, "today")
   Write-Host $newString
   ```

   输出:

   ```
   The date is today.
   ```

4. **-creplace 操作符：** `-creplace` 操作符执行大小写不敏感的正则表达式替换。

   ```powershell
   $originalString = "PowerShell is powerful."
   $newString = $originalString -creplace "powershell", "Python"
   Write-Host $newString
   ```

   输出:

   ```
   Python is powerful.
   ```

## 7 获取Ip

在PowerShell中，你可以使用`Get-NetIPAddress`命令来获取本机的IPv4地址。

以下是一个示例命令：

```powershell
Get-NetIPAddress -AddressFamily IPv4 | Select-Object IPAddress
```

上述命令将返回本机所有的IPv4地址。如果你只想获取`主要的`IPv4地址，可以使用`-AddressFamily IPv4 -PrefixOrigin Manual`参数来过滤出手动配置的IPv4地址。

```powershell
Get-NetIPAddress -AddressFamily IPv4 -PrefixOrigin Manual | Select-Object IPAddress
```

执行上述命令后，将会返回本机手动配置的IPv4地址。

希望这个解释对你有帮助！如果你有其他问题，请随时提问。