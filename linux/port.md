# <font size='5'>1.Linux 常用服务协议的默认端口号</font>

|服务名|全称|端口号|
|--|--|--|
| FTP | File Transfer Protocol | 21
| SSH | Secure Shell | 22
| Telnet | teletype network | 23
| SMTP | Simple Mail Transfer Protocol | 25
| DNS | Domain Name System | 53
| TFTP | Trivial File Transfer Protocol | 69
| HTTP | Hypertext Transfer Protocol | 80/8080
| POP3 | Post Office Protocol 3 | 110
| IMAP | Internet Message Access Protocol | 143
| HTTPS | Hypertext Transfer Protocol Secure | 443
| SMB | Server Message Block | 445
| RDP | Remote Desktop Protocol | 3389
| VNC | Virtual Network Console | 5900+n

# <font size='5'>2.Linux 常见服务器程序默认端口号</font>

|程序名|说明|端口号|
|--|--|--|
| MySQL | Database Server | 3306
| PostgreSQL | Database Server | 5432
| Apache | Web Server| 80
| Nginx | Web Server| HTTP:80 HTTPS: 443
| Tomcat | Web Application Server | 8080
| Redis | Database Server | 6379
| php-fpm | PHP FastCGI Process Manager | 9000


# <font size='5'>3. Samba</font>

Samba通常使用以下端口进行不同的功能：

- 137/UDP：NetBIOS名称服务
- 138/UDP：NetBIOS数据报服务
- 139/TCP：NetBIOS会话服务（也称为SMB会话）
- **445/TCP：Server Message Block（SMB）协议（也称为CIFS协议）的使用端口**

