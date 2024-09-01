#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono> //Time
#include <ctime>
#include <Windows.h>
#include <regex> //Regular Expression

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

std::string hashPassword(const std::string& password)
{
	return BCrypt::generateHash(password, 12);
}

bool validatePassword(const std::string& password, const std::string& hash)
{
	return BCrypt::validatePassword(password, hash);
}



//Date::Date():
//    _year(-1),
//    _month(-1),
//    _day(-1)
//{
//
//}
//
//Date::Date(const Date& date)
//{
//	_year = date._year;
//	_month = date._month;
//	_day = date._day;
//}
//
//Date::Date(std::string date)
//{
//	_stringToDate(date);
//}
//
//Date::Date(std::wstring date)
//{
//    _stringToDate(date);
//}
//
//Date Date::operator=(const Date& date)
//{
//	_year = date._year;
//	_month = date._month;
//	_day = date._day;
//	return *this;
//}
//
//Date::~Date()
//{
//
//}
//
//void Date::setDate(std::string date)
//{
//	std::regex datePattern("\\d{4}-\\d{2}-\\d{2}");
//	if (std::regex_match(date, datePattern)) {
//		_stringToDate(date);
//	}
//}
//
//void Date::setDate(std::wstring date)
//{
//	std::regex datePattern("\\d{4}-\\d{2}-\\d{2}");
//	if (std::regex_match(wstring_to_string(date), datePattern)) {
//		_stringToDate(date);
//	}
//}
//
//void Date::setTodatyDate()
//{
//	auto now = std::chrono::system_clock::now();
//	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
//	std::tm localTime;
//	localtime_s(&localTime, &currentTime);
//	std::stringstream dateStream;
//	dateStream << std::put_time(&localTime, "%Y-%m-%d");
//
//	_stringToDate(dateStream.str());
//}
//
//
//
//std::string Date::getDate()
//{
//	return _dateToString();
//}
//
//std::wstring Date::getWDate()
//{
//	return _dateToWString();
//}
//
//int Date::getYear()
//{
//	return _year;
//}
//
//int Date::getMonth()
//{
//	return _month;
//}
//
//int Date::getDay()
//{
//	return _day;
//}
//
//void Date::_stringToDate(std::string date)
//{
//	_year = std::stoi(date.substr(0, 4));
//	_month = std::stoi(date.substr(5, 2));
//	_day = std::stoi(date.substr(8, 2));
//}
//
//void Date::_stringToDate(std::wstring date)
//{
//	_year = std::stoi(date.substr(0, 4));
//	_month = std::stoi(date.substr(5, 2));
//	_day = std::stoi(date.substr(8, 2));
//}
//
//std::string Date::_dateToString()
//{
//	if (_year == -1 || _month == -1 || _day == -1)
//	{
//		return "NULL";
//	}
//
//	std::string date = std::format("{:04}", _year) + "-" + std::format("{:02}", _month) + "-" + std::format("{:02}", _day);	
//	return date;
//}
//
//std::wstring Date::_dateToWString()
//{
//	if (_year == -1 || _month == -1 || _day == -1)
//	{
//		return L"NULL";
//	}
//
//	std::wstring date = std::format(L"{:04}", _year) + L"-" + std::format(L"{:02}", _month) + L"-" + std::format(L"{:02}", _day);
//	return date;
//}



// Default constructor
Date::Date() {
    setTodayDate();
}

// Copy constructor
Date::Date(const Date& date) {
    this->dateStruct = date.dateStruct;
	this->isNullDate = date.isNullDate;
}

// Constructor from std::string
Date::Date(std::string date) {
    setDate(date);
}

// Constructor from std::wstring
Date::Date(std::wstring date) {
    setDate(date);
}

// Assignment operator
Date& Date::operator=(const Date& date) {
    if (this != &date) {
        this->dateStruct = date.dateStruct;
		this->isNullDate = date.isNullDate;
    }
    return *this;
}

// Equality operator
bool Date::operator==(const Date& date) const {
    return std::mktime(const_cast<std::tm*>(&this->dateStruct)) == std::mktime(const_cast<std::tm*>(&date.dateStruct));
}

// Inequality operator
bool Date::operator!=(const Date& date) const {
    return !(*this == date);
}

// Less-than operator
bool Date::operator<(const Date& date) const {
    return std::mktime(const_cast<std::tm*>(&this->dateStruct)) < std::mktime(const_cast<std::tm*>(&date.dateStruct));
}

