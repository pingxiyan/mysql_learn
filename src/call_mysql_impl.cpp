#include "call_mysql_impl.hpp"

/**
 * @Brief Only for debug. Show student table.
 */
inline void show_one_student_msg(sql::ResultSet *res) {
	std::cout << "id:" << res->getUInt("id") << std::endl;
	std::cout << "姓名:" << utf8_to_gbk(res->getString(gbk_to_utf8("姓名")).asStdString()) << std::endl;
	std::cout << "性别:" << utf8_to_gbk(res->getString(gbk_to_utf8("性别")).asStdString()) << std::endl;
}

bool CCallMysqlImpl::reconnect() {
	return false;
}

bool CCallMysqlImpl::connect() {
	if (con) {
		disconnect();
	}
	driver = sql::mysql::get_mysql_driver_instance();
	try {
		// "tcp://127.0.0.1:3306"
		// sql::Connection::reconnect()
		std::string strIpPort;
		//_ip = "192.168.2.126";
		strIpPort = std::string("tcp://") + _ip + std::string(":") + std::to_string(_port);
		//strIpPort = gbk_to_utf8(strIpPort);
		con = driver->connect(strIpPort, _usr, _pw);
		if (!con->isValid()) {
			COUT_DEBUG("Connect is invalid");
			return false;
		}
		/* Connect to MySQL imimdb database */
		con->setSchema(_dbName);
	}
	catch (sql::SQLException &e){
		COUT_DEBUG(e.what());
		COUT_DEBUG(e.getErrorCode());
		COUT_DEBUG(e.getSQLState());
	}

	return true;
}

bool CCallMysqlImpl::disconnect() {
	return false;
}

void CCallMysqlImpl::check_machine(const std::string& machine_id, std::string login_tm, int& ok) {
	std::cout << __FUNCTION__ << std::endl;
	sql::Statement *stmt = nullptr;
	sql::ResultSet  *res = nullptr;

	//stmt = con->createStatement();
	//res = stmt->executeQuery("SELECT * FROM imimdb.testtable");

	//while (res->next()) {
	//	std::cout << "id: " << res->getUInt("id") << std::endl;
	//	std::cout << "lable: " << utf8_to_gbk(res->getString("label")) << std::endl;
	//	std::cout << "lable: " << res->getString("label") << std::endl;
	//	//show_one_student_msg(res);
	//}

	if (stmt) delete stmt;
	if (res) delete res;
}

static void db_to_struct(sql::ResultSet  *res, TableStudent& outStudent) {
//#define AssignValStr(mapVar, itemVal) mapVar["itemVal"] = utf8_to_gbk(res->getString(gbk_to_utf8("itemVal")))
#define AssignValStr(itm, itemVal) itm = utf8_to_gbk(res->getString(gbk_to_utf8(itemVal)))
	AssignValStr(outStudent.name, "姓名");
	AssignValStr(outStudent.sex, "性别");
	AssignValStr(outStudent.studentClass, "班级");
	AssignValStr(outStudent.birthday, "出生日期");
	AssignValStr(outStudent.address, "住址");
	AssignValStr(outStudent.parentPhone1, "家长电话1");
	AssignValStr(outStudent.wechatOpenId1, "微信openid1");

	outStudent.id = res->getUInt("id");
	outStudent.school_id = res->getInt(gbk_to_utf8("学校id"));
}

bool CCallMysqlImpl::get_student(const std::string& card_id, TableStudent& outStudent) {
	sql::Statement *stmt = nullptr;
	sql::ResultSet  *res = nullptr;

	stmt = con->createStatement();
	std::string sql = "SELECT * FROM 学生 WHERE card_id1=" + card_id + " or card_id2=" + card_id;
#ifdef _WIN32
	sql = gbk_to_utf8(sql);
#endif
	res = stmt->executeQuery(sql);

	while (res->next()) {
		//show_one_student_msg(res);
		db_to_struct(res, outStudent);
	}

	if (stmt) delete stmt;
	if (res) delete res;

	return false;
}

bool CCallMysqlImpl::save_rec_rslt_to_db(const TableAnaRslt& anaRslt) {

	std::string strSQL = "INSERT INTO 识别结果(学生id, 识别时间, 眼睛图片路径, 眼睛结果, \
		口腔图片路径, 口腔结果,	\
		脸部图片路径, 脸部结果,	\
		手部图片路径, 手部结果,	\
		接送人员照片路径, 体温, 身高, 体重)	\
		VALUES(";
	strSQL += std::to_string(anaRslt.student_id) + ", '" + anaRslt.rec_time + "', '" +
		anaRslt.eye_img_path + "', '" + anaRslt.eye_rslt + "','" +
		anaRslt.mouth_img_path + "','" + anaRslt.mouth_rslt + "','" +
		anaRslt.face_img_path + "','" + anaRslt.face_rslt + "','"  +
		anaRslt.hands_img_path + "','" + anaRslt.hands_rslt + "','" +
		anaRslt._img_path + "'," + std::to_string(anaRslt.temperature) + ", " +
		std::to_string(anaRslt.height) + ", " + std::to_string(anaRslt.weight) + ")";

	strSQL = gbk_to_utf8(strSQL);

	sql::Statement *stmt;
	stmt = con->createStatement();
	stmt->execute(strSQL);
	delete stmt;

	return false;
}