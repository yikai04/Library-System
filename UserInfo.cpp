#include <regex>
#include "UserInfo.hpp"

UserType stringToUserType(const std::string& str)
{
	if (str == "Student") {
		return UserType::Student;
	}
	else if (str == "Teacher") {
		return UserType::Teacher;
	}
	else if (str == "Admin") {
		return UserType::Admin;
	}
	else {
		return UserType::Guest;
	}
}

std::string userTypeToString(UserType type)
{
	switch (type)
	{
	case UserType::Student:
		return "Student";
	case UserType::Teacher:
		return "Teacher";
	case UserType::Admin:
		return "Admin";
	default:
		return "Guest";
	}
}

UserInfo::UserInfo() :
	_userId(-1),
	_username(L""),
	_email(L""),
	_name(L""),
	_role(UserType::Guest),
	_gender(L""),
	_registerDate(Date()),
	_delFlg(0)
{

}

UserInfo::UserInfo(int userId)
{
	_userId = userId;
	_setUserAllDetails();
}

UserInfo::UserInfo(const UserInfo& userInfo)
{
	_userId = userInfo._userId;
	_username = userInfo._username;
	_email = userInfo._email;
	_name = userInfo._name;
	_role = userInfo._role;
	_gender = userInfo._gender;
	_registerDate = userInfo._registerDate;
	_delFlg = userInfo._delFlg;
}

UserInfo::~UserInfo()
{

}

void UserInfo::setUserId(int userId)
{
	if (userId >= 0) {
		_userId = userId;
		_setUserAllDetails();
	}
	else {
		_userId = -1;
		_username = L"";
		_email = L"";
		_name = L"";
		_role = UserType::Guest;
		_gender = L"";
		_registerDate = Date();
		_delFlg = 0;
	}
}

int UserInfo::getUserId()
{
	return _userId;
}

std::wstring UserInfo::getUsername()
{
	return _username;
}

std::wstring UserInfo::getName()
{
	return _name;
}

std::wstring UserInfo::getEmail()
{
	return _email;
}

UserType UserInfo::getRole()
{
	return _role;
}

std::wstring UserInfo::getGender()
{
	return _gender;
}

Date UserInfo::getRegisterDate()
{
	return _registerDate;
}

