## 一、win10打开文件资源管理器默认打开我的电脑

win10打开文件资源管理器,不像win7默认打开我的电脑，有时按快捷键 Win+e 打开快速访问而不是我的电脑，这里介绍怎么默认打开我的电脑。
1. 点开文件资源管理器的上方工具栏，点击【查看】->【选项】（即文件夹选项）
2. 在选项卡中选择【常规】，“打开文件资源管理器时打开”选择此电脑

## 二、电脑总是莫名其妙出现USB拔出的那种提示声音
问题:来自 <https://tieba.baidu.com/p/6266774292#134513102190l> 

Windows 默认开启了【节电模式】，致使USB接口zhi供电不足，使USB接口间歇性失灵。

1. 打开—【设备管理器】（【开始】—【运行】中输入【devmgmt.msc】回车即可打开设备管理器）
2. 双击【通用串行总线控制器】—【USB Root Hub】双击任意一个
3. 打开属性对话框，切换到【电源管理】选项卡，去除【允许计算机关闭这个设备以节约电源】前的勾选
4. 点击确定返回，依次将每个【USB RootHub】的属性都修改完后重新启动电脑

## 三、总是无故提示“您有等待写入光盘的文件”解决方法

启动Windows，总是要提示“您有等待写入光盘的文件”，启动时间也变慢。

可能是通过资源管理器刻录光盘的时候留下的垃圾。

删除下边的目录即可C:\Users\%USER%\AppData\Local\Microsoft\Windows\Burn\Temporary\Burn Folder

## 四、WSL2桌面环境配置
在子系统 ~/.bashrc 后追加以下内容

```bash
export DISPLAY=$(grep -m 1 nameserver /etc/resolv.conf | awk '{print $2}'):0
export XDG_SESSION_TYPE=x11
```