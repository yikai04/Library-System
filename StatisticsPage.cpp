#include "StatisticsPage.hpp"
#include "PageManager.hpp"


StatisticsPage::StatisticsPage(User& user, PageManager& pageManager) :
	PageBase(user, pageManager),

	_topBarButton1(sf::Vector2f(100, 70), sf::Vector2f(720, 80), sf::Color::Transparent, L"首页", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Home); }),
	_topBarButton2(sf::Vector2f(100, 70), sf::Vector2f(870, 80), sf::Color::Transparent, L"书架", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Search); }),
	_topBarButton3(sf::Vector2f(150, 70), sf::Vector2f(1020, 80), sf::Color::Transparent, L"借阅记录", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Records); }),
	_topBarButton4(sf::Vector2f(210, 70), sf::Vector2f(1220, 80), sf::Color::Transparent, L"书籍统计分析", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Statistics); }),
	_topBarButton5(sf::Vector2f(150, 70), sf::Vector2f(1480, 80), sf::Color::Transparent, L"用户设置", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Setting); }),
	_topBarButton6(sf::Vector2f(100, 70), sf::Vector2f(1680, 80), sf::Color::Transparent, L"登录", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Login); }),

	_topBorrowedBooksTable(sf::Vector2f(800, 250), sf::Vector2f(130, 200), _font, 20, { L"排名", L"书名", L"借阅量" }, { 200.f, 400.f, 200.f }, 50.f, sf::Color(203, 140, 63, 128), sf::Color(240, 210, 170, 128), sf::Color(229, 182, 127, 128), false),
	_topBorrowedUsersTable(sf::Vector2f(800, 250), sf::Vector2f(1000, 200), _font, 20, { L"排名", L"用户名", L"借阅量" }, { 200.f, 400.f, 200.f }, 50.f, sf::Color(203, 140, 63, 128), sf::Color(240, 210, 170, 128), sf::Color(229, 182, 127, 128), false)
{
	_backgroundTexture.loadFromFile("Image/Background(1920x1080).png");

	_sprite.setScale(1, 1);
	_sprite.setPosition(0, 0);
	_sprite.setTexture(_backgroundTexture);

	_topBorrowedBooksTable.setLeftArrowSize(sf::Vector2f(40, 40));
	_topBorrowedBooksTable.setRightArrowSize(sf::Vector2f(40, 40));
	_topBorrowedBooksTable.setLeftArrowPosition(sf::Vector2f(700, 520));
	_topBorrowedBooksTable.setRightArrowPosition(sf::Vector2f(760, 520));
	_topBorrowedBooksTable.setPageNumberPosition(sf::Vector2f(830, 520));
}

StatisticsPage::~StatisticsPage()
{

}

void StatisticsPage::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	_topBarButton1.handleEvent(event, window);
	_topBarButton2.handleEvent(event, window);
	_topBarButton3.handleEvent(event, window);
	_topBarButton4.handleEvent(event, window);
	_topBarButton5.handleEvent(event, window);
	_topBarButton6.handleEvent(event, window);

	_topBorrowedBooksTable.handleEvent(event, window);
	_topBorrowedUsersTable.handleEvent(event, window);
}

void StatisticsPage::update(sf::Time dt)
{
	_topBorrowedBooksTable.update(dt);
	_topBorrowedUsersTable.update(dt);
}

void StatisticsPage::render(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	window.draw(_sprite);

	_topBarButton1.render(window);
	_topBarButton2.render(window);
	_topBarButton3.render(window);
	_topBarButton4.render(window);
	_topBarButton5.render(window);
	_topBarButton6.render(window);

	_topBorrowedBooksTable.render(window);
	_topBorrowedUsersTable.render(window);
	//window.display() called in main.cpp
}

void StatisticsPage::onEnter()
{
	if (_user.getSelfUserInfo().getRole() != UserType::Guest) {
		_topBarButton6.setText(L"登出");
		_topBarButton6.setOnClickHandler([&]() {_logoutHandler(); });
	}

	_topBarButton1.setButtonState(ButtonState::normal);
	_topBarButton2.setButtonState(ButtonState::normal);
	_topBarButton3.setButtonState(ButtonState::normal);
	_topBarButton4.setButtonState(ButtonState::normal);
	_topBarButton5.setButtonState(ButtonState::normal);
	_topBarButton6.setButtonState(ButtonState::normal);

	_showTopBorrowedBooks();
	_showTopBorrowedUsers();
}

void StatisticsPage::_logoutHandler()
{
	_user.logout();
	_topBarButton6.setText(L"登录");
	_topBarButton6.setOnClickHandler([&]() {_pageManager.setPage(Page::Login); });
	_pageManager.setPage(Page::Login);
}

void StatisticsPage::_showTopBorrowedBooks()
{
	std::vector<Book> allBooks = Book::getAllBooks();
	std::sort(allBooks.begin(), allBooks.end(), [](Book& a, Book& b) {return a.getBorrowVolume() > b.getBorrowVolume(); });

	std::vector<std::vector<std::wstring>> rows;

	for (size_t i = 0; i < allBooks.size(); i++)
	{
		rows.push_back({ std::to_wstring(i + 1), allBooks[i].getBookName(), std::to_wstring(allBooks[i].getBorrowVolume()) });
	}

	_topBorrowedBooksTable.setRows(std::move(rows), std::move(allBooks));
}

void StatisticsPage::_showTopBorrowedUsers()
{
	std::vector<UserInfo> allUsers = UserInfo::getAllUsers();
	std::sort(allUsers.begin(), allUsers.end(), [](UserInfo& a, UserInfo& b) {return a.getBorrowVolume() > b.getBorrowVolume(); });

	std::vector<std::vector<std::wstring>> rows;

	for (size_t i = 0; i < allUsers.size(); i++)
	{
		rows.push_back({ std::to_wstring(i + 1), allUsers[i].getUsername(), std::to_wstring(allUsers[i].getBorrowVolume()) });
	}

	_topBorrowedUsersTable.setRows(std::move(rows));
}