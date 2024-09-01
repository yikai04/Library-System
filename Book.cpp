#include <regex>
#include "Book.hpp"

BookCategory getCategoryByName(std::wstring categoryName)
{
	if (categoryName == L"小说类")
	{
		return Fiction;
	}
	else if (categoryName == L"传记与回忆录")
	{
		return BiographiesMemoirs;
	}
	else if (categoryName == L"历史与文化")
	{
		return HistoryCulture;
	}
	else if (categoryName == L"科学与自然")
	{
		return ScienceNature;
	}
	else if (categoryName == L"商业与经济")
	{
		return BusinessEconomics;
	}
	else if (categoryName == L"健康与生活方式")
	{
		return HealthLifestyle;
	}
	else if (categoryName == L"艺术与设计")
	{
		return ArtDesign;
	}
	else if (categoryName == L"语言与文学")
	{
		return LanguageLiterature;
	}
	else if (categoryName == L"参考手册")
	{
		return ReferenceManuals;
	}
	else if (categoryName == L"儿童读物")
	{
		return ChildrensBooks;
	}
	else
	{
		return Others;
	}
}

std::wstring getCategoryNameByCategory(BookCategory category)
{
	switch (category)
	{
	case Fiction:
		return L"小说类";
	case BiographiesMemoirs:
		return L"传记与回忆录";
	case HistoryCulture:
		return L"历史与文化";
	case ScienceNature:
		return L"科学与自然";
	case BusinessEconomics:
		return L"商业与经济";
	case HealthLifestyle:
		return L"健康与生活方式";
	case ArtDesign:
		return L"艺术与设计";
	case LanguageLiterature:
		return L"语言与文学";
	case ReferenceManuals:
		return L"参考手册";
	case ChildrensBooks:
		return L"儿童读物";
	case Others:
		return L"其他";
	default:
		return L"其他";
	}
}

Book::Book() :
	_id(-1),
	_bookName(L""),
	_author(L""),
	_publisher(L""),
	_category(Others),
	_publishDate(),
	_pages(0),
	_totalBook(0),
	_remainBook(0),
	_price(0),
	_description(L""),
	_imgUrl(""),
	_borrowVolume(0),
	_delFlg(false)
{

}

Book::Book(int id) :
	_id(id)
{
	_loadBookInfosFromDB();
}

Book::Book(const Book& book) :
	_id(book._id),
	_bookName(book._bookName),
	_author(book._author),
	_publisher(book._publisher),
	_category(book._category),
	_publishDate(book._publishDate),
	_pages(book._pages),
	_totalBook(book._totalBook),
	_remainBook(book._remainBook),
	_price(book._price),
	_description(book._description),
	_imgUrl(book._imgUrl),
	_borrowVolume(book._borrowVolume),
	_delFlg(book._delFlg)
{

}

Book& Book::operator=(const Book& book)
{
	_id = book._id;
	_bookName = book._bookName;
	_author = book._author;
	_publisher = book._publisher;
	_category = book._category;
	_publishDate = book._publishDate;
	_pages = book._pages;
	_totalBook = book._totalBook;
	_remainBook = book._remainBook;
	_price = book._price;
	_description = book._description;
	_imgUrl = book._imgUrl;
	_borrowVolume = book._borrowVolume;
	_delFlg = book._delFlg;

	return *this;
}

Book::~Book()
{

}

int Book::getBookId()
{
	return _id;
}

std::wstring Book::getBookName()
{
	return _bookName;
}

std::wstring Book::getAuthor()
{
	return _author;
}

std::wstring Book::getPublisher()
{
	return _publisher;
}

BookCategory Book::getCategory()
{
	return _category;
}

std::wstring Book::getCategoryName()
{
	switch (_category)
	{
	case Fiction:
		return L"小说类";
	case BiographiesMemoirs:
		return L"传记与回忆录";
	case HistoryCulture:
		return L"历史与文化";
	case ScienceNature:
		return L"科学与自然";
	case BusinessEconomics:
		return L"商业与经济";
	case HealthLifestyle:
		return L"健康与生活方式";
	case ArtDesign:
		return L"艺术与设计";
	case LanguageLiterature:
		return L"语言与文学";
	case ReferenceManuals:
		return L"参考手册";
	case ChildrensBooks:
		return L"儿童读物";
	case Others:
		return L"其他";
	default:
		return L"其他";
	}
}

Date Book::getPublishDate()
{
	return _publishDate;
}

int Book::getPages()
{
	return _pages;
}

int Book::getTotalBook()
{
	return _totalBook;
}

int Book::getRemainBook()
{
	return _remainBook;
}

double Book::getPrice()
{
	return _price;
}

std::wstring Book::getDescription()
{
	return _description;
}

