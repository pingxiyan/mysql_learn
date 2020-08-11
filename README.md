# mysql_learn

# How to install mysql
Download: https://dev.mysql.com/downloads/mysql/

#### Linux
Install guide: https://dev.mysql.com/doc/refman/8.0/en/binary-installation.html   <br>

MySQL connector: <br>
https://dev.mysql.com/downloads/connector/cpp/


#### Windows

Dependencies
1. mysql cpp connect dependency: [boost](https://nchc.dl.sourceforge.net/project/boost/boost-binaries/1.67.0/boost_1_67_0-msvc-14.1-64.exe) Download and extract to default path.

# Database tools: Dbeaver
You can use Dbeaver to create database and table.

# Issues
#### Chinese charset

MySQL database use utf-8 charset. So your app also pass utf-8 to database. 	<br>
However windows app default adopt gbk code, so we must convert utf-8 to gbk to display. <br>
In our sample, we have provided convert functions. <br>

#### Remote login to database.
MySQL default don't allow remote login to database(Only support localhost login).	<br>
We can do setting to allow extra PC to login as follow:	<br>

	cd C:\Windows\System32\cmd.exe
	mysql -u root -p
	# input you password
	use mysql
	update user set host = '%' where user = 'root';
	select host, user from user;
	
	restart MySQL (Take care)

Detail please [refer](https://www.cnblogs.com/xxx-xxx/p/7492288.html)
