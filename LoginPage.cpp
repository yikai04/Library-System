#include "LoginPage.hpp"
#include "PageManager.hpp"

LoginPage::LoginPage(User& user, PageManager& pageManager) :
    PageBase(user, pageManager),

    _topBarButton1(sf::Vector2f(100, 70), sf::Vector2f(720, 80), sf::Color::Transparent, L"首页", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Home); }),
    _topBarButton2(sf::Vector2f(100, 70), sf::Vector2f(870, 80), sf::Color::Transparent, L"书架", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Search); }),
    _topBarButton3(sf::Vector2f(150, 70), sf::Vector2f(1020, 80), sf::Color::Transparent, L"借阅记录", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Records); }),
    _topBarButton4(sf::Vector2f(210, 70), sf::Vector2f(1220, 80), sf::Color::Transparent, L"书籍统计分析", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Statistics); }),
    _topBarButton5(sf::Vector2f(150, 70), sf::Vector2f(1480, 80), sf::Color::Transparent, L"用户设置", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Setting); }),
    _topBarButton6(sf::Vector2f(100, 70), sf::Vector2f(1680, 80), sf::Color::Transparent, L"登录", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Login); }),

    _username(550.f, sf::Vector2f(660, 500), _font, 35, L"用户名", sf::Color::Transparent,false),
	_password(550.f, sf::Vector2f(660, 625), _font, 35, L"密码", sf::Color::Transparent, true),
	_loginButton(sf::Vector2f(600, 70), sf::Vector2f(630, 755), [&]() {_loginHandler(); }, sf::Color::Transparent),
	_signupButton(sf::Vector2f(600, 50), sf::Vector2f(630, 840), sf::Color::Transparent, L"没有账号？ 注册", _font, 22, 20, sf::Color(203, 140, 63, 255), sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Signup); }, false),
	_popUpMsg(_font)
{
    _backgroundTexture.loadFromFile("Image/LoginPage.png");
    _sprite.setScale(1, 1);
    _sprite.setPosition(0, 0);
    _sprite.setTexture(_backgroundTexture);
}

LoginPage::~LoginPage()
{

}

void LoginPage::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    if (_popUpMsg.getPopUpVisiblity())
    {
        _popUpMsg.handleEvent(event, window);
        return;
    }

    _topBarButton1.handleEvent(event, window);
    _topBarButton2.handleEvent(event, window);
    _topBarButton3.handleEvent(event, window);
    _topBarButton4.handleEvent(event, window);
    _topBarButton5.handleEvent(event, window);
    _topBarButton6.handleEvent(event, window);

	_username.handleEvent(event, window);
	_password.handleEvent(event, window);
	_loginButton.handleEvent(event, window);
	_signupButton.handleEvent(event, window);
}

void LoginPage::update(sf::Time dt)
{
    if (_popUpMsg.getPopUpVisiblity()) {
        _popUpMsg.update(dt);
        return;
    }

	_username.update(dt);
	_password.update(dt);
}

void LoginPage::render(sf::RenderWindow& window)
{
    window.clear(sf::Color::White);
    window.draw(_sprite);
    _topBarButton1.render(window);
    _topBarButton2.render(window);
    _topBarButton3.render(window);
    _topBarButton4.render(window);
    _topBarButton5.render(window);
    _topBarButton6.render(window);

	_username.render(window);
	_password.render(window);
	_loginButton.render(window);
	_signupButton.render(window);
	_popUpMsg.render(window);
    //window.display() called in main.cpp
}

void LoginPage::onEnter()
{
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

    _username.setText(L"");
    _password.setText(L"");
}

void LoginPage::_loginHandler()
{
	int status = _user.login(_username.getText(), _password.getText());
    
    if (status == LOGIN_SUCESSFUL) {
        if (_pageManager.getLastPage() == Page::Setting && _user.getSelfUserInfo().getRole() == UserType::Admin) {
			_pageManager.setPage(Page::UserManagement);
        }
		else if (_pageManager.getLastPage() != Page::Login && _pageManager.getLastPage() != Page::Signup)
			_pageManager.setPage(_pageManager.getLastPage());
		else
			_pageManager.setPage(Page::Home);
        return;
    }
	else if (status == WRONG_PASSWORD) {
        _password.setText(L"");
        _popUpMsg.OpenPopUp(L"提示", L"密码错误", L"", false);
    }
    else if (status == INVALID_USERNAME) {
        _username.setText(L"");
        _password.setText(L"");
		_popUpMsg.OpenPopUp(L"提示", L"用户名不存在", L"", false);
    }
    else {
		_popUpMsg.OpenPopUp(L"提示", L"未知错误", L"", false);
    }
}

void LoginPage::_logoutHandler()
{
    _user.logout();
    _topBarButton6.setText(L"登录");
    _topBarButton6.setOnClickHandler([&]() {_pageManager.setPage(Page::Login); });
    _pageManager.setPage(Page::Login);
}