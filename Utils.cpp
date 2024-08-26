#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <Windows.h>

sqlite3* mDatabase;

bool loadDataBase()
{
	int rc;
	rc = sqlite3_open(DATABASE_FILE, &mDatabase);

	if (rc) {
		std::cout << "Can't open database : " << sqlite3_errmsg(mDatabase) << std::endl;
		return false;
	}

	//create user_info table
	rc = sqlite3_exec(mDatabase, CREATE_USER_INFO_TABLE_SQLCMD, NULL, NULL, NULL);

	if (rc) {
		std::cout << "Failed to create user table: " << sqlite3_errmsg(mDatabase) << std::endl;
	}

	//create book_info table
	rc = sqlite3_exec(mDatabase, CREATE_BOOK_INFO_TABLE_SQLCMD, NULL, NULL, NULL);

	if (rc) {
		std::cout << "Failed to create book table: " << sqlite3_errmsg(mDatabase) << std::endl;
	}

	//create borrow_info table
	rc = sqlite3_exec(mDatabase, CREATE_BORROW_INFO_TABLE_SQLCMD, NULL, NULL, NULL);

	if (rc) {
		std::cout << "Failed to create borrow table: " << sqlite3_errmsg(mDatabase) << std::endl;
	}

	return true;
}

void closeDataBase()
{
	sqlite3_close(mDatabase);
}

bool insertDatas(const char* filename)
{
    int rc = 1;
    char sqlCmd[10000];
    std::ifstream fin(filename, std::ios_base::in);

    if (!fin) {
        std::cerr << "Can't open " << filename << std::endl;
        return false;
    }

    while (fin.getline(sqlCmd, 10000)) {

        rc = sqlite3_exec(mDatabase, sqlCmd, NULL, NULL, NULL);

        if (rc) {
            std::cout << "Failed to add data: " << sqlite3_errmsg(mDatabase) << std::endl;
            return false;
        }

    }

    return true;
}


//std::string wstringToString(std::wstring wstr)
//{
//	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
//	return converter.to_bytes(wstr);
//}

std::string wstring_to_string(const std::wstring& wstr) {
	int size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
	if (size == 0) {
		throw std::runtime_error("WideCharToMultiByte failed");
	}

	// Allocate a buffer and perform the conversion
	std::string str(size - 1, '\0'); // size includes null terminator, so use size - 1
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], size, nullptr, nullptr);
	return str;
}



Date::Date():
    _year(-1),
    _month(-1),
    _day(-1)
{

}

Date::Date(const Date& date)
{
	_year = date._year;
	_month = date._month;
	_day = date._day;
}

Date::Date(std::string date)
{
	_stringToDate(date);
}

Date::Date(std::wstring date)
{
    _stringToDate(date);
}

Date Date::operator=(const Date& date)
{
	_year = date._year;
	_month = date._month;
	_day = date._day;
	return *this;
}

Date::~Date()
{

}

void Date::setDate(std::string date)
{
	_stringToDate(date);
}

void Date::setDate(std::wstring date)
{
	_stringToDate(date);
}

void Date::setTodatyDate()
{
	auto now = std::chrono::system_clock::now();
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
	std::tm localTime;
	localtime_s(&localTime, &currentTime);
	std::stringstream dateStream;
	dateStream << std::put_time(&localTime, "%Y-%m-%d");

	_stringToDate(dateStream.str());
}

std::string Date::getDate()
{
	return _dateToString();
}

int Date::getYear()
{
	return _year;
}

int Date::getMonth()
{
	return _month;
}

int Date::getDay()
{
	return _day;
}

void Date::_stringToDate(std::string date)
{
	_year = std::stoi(date.substr(0, 4));
	_month = std::stoi(date.substr(5, 2));
	_day = std::stoi(date.substr(8, 2));
}

void Date::_stringToDate(std::wstring date)
{
	_year = std::stoi(date.substr(0, 4));
	_month = std::stoi(date.substr(5, 2));
	_day = std::stoi(date.substr(8, 2));
}

std::string Date::_dateToString()
{
	std::string date = std::to_string(_year) + "-" + std::to_string(_month) + "-" + std::to_string(_day);
	return date;
}