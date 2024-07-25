
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

## XDG

**XDG Base Directory规范**，定义了几种重要的环境变量路径。这些环境变量将可能被多个程序所共享，不同的应用程序会在该目录下创建各自的子目录来存储配置文件。

- 用于写入特定用户数据文件的基本目录: XDG_DATA_HOME.
- 用于写入特定用户的配置文件基本目录: XDG_CONFIG_HOME.
- 首选的基本数据目录: XDG_DATA_DIRS.
- 首选的基本配置目录: XDG_CONFIG_DIRS.
- 用于写入用户特定的非必要（缓存）数据的基本目录: XDG_CACHE_HOME.
- 用户放置特定于用户的运行时文件和其他文件对象: XDG_RUNTIME_DIR.

不同系统下的默认值以及NVIM中的变量值

XDG环境变量 | 默认值
-- | --
$XDG_DATA_HOME | $HOME/.local/share
$XDG_CONFIG_HOME | $HOME/.config
$XDG_DATA_DIRS | /usr/local/share/:/usr/share/
$XDG_CONFIG_DIRS | /etc/xdg
$XDG_CACHE_HOME | $HOME/.cache

```js
CONFIG DIRECTORY (DEFAULT)
                  $XDG_CONFIG_HOME            Nvim: stdpath("config")
    Unix:         ~/.config                   ~/.config/nvim
    Windows:      ~/AppData/Local             ~/AppData/Local/nvim


DATA DIRECTORY (DEFAULT)
                  $XDG_DATA_HOME              Nvim: stdpath("data")
    Unix:         ~/.local/share              ~/.local/share/nvim
    Windows:      ~/AppData/Local             ~/AppData/Local/nvim-data


RUN DIRECTORY (DEFAULT)
                  $XDG_RUNTIME_DIR            Nvim: stdpath("run")
    Unix:         /tmp/nvim.user/xxx          /tmp/nvim.user/xxx
    Windows:      $TMP/nvim.user/xxx          $TMP/nvim.user/xxx


STATE DIRECTORY (DEFAULT)
                  $XDG_STATE_HOME             Nvim: stdpath("state")
    Unix:         ~/.local/state              ~/.local/state/nvim
    Windows:      ~/AppData/Local             ~/AppData/Local/nvim-data


CACHE DIRECTORY (DEFAULT)
                  $XDG_CACHE_HOME             Nvim: stdpath("cache")
    Unix:         ~/.cache                    ~/.cache/nvim
    Windows:      ~/AppData/Local/Temp        ~/AppData/Local/Temp/nvim-data


LOG FILE (DEFAULT)
                  $NVIM_LOG_FILE              Nvim: stdpath("log")/log
    Unix:         ~/.local/state/nvim         ~/.local/state/nvim/log
    Windows:      ~/AppData/Local/nvim-data   ~/AppData/Local/nvim-data/log
Note that stdpath("log") is currently an alias for stdpath("state").


ADDITIONAL CONFIGS DIRECTORY (DEFAULT)
                  $XDG_CONFIG_DIRS            Nvim: stdpath("config_dirs")
    Unix:         /etc/xdg/                   /etc/xdg/nvim
    Windows:      Not applicable              Not applicable


ADDITIONAL DATA DIRECTORY (DEFAULT)
                  $XDG_DATA_DIRS              Nvim: stdpath("data_dirs")
    Unix:         /usr/local/share            /usr/local/share/nvim
                  /usr/share                  /usr/share/nvim
    Windows:      Not applicable              Not applicable

```
