# NixOS 物理机安装指南

**场景**：联想昭阳 E41 笔记本，SATA SSD，UEFI 模式，btrfs 文件系统，无线网络

---

## 1. BIOS 设置

1. 开机按 **F2** 进入 BIOS
2. **关闭 Secure Boot**：Security → Secure Boot → Disabled
3. 确认启动模式为 **UEFI**（Boot Mode → UEFI）
4. 保存退出（F10）

## 2. 制作启动盘 & 启动

1. 用 Ventoy 制作 USB 启动盘，将 NixOS minimal ISO 放入
2. 开机按 **F12** 进入 Boot Menu，选择 USB 启动
3. Ventoy 界面选择 ISO → **正常模式（Normal）**
4. 出现系统选择界面 → 选 **lts 内核**
5. 如卡住按 Esc 切换详细日志，或在启动提示符输入 `nixos nomodeset`

## 3. 连接无线网络

```bash
# 启动 wpa_supplicant
systemctl start wpa_supplicant

# 交互式连接 WiFi
wpa_cli
> add_network
> 0
> set_network 0 ssid "你的WiFi名"
> set_network 0 psk "密码"
> enable_network 0
> quit

# 确认拿到 IP
ip addr show
ping -c 3 baidu.com
```

## 4. 分区（GPT + ESP + btrfs）

```bash
# 确认磁盘设备名
lsblk

# 创建 GPT 分区表
parted /dev/sda -- mklabel gpt

# EFI 系统分区（1024MiB）
parted /dev/sda -- mkpart ESP fat32 1MiB 1024MiB
parted /dev/sda -- set 1 esp on

# 主分区（剩余全部空间）
parted /dev/sda -- mkpart primary 1024MiB 100%
```

### 格式化

```bash
mkfs.fat -F32 /dev/sda1
mkfs.btrfs -L nixos /dev/sda2
```

## 5. 创建 btrfs 子卷

```bash
# 挂载根分区
mount /dev/sda2 /mnt

# 创建子卷
btrfs subvolume create /mnt/@        # 系统根目录
btrfs subvolume create /mnt/@home    # 用户目录
btrfs subvolume create /mnt/@nix     # nix store（包仓库）
btrfs subvolume create /mnt/@swap    # swap 文件

# 卸载
umount /mnt
```

### 各子卷用途

| 子卷 | 挂载点 | 说明 |
|------|--------|------|
| @ | / | 系统根目录 |
| @home | /home | 用户数据，可独立快照 |
| @nix | /nix | nix store，体积大，建议单独管理 |
| @swap | /swap | 存放 swapfile |

## 6. 重新挂载子卷

```bash
# 根子卷
mount -o subvol=@,compress=zstd,ssd,compress-force=zstd /dev/sda2 /mnt

# 创建挂载点
mkdir -p /mnt/{home,nix,boot,swap}

# 挂载其余子卷
mount -o subvol=@home,compress=zstd,ssd,compress-force=zstd /dev/sda2 /mnt/home
mount -o subvol=@nix,compress=zstd,ssd,compress-force=zstd /dev/sda2 /mnt/nix
mount -o subvol=@swap,ssd /dev/sda2 /mnt/swap

# 挂载 EFI 分区
mount /dev/sda1 /mnt/boot

# 创建 swap 文件（4G）
btrfs filesystem mkswapfile --size 4g /mnt/swap/swapfile
swapon /mnt/swap/swapfile
```

### 挂载选项说明

- `compress=zstd`：透明压缩，省空间，老机器读取也更快
- `compress-force=zstd`：强制压缩所有数据（含已压缩的）
- `ssd`：SSD 优化（TRIM 等）
- 非 SSD 用 `discard=async` 替代 `ssd`

## 7. 生成硬件配置

```bash
nixos-generate-config --root /mnt
```

## 8. 编辑配置文件

```bash
nano /mnt/etc/nixos/configuration.nix
```

### 必改项

```nix
{ config, pkgs, ... }:

{
  imports = [ ./hardware-configuration.nix ];

  # 引导加载器（UEFI）
  boot.loader.systemd-boot.enable = true;
  boot.loader.efi.canTouchEfiVariables = true;

  # 主机名
  networking.hostName = "nixos";
  # 重要!!!: 无线连接情况下重启后nmtui连WiFi更方便, 或是其他无线连接方式（至少开启一种）
  networking.networkmanager.enable = true;

  # 时区
  time.timeZone = "Asia/Shanghai";

  # 区域
  i18n.defaultLocale = "zh_CN.UTF-8";

  # 用户（安装时先不创建，装完后再加）
  # users.users.yourname = {
  #   isNormalUser = true;
  #   extraGroups = [ "wheel" "networkmanager" ];
  # };

  # 基础软件包
  environment.systemPackages = with pkgs; [
    vim
    git
    wget
    curl
  ];

  # 防火墙（可选关闭）
  networking.firewall.enable = false;

  # Swap（hardware-configuration.nix 里已自动检测）
  # 如需调整 swappiness：
  boot.kernel.sysctl."vm.swappiness" = 10;

  system.stateVersion = "25.05";
}
```

### 检查 hardware-configuration.nix

确认 swap 和 btrfs 子卷配置正确：

```bash
nano /mnt/etc/nixos/hardware-configuration.nix
```

应该能看到类似：

```nix
fileSystems."/" = {
  device = "/dev/sda2";
  fsType = "btrfs";
  options = [ "subvol=@" ];
};

fileSystems."/home" = {
  device = "/dev/sda2";
  fsType = "btrfs";
  options = [ "subvol=@home" ];
};

fileSystems."/nix" = {
  device = "/dev/sda2";
  fsType = "btrfs";
  options = [ "subvol=@nix" ];
};

fileSystems."/swap" = {
  device = "/dev/sda2";
  fsType = "btrfs";
  options = [ "subvol=@swap" ];
};

fileSystems."/boot" = {
  device = "/dev/sda1";
  fsType = "vfat";
};

swapDevices = [ { device = "/swap/swapfile"; } ];
```

如果缺少 swap 或子卷条目，手动补上。

## 9. 安装系统

```bash
nixos-install
```

- 会要求设置 **root 密码**
- 等待下载和构建（首次较慢）

## 10. 创建非特权用户

```bash
# chroot 进已安装的系统
nixos-enter

# 创建用户
useradd -m -G wheel -s /bin/bash yourname
passwd yourname

# 确认 sudo 可用
visudo   # 取消 %wheel ALL=(ALL) ALL 的注释（如需要）

# 退出 chroot
exit
```

## 11. 重启

```bash
reboot
```

拔掉 USB，从硬盘启动。

## 12. 首次启动后

```bash
# 连接 WiFi（NetworkManager）
nmtui

# 更新系统
sudo nixos-rebuild switch

# 搜索安装软件
nix search nixpkgs firefox
```

---

## 常见问题

### 启动卡住
在 systemd-boot 菜单按 `e`，在 linux 行末尾加 `nomodeset`，按 Enter 启动。

### WiFi 连不上
```bash
sudo systemctl restart NetworkManager
nmcli device wifi list
nmcli device wifi connect "SSID" password "密码"
```

### btrfs 空间不足
```bash
btrfs filesystem usage /
btrfs subvolume list /
```

### 回滚到上一次配置
重启时在 systemd-boot 菜单选择之前的 generation。
