#include "call_mysql.hpp"


bool CCallMysql::connect() {
	return false;
}

bool CCallMysql::disconnect() {
	return false;
}

void CCallMysql::check_machine(const std::string& machine_id, std::string login_tm, int& ok) {

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