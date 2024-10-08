
## Gui

Manjaro设置管理器提供了一种添加和删除内核的简便方法。可以通过点击“安装”按钮来安装新内核。所有必需的内核模块也将与新内核一起自动安装。 选择内核时，请考虑“推荐”标签。LTS意味着长期支持，这对大多数用户来说是最安全的。默认情况下将启动最新安装的内核，但要运行已安装的其他内核，请参阅下面的“选择内核”部分。

## Terminal

添加和删除内核，也可以在终端上完成所有操作。

### 识别正在使用的内核
以下终端命令将为你提供系统的内核信息：

```sh
mhwd-kernel -li
```

上面的命令不仅显示正在使用哪个内核，还列出了所有其他已安装的内核，如以下示例终端输出所示：

```
当前正在运行：5.0.17-1-MANJARO（linux50）
系统中安装了以下内核：
* Linux419
* linux420
* linux50
```

如上面的示例所示，Manjaro正在运行内核5.0.17-1-MANJARO。此处提供的信息不是随便给的，内核名称的每个部分都有特定的含义：

- 5表示版本
- 0表示主要版本
- 17表示次要修订
- 1表示Manjaro软件包的修订版本
- MANJARO指示其用于的特定发行版

### 添加新内核

Manjaro不仅支持使用多个内核（可从开机画面处选择），也可以方便地安装最新的内核。这需要借助Manjaro的硬件检测命令来完成。该命令的语法如下：

```sh
sudo mhwd-kernel [-i] [新内核：linux（version）] [可选-删除当前内核：rmc]
```

当要用命令安装的新内核时，不必写完整的版本号。例如，任何版本的`Kernel 4.19`都可以简单地列为 `linux419`，而任何版本的`Kernel 4.14`都可以列为`linux414`，依此类推。可选的RMC是至关重要的。使用此选项将会在安装新内核时删除现有内核，如果不使用它，则将保留现有内核。建议（尤其是在更新到最新的内核时）保留你的旧内核。当对新内核的稳定性和功能感到满意时，再去删除旧内核。

打开终端后，以下命令将安装新内核（4.19），而不会删除当前正在使用的现有内核：

```sh
sudo mhwd-kernel -i Linux419
```

以下命令将安装一个新的内核（3.13）来替换现有的内核，且现有内核将被删除：

```sh
sudo mhwd-kernel -i Linux419 rmc
```

无论哪种方式，Manjaro都会为你自动配置新内核。完成后，关闭终端并重新启动系统，以使更改生效。

### 移除内核

**警告：正在使用现有的内核时，请勿尝试删除它。你可以首先在终端中使用命令`mhwd-kernel -li`来识别系统上正在运行的内核（请参见上文）。如果系统上存在多个内核，则可以使用pacman在终端中将其删除。总共删除三个内核元素才能完全删除它**：

- 内核本身
- 内核头文件
- 内核的额外模块

1.要删除内核，使用以下语法：
```sh
sudo mhwd-kernel -r linux[version]
```

例如，删除内核5.0.17-1
```sh
sudo mhwd-kernel -r linux50
```

2.同理，要从系统中删除内核版本5.0.x的标头，将输入以下命令：

```sh
sudo pacman -R linux50-headers
```

3.同理，要从系统中删除内核版本5.0.x的额外模块，将输入以下命令：

```sh
sudo pacman -R linux50-extramodules
```

4.要同时删除内核的所有元素，语法是：

```sh
sudo pacman -R linux[version] linux[version]-headers linux[version]-extramodules
```
例如，要完全删除内核版本5.0.x的所有元素，将输入以下命令：

```sh
sudo pacman -R linux50 linux50-headers linux50-extramodules
```

但是请注意，如果一次删除多个元素（且某些元素您的系统中不存在），则会在中止之前产生一条报错消息。还值得注意的是，如果Manjaro在虚拟机（例如Oracle Virtualbox）中运行，若某些内核包含对虚拟化过程本身很重要的元素，则可能无法删除它们。

### mhwd-kernel -h命令

与大多数可以在终端中输入的Linux命令一样，在键入命令后再键入-h或--help将向终端打印出用法和可用选项，以供您参考。这是`mhwd-kernel -h`命令的输出：

```sh
$ mhwd-kernel -h
用法：mhwd-kernel [选项]
   -h --help显示此帮助消息
   -i --install安装新内核[可选：rmc =删除当前内核]
   -l --list列出所有可用的内核
   -li --listinstalled列出已安装的内核
   -r --remove删除内核
```