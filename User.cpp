#include "User.hpp"
#include "Config.h"
#include "Utils.hpp"

User::User() :
	_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Library Management System", sf::Style::Default),
	_userType(UserType::Guest),
	_pageManager(*this),
	_userId(-1)
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
			std::wstring truthPassword = std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 3));
			if (password == truthPassword) {
				_userId = sqlite3_column_int(stmt, 0);
				_setUserType(std::string((const char*)sqlite3_column_text(stmt, 4)));
				sqlite3_finalize(stmt);

				_setUserDetail();
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
	_userType = UserType::Guest;
	_userId = -1;
}

UserType User::getUserType()
{
	return _userType;
}

std::wstring User::getName()
{
	return _name;
}

Date User::getRegisterDate()
{
	return _registerDate;
}

std::wstring User::getEmail()
{
	return _email;
}

std::wstring User::getGender()
{
	return _gender;
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
		book.setDelFlg(sqlite3_column_int(stmt, 12));

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
		book.setDelFlg(sqlite3_column_int(stmt, 12));

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
		book.setDelFlg(sqlite3_column_int(stmt, 12));

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
		book.setDelFlg(sqlite3_column_int(stmt, 12));

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
		book.setDelFlg(sqlite3_column_int(stmt, 12));

		books.push_back(book);

		rc = sqlite3_step(stmt);
	}

	sqlite3_finalize(stmt);
	return books;
}

std::vector<BorrowBookDetail> User::getBorrowedBooks()
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
		borrowBookDetail.setReturnDate(std::string((const char*)sqlite3_column_text(stmt, 4)));

		borrowBookDetailList.push_back(borrowBookDetail);

		rc = sqlite3_step(stmt);
	}

	sqlite3_finalize(stmt);
	return borrowBookDetailList;
}



void User::_setUserType(std::string type)
{
	if (type == "Student") {
		_userType = UserType::Student;
	}
	else if (type == "Teacher") {
		_userType = UserType::Teacher;
	}
	else if (type == "Admin") {
		_userType = UserType::Admin;
	}
	else if (type == "Guest") {
		_userType = UserType::Guest;
	}
}

void User::_setUserDetail()
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
		_registerDate = Date(std::string((const char*)sqlite3_column_text(stmt, 5)));
		_gender = std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 6));
		_email = std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 7));
	}
}