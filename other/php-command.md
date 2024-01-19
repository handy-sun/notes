
## php 命令行(linux)出错的问题

php -f 的内容有错误的话会对当前的shell(zsh)环境产生影响，表现为php会变成shell的一个函数，zsh中所有的php命令都提示： zsh: no matches found: ?php
php命令都会执行失败, **错误事例**如:

```php
# 不能加单引号
php -f '<?php $php-version();\n?>\n'

# echo应该前用$
php -f <?php echo $php-version();\n?>\n

```

正确的格式应该是

```php
php -f <?php $php-version();\n?>\n
```

使用`declare -f php`甚至可以看到函数的定义
```shell
unset -f php
```
