## 现象

在Ubuntu 23.04、Fedora、Manjaro 等最新的linux发行版中运行
`pip install` 命令时，通常会收到一个错误提示（以Manjaro的为例）：


```bash
$ pip3 install -r requirements.txt
error: externally-managed-environment

× This environment is externally managed
╰─> To install Python packages system-wide, try 'pacman -S
    python-xyz', where xyz is the package you are trying to
    install.
    
    If you wish to install a non-Arch-packaged Python package,
    create a virtual environment using 'python -m venv path/to/venv'.
    Then use path/to/venv/bin/python and path/to/venv/bin/pip.
    
    If you wish to install a non-Arch packaged Python application,
    it may be easiest to use 'pipx install xyz', which will manage a
    virtual environment for you. Make sure you have python-pipx
    installed via pacman.

note: If you believe this is a mistake, please contact your Python installation or OS distribution provider. \
You can override this, at the risk of breaking your Python installation or OS, by passing --break-system-packages.
hint: See PEP 668 for the detailed specification.
```

即“外部管理环境”错误，但这不是一个 bug。

## 原因

“外部管理环境”错误背后的原因：这些新的linux发行版中，正在使用 Python 包来实现此增强功能。

这个更新是为了避免「操作系统包管理器 (如pacman、yum、apt) 和 pip 等特定于 Python 的包管理工具之间的冲突」。

这些冲突包括 Python 级 API 不兼容和文件所有权冲突

## 方案一、 使用venv

> 适合从事Python项目的软件开发人员和程序员。

安装 `python3-venv` 包

```bash
sudo apt install python3-venv
# 或
sudo apt install python3.10-venv
```

配置一个python虚拟环境

```bash
cd your/project/dir
mkdir .env
python3 -m venv .env
ll .env
```

能看到有这几个目录

```bash
total 16
drwxr-xr-x 2 qi qi 4096 Feb  1 16:25 bin/
drwxr-xr-x 3 qi qi 4096 Feb  1 16:25 include/
drwxr-xr-x 3 qi qi 4096 Feb  1 16:25 lib/
lrwxrwxrwx 1 qi qi    3 Feb  1 16:25 lib64 -> lib/
-rw-r--r-- 1 qi qi  175 Feb  1 16:25 pyvenv.cfg
```

每个虚拟环境项目目录中都会有自己的 Python 和 Pip 副本
之后可以在虚拟环境中运行 `pip install` 命令

```bash
.env/bin/pip3 install -r requirements.txt
# 注意：之后执行python命令也要用venv中的python
.env/bin/python3 main.py
```

## 方案二、 使用pipx


它会自动为您安装的每个应用程序创建一个新的虚拟环境。不仅。它还在 中创建指向它的链接.local/bin。这样，安装该软件包的用户就可以从命令行中的任何位置运行它。

```bash
sudo apt install pipx
pipx ensurepath
# 必须关闭终端并重新登录才能发生更改。
# for example:
pipx install package_name
pipx uninstall package_name
```
