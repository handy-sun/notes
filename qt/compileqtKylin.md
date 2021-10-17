# 麒麟V10桌面版 编译安装Qt
## 一，安装依赖
### 1.安装包
```bash
sudo apt-get install -y libxcb-xinerama0-dev 
# sudo apt-get install build-essential perl python git
sudo apt-get install -y '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev
sudo apt-get install -y flex bison gperf libicu-dev libxslt-dev ruby
sudo apt-get install -y libssl-dev libxcursor-dev libxcomposite-dev libxdamage-dev libxrandr-dev libdbus-1-dev libfontconfig1-dev libcap-dev libxtst-dev libpulse-dev libudev-dev libpci-dev libnss3-dev libasound2-dev libxss-dev libegl1-mesa-dev
# sudo apt-get install -y  libasound2-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev
sudo apt-get -y install libclang-6.0-dev llvm-6.0
# sudo apt-get -y install clang-8
```

### 2.安装ninja编译依赖re2c
```bash
sudo apt-get install re2c
# 编译ninja
cur_path=$PWD
cd $cur_path/qt-everywhere-src-5.12.8/qtwebengine/src/3rdparty/ninja
./configure.py --bootstrap 
# 安装ninja
sudo cp ./ninja /usr/bin
# 检查安装是否完成
ninja --version
```

## 二，生成、编译、安装
```bash
# 执行源码根目录下的configure
cd $cur_path/qt-everywhere-src-5.12.8
chmod +x zgenerate.sh
./zgenerate.sh
# 编译
make -j 4
# 安装
make install
```

## 三，测试
```bash
# 安装qtchooser并加入新的qmake
sudo apt-get install qtchooser
qtchooser -install 'qt5.12.8' '/opt/Qt-5.12.8-shared/bin/qmake'
# 可查看当前系统中qmake的版本
qtchooser -l
#（该处只是添加了临时变量，建议直接添加到环境变量中）
export QT_SELECT=qt5.12.8
qmake -v
```
## 四，添加环境变量
```bash
sudo vim /etc/profile
# -------------按下i输入，在其最后添加以下信息
export QTDIR=/opt/Qt-5.12.8-shared
export PATH=$QTDIR/bin:$PATH
export MANPATH=$QTDIR/man:$MANPATH
export LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH
# ---保存后应用修改
sudo source /etc/profile
qmake -v
```

## 五，编译、安装qtcreator（容易失败，麻烦）
```bash
cd $cur_path/qt-creator-opensource-src-4.10.0-beta2
export QT_SELECT=qt5.12.8
qmake -r
make -j 4
# 安装系统路径下，需要sudo权限
sudo make install
```
