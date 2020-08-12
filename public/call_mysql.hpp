#pragma once
#include <iostream>
#include <map>
#include <memory>

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

#include "table_struct.hpp"

class CCallMysql
{
public:
	using PTR = std::shared_ptr<CCallMysql>;
	
	/**
	 * Check machine.
	 */
	virtual void check_machine(const std::string& machine_id, std::string login_tm, int& ok) = 0;

	/**
	 * Get student from database by card_id.
	 */
	virtual bool get_student(const std::string& card_id, TableStudent& outStudent) = 0;

	/**
	 * Save analysis results to database.
	 */
	virtual bool save_rec_rslt_to_db(const TableAnaRslt& anaRslt) = 0;
};

CALLMYSQL_CPP(CCallMysql::PTR) createCallMySQLPtr(const std::string& ip, const int& port, 
	const std::string& usr, const std::string& pw, const std::string& dbName);

#define COUT_DEBUG(INF) std::cout << __FUNCTION__ << " : " << __LINE__  << " :: " << INF << std::endl