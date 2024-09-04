#include "RecordsPage.hpp"
#include "PageManager.hpp"
//#include "UserInfo.hpp"

RecordsPage::RecordsPage(User& user, PageManager& pageManager) :
	PageBase(user, pageManager),

	_topBarButton1(sf::Vector2f(100, 70), sf::Vector2f(720, 80), sf::Color::Transparent, L"首页", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Home); }),
	_topBarButton2(sf::Vector2f(100, 70), sf::Vector2f(870, 80), sf::Color::Transparent, L"书架", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Search); }),
	_topBarButton3(sf::Vector2f(150, 70), sf::Vector2f(1020, 80), sf::Color::Transparent, L"借阅记录", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Records); }),
	_topBarButton4(sf::Vector2f(210, 70), sf::Vector2f(1220, 80), sf::Color::Transparent, L"书籍统计分析", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Statistics); }),
	_topBarButton5(sf::Vector2f(150, 70), sf::Vector2f(1480, 80), sf::Color::Transparent, L"用户设置", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Setting); }),
	_topBarButton6(sf::Vector2f(100, 70), sf::Vector2f(1680, 80), sf::Color::Transparent, L"登录", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Login); }),

	_table(sf::Vector2f(1650, 700), sf::Vector2f(130, 200), _font, 30, { L"序号", L"书名", L"借书日期", L"应归还日期", L"归还日期" }, { 140.f, 700.f, 280.f, 280.f, 280.f }, 100.f, sf::Color(203, 140, 63, 128), sf::Color(240, 210, 170, 128), sf::Color(229, 182, 127, 128), false, [&](Book* book) {_bookDetailPopUpHandler(book); }, [](UserInfo* userInfo) {}, ALL_COLUMNS, -1),
	_bookDetailPopUp(_font),
	_borrowBookButton(sf::Vector2f(400, 70), sf::Vector2f(200, 950), sf::Color(203, 140, 63, 255), sf::Color::White, L"借书操作", _font, 30, [&]() {_openBorrowBookPopUp(); }),
	_returnBookButton(sf::Vector2f(400, 70), sf::Vector2f(700, 950), sf::Color(203, 140, 63, 255), sf::Color::White, L"还书操作", _font, 30, [&]() {_openReturnBookPopUp(); }),
	_popUpMsg(_font)
{
	_backgroundTexture.loadFromFile("Image/Background(1920x1080).png");

	_sprite.setScale(1, 1);
	_sprite.setPosition(0, 0);
	_sprite.setTexture(_backgroundTexture);
}

RecordsPage::~RecordsPage()
{

}

void RecordsPage::handleEvent(const sf::Event& event, sf::RenderWindow& window)
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

	_table.handleEvent(event, window);

	if (_user.getSelfUserInfo().getRole() == UserType::Admin)
	{
		_borrowBookButton.handleEvent(event, window);
		_returnBookButton.handleEvent(event, window);
	}
}

void RecordsPage::update(sf::Time dt)
{
	if (_popUpMsg.getPopUpVisiblity()) {
		_popUpMsg.update(dt);
		return;
	}

	if (_bookDetailPopUp.getPopUpVisiblity()) {
		_bookDetailPopUp.update(dt);
		return;
	}

	_table.update(dt);
}

void RecordsPage::render(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	window.draw(_sprite);

	_topBarButton1.render(window);
	_topBarButton2.render(window);
	_topBarButton3.render(window);
	_topBarButton4.render(window);
	_topBarButton5.render(window);
	_topBarButton6.render(window);

	_table.render(window);

	if (_user.getSelfUserInfo().getRole() == UserType::Admin)
	{
		_borrowBookButton.render(window);
		_returnBookButton.render(window);
	}

	_bookDetailPopUp.render(window);
	_popUpMsg.render(window);
	//window.display() called in main.cpp
}

void RecordsPage::onEnter()
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

	_topBarButton1.setButtonState(ButtonState::normal);
	_topBarButton2.setButtonState(ButtonState::normal);
	_topBarButton3.setButtonState(ButtonState::normal);
	_topBarButton4.setButtonState(ButtonState::normal);
	_topBarButton5.setButtonState(ButtonState::normal);
	_topBarButton6.setButtonState(ButtonState::normal);
	
	_showBorrowRecords();
}

