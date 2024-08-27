#include "RecordsPage.hpp"
#include "PageManager.hpp"


RecordsPage::RecordsPage(User& user, PageManager& pageManager) :
	PageBase(user, pageManager),

	_topBarButton1(sf::Vector2f(100, 70), sf::Vector2f(720, 80), sf::Color::Transparent, L"首页", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Home); }),
	_topBarButton2(sf::Vector2f(100, 70), sf::Vector2f(870, 80), sf::Color::Transparent, L"书架", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Search); }),
	_topBarButton3(sf::Vector2f(150, 70), sf::Vector2f(1020, 80), sf::Color::Transparent, L"借阅记录", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Records); }),
	_topBarButton4(sf::Vector2f(210, 70), sf::Vector2f(1220, 80), sf::Color::Transparent, L"书籍统计分析", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Statistics); }),
	_topBarButton5(sf::Vector2f(150, 70), sf::Vector2f(1480, 80), sf::Color::Transparent, L"用户设置", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Setting); }),
	_topBarButton6(sf::Vector2f(100, 70), sf::Vector2f(1680, 80), sf::Color::Transparent, L"登录", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Login); }),

	_table(sf::Vector2f(1650,600), sf::Vector2f(130,200), _font, 30, {L"序号", L"书名", L"借书日期", L"归还日期", L"备注"}, {150.f, 600.f, 250.f, 250.f, 400.f}, 100.f, sf::Color::Cyan, sf::Color::White, sf::Color::Magenta)
{
	_backgroundTexture.loadFromFile("Image/Background(1920x1080).png");

	_sprite.setScale(1, 1);
	_sprite.setPosition(0, 0);
	_sprite.setTexture(_backgroundTexture);

	//_table.setRows({ { L"1", L"书名1", L"2020-01-01", L"2020-01-02", L"备注1" }, { L"2", L"书名2", L"2020-01-01", L"2020-01-02", L"备注2" }, { L"3", L"书名3", L"2020-01-01", L"2020-01-02", L"备注3" } });
	
}

RecordsPage::~RecordsPage()
{

}

void RecordsPage::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	_topBarButton1.handleEvent(event, window);
	_topBarButton2.handleEvent(event, window);
	_topBarButton3.handleEvent(event, window);
	_topBarButton4.handleEvent(event, window);
	_topBarButton5.handleEvent(event, window);
	_topBarButton6.handleEvent(event, window);

	_table.handleEvent(event, window);
}

void RecordsPage::update(sf::Time dt)
{

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
	//window.display() called in main.cpp
}

void RecordsPage::onEnter()
{
	_showBorrowRecords();

	if (_user.getUserType() != UserType::Guest) {
		_topBarButton6.setText(L"登出");
		_topBarButton6.setOnClickHandler([&]() {_logoutHandler(); });
	}
}

void RecordsPage::_showBorrowRecords()
{
	if (_user.getUserType() == UserType::Admin) {
		//show all records
	}
	else if (_user.getUserType() == UserType::Student || _user.getUserType() == UserType::Teacher) {
		//show records of current user
		std::vector<BorrowBookDetail> borrowBookDetailList = _user.getBorrowedBooks();
		std::vector<std::vector<std::wstring>> rows;
		std::vector<Book> books;

		for (int i = 0; i < borrowBookDetailList.size(); i++) {
			Book book = _user.getBookInfoById(borrowBookDetailList[i].getBookId());
			rows.push_back({ std::to_wstring(i + 1), book.getBookName(), borrowBookDetailList[i].getBorrowDate().getWDate(), borrowBookDetailList[i].getReturnDate().getWDate(), L""});
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