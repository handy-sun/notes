# <font style="medium"> 要在 Manjaro 中刷新 DNS 缓存

可以使用以下几种方法：

## <font size="5"> 1. 重启网络服务</font>
   你可以通过重新启动网络服务来刷新 DNS 缓存。可以使用以下命令：

   ```bash
   sudo systemctl restart NetworkManager
   ```

## <font size="5">2. 使用 NetworkManager applet</font>
   你可以通过 NetworkManager 的图形界面来重新连接网络。在系统托盘中找到网络连接图标，然后断开并重新连接网络。

## <font size="5">3. 清除 DNS 缓存</font>
   你也可以直接清除 DNS 缓存。首先安装 `nscd` 工具，然后运行以下命令：

   ```bash
   sudo pacman -S nscd
   sudo systemctl restart nscd
   ```

   这将清除系统的 DNS 缓存并重新加载 DNS 信息。

## <font size="5">4. 更新 DHCP 客户端</font>
   有时 DHCP 客户端也会缓存 DNS 信息。你可以通过重新启动 DHCP 客户端来更新缓存。运行以下命令：

   ```bash
   sudo dhclient -r
   sudo dhclient
   ```
