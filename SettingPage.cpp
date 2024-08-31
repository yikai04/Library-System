#include "SettingPage.hpp"
#include "PageManager.hpp"


SettingPage::SettingPage(User& user, PageManager& pageManager) :
	PageBase(user, pageManager),

	_topBarButton1(sf::Vector2f(100, 70), sf::Vector2f(720, 80), sf::Color::Transparent, L"首页", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Home); }),
	_topBarButton2(sf::Vector2f(100, 70), sf::Vector2f(870, 80), sf::Color::Transparent, L"书架", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Search); }),
	_topBarButton3(sf::Vector2f(150, 70), sf::Vector2f(1020, 80), sf::Color::Transparent, L"借阅记录", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Records); }),
	_topBarButton4(sf::Vector2f(210, 70), sf::Vector2f(1220, 80), sf::Color::Transparent, L"书籍统计分析", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Statistics); }),
	_topBarButton5(sf::Vector2f(150, 70), sf::Vector2f(1480, 80), sf::Color::Transparent, L"用户设置", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Setting); }),
	_topBarButton6(sf::Vector2f(100, 70), sf::Vector2f(1680, 80), sf::Color::Transparent, L"登录", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Login); }),

	_username(sf::Vector2f(430, 50), sf::Vector2f(420, 570), _font, 30, sf::Color::Transparent, L"用户名", L"", true, [&]() {return _updateUsername(); }),
	_email(sf::Vector2f(430, 50), sf::Vector2f(420, 680), _font, 30, sf::Color::Transparent, L"电子邮箱", L"", true, [&]() {return _updateEmail(); }),
	_name(sf::Vector2f(430, 50), sf::Vector2f(1020, 570), _font, 30, sf::Color::Transparent, L"姓名", L"", true, [&]() {return _updateName(); }),
	_id(sf::Vector2f(430, 50), sf::Vector2f(1020, 680), _font, 30, sf::Color::Transparent, L"编号", L"", true, [&]() {return _updateId(); }),
	_registerDate(sf::Vector2f(150, 50), sf::Vector2f(900, 985), _font, 24, sf::Color::Transparent, L"注册日期", L"", false),
	_gender(sf::Vector2f(430, 50), sf::Vector2f(1020, 790), _font, 30, sf::Color(240, 240, 240, 255), L"", { L"男", L"女" }, true, [&]() {return _updateGender(); }),
	_role(sf::Vector2f(430, 50), sf::Vector2f(1020, 900), _font, 30, sf::Color(240, 240, 240, 255), L"", { L"学生", L"教师" }, true, [&]() {return _updateRole(); }),
	_password(480.f, sf::Vector2f(420, 790), _font, 35, L"密码", sf::Color::Transparent, true),
	_confirmPassword(430.f, sf::Vector2f(420, 900), _font, 35, L"确认密码", sf::Color::Transparent, true),
	_changePasswordButton(sf::Vector2f(50, 50), sf::Vector2f(850, 900), "Icon/tickIcon.png", [&]() {_updatePassword(); }),
	_deleteAccountButton(sf::Vector2f(600, 50), sf::Vector2f(1550, 250), sf::Color::Transparent, L"注销账号", _font, 30, 33, sf::Color::Red, sf::Color::Red, [&]() {_deleteAccountHandler(); }, true)
{
	_backgroundTexture.loadFromFile("Image/SettingPage.png");

	_sprite.setScale(1, 1);
	_sprite.setPosition(0, 0);
	_sprite.setTexture(_backgroundTexture);

}

SettingPage::~SettingPage()
{

}

void SettingPage::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	_topBarButton1.handleEvent(event, window);
	_topBarButton2.handleEvent(event, window);
	_topBarButton3.handleEvent(event, window);
	_topBarButton4.handleEvent(event, window);
	_topBarButton5.handleEvent(event, window);
	_topBarButton6.handleEvent(event, window);

	_username.handleEvent(event, window);
	_email.handleEvent(event, window);
	_name.handleEvent(event, window);
	_id.handleEvent(event, window);
	_registerDate.handleEvent(event, window);
	_gender.handleEvent(event, window);
	_role.handleEvent(event, window);
	_password.handleEvent(event, window);
	_confirmPassword.handleEvent(event, window);
	_changePasswordButton.handleEvent(event, window);
	_deleteAccountButton.handleEvent(event, window);
}

void SettingPage::update(sf::Time dt)
{
	_username.update(dt);
	_email.update(dt);
	_name.update(dt);
	_id.update(dt);
	_registerDate.update(dt);
	_password.update(dt);
	_confirmPassword.update(dt);
}

void SettingPage::render(sf::RenderWindow& window)
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
	_email.render(window);
	_name.render(window);
	_id.render(window);
	_registerDate.render(window);
	_gender.render(window);
	_role.render(window);
	_password.render(window);
	_confirmPassword.render(window);
	_changePasswordButton.render(window);
	_deleteAccountButton.render(window);
	//window.display() called in main.cpp
}

void SettingPage::onEnter()
{
	_showUserInfo();

	if (_user.getSelfUserInfo().getRole() != UserType::Guest) {
		_topBarButton6.setText(L"登出");
		_topBarButton6.setOnClickHandler([&]() {_logoutHandler(); });
	}
}

void SettingPage::_logoutHandler()
{
	_user.logout();
	_topBarButton6.setText(L"登录");
	_topBarButton6.setOnClickHandler([&]() {_pageManager.setPage(Page::Login); });
	_pageManager.setPage(Page::Login);
}

void SettingPage::_showUserInfo()
{
	UserInfo userInfo = _user.getSelfUserInfo();
	if (userInfo.getRole() == UserType::Admin) {

	}
	else if (userInfo.getRole() == UserType::Student || userInfo.getRole() == UserType::Teacher) {
		_username.setText(userInfo.getUsername());
		_email.setText(userInfo.getEmail());
		_name.setText(userInfo.getName());
		_id.setText(std::to_wstring(userInfo.getUserId()));
		_registerDate.setText(userInfo.getRegisterDate().getWDate());
		
		if (userInfo.getGender() == L"M") {
			_gender.setText(L"男");
		}
		else if (userInfo.getGender() == L"F") {
			_gender.setText(L"女");
		}

		if (userInfo.getRole() == UserType::Student) {
			_role.setText(L"学生");
		}
		else if (userInfo.getRole() == UserType::Teacher) {
			_role.setText(L"教师");
		}
	}
	else {
		_pageManager.setPage(Page::Login);
	}
}

void SettingPage::_deleteAccountHandler()
{
	_user.deleteAccount(_user.getSelfUserInfo());
	_pageManager.setPage(Page::Login);
}

bool SettingPage::_updateUsername()
{
	return _user.getSelfUserInfo().changeUsername(_username.getText());
}

bool SettingPage::_updateEmail()
{
	return _user.getSelfUserInfo().changeEmail(_email.getText());
}

bool SettingPage::_updateName()
{
	return _user.getSelfUserInfo().changeName(_name.getText());
}

bool SettingPage::_updateId()
{
	return _user.getSelfUserInfo().changeId(_id.getText());
}

bool SettingPage::_updateGender()
{

	return _user.getSelfUserInfo().changeGender(_gender.getText());
}

bool SettingPage::_updateRole()
{
	return _user.getSelfUserInfo().changeRole(_role.getText());
}

void SettingPage::_updatePassword()
{
	if (_password.getText() == _confirmPassword.getText()) {
		if (_user.getSelfUserInfo().changePassword(_password.getText())) {
			_password.setText(L"");
			_confirmPassword.setText(L"");
		}
	}
}