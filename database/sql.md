从功能上划分，SQL 语言可以分为DDL,DML和DCL三大类。
1. DDL（Data Definition Language） 
    数据定义语言，用于定义和管理 SQL 数据库中的所有对象的语言 ；
    CREATE---创建表
    ALTER---修改表
    DROP---删除表
2. DML（Data Manipulation Language） 
    数据操纵语言，SQL中处理数据等操作统称为数据操纵语言 ； 
    INSERT---数据的插入
    DELETE---数据的删除
    UPDATE---数据的修改
    SELECT---数据的查询
3. DCL（Data Control Language） 
    数据控制语言，用来授予或回收访问数据库的某种特权，并控制 数据库操纵事务发生的时间及效果，对数据库实行监视等；
    GRANT--- 授权。
     ROLLBACK---回滚。
     COMMIT--- 提交。

4. 提交数据有三种类型：显式提交、隐式提交及自动提交。
   (1) 显式提交
   用 COMMIT 命令直接完成的提交为显式提交。
   (2) 隐式提交
   用 SQL 命令间接完成的提交为隐式提交。这些命令是：
   ALTER，AUDIT，COMMENT，CONNECT，CREATE，DISCONNECT，DROP，EXIT，GRANT，NOAUDIT，QUIT，REVOKE，RENAME。
   (3) 自动提交
   若把 AUTOCOMMIT 设置为 ON ，则在插入、修改、删除语句执行后，系统将自动进行提交，这就是自动提交。其格式为：
	    SQL>SET AUTOCOMMIT ON ；
     COMMIT / ROLLBACK这两个命令用的时候要小心。 COMMIT / ROLLBACK 都是用在执行 DML语句（INSERT / DELETE / UPDATE / SELECT ）之后的。DML 语句，执行完之后，处理的数据，都会放在回滚段中（除了 SELECT 语句），等待用户进行提交（COMMIT）或者回滚 （ROLLBACK），当用户执行 COMMIT / ROLLBACK后，放在回滚段中的数据就会被删除。
    （SELECT 语句执行后，数据都存在共享池。提供给其他人查询相同的数据时，直接在共享池中提取，不用再去数据库中提取，提高了数据查询的速度。）
      所有的 DML 语句都是要显式提交的，也就是说要在执行完DML语句之后，执行 COMMIT 。而其他的诸如 DDL 语句的，都是隐式提交的。也就是说，在运行那些非 DML 语句后，数据库已经进行了隐式提交，例如 CREATE TABLE，在运行脚本后，表已经建好了，并不在需要你再进行显式提交。
在提交事务（commit）之前可以用rollback回滚事务。

来自 <https://blog.csdn.net/ying_593254979/article/details/12134629> 
