#include <regex>

#include "User.hpp"
#include "Config.h"
#include "Utils.hpp"

User::User() :
	_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Library Management System", sf::Style::Titlebar | sf::Style::Close),
	_pageManager(*this),
	_userInfo(UserInfo())
{
	_window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width - WINDOW_WIDTH) >> 1, (sf::VideoMode::getDesktopMode().height - WINDOW_HEIGHT) >> 1));
}

User::~User()
{

}

void User::run()
{
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }

			if (event.type == sf::Event::Resized)
			{
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				_window.setView(sf::View(visibleArea));
			}

            _pageManager.handleEvent(event, _window);
        }

        sf::Time dt = _clock.restart();
        _pageManager.update(dt);

        _pageManager.render(_window);
        _window.display();
    }
}

int User::login(std::wstring username, std::wstring password)
{
	const char* sql = "SELECT * FROM user_info WHERE username = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return SQLITE_DATABASE_ERROR;
	}

	std::string usernameStr = wstring_to_string(username);
	rc = sqlite3_bind_text(stmt, 1, usernameStr.c_str(), -1, SQLITE_STATIC);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return SQLITE_DATABASE_ERROR;
	}

	rc = sqlite3_step(stmt);
	while (rc == SQLITE_ROW) {
		int delFlg = sqlite3_column_int(stmt, 9);
		if (!delFlg) {
			std::string truthPassword = std::string((const char*)sqlite3_column_text(stmt, 3));
			if (validatePassword(wstring_to_string(password), truthPassword)) {
				_userInfo.setUserId(sqlite3_column_int(stmt, 0));
				sqlite3_finalize(stmt);
				return LOGIN_SUCESSFUL;
			}
			else {
				sqlite3_finalize(stmt);
				return WRONG_PASSWORD;
			}
		}

		rc = sqlite3_step(stmt);
	}

	sqlite3_finalize(stmt);
	return INVALID_USERNAME;
}

void User::logout()
{
	_userInfo.setUserId(-1);
}

UserInfo& User::getSelfUserInfo()
{
	return _userInfo;
}

void User::deleteAccount(UserInfo& user)
{
	const char* sql = "UPDATE user_info SET del_flg = 1 WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return;
	}

	rc = sqlite3_bind_int(stmt, 1, user.getUserId());
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		sqlite3_finalize(stmt);
		user.setUserId(-1);
	}
	else {
		sqlite3_finalize(stmt);
	}
}

int User::registerAccount(std::wstring username, std::wstring password, std::wstring email, std::wstring name, std::wstring id, std::wstring role, std::wstring gender)
{
	if (!UserInfo::checkUsernameValidaty(username)) {
		return INVALID_USERNAME;
	}
	std::string usernameStr = wstring_to_string(username);

	int idInt = std::stoi(wstring_to_string(id));
	if (!UserInfo::checkIdValidaty(idInt)) {
		return INVALID_ID;
	}

	std::regex emailPattern("^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)+$");
	std::string emailStr = wstring_to_string(email);
	if (!std::regex_match(emailStr, emailPattern)) {
		return INVALID_EMAIL;
	}

	if (name == L"") {
		return INVALID_NAME;
	}
	std::string nameStr = wstring_to_string(name);

	std::string roleStr;
	if (role == L"学生") {
		roleStr = "Student";
	}
	else if (role == L"教师") {
		roleStr = "Teacher";
	}
	else if (role == L"管理员") {
		roleStr = "Admin";
	}
	else {
		roleStr = "Student";
	}

	std::string genderStr;
	if (gender == L"男") {
		genderStr = "M";
	}
	else if (gender == L"女") {
		genderStr = "F";
	}
	else {
		genderStr = "M";
	}

	const char* sql = "INSERT INTO user_info (id, name, username, password, role, register_date, gender, email, del_flg) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return SQLITE_DATABASE_ERROR;
	}

	std::string passwordStr = hashPassword(wstring_to_string(password));
	Date todayDate;
	todayDate.setTodayDate();

	rc = sqlite3_bind_int(stmt, 1, idInt);
	rc = sqlite3_bind_text(stmt, 2, nameStr.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_text(stmt, 3, usernameStr.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_text(stmt, 4, passwordStr.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_text(stmt, 5, roleStr.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_text(stmt, 6, todayDate.getDate().c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_text(stmt, 7, genderStr.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_text(stmt, 8, emailStr.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_int(stmt, 9, 0);

	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return SQLITE_DATABASE_ERROR;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		sqlite3_finalize(stmt);
		return REGISTER_SUCESSFUL;
	}
	else {
		sqlite3_finalize(stmt);
		return SQLITE_DATABASE_ERROR;
	}
}

bool User::borrowBook(int userId, int bookId)
{
	const char* sql = "INSERT INTO borrow_info (book_id, user_id, borrow_date, due_date) VALUES (?, ?, ?, ?)";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	Date todayDate;
	todayDate.setTodayDate();
	Date dueDate;
	dueDate.setTodayDate();
	UserInfo user(userId);
	if (user.getRole() == UserType::Student) {
		dueDate.addMonths(1);
	}
	else if (user.getRole() == UserType::Teacher) {
		dueDate.addMonths(3);
	}
	else if (user.getRole() == UserType::Admin) {
		dueDate.addMonths(6);
	}
	else {
		return false;
	}

	rc = sqlite3_bind_int(stmt, 1, bookId);
	rc = sqlite3_bind_int(stmt, 2, userId);
	rc = sqlite3_bind_text(stmt, 3, todayDate.getDate().c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_text(stmt, 4, dueDate.getDate().c_str(), -1, SQLITE_STATIC);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		user.addBorrowVolume();
		Book book(bookId);
		book.addBorrowVolume();
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

bool User::returnBook(int bookId)
{
	const char* sql = "UPDATE borrow_info SET return_date = ? WHERE book_id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	Date todayDate;
	todayDate.setTodayDate();

	rc = sqlite3_bind_text(stmt, 1, todayDate.getDate().c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_int(stmt, 2, bookId);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind: " << sqlite3_errmsg(mDatabase) << std::endl;
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