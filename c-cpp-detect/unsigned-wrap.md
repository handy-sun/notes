#  无符号类型的环绕和有符号类型的溢出问题

`C11`第6.2.5节第89段：

*A computation involving unsigned operands can never overflow, because a result that cannot be represented by the resulting unsigned integer type is reduced modulo the number that is one greater than the largest value that can be represented by the resulting type.*

这个行为更通俗的说法是无符号整数将会回绕。
如果无符号整数运算的结果值无法用这种整数的底层表示形式表示，它就会回绕。

同理的，整数溢出是一种**未定义的行为**。因此，编译器在处理有符号整数溢出时具有很多选择。例如一种实现方式就是将有符号整数定义为具有求模行为的编译器就不需要检测整数溢出。编译器也可以捕捉有符号算术溢出或者假设溢出永远不会发生，并相应地生成代码。例如，一种编译器可能定义一个在局部范围内不会发生溢出的有符号整数循环控制变量并生成有效的代码，然而相同的编译器可能定义一个使用类似的上下文的全局变量会发生回绕。

下表给出了哪些操作符可能会导致回绕或溢出：

---

| Operator | Wrap | Operator | Wrap | Operator  | Wrap | Operator | Wrap |
| :------: | :--: | :------: | :--: | :-------: | :--: | :------: | :--: |
|   `+`    | Yes  |   `-=`   | Yes  |   `<<`    | Yes  |   `<`    |  No  |
|   `-`    | Yes  |   `*=`   | Yes  |   `>>`    |  No  |   `>`    |  No  |
|   `*`    | Yes  |   `/=`   | Yes  |    `&`    |  No  |   `>=`   |  No  |
|   `/`    | Yes  |   `%=`   | Yes  |    `|`    |  No  |   `<=`   |  No  |
|   `%`    | Yes  |  `<<=`   | Yes  |    `^`    |  No  |   `==`   |  No  |
|   `++`   | Yes  |  `>>=`   |  No  |    `~`    |  No  |   `!=`   |  No  |
|   `--`   | Yes  |   `&=`   |  No  |    `!`    |  No  |   `&&`   |  No  |
|   `=`    |  No  |   `\|=`   |  No  | `unary +` |  No  |   `\|\|`   |  No  |
|   `+=`   | Yes  |   `^=`   |  No  | `unary -` | Yes  |   `?:`   |  No  |
