#pragma once
#include <iostream>
#include <map>
#include "call_mysql.hpp"

#include "mysql/jdbc.h"
#include "call_mysql.hpp"
#include "charset_cvt.hpp"

class CCallMysqlImpl : public CCallMysql
{
public:
	CCallMysqlImpl() = delete;
	CCallMysqlImpl(const std::string& ip, const int& port, 
		const std::string& usr, const std::string& pw, 
		const std::string& dbName) :
		_ip(ip), _port(port), _usr(usr), _pw(pw), _dbName(dbName) {
		try {
			connect();
		}
		catch (sql::SQLException& e) {
			COUT_DEBUG(e.what());
			COUT_DEBUG(e.getErrorCode());
			COUT_DEBUG(e.getSQLState());
		}
	}
	~CCallMysqlImpl() {
		disconnect();
#define DEL_VAR(var) if(var) {delete var; var = nullptr;}
		DEL_VAR(con)
		DEL_VAR(driver)
	}
	
	void check_machine(const std::string& machine_id, std::string login_tm, int& ok);
	bool get_student(const std::string& card_id, TableStudent& outStudent);
	bool save_rec_rslt_to_db(const TableAnaRslt& anaRslt);
private:
	bool connect();
	bool reconnect();
	bool disconnect();

private:
	std::string _ip = "localhost";
	int _port = 3306;
	std::string _usr = "root";
	std::string _pw = "imim";
	std::string _dbName = "imimdb";

	sql::mysql::MySQL_Driver *driver = nullptr;
	sql::Connection *con = nullptr;
};