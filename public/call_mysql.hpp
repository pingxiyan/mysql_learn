#pragma once
#include <iostream>
#include <map>

#if defined(_WIN32)
#ifdef IMPLEMENT_MYSQL_API
#define CALLMYSQL(type) extern "C"   __declspec(dllexport) type __cdecl
#define CALLMYSQL_CPP(type)	__declspec(dllexport) type __cdecl
#define CALLMYSQL_CLASS(type)       __declspec(dllexport) type
#else
#define CALLMYSQL(type) extern "C"  __declspec(dllimport) type __cdecl
#define CALLMYSQL_CPP(type)	__declspec(dllimport) type __cdecl
#define CALLMYSQL_CLASS(type)   __declspec(dllimport) type
#endif
#else
#ifdef IMPLEMENT_MYSQL_API
#define CALLMYSQL(type) extern "C" __attribute__((visibility("default"))) type
#define CALLMYSQL_CPP(type) __attribute__((visibility("default"))) type
#define CALLMYSQL_CLASS(type) __attribute__((visibility("default"))) type
#else
#define CALLMYSQL(type)   extern "C"   type
#define CALLMYSQL_CPP(type)   type
#define CALLMYSQL_CLASS(type)   type
#endif
#endif

class CCallMysql
{
public:
	CCallMysql() = delete;
	CCallMysql(const std::string& ip, const int& port, const std::string& usr, const std::string& pw):
		_ip(ip), _port(port), _usr(usr), _pw(pw) {
		connect();
	}
	~CCallMysql() {
		disconnect();
	}

	using PTR = std::shared_ptr<CCallMysql>;
	static PTR createPtr(const std::string& ip, const int& port, const std::string& usr, const std::string& pw) {
		return std::make_shared<CCallMysql>(ip, port, usr, pw);
	}
	
	CALLMYSQL_CPP(void) check_machine(const std::string& machine_id, std::string login_tm, int& ok);

	CALLMYSQL_CPP(bool) get_student(const std::string& card_id, std::map<std::string, std::string>& mapStudentInfor);

	CALLMYSQL_CPP(bool) save_rec_rslt_to_db(const std::string& card_id, const std::string& machine_id,
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
		const int& height);


private:
	CALLMYSQL_CPP(bool) connect();
	CALLMYSQL_CPP(bool) disconnect();

	std::string _ip;
	int _port = 3306;
	std::string _usr;
	std::string _pw;
};

#define COUT_DEBUG(INF) std::cout << __FUNCTION__ << " : " << __LINE__  << " :: " << INF << std::endl