void RecordsPage::_showBorrowRecords()
{
	if (_user.getSelfUserInfo().getRole() == UserType::Admin) {
		//show all records
		_table.setHeaders({ L"编号", L"姓名", L"书名", L"借书日期", L"应归还日期", L"归还日期" }, {200.f, 350.f, 500.f, 200.f, 200.f, 200.f});
		
		std::vector<std::vector<std::wstring>> rows;
		std::vector<Book> books;

		std::vector<UserInfo> users = UserInfo::getAllUsers();
		for (UserInfo user : users) {
			std::vector<BorrowBookDetail> borrowBookDetailList = user.getBorrowedBooks();
			std::sort(borrowBookDetailList.begin(), borrowBookDetailList.end(), [](BorrowBookDetail& a, BorrowBookDetail& b) {return a.getBorrowDate() > b.getBorrowDate(); });
			for (size_t i = 0; i < borrowBookDetailList.size(); i++) {
				Book book(borrowBookDetailList[i].getBookId());
				rows.push_back({std::to_wstring(user.getUserId()), user.getName(), book.getBookName(), borrowBookDetailList[i].getBorrowDate().getWDate(), borrowBookDetailList[i].getDueDate().getWDate(), borrowBookDetailList[i].getReturnDate().getWDate() });
				books.push_back(book);
			}
		}
		_table.setRows(std::move(rows), std::move(books));
	}
	else if (_user.getSelfUserInfo().getRole() == UserType::Student || _user.getSelfUserInfo().getRole() == UserType::Teacher) {
		_table.setHeaders({ L"序号", L"书名", L"借书日期", L"应归还日期", L"归还日期" }, { 140.f, 700.f, 280.f, 280.f, 280.f });
		//show records of current user
		std::vector<BorrowBookDetail> borrowBookDetailList = _user.getSelfUserInfo().getBorrowedBooks();
		std::sort(borrowBookDetailList.begin(), borrowBookDetailList.end(), [](BorrowBookDetail& a, BorrowBookDetail& b) {return a.getBorrowDate() > b.getBorrowDate(); });

		std::vector<std::vector<std::wstring>> rows;
		std::vector<Book> books;

		for (size_t i = 0; i < borrowBookDetailList.size(); i++) {
			Book book(borrowBookDetailList[i].getBookId());
			rows.push_back({ std::to_wstring(i + 1), book.getBookName(), borrowBookDetailList[i].getBorrowDate().getWDate(), borrowBookDetailList[i].getDueDate().getWDate(), borrowBookDetailList[i].getReturnDate().getWDate() });
			books.push_back(book);
		}
		_table.setRows(std::move(rows), std::move(books));
	}
	else {
		//show nothing
		_pageManager.setPage(Page::Login);
	}
}

void RecordsPage::_logoutHandler()
{
	_user.logout();
	_topBarButton6.setText(L"登录");
	_topBarButton6.setOnClickHandler([&]() {_pageManager.setPage(Page::Login); });
	_pageManager.setPage(Page::Login);
}

void RecordsPage::_openBorrowBookPopUp()
{
	_popUpMsg.OpenPopUp(L"借书操作", L"书籍编号", L"用户编号", true, [&]() {return _borrowBookHandler(); });
}

void RecordsPage::_openReturnBookPopUp()
{
	_popUpMsg.OpenPopUp(L"还书操作", L"书籍编号", L"用户编号", true, [&]() {return _returnBookHandler(); });
}

bool RecordsPage::_borrowBookHandler()
{
	int status = _user.borrowBook(_popUpMsg.getMsg1(), _popUpMsg.getMsg2());
	if (status == SUCESSFUL)
	{
		_showBorrowRecords();
		_popUpMsg.OpenPopUp(L"提示", L"借书成功", L"", false);
		return false;
	}
	else if (status == INVALID_USER_ID)
	{
		_popUpMsg.OpenPopUp(L"提示", L"用户ID无效", L"", false);
		return false;
	}
	else if (status == INVALID_BOOK_ID)
	{
		_popUpMsg.OpenPopUp(L"提示", L"书籍ID无效", L"", false);
		return false;
	}
	else if (status == NO_BOOK)
	{
		_popUpMsg.OpenPopUp(L"提示", L"书籍已借完", L"", false);
		return false;
	}
	else
	{
		_popUpMsg.OpenPopUp(L"提示", L"借书失败", L"", false);
		return false;
	}
}

bool RecordsPage::_returnBookHandler()
{
	int status = _user.returnBook(_popUpMsg.getMsg1(), _popUpMsg.getMsg2());
	if (status == SUCESSFUL)
	{
		_showBorrowRecords();
		_popUpMsg.OpenPopUp(L"提示", L"还书成功", L"", false);
		return false;
	}
	else if (status == INVALID_USER_ID)
	{
		_popUpMsg.OpenPopUp(L"提示", L"用户ID无效", L"", false);
		return false;
	}
	else if (status == INVALID_BOOK_ID)
	{
		_popUpMsg.OpenPopUp(L"提示", L"书籍ID无效", L"", false);
		return false;
	}
	else if (status == NO_BOOK)
	{
		_popUpMsg.OpenPopUp(L"提示", L"此用户未借此书", L"", false);
		return false;
	}
	else
	{
		_popUpMsg.OpenPopUp(L"提示", L"还书失败", L"", false);
		return false;
	}
}

void RecordsPage::_bookDetailPopUpHandler(Book* book)
{
	_bookDetailPopUp.setBook(book);
	_bookDetailPopUp.setPopUpVisiblity(true, false);
}