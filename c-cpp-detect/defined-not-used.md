# 关于c++(clang): static const T *  已定义但未使用

## 代码形式

在每个标头(.h)中有类似下边这样的定义

```cpp
static const char * one_time_param = "ABCDEFG";
```

并且在其他代码的位置使用了此变量，但使用clang编译器(版本16)编译时会提示 `defined but not used`
变量明明使用了仍然会有这样的警告。

虽然可以使用 `-Wno-unused-parameter` 编译器标志，我们可以取消这些警告。
但是，这也会抑制一些其他未使用的参数，这些参数可能需要引起注意。

## 解决方案1

在这种情况下，它通常也是const指针，使用下边的定义

```cpp
static const char * const one_time_param = "ABCDEFG";
```

gcc编译器

`__attribute__((used))`

## 解决方案2（推荐）

要定义此变量，请使用数组而不是char *，以便仅存储数据，而不存储指针和数据：

```cpp
static const char one_time_param[] = "ABCDEFG";
```

- 为避免警告，您必须使符号在文件外部可见。
- 反过来，这意味着您必须使变量名唯一。

在GCC的发展过程中，结合使用命令行的经验：*除非得到声明并定义了变量，否则我会得到警告*


```cpp
extern const char jlss_id_filename_c[];
const char jlss_id_filename_c[] = "@(#)$Id$";
```
删除该声明后不会收到编译器警告

```c
gcc -m64 -g -O -std=c99 -pedantic -Wall -Wshadow -Wpointer-arith -Wcast-qual \\
-Wstrict-prototypes -Wmissing-prototypes -o al al.c
```

运行`what`命令时，没有任何标识输出。

## 解决方案3

```c
#define DECLARE_ONETIME_CONST(name, value) \\
    static const char* name = (value); \\
    static const char nowarning_##name = name[0];

// use the macro
DECLARE_ONETIME_CONST(one_time_param, "ABCDEFG");
```