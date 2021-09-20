# qmake 取变量值的几种区别
| 符号 | 含义| 
| --- | ----| 
| `$$varName` / `$${varName}` | qmake工程文件内定义变量的值 |
| `$$(varName)` | qmake运行时，环境变量的值 | 
| `$(varName)` | makefile被处理时，环境变量的值 |
| `$$[varName]` | Qt配置选项的值 |
| `${varName}` | 暂不讨论这个东西，以后用到时会提及 |

## $$varName 与 $${varName} 的区别

1.何时加大括号？当变量和后面的字符连接到一块的时候。

2.build_pass :如果没有它，同样的消息在windows下会被输出多次(生成几个makefile文件，就有几次)。


# Qt 维护-添加删除组件
## 一、 打开组件管理工具
QT安装目录发现了QT的组件管理软件MaintenanceTool
## 二、 选择添加或移除或更新
此时提示：“至少需要一个有效且已启用的储存库”
解决方法：
### 1、选择左下角的设置，进入如图界面，然后选择“临时存储库”
### 2、手动添加​临时储存库要定位一个储存有QT在线安装镜像的地址，这个地址可以从这里选择　　
http://download.qt.io/static/mirrorlist/

在这个网站，显示了各国的qt镜像站点，中国有四个，随便选一个中科大的站点击HTTP会进入一个网络文件夹。
以此进入如下路径：/online/qtsdkrepository/windows_x86/root/qt/.
然后把该路径添加到临时存储库中。然后就可以增删组件了。

直接添加地址：https://mirrors.tuna.tsinghua.edu.cn/qt/online/qtsdkrepository/windows_x86/root/qt/
* 若提示找不到”preview.qt.56.win64_msvc2015_64"的缺失依赖项“qt.563.win64_msvc2015_64这样的信息，需要点击 updata tools,之后会提示你更新 MaintenanceTool.exe

# <center>pro判断编译器</center>
```bash
## g++ 编译器（版本：9.3.0）
QMAKE_GCC_MAJOR_VERSION  # gcc 主版本号（如：9）
QMAKE_GCC_MINOR_VERSION  # gcc 次版本号（如：3）
QMAKE_GCC_PATCH_VERSION  # gcc 修订版本号（如：0）

## msvc 编译器
QMAKE_MSC_VER             # msvc _MSC_VER版本号 （如：1920）
QMAKE_MSC_FULL_VER        # msvc _MSC_FULL_VER版本号（如：192027508）

## clang 编译器（版本：10.0.1）
QMAKE_CLANG_MAJOR_VERSION  # clang 主版本号（如：10）
QMAKE_CLANG_MINOR_VERSION  # clang 次版本号（如：0）
QMAKE_CLANG_PATCH_VERSION  # clang 修订版本号（如：1）

## apple clang 编译器（版本11.0.3）
QMAKE_APPLE_CLANG_MAJOR_VERSION  # apple clang 主版本号（如：11）
QMAKE_APPLE_CLANG_MINOR_VERSION  # apple clang 次版本号（如：0）
QMAKE_APPLE_CLANG_PATCH_VERSION  # apple clang 次版本号（如：3）

## icc 编译器（Intel C++ Compiler）
QMAKE_ICC_VER          # icc 版本号
QMAKE_ICC_UPDATE_VER   # icc 版本号
```

# <center>文件大小写</center>

左侧选择c++  →  文件命名 然后倒数第二行的
lower case file names