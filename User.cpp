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
		int delFlg = sqlite3_column_int(stmt, 8);
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

Book User::getBookInfoById(int id)
{
    const char* sql = "SELECT * FROM book_info WHERE id = ?";
    int rc;
    sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return Book();
    }

	rc = sqlite3_bind_int(stmt, 1, id);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return Book();
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		Book book;
		book.setId(sqlite3_column_int(stmt, 0));
		book.setBookName(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 1)));
		book.setAuthor(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 2)));
		book.setPublisher(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 3)));
		book.setCategory(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 4)));
		book.setPublishDate(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 5)));
		book.setPages(sqlite3_column_int(stmt, 6));
		book.setTotalBooks(sqlite3_column_int(stmt, 7));
		book.setAvailableBooks(sqlite3_column_int(stmt, 8));
		book.setPrice(sqlite3_column_double(stmt, 9));
		book.setDescription(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 10)));
		book.setImgUrl(std::string((const char*)sqlite3_column_text(stmt, 11)));
		book.setBorrowVolume(sqlite3_column_int(stmt, 12));
		book.setDelFlg(sqlite3_column_int(stmt, 13));

		sqlite3_finalize(stmt);
		return book;
	}
	else {
		sqlite3_finalize(stmt);
		return Book();
	}
}

std::vector<Book> User::searchBooksInfo(std::wstring searchWord, const std::wstring& category)
{
	const char* sql = "SELECT * FROM book_info WHERE (book_name LIKE ? OR author LIKE ? OR publisher LIKE ?) AND category LIKE ?";
	int rc;
	std::vector<Book> books;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return books;
	}

	std::string searchWordStr;
	if (searchWord == L"") {
		searchWordStr = '%';
	}
	else {
		searchWordStr = wstring_to_string(searchWord);
		searchWordStr = '%' + searchWordStr + '%';
	}
	rc = sqlite3_bind_text(stmt, 1, searchWordStr.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_text(stmt, 2, searchWordStr.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_text(stmt, 3, searchWordStr.c_str(), -1, SQLITE_STATIC);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to search word: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return books;
	}

	std::string categoryStr;
	if (category == L"全部") {
		categoryStr = '%';
	}
	else {
		categoryStr = wstring_to_string(category);
		categoryStr = '%' + categoryStr + '%';
	}
	rc = sqlite3_bind_text(stmt, 4, categoryStr.c_str(), -1, SQLITE_STATIC);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to category: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return books;
	}

	rc = sqlite3_step(stmt);
	while (rc == SQLITE_ROW) {
		Book book;
		book.setId(sqlite3_column_int(stmt, 0));
		book.setBookName(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 1)));
		book.setAuthor(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 2)));
		book.setPublisher(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 3)));
		book.setCategory(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 4)));
		book.setPublishDate(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 5)));
		book.setPages(sqlite3_column_int(stmt, 6));
		book.setTotalBooks(sqlite3_column_int(stmt, 7));
		book.setAvailableBooks(sqlite3_column_int(stmt, 8));
		book.setPrice(sqlite3_column_double(stmt, 9));
		book.setDescription(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 10)));
		book.setImgUrl(std::string((const char*)sqlite3_column_text(stmt, 11)));
		book.setBorrowVolume(sqlite3_column_int(stmt, 12));
		book.setDelFlg(sqlite3_column_int(stmt, 13));

		books.push_back(book);

		rc = sqlite3_step(stmt);
	}

	sqlite3_finalize(stmt);
	return books;
}

std::vector<Book> User::searchBooksInfoByName(std::wstring bookName, const std::wstring& category)
{
	const char* sql = "SELECT * FROM book_info WHERE book_name LIKE ? AND category LIKE ?";
	int rc;
	std::vector<Book> books;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return books;
	}

	std::string bookNameStr;
	if (bookName == L"") {
		bookNameStr = '%';
	}
	else {
		bookNameStr = wstring_to_string(bookName);
		bookNameStr = '%' + bookNameStr + '%';
	}

	rc = sqlite3_bind_text(stmt, 1, bookNameStr.c_str(), -1, SQLITE_STATIC);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to book name: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return books;
	}

	std::string categoryStr;
	if (category == L"全部") {
		categoryStr = '%';
	}
	else {
		categoryStr = wstring_to_string(category);
		categoryStr = '%' + categoryStr + '%';
	}
	rc = sqlite3_bind_text(stmt, 2, categoryStr.c_str(), -1, SQLITE_STATIC);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to category: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return books;
	}

	rc = sqlite3_step(stmt);
	while (rc == SQLITE_ROW) {
		Book book;
		book.setId(sqlite3_column_int(stmt, 0));
		book.setBookName(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 1)));
		book.setAuthor(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 2)));
		book.setPublisher(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 3)));
		book.setCategory(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 4)));
		book.setPublishDate(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 5)));
		book.setPages(sqlite3_column_int(stmt, 6));
		book.setTotalBooks(sqlite3_column_int(stmt, 7));
		book.setAvailableBooks(sqlite3_column_int(stmt, 8));
		book.setPrice(sqlite3_column_double(stmt, 9));
		book.setDescription(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 10)));
		book.setImgUrl(std::string((const char*)sqlite3_column_text(stmt, 11)));
		book.setBorrowVolume(sqlite3_column_int(stmt, 12));
		book.setDelFlg(sqlite3_column_int(stmt, 13));

		books.push_back(book);

		rc = sqlite3_step(stmt);
	}
	
	sqlite3_finalize(stmt);
	return books;
}

