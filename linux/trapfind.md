## find的一个坑

匹配多个后缀时，如果后接执行命令选项，则执行的命令仅对最后的 `-name` 部分内容有效


```shell
find -name "*.yaml" -o -name "*.yml" -exec grep -rl earl {} +
# out: aa.yml

find -name "*.yml" -o -name "*.yaml" -exec grep -rl earl {} +
# out为空！

# 解决方案：用xargs吧。。
find -name "*.yaml" -o -name "*.yml" | xargs grep -rl earl
```

