
## std::string 长度问题


std::string 完全能够存储空值。但因为 const char* 不是，如下

```cpp
std::string a("\x00");
```

非常简单地构造了一个 const char*，从中创建 std::string字符串.
将创建一个仅包含空字符的常量 C 字符串，后跟空终止符。但是 C 字符串不知道它们有多长；所以字符串认为它一直运行到第一个空终止符，这是第一个字符。因此，创建了一个长度为零的字符串。


```cpp
std::string b("");
b.push_back('\0');
```

std::string 是 null-clean。字符 (\0) 也可以是零字节。所以，在这里，没有什么能阻止我们正确读取数据结构。 b 的长度为 1。

通常要避免构造包含空字符的 C 字符串。如果将文件中的输入直接读入 std::string 或确保一次推送一个字符，可以获得所需的结果。如果确实需要一个带有空字符的常量字符串，请考虑使用其他标记字符而不是 \0 然后(如果真的需要它)将这些字符替换为 '\0' 加载到 std::string 后。

在Stack Overflow上有一个类似的问题： https://stackoverflow.com/questions/48255276/
