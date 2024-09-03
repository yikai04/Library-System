#include "UserManagementPage.hpp"
#include "PageManager.hpp"

UserManagementPage::UserManagementPage(User& user, PageManager& pageManager) :
	PageBase(user, pageManager),

	_topBarButton1(sf::Vector2f(100, 70), sf::Vector2f(720, 80), sf::Color::Transparent, L"首页", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Home); }),
	_topBarButton2(sf::Vector2f(100, 70), sf::Vector2f(870, 80), sf::Color::Transparent, L"书架", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Search); }),
	_topBarButton3(sf::Vector2f(150, 70), sf::Vector2f(1020, 80), sf::Color::Transparent, L"借阅记录", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Records); }),
	_topBarButton4(sf::Vector2f(210, 70), sf::Vector2f(1220, 80), sf::Color::Transparent, L"书籍统计分析", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Statistics); }),
	_topBarButton5(sf::Vector2f(150, 70), sf::Vector2f(1480, 80), sf::Color::Transparent, L"用户管理", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::UserManagement); }),
	_topBarButton6(sf::Vector2f(100, 70), sf::Vector2f(1680, 80), sf::Color::Transparent, L"登录", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Login); }),

	_table(sf::Vector2f(1650, 700), sf::Vector2f(130, 200), _font, 30, { L"序号", L"编号", L"姓名", L"性别", L"身份", L"电子邮箱", L"借阅量" }, { 150.f, 200.f, 350.f, 100.f, 200.f, 450.f, 200.f }, 100.f, sf::Color(203, 140, 63, 128), sf::Color(240, 210, 170, 128), sf::Color(229, 182, 127, 128), false, [](Book* book) {}, [=](UserInfo* user) { _editUserHandler(user); }, -1, ALL_COLUMNS)
{
	_backgroundTexture.loadFromFile("Image/Background(1920x1080).png");

	_sprite.setScale(1, 1);
	_sprite.setPosition(0, 0);
	_sprite.setTexture(_backgroundTexture);

}

UserManagementPage::~UserManagementPage()
{

}

void UserManagementPage::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	_topBarButton1.handleEvent(event, window);
	_topBarButton2.handleEvent(event, window);
	_topBarButton3.handleEvent(event, window);
	_topBarButton4.handleEvent(event, window);
	_topBarButton5.handleEvent(event, window);
	_topBarButton6.handleEvent(event, window);

	_table.handleEvent(event, window);
}

void UserManagementPage::update(sf::Time dt)
{
	_table.update(dt);
}

void UserManagementPage::render(sf::RenderWindow& window)
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

void UserManagementPage::onEnter()
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

	_showUsersDetail();
}

void UserManagementPage::_showUsersDetail()
{
	std::vector<std::vector<std::wstring>> rows;

	std::vector<UserInfo> users = UserInfo::getAllUsers();
	for (size_t i = 0; i < users.size(); i++) {
		rows.push_back({ std::to_wstring(i + 1), std::to_wstring(users[i].getUserId()), users[i].getName(), users[i].getGender(), userTypeToWString(users[i].getRole()), users[i].getEmail(), std::to_wstring(users[i].getBorrowVolume())});
	}
	_table.setRows(std::move(rows), {}, std::move(users));
}

void UserManagementPage::_logoutHandler()
{
	_user.logout();
	_topBarButton6.setText(L"登录");
	_topBarButton6.setOnClickHandler([&]() {_pageManager.setPage(Page::Login); });
	_pageManager.setPage(Page::Login);
}

void UserManagementPage::_editUserHandler(UserInfo* user)
{
	_pageManager.userManagementPageSearch(std::to_wstring(user->getUserId()));
	_pageManager.setPage(Page::Setting);
}