#include "User.hpp"
#include "Config.h"
#include "Utils.hpp"

User::User() :
	_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Library Management System", sf::Style::Default),
	_userType(UserType::Guest),
	_pageManager(*this)
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



Book User::getBookInfoById(int id)
{
    const char* sql = "SELECT * FROM book_info WHERE id = ?";
    int rc;
    sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
        return Book();
    }

	rc = sqlite3_bind_int(stmt, 1, id);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
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

		return book;
	}
	else {
		return Book();
	}
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
		return books;
	}

	std::string bookNameStr = wstring_to_string(bookName);
	bookNameStr = '%' + bookNameStr + '%';
	rc = sqlite3_bind_text(stmt, 1, bookNameStr.c_str(), -1, SQLITE_STATIC);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
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
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
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

	if (rc != SQLITE_DONE) {
		std::cerr << "Search book by book name failed: " << sqlite3_errmsg(mDatabase) << std::endl;
	}
	
	return books;
}