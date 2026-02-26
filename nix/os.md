
## Some tips

### 一个刚重装完的Nixos该怎么配置

先改 `/etc/nixos/configuration.nix` 中的配置, 启动flake

```sh
# 修改完配置后，使配置生效
nixos-rebuild switch
```

### 修改系统主机名

`flake.nix`

```nix
nixosConfigurations.your-hostname= nixpkgs.lib.nixosSystem {
  ...
};
```

如果希望以后直接运行 `nixos-rebuild switch` 而不加参数，可以修改系统的主机名定义

`configuration.nix`

```nix
{
  networking.hostName = "your-hostname"
}
```


```sh
sudo nixos-rebuild switch --flake '.#your-hostname'
```


注：`.` 表示当前路径，`#` 后接输出名称。

**PS: 如果更改hostname成功了最好重启机器使新的hostname生效, 这样之后rebuild就不用加--flake指定额外的hostname参数了**

### zsh配置

在 `/etc/nixos/configuration.nix` 中

```nix
{
  programs.zsh.enable = true;
  users.users.<myusername> = {
    shell = pkgs.zsh;
  };
}
```

`home.nix`

方案1: 配置写在nix中

```nix
{
  programs.zsh = {
    enable = true;
    ...
  };
}

```

方案2: 修改 `~/.zshrc` 内容,使用自己的配置


```nix
{
  home.file.".zshrc".text = ''
    source $HOME/.config/dotzsh/zshrc
  '';
}

```

### 其他常用命令

构建类`nixos-rebuild`

```sh
# 测试配置能否通过构建（但是并不切换到该配置）,当前目录生成个result软链接指向构建结果
nixos-rebuild build

# 修改完配置后，使配置生效，但是不将它设置为默认启动项
nixos-rebuild test

# 修改完配置后，将它设置为默认启动项,（但是要下次启动才生效，不立即生效）
nixos-rebuild boot

# 使配置立即生效并将修改完的配置加入到 grub 选项并命名为 test.
nixos-rebuild switch -p test
```

查看和清除

```sh
# 查看已安装的包（去重 + 去版本号后缀）
nix-store -q --references /run/current-system/sw | sed 's|.*/||; s/-[0-9].*//' | sort -u

# 查看已安装的包（去重 + 去版本号后缀以及 - 之前的digest（哈希值））
nix-store -q --references /run/current-system/sw | sed 's|.*/||; s/-[0-9].*//' | sort -u | cut -d- -f2-

# 查看构建过的系统历史
nix profile history --profile /nix/var/nix/profiles/system

sudo nix profile wipe-history --older-than 2d --profile /nix/var/nix/profiles/system

# 垃圾回收: 递归遍历 /nix/var/nix/gcroots/ 目录下的所有软链接，找出所有被引用的软件包，然后将不再被引用的软件包删除
nix-store --gc

# 进一步回收空间： 删除掉所有旧的 profiles，再执行 nix-store --gc 命令清理掉不再被引用的软件包
nix-collect-garbage --delete-old
```