#include "SearchPage.hpp"
#include "PageManager.hpp"


SearchPage::SearchPage(User& user, PageManager& pageManager) :
	PageBase(user, pageManager),
	
	_topBarButton1(sf::Vector2f(100, 70), sf::Vector2f(720, 80), sf::Color::Transparent, L"首页", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Home); }),
	_topBarButton2(sf::Vector2f(100, 70), sf::Vector2f(870, 80), sf::Color::Transparent, L"书架", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Search); }),
	_topBarButton3(sf::Vector2f(150, 70), sf::Vector2f(1020, 80), sf::Color::Transparent, L"借阅记录", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Records); }),
	_topBarButton4(sf::Vector2f(210, 70), sf::Vector2f(1220, 80), sf::Color::Transparent, L"书籍统计分析", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Statistics); }),
	_topBarButton5(sf::Vector2f(150, 70), sf::Vector2f(1480, 80), sf::Color::Transparent, L"用户设置", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Setting); }),
	_topBarButton6(sf::Vector2f(100, 70), sf::Vector2f(1680, 80), sf::Color::Transparent, L"登录", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Login); }),

	_booksDisplay(_font, [&](Book* book) {_bookDetailPopUpHandler(book); }),
	_searchBar(700.0, sf::Vector2f(650, 220), L"搜索", _font, 42, [&]() {_searchBarHandler(); }),
	_bookDetailPopUp(_font, false, false, false, [&](Book* book) {return _editBookHandler(book); }, [&](Book* book) {_deleteBookHandler(book); }),
	_newBookButton(sf::Vector2f(150, 70), sf::Vector2f(1680, 250), sf::Color::Transparent, L"增加书籍", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_newBookHandler(); }),
	_isNewBookButtonClicked(false),
	_isCalledSearch(false),
	_popUpMsg(_font)
{
	_backgroundTexture.loadFromFile("Image/Background(1920x1080).png");

	_sprite.setScale(1, 1);
	_sprite.setPosition(0, 0);
	_sprite.setTexture(_backgroundTexture);
}

SearchPage::~SearchPage()
{

}

void SearchPage::search(std::wstring searchText)
{
	_searchBar.setText(searchText);
	_isCalledSearch = true;
}

void SearchPage::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	if (_popUpMsg.getPopUpVisiblity())
	{
		_popUpMsg.handleEvent(event, window);
		return;
	}

	if (_bookDetailPopUp.getPopUpVisiblity())
	{
		_bookDetailPopUp.handleEvent(event, window);
		return;
	}
	_topBarButton1.handleEvent(event, window);
	_topBarButton2.handleEvent(event, window);
	_topBarButton3.handleEvent(event, window);
	_topBarButton4.handleEvent(event, window);
	_topBarButton5.handleEvent(event, window);
	_topBarButton6.handleEvent(event, window);

	_searchBar.handleEvent(event, window);
	if (!_searchBar.getDropDownVisibility()) {
		_booksDisplay.handleEvent(event, window);
	}

	if (_user.getSelfUserInfo().getRole() == UserType::Admin) {
		_newBookButton.handleEvent(event, window);
	}
}

void SearchPage::update(sf::Time dt)
{
	if (_popUpMsg.getPopUpVisiblity()) {
		_popUpMsg.update(dt);
		return;
	}

	if (_bookDetailPopUp.getPopUpVisiblity()) {
		_bookDetailPopUp.update(dt);
		return;
	}

	_searchBar.update(dt);
}

void SearchPage::render(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	window.draw(_sprite);
	
	_topBarButton1.render(window);
	_topBarButton2.render(window);
	_topBarButton3.render(window);
	_topBarButton4.render(window);
	_topBarButton5.render(window);
	_topBarButton6.render(window);

	_booksDisplay.render(window);
	_searchBar.render(window);

	if (_user.getSelfUserInfo().getRole() == UserType::Admin) {
		_newBookButton.render(window);
	}

	_bookDetailPopUp.render(window);
	_popUpMsg.render(window);
	//window.display() called in main.cpp
}

