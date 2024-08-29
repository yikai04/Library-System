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

	_username(sf::Vector2f(430, 50), sf::Vector2f(420, 570), _font, 30, sf::Color::Transparent, L"用户名", L"", true),
	_email(sf::Vector2f(430, 50), sf::Vector2f(420, 680), _font, 30, sf::Color::Transparent, L"电子邮箱", L"", true, [&]() {return _updateEmail(); }),
	_name(sf::Vector2f(430, 50), sf::Vector2f(1020, 570), _font, 30, sf::Color::Transparent, L"姓名", L"", true, [&]() {return _updateName(); }),
	_id(sf::Vector2f(430, 50), sf::Vector2f(1020, 680), _font, 30, sf::Color::Transparent, L"编号", L"", true),
	_registerDate(sf::Vector2f(150, 50), sf::Vector2f(900, 985), _font, 24, sf::Color::Transparent, L"注册日期", L"", false),
	_gender(sf::Vector2f(480, 50), sf::Vector2f(1020, 790), sf::Color(240, 240, 240, 255), _font, 30),
	_role(sf::Vector2f(480, 50), sf::Vector2f(1020, 900), sf::Color(240, 240, 240, 255), _font, 30),
	_password(480.f, sf::Vector2f(420, 790), _font, 35, L"密码", sf::Color::Transparent, true),
	_confirmPassword(480.f, sf::Vector2f(420, 900), _font, 35, L"确认密码", sf::Color::Transparent, true)
{
	_backgroundTexture.loadFromFile("Image/SettingPage.png");

	_sprite.setScale(1, 1);
	_sprite.setPosition(0, 0);
	_sprite.setTexture(_backgroundTexture);

	_gender.setOptions({ L"男", L"女"} );
	_role.setOptions({ L"学生", L"教师" });
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
	//window.display() called in main.cpp
}

void SettingPage::onEnter()
{
	_showUserInfo();

	if (_user.getUserType() != UserType::Guest) {
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
	if (_user.getUserType() == UserType::Admin) {

	}
	else if (_user.getUserType() == UserType::Student || _user.getUserType() == UserType::Teacher) {
		_username.setText(_user.getUsername());
		_email.setText(_user.getEmail());
		_name.setText(_user.getName());
		_id.setText(_user.getId());
		_registerDate.setText(_user.getRegisterDate().getWDate());
		
		if (_user.getGender() == L"M") {
			_gender.setSelectOption(L"男");
		}
		else if (_user.getGender() == L"F") {
			_gender.setSelectOption(L"女");
		}

		if (_user.getUserType() == UserType::Student) {
			_role.setSelectOption(L"学生");
		}
		else if (_user.getUserType() == UserType::Teacher) {
			_role.setSelectOption(L"教师");
		}
	}
	else {
		_pageManager.setPage(Page::Login);
	}
}

bool SettingPage::_updateName()
{
	std::wstring name = _name.getText();
	if (name == L"") {
		return false;
	}

	return _user.changeName(name);
}

bool SettingPage::_updateEmail()
{
	std::wstring email = _email.getText();
	if (email == L"") {
		return false;
	}

	return _user.changeEmail(email);
}

bool SettingPage::_updateGender()
{

	return _user.changeGender(_gender.getSelectedOption());
}

bool SettingPage::_updateRole()
{
	return _user.changeRole(_role.getSelectedOption());
}