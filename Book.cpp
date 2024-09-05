#include <regex>
#include "Book.hpp"

BookCategory getCategoryByName(std::wstring categoryName)
{
	if (categoryName == L"小说类")
	{
		return BookCategory::Fiction;
	}
	else if (categoryName == L"传记与回忆录")
	{
		return BookCategory::BiographiesMemoirs;
	}
	else if (categoryName == L"历史与文化")
	{
		return BookCategory::HistoryCulture;
	}
	else if (categoryName == L"科学与自然")
	{
		return BookCategory::ScienceNature;
	}
	else if (categoryName == L"商业与经济")
	{
		return BookCategory::BusinessEconomics;
	}
	else if (categoryName == L"健康与生活方式")
	{
		return BookCategory::HealthLifestyle;
	}
	else if (categoryName == L"艺术与设计")
	{
		return BookCategory::ArtDesign;
	}
	else if (categoryName == L"语言与文学")
	{
		return BookCategory::LanguageLiterature;
	}
	else if (categoryName == L"参考手册")
	{
		return BookCategory::ReferenceManuals;
	}
	else if (categoryName == L"儿童读物")
	{
		return BookCategory::ChildrensBooks;
	}
	else
	{
		return BookCategory::Others;
	}
}

std::wstring getCategoryNameByCategory(BookCategory category)
{
	switch (category)
	{
	case BookCategory::Fiction:
		return L"小说类";
	case BookCategory::BiographiesMemoirs:
		return L"传记与回忆录";
	case BookCategory::HistoryCulture:
		return L"历史与文化";
	case BookCategory::ScienceNature:
		return L"科学与自然";
	case BookCategory::BusinessEconomics:
		return L"商业与经济";
	case BookCategory::HealthLifestyle:
		return L"健康与生活方式";
	case BookCategory::ArtDesign:
		return L"艺术与设计";
	case BookCategory::LanguageLiterature:
		return L"语言与文学";
	case BookCategory::ReferenceManuals:
		return L"参考手册";
	case BookCategory::ChildrensBooks:
		return L"儿童读物";
	case BookCategory::Others:
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
	_imgUrl(L"blankBook.jpg"),
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
	return wstring_to_string(_imgUrl);
}

std::wstring Book::getImgUrlWstring()
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

bool Book::setBookId(std::wstring id)
{
	if (!checkIntValidaty(id))
	{
		return false;
	}

	try {
		_id = std::stoi(id);
	}
	catch (...)
	{
		return false;
	}
	
	return true;
}

bool Book::setBookName(std::wstring bookName)
{
	if (!checkStringValidaty(bookName))
	{
		return false;
	}

	try {
		_bookName = bookName;
	}
	catch (...)
	{
		return false;
	}
	
	return true;
}

bool Book::setAuthor(std::wstring author)
{
	if (!checkStringValidaty(author))
	{
		return false;
	}

	try {
		_author = author;
	}
	catch (...)
	{
		return false;
	}

	return true;
}

bool Book::setPublisher(std::wstring publisher)
{
	if (!checkStringValidaty(publisher))
	{
		return false;
	}

	try {
		_publisher = publisher;
	}
	catch (...)
	{
		return false;
	}

	return true;
}

bool Book::setCategory(std::wstring category)
{
	if (!checkStringValidaty(category))
	{
		return false;
	}

	try {
		_category = getCategoryByName(category);
	}
	catch (...)
	{
		return false;
	}

	return true;
}

bool Book::setPublishDate(Date publishDate)
{
	if (publishDate.getDate() == "NULL")
	{
		return false;
	}

	try {
		_publishDate = publishDate;
	}
	catch (...)
	{
		return false;
	}

	return true;
}

bool Book::setPages(std::wstring pages)
{
	if (!checkIntValidaty(pages))
	{
		return false;
	}

	try {
		_pages = std::stoi(pages);
	}
	catch (...)
	{
		return false;
	}

	return true;
}

bool Book::setTotalBook(std::wstring totalBook)
{
	if (!checkIntValidaty(totalBook))
	{
		return false;
	}

	try {
		_totalBook = std::stoi(totalBook);
	}
	catch (...)
	{
		return false;
	}

	return true;
}

bool Book::setRemainBook(std::wstring remainBook)
{
	if (!checkIntValidaty(remainBook))
	{
		return false;
	}

	try {
		_remainBook = std::stoi(remainBook);
	}
	catch (...)
	{
		return false;
	}

	if (_remainBook > _totalBook)
	{
		return false;
	}

	return true;
}

bool Book::setPrice(std::wstring price)
{
	if (!checkDoubleValidaty(price))
	{
		return false;
	}

	try {
		_price = std::stod(price);
	}
	catch (...)
	{
		return false;
	}

	return true;
}

bool Book::setDescription(std::wstring description)
{
	if (!checkStringValidaty(description))
	{
		return false;
	}

	try {
		_description = description;
	}
	catch (...)
	{
		return false;
	}

	return true;
}

bool Book::setImgUrl(std::wstring imgUrl)
{
	if (!checkImgUrlValidaty(wstring_to_string(imgUrl)))
	{
		return false;
	}

	try {
		_imgUrl = imgUrl;
	}
	catch (...)
	{
		return false;
	}

	return true;
}

bool Book::setBorrowVolume(std::wstring borrowVolume)
{
	if (!checkIntValidaty(borrowVolume))
	{
		return false;
	}

	_borrowVolume = std::stoi(borrowVolume);
	return true;
}

bool Book::setDelFlg(std::wstring delFlg)
{
	if (!checkIntValidaty(delFlg))
	{
		return false;
	}

	_delFlg = std::stoi(delFlg);
	return true;
}

bool Book::changeBookId(std::wstring id)
{
	if (!checkIntValidaty(id)) {
		return false;
	}

	int idInt = std::stoi(id);
	
	if (_id == idInt)
	{
		return true;
	}

	if (!checkBookIdValidaty(idInt))
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
	if (!checkStringValidaty(bookName)) {
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
	if (!checkStringValidaty(author))
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
	if (!checkStringValidaty(publisher)) {
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
	if (!checkStringValidaty(category)) {
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
	if (publishDate.getDate() == "NULL")
	{
		return false;
	}

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
	if (!checkIntValidaty(pages))
	{
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
	if (!checkIntValidaty(totalBook))
	{
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
	if (!checkIntValidaty(remainBook)) {
		return false;
	}

	int remainBookInt = std::stoi(remainBook);
	if (_remainBook == remainBookInt)
	{
		return true;
	}

	if (remainBookInt > _totalBook)
	{
		return false;
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
	if (!checkDoubleValidaty(price)) {
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
	if (!checkStringValidaty(description)) {
		return false;
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

bool Book::changeImgUrl(std::wstring imgUrl)
{
	if (!checkImgUrlValidaty(wstring_to_string(imgUrl)))
	{
		return false;
	}

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

	rc = sqlite3_bind_text16(stmt, 1, imgUrl.c_str(), -1, SQLITE_STATIC);
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

std::vector<Book> Book::getBooksByCategory(BookCategory category)
{
	std::vector<Book> books;
	const char* sql = "SELECT id, del_flg FROM book_info WHERE category = ?";
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
		int delFlg = sqlite3_column_int(stmt, 1);
		if (!delFlg) {
			books.push_back(Book(id));
		}
	}

	sqlite3_finalize(stmt);
	return books;
}

std::vector<Book> Book::getAllBooks()
{
	std::vector<Book> books;
	const char* sql = "SELECT id, del_flg FROM book_info";
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
		int delFlg = sqlite3_column_int(stmt, 1);
		if (!delFlg) {
			books.push_back(Book(id));
		}
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
		int delFlg = sqlite3_column_int(stmt, 13);
		if (!delFlg) {
			Book book(sqlite3_column_int(stmt, 0));
			books.push_back(book);
		}

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
		int delFlg = sqlite3_column_int(stmt, 13);
		if (!delFlg) {
			Book book(sqlite3_column_int(stmt, 0));
			books.push_back(book);
		}

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
		int delFlg = sqlite3_column_int(stmt, 13);
		if (!delFlg) {
			Book book(sqlite3_column_int(stmt, 0));
			books.push_back(book);
		}

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
		int delFlg = sqlite3_column_int(stmt, 13);
		if (!delFlg) {
			Book book(sqlite3_column_int(stmt, 0));
			books.push_back(book);
		}

		rc = sqlite3_step(stmt);
	}

	sqlite3_finalize(stmt);
	return books;
}

int Book::addBook(Book* book)
{
	int bookCheck = checkBookIdValidaty(book->getBookId());
	
	if (bookCheck == DELETED) {
		return updateBook(book);
	}
	else if (bookCheck == false) {
		return INVALID_BOOK_ID;
	}

	const char* sql = "INSERT INTO book_info (id, book_name, author, publisher, category, publish_date, pages, total_book, remain_book, price, description, img_url, borrow_volume, del_flg) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		delete book;
		return SQLITE_DATABASE_ERROR;
	}

	rc = sqlite3_bind_int(stmt, 1, book->getBookId());
	rc = sqlite3_bind_text16(stmt, 2, book->getBookName().c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_text16(stmt, 3, book->getAuthor().c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_text16(stmt, 4, book->getPublisher().c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_text16(stmt, 5, book->getCategoryName().c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_text16(stmt, 6, book->getPublishDate().getWDate().c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_int(stmt, 7, book->getPages());
	rc = sqlite3_bind_int(stmt, 8, book->getTotalBook());
	rc = sqlite3_bind_int(stmt, 9, book->getRemainBook());
	rc = sqlite3_bind_double(stmt, 10, book->getPrice());
	rc = sqlite3_bind_text16(stmt, 11, book->getDescription().c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_text16(stmt, 12, book->getImgUrlWstring().c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_int(stmt, 13, book->getBorrowVolume());
	rc = sqlite3_bind_int(stmt, 14, book->getDelFlg());

	if (rc != SQLITE_OK) {
		std::cerr << "Failed to bind: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		delete book;
		return SQLITE_DATABASE_ERROR;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		sqlite3_finalize(stmt);
		delete book;
		return SUCESSFUL;
	}
	else {
		sqlite3_finalize(stmt);
		delete book;
		return SQLITE_DATABASE_ERROR;
	}
}

int Book::deleteBook(Book* book)
{
	if (checkBookIdValidaty(book->getBookId()))
	{
		return INVALID_BOOK_ID;
	}

	const char* sql = "UPDATE book_info SET del_flg = 1 WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return SQLITE_DATABASE_ERROR;
	}

	rc = sqlite3_bind_int(stmt, 1, book->getBookId());
	if (rc != SQLITE_OK)
	{
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return SQLITE_DATABASE_ERROR;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE)
	{
		sqlite3_finalize(stmt);
		return SUCESSFUL;
	}
	else
	{
		sqlite3_finalize(stmt);
		return SQLITE_DATABASE_ERROR;
	}
}

int Book::updateBook(Book* book)
{
	if (checkBookIdValidaty(book->getBookId()))
	{
		return INVALID_BOOK_ID;
	}

	const char* sql = "UPDATE book_info SET book_name = ?, author = ?, publisher = ?, category = ?, publish_date = ?, pages = ?, total_book = ?, remain_book = ?, price = ?, description = ?, img_url = ?, borrow_volume = ?, del_flg = ? WHERE id = ?";
	int rc;
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(mDatabase, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return SQLITE_DATABASE_ERROR;
	}

	rc = sqlite3_bind_text16(stmt, 1, book->getBookName().c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_text16(stmt, 2, book->getAuthor().c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_text16(stmt, 3, book->getPublisher().c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_text16(stmt, 4, book->getCategoryName().c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_text16(stmt, 5, book->getPublishDate().getWDate().c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_int(stmt, 6, book->getPages());
	rc = sqlite3_bind_int(stmt, 7, book->getTotalBook());
	rc = sqlite3_bind_int(stmt, 8, book->getRemainBook());
	rc = sqlite3_bind_double(stmt, 9, book->getPrice());
	rc = sqlite3_bind_text16(stmt, 10, book->getDescription().c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_text16(stmt, 11, book->getImgUrlWstring().c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_int(stmt, 12, book->getBorrowVolume());
	rc = sqlite3_bind_int(stmt, 13, book->getDelFlg());
	rc = sqlite3_bind_int(stmt, 14, book->getBookId());

	if (rc != SQLITE_OK)
	{
		std::cerr << "Failed to bind id: " << sqlite3_errmsg(mDatabase) << std::endl;
		sqlite3_finalize(stmt);
		return SQLITE_DATABASE_ERROR;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE)
	{
		sqlite3_finalize(stmt);
		return SUCESSFUL;
	}
	else
	{
		sqlite3_finalize(stmt);
		return SQLITE_DATABASE_ERROR;
	}
}

//@return true if the id is valid(not exist), false otherwise
int Book::checkBookIdValidaty(int id)
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
		int delFlg = sqlite3_column_int(stmt, 13);
		if (delFlg == 0)
		{
			sqlite3_finalize(stmt);
			return false;
		}
		else
		{
			sqlite3_finalize(stmt);
			return DELETED;
		}
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
		_imgUrl = std::wstring((const wchar_t*)sqlite3_column_text16(stmt, 11));
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
		_imgUrl = L"blankBook.jpg";
		_borrowVolume = 0;
		_delFlg = false;
	}

	sqlite3_finalize(stmt);
}