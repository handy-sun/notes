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

## 只 eval，本地推 `.drv` 到远端 build

还有一种更底层的远程构建方式：本地只做 eval，拿到 `.drv`，然后把 `.drv`
及其闭包推到远端 store，让远端执行 build。

`.drv` 是 Nix 的构建计划。它来自 flake/表达式求值结果，记录 builder、参数、输入
store paths 和输出路径，但还不是最终 build output。这个流程把 Nix 的工作拆成：

- 本地 eval：生成 `.drv`
- 复制 `.drv` closure 到远端
- 远端 realise/build `.drv`
- 可选：把 build output closure 拉回本地，或直接在远端部署

下面这个例子里：

- `reinsvps` 是要构建的目标 NixOS 配置
- `qi@nixwsl` 是负责实际 build 的 Linux 构建机
- `root@reinsvps` 是最终接收并激活系统的目标 VPS

构建机和目标机器可以是同一台，也可以不是同一台。macOS 发起部署 Linux VPS 时，常见做法是：
本机 eval `reinsvps` 配置，把 `.drv` 交给 `nixwsl` 这类 Linux builder 构建，最后再把
build output copy 到 `reinsvps` 激活。

```sh
target_attr='.#nixosConfigurations.reinsvps.config.system.build.toplevel'
builder='qi@nixwsl'
target='root@reinsvps'

# 1. 本地只求值，拿到系统配置对应的 .drv
drv=$(nix path-info --derivation "$target_attr")

# 2. 把 .drv 及其求值闭包推到远端 builder
nix copy --to "ssh://$builder" "$drv"

# 如果远端访问 cache 更快，可以让远端自己 substitute 缺失路径
nix copy --substitute-on-destination --to "ssh://$builder" "$drv"

# 3. 在远端 realise/build 这个 .drv
ssh "$builder" "nix-store --realise '$drv'"

# 4. 可选：把 build outputs 拉回本地
outs=$(nix-store -q --outputs "$drv")
nix copy --from "ssh://$builder" $outs

# 5. 可选：把 build outputs 推到目标 VPS 并激活
nix copy --to "ssh://$target" $outs
system_path=$(nix-store -q --outputs "$drv" | head -n1)
ssh "$target" "$system_path/bin/switch-to-configuration switch"
```

注意点：

- 远端 builder 的 `system` 必须能构建这个 `.drv`，例如 `x86_64-linux` 的系统
  closure 需要 `x86_64-linux` builder。
- `target_attr` 决定构建哪个主机配置；`builder` 决定在哪台机器 build；
  `target` 决定最终 copy 到哪里并激活。
- 复制 `.drv` 不等于复制最终系统 closure；远端 build 成功后才有 output closure。
- 如果远端能访问 `cache.nixos.org` 或私有 binary cache，推 `.drv` 通常很轻，依赖可以由远端自己拉。
- 这类流程适合 CI 或自定义调度器：CI 负责 eval 和调度，专门 builder 负责实际构建。
- Nix 的 remote builder / `--build-host` 本质上是在更高层把这个过程自动化；日常部署优先用
  `nixos-rebuild --build-host` 或 `nh os switch --build-host`。

也可以尝试直接让 eval store 和 build store 都指向远端：

```sh
nix build \
  --eval-store ssh-ng://qi@nixwsl \
  --store ssh-ng://qi@nixwsl \
  "$target_attr"
```

这表示本地发起命令，但 `.drv`、相关输入和 build 发生在远端 store。实际使用时要确认远端
SSH store 权限、trusted user 和目标系统架构都匹配。

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