void SearchPage::onEnter()
{
	if (_user.getSelfUserInfo().getRole() != UserType::Guest) {
		_topBarButton6.setText(L"登出");
		_topBarButton6.setOnClickHandler([&]() {_logoutHandler(); });
	}

	if (_user.getSelfUserInfo().getRole() == UserType::Admin)
	{
		_topBarButton5.setText(L"用户管理");
		_topBarButton5.setOnClickHandler([&]() {_pageManager.setPage(Page::UserManagement); });
	}
	else if (_user.getSelfUserInfo().getRole() == UserType::Student || _user.getSelfUserInfo().getRole() == UserType::Teacher)
	{
		_topBarButton5.setText(L"用户设置");
		_topBarButton5.setOnClickHandler([&]() {_pageManager.setPage(Page::Setting); });
	}

	if (_user.getSelfUserInfo().getRole() == UserType::Admin) {
		_bookDetailPopUp.setEditable(true);
	}
	else {
		_bookDetailPopUp.setEditable(false);
	}

	_topBarButton1.setButtonState(ButtonState::normal);
	_topBarButton2.setButtonState(ButtonState::normal);
	_topBarButton3.setButtonState(ButtonState::normal);
	_topBarButton4.setButtonState(ButtonState::normal);
	_topBarButton5.setButtonState(ButtonState::normal);
	_topBarButton6.setButtonState(ButtonState::normal);

	std::vector<Book> allBooks = Book::searchBooksInfo();
	_booksDisplay.setBooks(std::move(allBooks));

	if (!_isCalledSearch) {
		_searchBar.setText(L"");
	}
	else {
		_searchBarHandler();
		_isCalledSearch = false;
	}
}

void SearchPage::_searchBarHandler()
{
	std::vector<Book> searchedBooks;

	if (_searchBar.getFilter() == L"全部") {
		searchedBooks = Book::searchBooksInfo(_searchBar.getSearchWord(), _searchBar.getCategory());
	}
	else if (_searchBar.getFilter() == L"书名") {
		searchedBooks = Book::searchBooksInfoByName(_searchBar.getSearchWord(), _searchBar.getCategory());
	}
	else if (_searchBar.getFilter() == L"作者") {
		searchedBooks = Book::searchBooksInfoByAuthor(_searchBar.getSearchWord(), _searchBar.getCategory());
	}
	else if (_searchBar.getFilter() == L"出版社") {
		searchedBooks = Book::searchBooksInfoByPublisher(_searchBar.getSearchWord(), _searchBar.getCategory());
	}
	else {
		return;
	}

	if (searchedBooks.empty()) {
		_popUpMsg.OpenPopUp(L"提示", L"未找到相关书籍", L"", false);
	}

	_booksDisplay.setBooks(std::move(searchedBooks));
}

void SearchPage::_logoutHandler()
{
	_user.logout();
	_topBarButton6.setText(L"登录");
	_topBarButton6.setOnClickHandler([&]() {_pageManager.setPage(Page::Login); });
	_pageManager.setPage(Page::Login);
}

void SearchPage::_bookDetailPopUpHandler(Book* book)
{
	_bookDetailPopUp.setBook(book);
	_bookDetailPopUp.setPopUpVisiblity(true, false);

}

bool SearchPage::_editBookHandler(Book* book)
{
	if (_user.getSelfUserInfo().getRole() == UserType::Admin) {
		if (_isNewBookButtonClicked) {
			_isNewBookButtonClicked = false;
			int status = book->addBook(book);
			if (status == SUCESSFUL) {
				return true;
			}
			else if (status == ID_EXIST) {
				_popUpMsg.OpenPopUp(L"提示", L"书籍ID已存在", L"", false);
				return false;
			}
			else {
				_popUpMsg.OpenPopUp(L"提示", L"添加书籍失败", L"", false);
				return false;
			}
		}
		else {
			int status = book->updateBook(book);
			if (status == SUCESSFUL) {
				return true;
			}
			else if (status == ID_EXIST) {
				_popUpMsg.OpenPopUp(L"提示", L"书籍ID不存在", L"", false);
				return false;
			}
			else {
				_popUpMsg.OpenPopUp(L"提示", L"更新书籍失败", L"", false);
				return false;
			}
		}
	}
	else {
		return false;
	}
}

void SearchPage::_deleteBookHandler(Book* book)
{
	if (_user.getSelfUserInfo().getRole() == UserType::Admin) {
		book->deleteBook(book);
	}
}

void SearchPage::_newBookHandler()
{
	_bookDetailPopUp.setPopUpVisiblity(true, true);
	_isNewBookButtonClicked = true;
	Book* newBook = new Book();
	_bookDetailPopUp.setBook(newBook);
}