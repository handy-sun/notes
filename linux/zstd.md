# zstd 压缩和解压命令

Zstandard，或简称为 zstd ，是一种快速无损压缩算法，针对 zlib 级别的实时压缩场景和更好的压缩率。它由Huff0 和 FSE 库提供的非常快的熵阶段支持。
[github地址](https://github.com/facebook/zstd)

## 1. 安装 zstd


```shell
## debian/ubuntu
sudo apt install -y zstd && zstd --version
## arch/manjaro
sudo pacman -S zstd && zstd --version
```

## 2. 单个文件

### 压缩

```shell
zstd a.yml
```

### 解压

```shell
## 标准
zstd -d a.sql.zst
## tar解压
tar -I zstd -xvf a.zst
## tar解压（tar-1.31及以上版本）
tar xvf s.tar.zst
```

## 3. 文件夹


### 压缩


```shell
## 方法一：先归档成一个文件再压缩
tar cvf backup.tar ./ && zstd backup.tar
## 方法二：指定
tar -I zstd -cf backup.tar.zst ./
## 方法三（tar-1.31及以上版本）
tar cfa backup.tar.zst ./
## 方法四（tar-1.31及以上版本，不建议，太慢）
tar cfz backup.tar.zst ./
```

### 解压

```shell
## 方法二: 用tar直接一步到位
tar xf backup.tar.zst
## 方法二: 分步骤
zstd -d backup.tar.zst && tar xf backup.tar
```

## 4. 字典压缩操作方法：

创建词典

```shell
zstd --train FullPathToTrainingSet/* -o dictionaryName
```

使用字典压缩

```shell
zstd -D dictionaryName FILE
```

使用字典解压

```shell
zstd -D dictionaryName --decompress FILE.zst
```