std::vector<Book> User::searchBooksInfoByAuthor(std::wstring author, const std::wstring& category)
{
	const char* sql = "SELECT * FROM book_info WHERE author LIKE ? AND category LIKE ?";
	int rc;
	std::vector<Book> books;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return books;
	}

	std::string authorStr;
	if (author == L"") {
		authorStr = '%';
	}
	else {
		authorStr = wstring_to_string(author);
		authorStr = '%' + authorStr + '%';
	}

	rc = sqlite3_bind_text(stmt, 1, authorStr.c_str(), -1, SQLITE_STATIC);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to author: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return books;
	}

	std::string categoryStr;
	if (category == L"全部") {
		categoryStr = '%';
	}
	else {
		categoryStr = wstring_to_string(category);
		categoryStr = '%' + categoryStr + '%';
	}
	rc = sqlite3_bind_text(stmt, 2, categoryStr.c_str(), -1, SQLITE_STATIC);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to category: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return books;
	}

	rc = sqlite3_step(stmt);
	while (rc == SQLITE_ROW) {
		Book book;
		book.setId(sqlite3_column_int(stmt, 0));
		book.setBookName(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 1)));
		book.setAuthor(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 2)));
		book.setPublisher(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 3)));
		book.setCategory(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 4)));
		book.setPublishDate(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 5)));
		book.setPages(sqlite3_column_int(stmt, 6));
		book.setTotalBooks(sqlite3_column_int(stmt, 7));
		book.setAvailableBooks(sqlite3_column_int(stmt, 8));
		book.setPrice(sqlite3_column_double(stmt, 9));
		book.setDescription(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 10)));
		book.setImgUrl(std::string((const char*)sqlite3_column_text(stmt, 11)));
		book.setBorrowVolume(sqlite3_column_int(stmt, 12));
		book.setDelFlg(sqlite3_column_int(stmt, 13));

		books.push_back(book);

		rc = sqlite3_step(stmt);
	}

	sqlite3_finalize(stmt);
	return books;
}

std::vector<Book> User::searchBooksInfoByPublisher(std::wstring publisher, const std::wstring& category)
{
	const char* sql = "SELECT * FROM book_info WHERE publisher LIKE ? AND category LIKE ?";
	int rc;
	std::vector<Book> books;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return books;
	}

	std::string publisherStr;
	if (publisher == L"") {
		publisherStr = '%';
	}
	else {
		publisherStr = wstring_to_string(publisher);
		publisherStr = '%' + publisherStr + '%';
	}

	rc = sqlite3_bind_text(stmt, 1, publisherStr.c_str(), -1, SQLITE_STATIC);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to book name: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return books;
	}

	std::string categoryStr;
	if (category == L"全部") {
		categoryStr = '%';
	}
	else {
		categoryStr = wstring_to_string(category);
		categoryStr = '%' + categoryStr + '%';
	}
	rc = sqlite3_bind_text(stmt, 2, categoryStr.c_str(), -1, SQLITE_STATIC);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to category: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return books;
	}

	rc = sqlite3_step(stmt);
	while (rc == SQLITE_ROW) {
		Book book;
		book.setId(sqlite3_column_int(stmt, 0));
		book.setBookName(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 1)));
		book.setAuthor(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 2)));
		book.setPublisher(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 3)));
		book.setCategory(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 4)));
		book.setPublishDate(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 5)));
		book.setPages(sqlite3_column_int(stmt, 6));
		book.setTotalBooks(sqlite3_column_int(stmt, 7));
		book.setAvailableBooks(sqlite3_column_int(stmt, 8));
		book.setPrice(sqlite3_column_double(stmt, 9));
		book.setDescription(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 10)));
		book.setImgUrl(std::string((const char*)sqlite3_column_text(stmt, 11)));
		book.setBorrowVolume(sqlite3_column_int(stmt, 12));
		book.setDelFlg(sqlite3_column_int(stmt, 13));

		books.push_back(book);

		rc = sqlite3_step(stmt);
	}

	sqlite3_finalize(stmt);
	return books;
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