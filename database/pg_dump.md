## pg_dump 备份和恢复数据

1. 只导出postgres数据库的数据，不包括模式 -s

    ```sh
    pg_dump -U postgres -f /postgres.sql -s postgres(数据库名)
    ```

2. 导出postgres数据库（包括数据）

    ```sh
    pg_dump -U postgres -f /postgres.sql  postgres(数据库名)
    ```

3. 导出postgres数据库中表test01的数据

    ```sh
    create database "test01" with owner="postgres" encoding='utf-8';(单引号，双引号不能错)
    pg_dump -U postgres -f /postgres.sql -t test01 postgres(数据库名)
    ```

4. 导出postgres数据库中表test01的数据,以insert语句的形式

    ```sh
    pg_dump -U postgres -f /postgres.sql -t test01 --column-inserts postgres(数据库名)
    ```

5. 恢复数据到数据库

    ```sh
    psql -U postgres -f /postgres.sql bk01
    ```
