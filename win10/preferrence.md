# <font size='5'>1. win10打开文件资源管理器默认打开我的电脑</font>

win10打开文件资源管理器,不像win7默认打开我的电脑，有时按快捷键 Win+e 打开快速访问而不是我的电脑，这里介绍怎么默认打开我的电脑。
1. 点开文件资源管理器的上方工具栏，点击【查看】->【选项】（即文件夹选项）
2. 在选项卡中选择【常规】，“打开文件资源管理器时打开”选择此电脑

# <font size='5'>2. 电脑总是莫名其妙出现USB拔出的那种提示声音</font>
问题:来自 <https://tieba.baidu.com/p/6266774292#134513102190l> 

Windows 默认开启了【节电模式】，致使USB接口zhi供电不足，使USB接口间歇性失灵。

1. 打开—【设备管理器】（【开始】—【运行】中输入【devmgmt.msc】回车即可打开设备管理器）
2. 双击【通用串行总线控制器】—【USB Root Hub】双击任意一个
3. 打开属性对话框，切换到【电源管理】选项卡，去除【允许计算机关闭这个设备以节约电源】前的勾选
4. 点击确定返回，依次将每个【USB RootHub】的属性都修改完后重新启动电脑

# <font size='5'>3. 总是无故提示“您有等待写入光盘的文件”解决方法</font>

启动Windows，总是要提示“您有等待写入光盘的文件”，启动时间也变慢。

可能是通过资源管理器刻录光盘的时候留下的垃圾。

删除下边的目录即可C:\Users\%USER%\AppData\Local\Microsoft\Windows\Burn\Temporary\Burn Folder

# <font size='5'>4. Win10系统下打开文件资源管理器很慢</font>

- 开始-->设置（按Windows键+i键 也可以）
- 在搜索框中输入索引，会有提示索引选项，如果没有，就输入完整的索引选项，回车
- 选择“修改”添加需要重建的位置，选择完成后点击确认
- 在弹出的窗口中选择更改所选位置
- 然后选择“高级”（说明：因为下面的只是过程说明，为了节省时间没有选择所有的位置，和上图的不一样。具体操作根据实际需要选择）
- 选择“重建”，提示需要很长时间，点确定
- 重建索引完成，关闭该窗口，关闭文件资源管理器，重新打开

# <font size='5'>5. 重建图标缓存 </font>

只需一条命令：

```cmd
ie4uinit -show
```

无需关闭或重启explorer