// Greater-than operator
bool Date::operator>(const Date& date) const {
    return std::mktime(const_cast<std::tm*>(&this->dateStruct)) > std::mktime(const_cast<std::tm*>(&date.dateStruct));
}

// Less-than or equal-to operator
bool Date::operator<=(const Date& date) const {
    return !(*this > date);
}

// Greater-than or equal-to operator
bool Date::operator>=(const Date& date) const {
    return !(*this < date);
}

// Destructor
Date::~Date() {
    // No dynamic memory to clean up
}

// Set date from std::string
void Date::setDate(std::string date) {
    parseDateString(date);
}

// Set date from std::wstring
void Date::setDate(std::wstring date) {
    parseWDateString(date);
}

// Set the current date
void Date::setTodayDate() {
    std::time_t t = std::time(nullptr);
	localtime_s(&dateStruct, &t);
    dateStruct.tm_hour = 0;
    dateStruct.tm_min = 0;
    dateStruct.tm_sec = 0;

    isNullDate = false;
}

// Add days to the current date
void Date::addDays(int days) {
    std::time_t t = std::mktime(&dateStruct);
    t += days * 24 * 3600; // Add days in seconds
	localtime_s(&dateStruct, &t);
}

// Add months to the current date
void Date::addMonths(int months) {
    int year = dateStruct.tm_year + 1900;
    int month = dateStruct.tm_mon + 1;

    // Add months
    month += months;
    while (month > 12) {
        month -= 12;
        ++year;
    }
    while (month < 1) {
        month += 12;
        --year;
    }

    // Set the new year and month
    dateStruct.tm_year = year - 1900;
    dateStruct.tm_mon = month - 1;

    // Adjust the day if it exceeds the days in the new month
    int day = dateStruct.tm_mday;
    int maxDay = daysInMonth(year, month);
    if (day > maxDay) {
        dateStruct.tm_mday = maxDay;
    }

    // Normalize the time structure
    std::mktime(&dateStruct);
}

// Add years to the current date
void Date::addYears(int years) {
    int year = dateStruct.tm_year + 1900 + years;

    // Set the new year
    dateStruct.tm_year = year - 1900;

    // Adjust the day if the current date is February 29 and the new year is not a leap year
    if (dateStruct.tm_mon == 1 && dateStruct.tm_mday == 29) {
        int maxDay = daysInMonth(year, 2);
        if (maxDay < 29) {
            dateStruct.tm_mday = maxDay;
        }
    }

    // Normalize the time structure
    std::mktime(&dateStruct);
}

// Get date as std::string
std::string Date::getDate() {
    return formatDate(dateStruct);
}

// Get date as std::wstring
std::wstring Date::getWDate() {
    return formatWDate(dateStruct);
}

// Get year
int Date::getYear() {
    if (isNullDate) {
        return 0;
    }
    return dateStruct.tm_year + 1900;
}

// Get month
int Date::getMonth() {
    if (isNullDate) {
        return 0;
    }
    return dateStruct.tm_mon + 1;
}

// Get day
int Date::getDay() {
    if (isNullDate) {
        return 0;
    }
    return dateStruct.tm_mday;
}

// Private methods for parsing and formatting
void Date::parseDateString(const std::string& date) {
    std::istringstream ss(date);
    ss >> std::get_time(&dateStruct, "%Y-%m-%d");
    if (ss.fail()) {
        isNullDate = true;
    }
    else {
        isNullDate = false;
    }
}

void Date::parseWDateString(const std::wstring& date) {
    std::wistringstream ss(date);
    ss >> std::get_time(&dateStruct, L"%Y-%m-%d");
    if (ss.fail()) {
        isNullDate = true;
    }
    else {
        isNullDate = false;
    }
}

std::string Date::formatDate(const std::tm& tm) {
    if (isNullDate) {
		return "NULL";
	}
    std::ostringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d");
    return ss.str();
}

std::wstring Date::formatWDate(const std::tm& tm) {
    if (isNullDate) {
        return L"NULL";
    }
    std::wostringstream ss;
    ss << std::put_time(&tm, L"%Y-%m-%d");
    return ss.str();
}

// Determine the number of days in a given month of a given year
int Date::daysInMonth(int year, int month) {
    static const int daysPerMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        return 29; // February in a leap year
    }
    return daysPerMonth[month - 1];
}