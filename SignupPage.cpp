#include "SignupPage.hpp"
#include "PageManager.hpp"


SignupPage::SignupPage(User& user, PageManager& pageManager) :
	PageBase(user, pageManager),

	_topBarButton1(sf::Vector2f(100, 70), sf::Vector2f(720, 80), sf::Color::Transparent, L"首页", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Home); }),
	_topBarButton2(sf::Vector2f(100, 70), sf::Vector2f(870, 80), sf::Color::Transparent, L"书架", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Search); }),
	_topBarButton3(sf::Vector2f(150, 70), sf::Vector2f(1020, 80), sf::Color::Transparent, L"借阅记录", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Records); }),
	_topBarButton4(sf::Vector2f(210, 70), sf::Vector2f(1220, 80), sf::Color::Transparent, L"书籍统计分析", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Statistics); }),
	_topBarButton5(sf::Vector2f(150, 70), sf::Vector2f(1480, 80), sf::Color::Transparent, L"用户设置", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Setting); }),
	_topBarButton6(sf::Vector2f(100, 70), sf::Vector2f(1680, 80), sf::Color::Transparent, L"登录", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Login); }),

	_username(480.f, sf::Vector2f(420, 410), _font, 35, L"用户名", sf::Color::Transparent, false),
	_email(480.f, sf::Vector2f(420, 520), _font, 35, L"邮箱", sf::Color::Transparent, false),
	_password(480.f, sf::Vector2f(420, 630), _font, 35, L"密码", sf::Color::Transparent, true),
	_confirmPassword(480.f, sf::Vector2f(420, 740), _font, 35, L"确认密码", sf::Color::Transparent, true),
	_name(480.f, sf::Vector2f(1020, 410), _font, 35, L"姓名", sf::Color::Transparent, false),
	_id(480.f, sf::Vector2f(1020, 520), _font, 35, L"编号", sf::Color::Transparent, false),
	_gender(sf::Vector2f(480, 50), sf::Vector2f(1020, 630), sf::Color(240, 240, 240, 255), _font, 35, L"男"),
	_role(sf::Vector2f(480, 50), sf::Vector2f(1020, 740), sf::Color(240, 240, 240, 255), _font, 35, L"学生"),
	_signupButton(sf::Vector2f(600, 70), sf::Vector2f(660, 845), [&]() {_signupHandler(); }, sf::Color::Transparent),
	_loginButton(sf::Vector2f(600, 50), sf::Vector2f(880, 940), sf::Color::Transparent, L"已注册？ 登录", _font, 22, 20, sf::Color(203, 140, 63, 255), sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Login); }, true)
{
	_backgroundTexture.loadFromFile("Image/SignupPage.png");

	_sprite.setScale(1, 1);
	_sprite.setPosition(0, 0);
	_sprite.setTexture(_backgroundTexture);

	_gender.setOptions({ L"男", L"女" });
	_role.setOptions({ L"学生", L"教师" });
}

SignupPage::~SignupPage()
{

}

void SignupPage::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	_topBarButton1.handleEvent(event, window);
	_topBarButton2.handleEvent(event, window);
	_topBarButton3.handleEvent(event, window);
	_topBarButton4.handleEvent(event, window);
	_topBarButton5.handleEvent(event, window);
	_topBarButton6.handleEvent(event, window);

	_username.handleEvent(event, window);
	_email.handleEvent(event, window);
	_password.handleEvent(event, window);
	_confirmPassword.handleEvent(event, window);
	_name.handleEvent(event, window);
	_id.handleEvent(event, window);
	_role.handleEvent(event, window);
	_gender.handleEvent(event, window);
	_signupButton.handleEvent(event, window);
	_loginButton.handleEvent(event, window);
}

void SignupPage::update(sf::Time dt)
{
	_username.update(dt);
	_email.update(dt);
	_password.update(dt);
	_confirmPassword.update(dt);
	_name.update(dt);
	_id.update(dt);
}

void SignupPage::render(sf::RenderWindow& window)
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
	_password.render(window);
	_confirmPassword.render(window);
	_name.render(window);
	_id.render(window);
	_role.render(window);
	_gender.render(window);
	_signupButton.render(window);
	_loginButton.render(window);
	//window.display() called in main.cpp
}

void SignupPage::onEnter()
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
}

void SignupPage::_logoutHandler()
{
	_user.logout();
	_topBarButton6.setText(L"登录");
	_topBarButton6.setOnClickHandler([&]() {_pageManager.setPage(Page::Login); });
	_pageManager.setPage(Page::Login);
}

void SignupPage::_signupHandler()
{
	if (_password.getText() != _confirmPassword.getText()) {

	}
	int status = _user.registerAccount(
		_username.getText(),
		_password.getText(),
		_email.getText(),
		_name.getText(),
		_id.getText(),
		_role.getSelectedOption(),
		_gender.getSelectedOption()
	);
	if (status == REGISTER_SUCESSFUL) {
		_username.setText(L"");
		_password.setText(L"");
		_email.setText(L"");
		_name.setText(L"");
		_id.setText(L"");
		_pageManager.setPage(Page::Login);
	}
	else if (status == INVALID_USERNAME) {

	}
	else if (status == INVALID_EMAIL) {

	}
	else if (status == INVALID_NAME) {

	}
	else if (status == INVALID_ID) {

	}
}