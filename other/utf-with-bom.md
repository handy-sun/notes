
## BOM的含义

　　BOM即Byte Order Mark字节序标记。BOM是为UTF-16和UTF-32准备的，用户标记字节序（byte order）。拿UTF-16来举例，其是以两个字节为编码单元，在解释一个UTF-16文本前，首先要弄清楚每个编码单元的字节序。例如收到一个“奎”的Unicode编码是594E，“乙”的Unicode编码是4E59。如果我们收到UTF-16字节流"594E"，那么这是“奎”还是“乙”？

　　Unicode规范中推荐的标记字节顺序的方法是BOM：在UCS编码中有一个叫做 `"ZERO WIDTH NO-BREAK SPACE"`（零宽度无间断空间）的字符，它的编码是FEFF。而FEFF在UCS中是不不能再的字符（即不可见），所以不应该出现在实际传输中。UCS规范建议我们在传输字节流前，先传输字符"ZERO WIDTH NO-BREAK SPACE"。这样如果接收者接收到FEFF，就表明这个字节流是Big-Endian的；如果收到FFFE，就表明这个字节流是Little-Endian的。因此字符`"ZERO WIDTH NO-BREAK SPACE"`又被称为BOM。

　　UTF-8是以字节为编码单元，没有字节序的问题。

### 延伸

UTF-8编码是以1个字节为单位进行处理的，不会受CPU大小端的影响；需要考虑下一位时就地址 + 1。

UTF-16、UTF-32是以2个字节和4个字节为单位进行处理的，即1次读取2个字节或4个字节，这样一来，在存储和网络传输时就要考虑1个单位内2个字节或4个字节之间顺序的问题。


## UTF-8 BOM

　　UTF-8 BOM又叫UTF-8 签名，UTF-8不需要BOM来表明字节顺序，但可以用BOM来表明编码方式。当文本程序读取到以 EF BB BF开头的字节流时，就知道这是UTF-8编码了。Windows就是使用BOM来标记文本文件的编码方式的。

### 补充

`"ZERO WIDTH NO-BREAK SPACE"`字符的UCS编码为FEFF（假设为大端），对应的UTF-8编码为 EF BB BF

即以EF BB BF开头的字节流可表明这是段UTF-8编码的字节流。但如果文件本身就是UTF-8编码的，EF BB BF这三个字节就毫无用处了。　所以，可以说BOM的存在对于UTF-8本身没有任何作用。


## UTF-8文件中包含BOM的坏处

### 1、在linux上执行脚本报错

最近开发过程中遇到，windows下编写的SQL/shell脚本文件，在linux下执行时，总是报错。

在文件的开头，无论是使用中文注释还是英文注

网上没有找到类似问题的解决办法，且文件编码确认已经更改为utf-8。
最后查看一下BOM与 no BOM的区别，尝试更改为no BOM，居然就没有再出现错误。

修改完成后，无论使用中文，还是英文，或者去掉注释，都能正常执行。

### 2、对php的影响

php在设计时就没有考虑BOM的问题，也就是说他不会忽略UTF-8编码的文件开头的那三个EF BB BF字符，直接当做文本进行解析，导致解析错误。



## 血泪建议：UTF-8最好不要带BOM

「UTF-8」和「带 BOM 的 UTF-8」的区别就是有没有 BOM。即文件开头有没有 U+FEFF。

Linux中查看BOM的方法：使用less命令，其它命令可能看不到效果：会发现词语之前多了一个<U+FEFF>。

### 2、UTF-8去除BOM的方法


#### 2.1

- 1) vim打开文件

- 2) 执行 `:set nobomb`

- 3) 保存 `:wq`

#### 2.2

```shell
dos2unix filename
```

将windows格式文件转为Unix、Linux格式文件。该命令不仅可将windows文件的换行符\r\n转为Unix、Linux文件的换行符\n，还可以将UTF-8 Unicode (with BOM)转换为UTF-8 Unicode.

PS:

还有些特殊情况，1个UTF-8 Unicode (with BOM)文件中包含两个<U+FEFF>，要执行两次才能将<U+FEFF>完全去除！

Windows下，使用NotePad++/vscode等编辑器打开文件，然后选择“编码”，再选择“以UTF-8无BOM格式编码”，最后重新保存文件即可
