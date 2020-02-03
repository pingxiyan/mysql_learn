#include "call_mysql.hpp"
#include "call_mysql_impl.hpp"

CCallMysql::PTR createCallMySQLPtr(const std::string& ip, const int& port,
	const std::string& usr, const std::string& pw, const std::string& dbName) {
	return std::make_shared<CCallMysqlImpl>(ip, port, usr, pw, dbName);
}