#include "call_mysql.hpp"
#include "mysql/jdbc.h"
#include "charset_cvt.hpp"

/**
 * Show student table.
 */
inline void show_one_student_msg(sql::ResultSet *res) {
	std::cout << "id:" << res->getUInt("id") << std::endl;
	std::cout << "姓名:" << res->getString("姓名").asStdString()<< std::endl;
	std::cout << "性别:" << res->getString("性别").asStdString() << std::endl;
}

bool CCallMysql::connect() {
	sql::mysql::MySQL_Driver *driver = nullptr;
	sql::Connection *con = nullptr;

	driver = sql::mysql::get_mysql_driver_instance();

	sql::Statement *stmt = nullptr;
	sql::ResultSet  *res = nullptr;

	try {
		// "tcp://127.0.0.1:3306"
		// sql::Connection::reconnect()
		std::string strIpPort;
		_ip = "192.168.2.126";
		strIpPort = std::string("tcp://") + _ip + std::string(":") + std::to_string(_port);
		con = driver->connect(strIpPort, _usr, _pw);
		if (!con->isValid()) {
			COUT_DEBUG("Connect is invalid");
			return false;
		}
		/* Connect to MySQL imimdb database */
		con->setSchema("imimdb");

		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT * FROM imimdb.testtable");
		while (res->next()) {
			std::cout << "id: " << res->getUInt("id") << std::endl;
			std::cout << "lable: " << utf8_to_gbk(res->getString("label")) << std::endl;
			std::cout << "lable: " << res->getString("label") << std::endl;
			//show_one_student_msg(res);
		}

	}
	catch (sql::SQLException &e){
		COUT_DEBUG(e.what());
		COUT_DEBUG(e.getErrorCode());
		COUT_DEBUG(e.getSQLState());
	}

	if(res) delete res;
	if(stmt) delete stmt;

	delete con;
	return true;
}

bool CCallMysql::disconnect() {
	return false;
}

void CCallMysql::check_machine(const std::string& machine_id, std::string login_tm, int& ok) {
	std::cout << __FUNCTION__ << std::endl;
}

bool CCallMysql::get_student(const std::string& card_id, std::map<std::string, std::string>& mapStudentInfor) {
	
	return false;
}

bool CCallMysql::save_rec_rslt_to_db(const std::string& card_id, const std::string& machine_id,
	const std::string& rec_time,
	const std::string& eye_imag_name,
	const std::string& eye_rslt,
	const std::string& mouth_img_name,
	const std::string& mouth_rslt,
	const std::string& face_img_name,
	const std::string& face_rslt,
	const std::string& hands_img_name,
	const std::string& hands_rslt,
	const std::string& parent_img_name,
	const float& temprature,
	const int& height) {

	return false;
}