bool UserInfo::changeUsername(std::wstring username)
{
	if (username == L"") {
		return false;
	}

	if (username == _username) {
		return true;
	}

	if (!checkUsernameValidaty(username)) {
		return false;
	}

	const char* sql = "UPDATE user_info SET username = ? WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	std::string usernameStr = wstring_to_string(username);
	rc = sqlite3_bind_text(stmt, 1, usernameStr.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_int(stmt, 2, _userId);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		_username = username;
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

bool UserInfo::changeEmail(std::wstring email)
{
	if (email == L"") {
		return false;
	}

	if (email == _email) {
		return true;
	}

	std::regex emailPattern("^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)+$");
	std::string emailStr = wstring_to_string(email);
	if (!std::regex_match(emailStr, emailPattern)) {
		return false;
	}

	const char* sql = "UPDATE user_info SET email = ? WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_bind_text(stmt, 1, emailStr.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_int(stmt, 2, _userId);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		_email = email;
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

bool UserInfo::changeName(std::wstring name)
{
	if (name == L"") {
		return false;
	}

	if (name == _name) {
		return true;
	}

	const char* sql = "UPDATE user_info SET name = ? WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	std::string nameStr = wstring_to_string(name);
	rc = sqlite3_bind_text(stmt, 1, nameStr.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_int(stmt, 2, _userId);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		_name = name;
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

bool UserInfo::changeId(std::wstring id)
{
	if (id == L"") {
		return false;
	}

	int idInt = std::stoi(id);
	if (idInt == _userId) {
		return true;
	}

	if (!checkIdValidaty(idInt)) {
		return false;
	}

	const char* sql = "UPDATE user_info SET id = ? WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	if (!checkIdValidaty(idInt)) {
		return false;
	}

	rc = sqlite3_bind_int(stmt, 1, idInt);
	rc = sqlite3_bind_int(stmt, 2, _userId);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		_userId = idInt;
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

bool UserInfo::changeGender(std::wstring gender)
{
	std::string genderStr;
	if (gender == L"男") {
		genderStr = "M";
	}
	else if (gender == L"女") {
		genderStr = "F";
	}
	else {
		return false;
	}

	const char* sql = "UPDATE user_info SET gender = ? WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_bind_text(stmt, 1, genderStr.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_int(stmt, 2, _userId);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		_gender = gender;
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

bool UserInfo::changeRole(std::wstring role)
{
	std::string roleStr;
	UserType userType;
	if (role == L"学生") {
		roleStr = "Student";
		userType = UserType::Student;
	}
	else if (role == L"教师") {
		roleStr = "Teacher";
		userType = UserType::Teacher;
	}
	else if (role == L"管理员") {
		roleStr = "Admin";
		userType = UserType::Admin;
	}
	else {
		return false;
	}

	const char* sql = "UPDATE user_info SET role = ? WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_bind_text(stmt, 1, roleStr.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_int(stmt, 2, _userId);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		_role = userType;
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

bool UserInfo::changePassword(std::wstring password)
{
	if (password == L"") {
		return false;
	}

	const char* sql = "UPDATE user_info SET password = ? WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	std::string hashedPassword = hashPassword(wstring_to_string(password));
	rc = sqlite3_bind_text(stmt, 1, hashedPassword.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_int(stmt, 2, _userId);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

std::vector<BorrowBookDetail> UserInfo::getBorrowedBooks()
{
	const char* sql = "SELECT * FROM borrow_info WHERE user_id = ?";
	int rc;
	std::vector<BorrowBookDetail> borrowBookDetailList;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return borrowBookDetailList;
	}

	rc = sqlite3_bind_int(stmt, 1, _userId);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return borrowBookDetailList;
	}

	rc = sqlite3_step(stmt);
	while (rc == SQLITE_ROW) {
		BorrowBookDetail borrowBookDetail;
		borrowBookDetail.setId(sqlite3_column_int(stmt, 0));
		borrowBookDetail.setBookId(sqlite3_column_int(stmt, 1));
		borrowBookDetail.setUserId(sqlite3_column_int(stmt, 2));
		borrowBookDetail.setBorrowDate(std::string((const char*)sqlite3_column_text(stmt, 3)));
		borrowBookDetail.setDueDate(std::string((const char*)sqlite3_column_text(stmt, 4)));
		borrowBookDetail.setReturnDate(std::string((const char*)sqlite3_column_text(stmt, 5)));

		borrowBookDetailList.push_back(borrowBookDetail);

		rc = sqlite3_step(stmt);
	}

	sqlite3_finalize(stmt);
	return borrowBookDetailList;
}



//@return true if the username is valid, false otherwise
bool UserInfo::checkUsernameValidaty(std::wstring username)
{
	const char* sql = "SELECT * FROM user_info WHERE username = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	std::string usernameStr = wstring_to_string(username);
	rc = sqlite3_bind_text(stmt, 1, usernameStr.c_str(), -1, SQLITE_STATIC);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		sqlite3_finalize(stmt);
		return false;
	}
	else {
		sqlite3_finalize(stmt);
		return true;
	}
}

//@return true if the id is valid, false otherwise
bool UserInfo::checkIdValidaty(int id)
{
	const char* sql = "SELECT * FROM user_info WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_bind_int(stmt, 1, id);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		sqlite3_finalize(stmt);
		return false;
	}
	else {
		sqlite3_finalize(stmt);
		return true;
	}
}

void UserInfo::_setUserAllDetails()
{
	const char* sql = "SELECT * FROM user_info WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return;
	}

	rc = sqlite3_bind_int(stmt, 1, _userId);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		_name = std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 1));
		_username = std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 2));
		_role = stringToUserType(std::string((const char*)sqlite3_column_text(stmt, 4)));
		_registerDate = Date(std::string((const char*)sqlite3_column_text(stmt, 5)));
		_gender = std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 6));
		_email = std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 7));
		_delFlg = sqlite3_column_int(stmt, 8);
	}
}