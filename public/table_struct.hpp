#pragma once
#include <string>

/**
 *@Brief Should keep same with database table "学生".
 */
typedef struct tagTableStudent
{
	int id = 0;
	std::string name;
	std::string sex;
	std::string birthday;
	std::string address;
	std::string parentPhone1;
	std::string parentPhone2;
	int school_id = 0;
	std::string admissionTime;
	std::string studentClass;
	std::string wechatOpenId1;
	std::string wechatOpenId2;
	std::string parentUserName;
	std::string parentPw;
}TableStudent;

/**
 *@Brief Database table "学生".
 */
typedef struct tagTableAnaRslt
{
	int student_id = 0;
	std::string rec_time;
	std::string eye_img_path;
	std::string eye_rslt;
	std::string mouth_img_path;
	std::string mouth_rslt;
	std::string face_img_path;
	std::string face_rslt;
	std::string hands_img_path;
	std::string hands_rslt;
	std::string _img_path;
	float temperature = 0;
	int height = 0;
	int weight = 0;
}TableAnaRslt;