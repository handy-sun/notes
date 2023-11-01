
# User Standard Config File Directory

用户软件标准配置文件目录取决于不同的操作系统和软件。

## 1. Windows

```powershell
C:\Users\<用户名>\AppData\Roaming     # 环境变量APPDATA的值
C:\Users\<用户名>\Documents
C:\Users\<用户名>\Application Data
```

## 2. Linux

```shell
${HOME}/.config
${HOME}/.local/share
```

## 3. MacOS

```shell
/Users/${USER}/Library/Application Support
/Users/${USER}/Library/Preferences
```