#!/bin/bash
exit

1.
sudo mkdir -p /offline
sudo cp -r /var/cache/apt/archives/ offline/
sudo chmod 777 -R offline/
sudo dpkg-scanpackages /offline/ /dev/null | gzip > /offline/Packages.gz
for i in `seq 1 16`; do sudo dpkg-scanpackages /offline/major /dev/null | gzip > /offline/major/Packages.gz & done
for i in `seq 1 $(cat /proc/cpuinfo |grep "physical id" |wc -l)`; do sudo dpkg-scanpackages /offline/major /dev/null | gzip > /offline/major/Packages.gz & done

# 将debs文件夹拷到离线机器的根目录下，修改系统源source.list（注意备份）
sudo vim /etc/apt/sources.list
# 指定路径，注意要相同
deb [trusted=yes] file:/// offline/


2.sed命令下批量替换文件内容
格式: sed -i 's/查找字段/替换字段/g' `grep 查找字段 -rl 路径` 文件名

-i 表示inplace edit，就地修改文件
-r 表示搜索子目录
-l 表示输出匹配的文件名
 
s表示替换，d表示删除

示例：# 把当前目录下 pkg.txt 里的 空格 都替换为 换行符
sed -i 's/ /\n/g' pkg.txt
高级：# 把当前目录下 pkg.txt 里的 换行符 都替换为 空格
sed -i ':a;N;s/\n/ /g;ta' pkg.txt
# 去掉括号及里面的内容
sed -r "s/[(][^)]*[)]//g"

dpkg -I $1 | grep Depends | sed 's/Depends://g' | sed -r "s/[(][^)]*[)]//g" | tr "| ," " "

# tar+pigz 压缩
sudo tar cvf - /offline/ | pigz -9 -p 16 > ~/offline.tgz
# tar+pigz 解压
sudo tar xvpf offline.tgz --use-compress-program=pigz -C /

du /offline/ --max-depth=1 -lh | sort -sh