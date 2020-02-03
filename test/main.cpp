#include <thread>
#include <chrono>
#include <iostream>

#include <call_mysql.hpp>
#include <ctime>
#include <chrono>

std::string get_current_tm() {
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	time_t tt = std::chrono::system_clock::to_time_t(now);
	tm local_tm = *localtime(&tt);

	std::string str_cur_tm = std::to_string(local_tm.tm_year + 1900) + "-" +
		std::to_string(local_tm.tm_mon + 1) + "-" +
		std::to_string(local_tm.tm_mday) + " " +
		std::to_string(local_tm.tm_hour) + ":" +
		std::to_string(local_tm.tm_min) + ":" +
		std::to_string(local_tm.tm_sec);
	return str_cur_tm;
}

int main(int argc, char** argv) {
	std::string strip = "localhost";
	int port = 3306;
	std::string username = "root";
	std::string pw = "imim";
	std::string dbName = "imimdb";
	if(argc == 2 && argv[1] == std::string("-h")) {
		std::cout << "Param guide:" << std::endl;
		std::cout << "Agrv[1]: ip [localhost]" << std::endl;
        std::cout << "Agrv[2]: port [3306] " << std::endl;
		std::cout << "Agrv[3]: username [root] " << std::endl;
		std::cout << "Agrv[4]: password [imim] " << std::endl;
		std::cout << "Agrv[5]: database name [imimdb] " << std::endl;
        std::cout << "$ ./mysql_test localhost 3306 root imim imimdb" << std::endl;
		return EXIT_SUCCESS;
	}
    else  if(argc == 6) {
		strip = std::string(argv[1]);
		port = std::atoi(argv[2]);
		username = std::string(argv[3]);
		pw = std::string(argv[4]);
		dbName = std::string(argv[5]);
	}

	std::cout << "Current all parameter as follow: " << std::endl;
    std::cout << "strip = " << strip.c_str() << std::endl;
	std::cout << "port = " << port << std::endl;
	std::cout << "username = " << username.c_str() << std::endl;
	std::cout << "pw = " << pw.c_str() << std::endl;
	std::cout << "dbName = " << dbName.c_str() << std::endl;
	
	COUT_DEBUG("Start connect database");
	CCallMysql::PTR mysqlPtr = createCallMySQLPtr(strip, port, username, pw, dbName);

	int bOk = false;
	mysqlPtr->check_machine("", "", bOk);

	COUT_DEBUG("**********Start query student**********");
	TableStudent outStudent;
	mysqlPtr->get_student("0000000003", outStudent);

	COUT_DEBUG("Show query information:");
	std::cout << "=================================" << std::endl;
#define ShowItem(itm) std::cout << #itm << " = " << itm << std::endl;
	ShowItem(outStudent.id);
	ShowItem(outStudent.name);
	ShowItem(outStudent.sex);
	ShowItem(outStudent.birthday);
	ShowItem(outStudent.studentClass);
	ShowItem(outStudent.parentPhone1);
	ShowItem(outStudent.wechatOpenId1);
	ShowItem(outStudent.school_id);
	std::cout << "=================================" << std::endl;

	COUT_DEBUG("**********Insert one analysis result to database '识别结果' table**********");
	COUT_DEBUG("Note: don't insert 2 same record.");
	TableAnaRslt anaRslt;
	static int g_id = 3;
	anaRslt.student_id = g_id++;
	anaRslt.rec_time = get_current_tm();
	anaRslt.eye_img_path = "test_eye_path";
	anaRslt.eye_rslt = "red";
	anaRslt.mouth_img_path = "tmp";
	anaRslt.mouth_rslt = "t";
	anaRslt.face_img_path = "tmp";
	anaRslt.face_rslt = "t";
	anaRslt.hands_img_path = "tmp";
	anaRslt.hands_rslt = "t";
	anaRslt.height = 110;
	anaRslt.temperature = 36.5;
	anaRslt.weight = 23;
	anaRslt._img_path = "p";
	mysqlPtr->save_rec_rslt_to_db(anaRslt);

	COUT_DEBUG("finish all");
	return EXIT_SUCCESS;
}
