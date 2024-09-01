#include "HomePage.hpp"
#include "PageManager.hpp"

HomePage::HomePage(User& user, PageManager& pageManager) :
    PageBase(user, pageManager),

    _topBarButton1(sf::Vector2f(100, 70), sf::Vector2f(720, 80), sf::Color::Transparent, L"首页", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Home); }),
    _topBarButton2(sf::Vector2f(100, 70), sf::Vector2f(870, 80), sf::Color::Transparent, L"书架", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Search); }),
    _topBarButton3(sf::Vector2f(150, 70), sf::Vector2f(1020, 80), sf::Color::Transparent, L"借阅记录", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Records); }),
    _topBarButton4(sf::Vector2f(210, 70), sf::Vector2f(1220, 80), sf::Color::Transparent, L"书籍统计分析", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Statistics); }),
    _topBarButton5(sf::Vector2f(150, 70), sf::Vector2f(1480, 80), sf::Color::Transparent, L"用户设置", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Setting); }),
    _topBarButton6(sf::Vector2f(100, 70), sf::Vector2f(1680, 80), sf::Color::Transparent, L"登录", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Login); }),

    _textBox(720.0, sf::Vector2f(570, 512), _font, 40, L"搜索", sf::Color::Transparent, false, [&]() {_searchHandler(); }),
	_searchButton(sf::Vector2f(60, 60), sf::Vector2f(1290, 510), "Icon/searchIcon.png", [&]() {_searchHandler(); }),
    _bookRowDisplay(720.f, _font, [&](Book* book) {_bookDetailPopUpHandler(book); }),
    _bookDetailPopUp(_font, false, true)
{
    _backgroundTexture.loadFromFile("Image/HomePage.png");
    //_sprite.setTextureRect(sf::IntRect(0, 0, 800, 800));
    _sprite.setScale(1, 1);
    _sprite.setPosition(0, 0);
    _sprite.setTexture(_backgroundTexture);

    std::vector<Book> allBooks = Book::searchBooksInfo();
    _bookRowDisplay.setBooks(std::move(allBooks));
}

HomePage::~HomePage()
{

}

void HomePage::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
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

    _textBox.handleEvent(event, window);
	_searchButton.handleEvent(event, window);
	_bookRowDisplay.handleEvent(event, window);
}

void HomePage::update(sf::Time dt)
{
    _textBox.update(dt);
	_bookDetailPopUp.update(dt);
}

void HomePage::render(sf::RenderWindow& window)
{
    window.clear(sf::Color::White);
    window.draw(_sprite);
    _topBarButton1.render(window);
	_topBarButton2.render(window);
	_topBarButton3.render(window);
	_topBarButton4.render(window);
	_topBarButton5.render(window);
	_topBarButton6.render(window);

    _textBox.render(window);
	_searchButton.render(window);
    _bookRowDisplay.render(window);
	_bookDetailPopUp.render(window);
    //window.display() called in main.cpp
}

void HomePage::onEnter()
{
    if (_user.getSelfUserInfo().getRole() != UserType::Guest) {
		_topBarButton6.setText(L"登出");
        _topBarButton6.setOnClickHandler([&]() {_logoutHandler(); });
    }

    _textBox.setText(L"");
    _topBarButton1.setButtonState(ButtonState::normal);
    _topBarButton2.setButtonState(ButtonState::normal);
    _topBarButton3.setButtonState(ButtonState::normal);
    _topBarButton4.setButtonState(ButtonState::normal);
    _topBarButton5.setButtonState(ButtonState::normal);
    _topBarButton6.setButtonState(ButtonState::normal);
}

void HomePage::_logoutHandler()
{
    _user.logout();
    _topBarButton6.setText(L"登录");
    _topBarButton6.setOnClickHandler([&]() {_pageManager.setPage(Page::Login); });
    _pageManager.setPage(Page::Login);
}

void HomePage::_bookDetailPopUpHandler(Book* book)
{
	_bookDetailPopUp.setBook(book);
	_bookDetailPopUp.setPopUpVisiblity(true);
}

void HomePage::_searchHandler()
{
	_pageManager.homePageSearch(_textBox.getText());
	_pageManager.setPage(Page::Search);
}