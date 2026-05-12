# NixOS 远程部署：本地构建后切换到 VPS

小配置 VPS 常见做法是：不要让 VPS 自己编译系统闭包，而是在本地机器或更强的构建机上完成 build，然后把完整的 Nix store closure 复制到 VPS，最后在 VPS 上执行 `switch-to-configuration switch`。

`nixos-rebuild` 和 `nh` 都可以自动完成这个流程。

## 核心概念

`nixos-rebuild switch --target-host` 的语义是：

- 构建新系统配置
- 把构建结果复制到目标机器
- 在目标机器上激活新系统，并设为默认启动项

如果只指定 `--target-host`，没有指定 `--build-host`，构建默认发生在当前本地机器。

```sh
nixos-rebuild switch --flake .#reinsvps --target-host root@reinsvps
```

使用 `nh` 时对应为：

```sh
nh os switch . --hostname reinsvps --target-host root@reinsvps
```

这就是“本地 build 完再 switch 上去”。

## 适用条件

本地构建机必须能构建目标系统的 closure。

例如目标机器 `reinsvps` 是 `x86_64-linux`：

- 在 `x86_64-linux` 的 NixOS / WSL / Linux 构建：通常可行
- 在 `aarch64-darwin` 的 macOS 上直接构建：通常不可行，因为平台不匹配
- 如果 macOS 要部署 Linux VPS，建议加一个 Linux 构建机作为 `--build-host`

## 从 Linux 本地部署 VPS

适合在 `x86_64-linux` 机器上部署 `reinsvps`。

```sh
nh os switch . --hostname reinsvps --target-host root@reinsvps
```

等价的 `nixos-rebuild` 写法：

```sh
nixos-rebuild switch --flake .#reinsvps --target-host root@reinsvps
```

这里的构建发生在当前机器，VPS 只负责接收闭包和激活。

## 从 macOS 经 Linux 构建机部署 VPS

如果当前机器是 `aarch64-darwin`，目标是 `x86_64-linux` VPS，可以让一台 Linux 机器负责构建：

```sh
nh os switch . \
  --hostname reinsvps \
  --build-host qi@nixwsl \
  --target-host root@reinsvps
```

等价的 `nixos-rebuild` 写法：

```sh
nixos-rebuild switch \
  --flake .#reinsvps \
  --build-host qi@nixwsl \
  --target-host root@reinsvps
```

这个流程是：

- 本机负责发起部署和读取 flake
- `qi@nixwsl` 负责实际构建 `x86_64-linux` 系统闭包
- `root@reinsvps` 接收闭包并激活

## 手动拆解流程

自动命令背后大致等价于：

```sh
nix build .#nixosConfigurations.reinsvps.config.system.build.toplevel
nix copy --to ssh://root@reinsvps ./result
ssh root@reinsvps /nix/store/...-nixos-system-reinsvps-.../bin/switch-to-configuration switch
```

实际使用时不建议手写最后一个 store path，让 `nixos-rebuild --target-host` 或 `nh os switch --target-host` 处理即可。

## 权限要求

远程激活 NixOS 系统需要 root 权限。

常见方式：

- 直接用 `root@host` 部署
- 使用普通用户 SSH 登录，再配合 sudo

`nixos-rebuild` 支持 `--sudo` 和 `--ask-sudo-password`；`nh` 支持 elevation strategy。服务器上如果希望用普通用户部署，需要确认该用户能执行系统激活所需的 sudo 操作。

## 远程 builder 和分布式构建

还有另一类配置是把远程 builder 写进 Nix 配置：

```nix
{
  nix.distributedBuilds = true;
  nix.buildMachines = [
    {
      hostName = "builder-host";
      system = "x86_64-linux";
      protocol = "ssh-ng";
      maxJobs = 4;
      speedFactor = 2;
      supportedFeatures = [ "nixos-test" "benchmark" "big-parallel" "kvm" ];
    }
  ];
}
```

这个适合长期固定使用某台构建机。临时部署 VPS 时，直接用 `--build-host` 更简单。

使用远程 builder 时，发起构建的用户通常需要是 Nix daemon 的 trusted user：

```nix
{
  nix.settings.trusted-users = [ "root" "qi" "@wheel" ];
}
```

## NixOS配置可加入的 Justfile recipe

从同架构 Linux 机器部署 VPS：

```just
[group('nix')]
switch-vps host="reinsvps" target="root@reinsvps":
  nh os switch . --hostname {{host}} --target-host {{target}}
```

从 macOS 发起，经 Linux 构建机部署 VPS：

```just
[group('nix')]
switch-vps-from-builder host="reinsvps" builder="qi@nixwsl" target="root@reinsvps":
  nh os switch . --hostname {{host}} --build-host {{builder}} --target-host {{target}}
```

## 远程部署 standalone Home Manager

可以做到，但 nh home switch 没有 --target-host，只有 --build-host。也就是说它没有像 nixos-rebuild --target-host 那样内建“一键远程激活”。

手动流程大概是：

```nix
nix build .#homeConfigurations.qi.activationPackage
path=$(readlink -f result)
nix copy --to ssh://qi@reinsvps "$path"
ssh qi@reinsvps "$path/activate"
```


## 参考

- `nixos-rebuild` man page: `--target-host` 指定远程激活目标；未显式指定 `--build-host` 时本地构建；`--build-host` 可指定 SSH 构建机。
- NixOS option `nix.buildMachines`: 开启分布式构建后，Nix 会通过 SSH 把输入复制到远程机器构建，再把输出复制回本地 store。
- NixOS option `nix.distributedBuilds`: 是否启用 `nix.buildMachines` 中的构建机器。
- NixOS option `nix.settings.trusted-users`: trusted user 可以指定额外 builder / cache 等影响 Nix daemon 的设置。
