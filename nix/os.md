
## Some tips

### 一个刚重装完的Nixos该怎么配置

先改 `/etc/nixos/configuration.nix` 中的配置, 启动flake

```sh
# 修改完配置后，使配置生效
nixos-rebuild switch
```
**PS: 如果更改hostname了(即配置文件里的hostname改了), 最好重启机器使新的hostname生效, 这样之后rebuild就不用加--flake指定额外的hostname参数了**

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
  programs.zsh.enable = true;
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

构建类

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

```sh
# 查看已安装的包（去重 + 去版本号后缀）
nix-store -q --references /run/current-system/sw | sed 's|.*/||; s/-[0-9].*//' | sort -u

# 查看已安装的包（去重 + 去版本号后缀以及 - 之前的hash特征码）
nix-store -q --references /run/current-system/sw | sed 's|.*/||; s/-[0-9].*//' | sort -u | cut -d- -f2-

# 查看构建过的系统历史
nix profile history --profile /nix/var/nix/profiles/system
```