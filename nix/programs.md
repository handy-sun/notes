
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