std::string Book::getImgUrl()
{
	return _imgUrl;
}

int Book::getBorrowVolume()
{
	return _borrowVolume;
}

bool Book::getDelFlg()
{
	return _delFlg;
}

bool Book::changeBookId(std::wstring id)
{
	std::regex digitRegex("^\\d+$");
	if (!std::regex_match(wstring_to_string(id), digitRegex)) {
		return false;
	}

	int idInt = std::stoi(id);
	
	if (_id == idInt)
	{
		return true;
	}

	if (!_checkBookIdValidaty(idInt))
	{
		return false;
	}

	const char* sql = "UPDATE book_info SET id = ? WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_bind_int(stmt, 1, idInt);
	rc = sqlite3_bind_int(stmt, 2, _id);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		_loadBookInfosFromDB();
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

bool Book::changeBookName(std::wstring bookName)
{
	if (bookName == L"")
	{
		return false;
	}

	if (_bookName == bookName)
	{
		return true;
	}

	const char* sql = "UPDATE book_info SET book_name = ? WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_bind_text16(stmt, 1, bookName.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_int(stmt, 2, _id);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind book name: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		_loadBookInfosFromDB();
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

bool Book::changeAuthor(std::wstring author)
{
	if (author == L"")
	{
		return false;
	}

	if (_author == author)
	{
		return true;
	}

	const char* sql = "UPDATE book_info SET author = ? WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_bind_text16(stmt, 1, author.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_int(stmt, 2, _id);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind author: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		_loadBookInfosFromDB();
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

bool Book::changePublisher(std::wstring publisher)
{
	if (publisher == L"")
	{
		return false;
	}

	if (_publisher == publisher)
	{
		return true;
	}

	const char* sql = "UPDATE book_info SET publisher = ? WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_bind_text16(stmt, 1, publisher.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_int(stmt, 2, _id);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind publisher: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		_loadBookInfosFromDB();
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

bool Book::changeCategory(std::wstring category)
{
	if (category == L"")
	{
		return false;
	}

	BookCategory newCategory = getCategoryByName(category);
	if (_category == newCategory)
	{
		return true;
	}

	const char* sql = "UPDATE book_info SET category = ? WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_bind_text16(stmt, 1, category.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_int(stmt, 2, _id);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind category: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		_loadBookInfosFromDB();
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

bool Book::changePublishDate(Date publishDate)
{
	if (_publishDate == publishDate)
	{
		return true;
	}

	const char* sql = "UPDATE book_info SET publish_date = ? WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	std::wstring date = publishDate.getWDate();
	rc = sqlite3_bind_text16(stmt, 1, date.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_int(stmt, 2, _id);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind publish date: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		_loadBookInfosFromDB();
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

bool Book::changePages(std::wstring pages)
{
	std::regex digitRegex("^\\d+$");
	if (!std::regex_match(wstring_to_string(pages), digitRegex)) {
		return false;
	}

	int pagesInt = std::stoi(pages);
	if (_pages == pagesInt)
	{
		return true;
	}

	const char* sql = "UPDATE book_info SET pages = ? WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_bind_int(stmt, 1, pagesInt);
	rc = sqlite3_bind_int(stmt, 2, _id);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind pages: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		_loadBookInfosFromDB();
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

bool Book::changeTotalBook(std::wstring totalBook)
{
	std::regex digitRegex("^\\d+$");
	if (!std::regex_match(wstring_to_string(totalBook), digitRegex)) {
		return false;
	}

	int totalBookInt = std::stoi(totalBook);
	if (_totalBook == totalBookInt)
	{
		return true;
	}

	const char* sql = "UPDATE book_info SET total_book = ? WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_bind_int(stmt, 1, totalBookInt);
	rc = sqlite3_bind_int(stmt, 2, _id);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind total book: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		_loadBookInfosFromDB();
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

bool Book::changeRemainBook(std::wstring remainBook)
{
	std::regex digitRegex("^\\d+$");
	if (!std::regex_match(wstring_to_string(remainBook), digitRegex)) {
		return false;
	}

	int remainBookInt = std::stoi(remainBook);
	if (_remainBook == remainBookInt)
	{
		return true;
	}

	const char* sql = "UPDATE book_info SET remain_book = ? WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_bind_int(stmt, 1, remainBookInt);
	rc = sqlite3_bind_int(stmt, 2, _id);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind remain book: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		_loadBookInfosFromDB();
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

bool Book::changePrice(std::wstring price)
{
	std::regex digitRegex("^\\d+(\\.\\d+)?$");
	if (!std::regex_match(wstring_to_string(price), digitRegex)) {
		return false;
	}

	double priceDouble = std::stod(price);
	if (_price == priceDouble)
	{
		return true;
	}

	const char* sql = "UPDATE book_info SET price = ? WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_bind_double(stmt, 1, priceDouble);
	rc = sqlite3_bind_int(stmt, 2, _id);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind price: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		_loadBookInfosFromDB();
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

bool Book::changeDescription(std::wstring description)
{
	if (_description == description)
	{
		return true;
	}

	const char* sql = "UPDATE book_info SET description = ? WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_bind_text16(stmt, 1, description.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_int(stmt, 2, _id);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind description: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		_loadBookInfosFromDB();
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

bool Book::changeImgUrl(std::string imgUrl)
{
	if (_imgUrl == imgUrl)
	{
		return true;
	}

	const char* sql = "UPDATE book_info SET img_url = ? WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_bind_text(stmt, 1, imgUrl.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_int(stmt, 2, _id);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind img url: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		_loadBookInfosFromDB();
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

bool Book::addBorrowVolume()
{
	const char* sql = "UPDATE book_info SET borrow_volume = borrow_volume + 1 WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_bind_int(stmt, 1, _id);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		_loadBookInfosFromDB();
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

std::vector<Book> Book::getAllBooks()
{
	std::vector<Book> books;
	const char* sql = "SELECT id FROM book_info";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return books;
	}

	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		int id = sqlite3_column_int(stmt, 0);
		books.push_back(Book(id));
	}

	sqlite3_finalize(stmt);
	return books;
}

std::vector<Book> Book::searchBooksInfo(std::wstring searchWord, const std::wstring& category)
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
		Book book(sqlite3_column_int(stmt, 0));
		books.push_back(book);

		rc = sqlite3_step(stmt);
	}

	sqlite3_finalize(stmt);
	return books;
}

std::vector<Book> Book::searchBooksInfoByName(std::wstring bookName, const std::wstring& category)
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
		Book book(sqlite3_column_int(stmt, 0));
		books.push_back(book);

		rc = sqlite3_step(stmt);
	}

	sqlite3_finalize(stmt);
	return books;
}

std::vector<Book> Book::searchBooksInfoByAuthor(std::wstring author, const std::wstring& category)
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
		Book book(sqlite3_column_int(stmt, 0));
		books.push_back(book);

		rc = sqlite3_step(stmt);
	}

	sqlite3_finalize(stmt);
	return books;
}

std::vector<Book> Book::searchBooksInfoByPublisher(std::wstring publisher, const std::wstring& category)
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
		Book book(sqlite3_column_int(stmt, 0));

		books.push_back(book);

		rc = sqlite3_step(stmt);
	}

	sqlite3_finalize(stmt);
	return books;
}

std::vector<Book> Book::getBooksByCategory(BookCategory category)
{
	std::vector<Book> books;
	const char* sql = "SELECT id FROM book_info WHERE category = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return books;
	}

	std::wstring categoryName = getCategoryNameByCategory(category);
	rc = sqlite3_bind_text16(stmt, 1, categoryName.c_str(), -1, SQLITE_STATIC);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind category: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return books;
	}

	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		int id = sqlite3_column_int(stmt, 0);
		books.push_back(Book(id));
	}

	sqlite3_finalize(stmt);
	return books;
}

//@return true if the id is valid(not exist), false otherwise
bool Book::_checkBookIdValidaty(int id)
{
	const char* sql = "SELECT * FROM book_info WHERE id = ?";
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

void Book::_loadBookInfosFromDB()
{
	const char* sql = "SELECT * FROM book_info WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return;
	}

	rc = sqlite3_bind_int(stmt, 1, _id);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		_bookName = std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 1));
		_author = std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 2));
		_publisher = std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 3));
		std::wstring category = std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 4));
		_category = getCategoryByName(category);
		_publishDate.setDate(std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 5)));
		_pages = sqlite3_column_int(stmt, 6);
		_totalBook = sqlite3_column_int(stmt, 7);
		_remainBook = sqlite3_column_int(stmt, 8);
		_price = sqlite3_column_double(stmt, 9);
		_description = std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 10));
		_imgUrl = "BookImage/" + std::string((const char*)sqlite3_column_text(stmt, 11));
		_borrowVolume = sqlite3_column_int(stmt, 12);
		_delFlg = sqlite3_column_int(stmt, 13);
	}
	else {
		_id = -1;
		_bookName = L"";
		_author = L"";
		_publisher = L"";
		_category = Others;
		_publishDate = Date();
		_pages = 0;
		_totalBook = 0;
		_remainBook = 0;
		_price = 0;
		_description = L"";
		_imgUrl = "";
		_borrowVolume = 0;
		_delFlg = false;
	}

	sqlite3_finalize(stmt);
}