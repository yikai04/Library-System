#pragma once	

#define LOGIN_SUCESSFUL 0
#define INVALID_USERNAME 1
#define INVALID_ID 2
#define INVALID_EMAIL 3
#define INVALID_NAME 4
#define WRONG_PASSWORD 5
#define SQLITE_DATABASE_ERROR 6
#define REGISTER_SUCESSFUL 7

#include "Dependencies/sqlite3/sqlite3.h"
#include "Dependencies/Bcrypt/BCrypt.hpp"
#include <string>
#include "Config.h"

constexpr const char* CREATE_USER_INFO_TABLE_SQLCMD = "CREATE TABLE IF NOT EXISTS `user_info` ( \
														`id` INT(11) NOT NULL , \
														`name` varchar(200) DEFAULT NULL , \
														`username` varchar(50) DEFAULT NULL , \
														`password` varchar(100) DEFAULT NULL , \
														`role` varchar(50) DEFAULT 'Student' , \
														`register_date` date DEFAULT NULL , \
														`gender` varchar(1) DEFAULT NULL , \
														`email` varchar(50) DEFAULT NULL , \
														`borrow_volume` int(10) DEFAULT '0', \
														`del_flg` int(1) DEFAULT '0' , \
														PRIMARY KEY(`id`) \
														);";

constexpr const char* CREATE_BOOK_INFO_TABLE_SQLCMD = "CREATE TABLE IF NOT EXISTS `book_info` ( \
														`id` INT(11) NOT NULL , \
														`book_name` varchar(200) DEFAULT NULL , \
														`author` varchar(50) DEFAULT NULL , \
														`publisher` varchar(50) DEFAULT NULL , \
														`category` varchar(50) DEFAULT '其他' , \
														`publish_date` date DEFAULT NULL , \
														`pages` int(10) DEFAULT '0' , \
														`total_book` INT(10) DEFAULT '1' , \
														`remain_book` INT(10) DEFAULT '1' , \
														`price` double DEFAULT '1' , \
														`description` varchar(15000) DEFAULT '' , \
														`img_url` varchar(200) DEFAULT NULL , \
														`borrow_volume` INT(10) DEFAULT '0' , \
														`del_flg` int(1) DEFAULT '0' , \
														PRIMARY KEY(`id`) \
														);";

constexpr const char* CREATE_BORROW_INFO_TABLE_SQLCMD = "CREATE TABLE IF NOT EXISTS `borrow_info` ( \
														`id` INT(11) NOT NULL , \
														`book_id` INT(11) DEFAULT NULL , \
														`user_id` INT(11) DEFAULT NULL , \
														`borrow_date` date DEFAULT NULL , \
														`due_date` date DEFAULT NULL , \
														`return_date` date DEFAULT NULL , \
														PRIMARY KEY(`id`) \
														);";

extern sqlite3* mDatabase;

bool loadDataBase();
void closeDataBase();
bool insertDatas(const char* filename);

//std::string wstringToString(std::wstring wstr);
std::string wstring_to_string(const std::wstring& wstr);

std::string hashPassword(const std::string& password);
bool validatePassword(const std::string& password, const std::string& hash);

//class Date
//{
//	public:
//		Date();
//		Date(const Date& date);
//		Date(std::string date);
//		Date(std::wstring date);
//		Date operator=(const Date& date);
//		~Date();
//		
//		void setDate(std::string date);
//		void setDate(std::wstring date);
//		void setTodatyDate();
//		void addDays(int days);
//
//		std::string getDate();
//		std::wstring getWDate();
//		int getYear();
//		int getMonth();
//		int getDay();
//
//	private:
//		void _stringToDate(std::string date);
//		void _stringToDate(std::wstring date);
//		std::string _dateToString();
//		std::wstring _dateToWString();
//		int _year;
//		int _month;
//		int _day;
//};

class Date {
	public:
		Date();
		Date(const Date& date);
		Date(std::string date);
		Date(std::wstring date);
		Date& operator=(const Date& date);
		~Date();
		bool operator==(const Date& date) const;
		bool operator!=(const Date& date) const;
		bool operator<(const Date& date) const;
		bool operator>(const Date& date) const;
		bool operator<=(const Date& date) const;
		bool operator>=(const Date& date) const;
		void setDate(std::string date);
		void setDate(std::wstring date);
		void setTodayDate();
		void addDays(int days);
		void addMonths(int months);
		void addYears(int years);

		std::string getDate();
		std::wstring getWDate();
		int getYear();
		int getMonth();
		int getDay();

	private:
		std::tm dateStruct;
		bool isNullDate;
		void parseDateString(const std::string& date);
		void parseWDateString(const std::wstring& date);
		std::string formatDate(const std::tm& tm);
		std::wstring formatWDate(const std::tm& tm);
		int daysInMonth(int year, int month);
};