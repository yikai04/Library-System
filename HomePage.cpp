#include "HomePage.hpp"
#include "PageManager.hpp"

HomePage::HomePage(User& user, PageManager& pageManager) :
    PageBase(user, pageManager),
    _topBarButton1(sf::Vector2f(100, 70), sf::Vector2f(720, 80), sf::Color::Transparent, L"首页", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Home); }),
    _topBarButton2(sf::Vector2f(100, 70), sf::Vector2f(870, 80), sf::Color::Transparent, L"书架", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Search); }),
    _topBarButton3(sf::Vector2f(150, 70), sf::Vector2f(1020, 80), sf::Color::Transparent, L"借阅记录", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Search); }),
    _topBarButton4(sf::Vector2f(210, 70), sf::Vector2f(1220, 80), sf::Color::Transparent, L"书籍统计分析", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_bookDisplay.setBookName(L"你好呀"); }),
    _topBarButton5(sf::Vector2f(150, 70), sf::Vector2f(1480, 80), sf::Color::Transparent, L"用户设置", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_bookDisplay.setBookName(L"你好呀我是神啊啊啊啊"); }),
    _topBarButton6(sf::Vector2f(100, 70), sf::Vector2f(1680, 80), sf::Color::Transparent, L"登录", _font, 30, 33, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Login); }),

    _searchBar(700.0, sf::Vector2f(650, 200), L"搜索", _font, 35),
    _bookDisplay(sf::Vector2f(200, 250), sf::Vector2f(200, 350), _font, 25),
    _bookRowDisplay(720.f, _font)
{
    mBackgroundTexture.loadFromFile("Image/Background(1920x1080).png");
    //mSprite.setTextureRect(sf::IntRect(0, 0, 800, 800));
    mSprite.setScale(1, 1);
    mSprite.setPosition(0, 0);
    mSprite.setTexture(mBackgroundTexture);

    Book book1 = _user.getBookInfoById(1000280);
	Book book2 = _user.getBookInfoById(1000517);
	Book book3 = _user.getBookInfoById(1000531);
	Book book4 = _user.getBookInfoById(1001204);
    Book book5 = _user.getBookInfoById(1001682);
    Book book6 = _user.getBookInfoById(1001885);
    Book book7 = _user.getBookInfoById(1003000);
	Book book8 = _user.getBookInfoById(1002299);
	Book book9 = _user.getBookInfoById(1005492);
	Book book10 = _user.getBookInfoById(1005521);
	Book book11 = _user.getBookInfoById(1005673);
	Book book12 = _user.getBookInfoById(1005918);
	_bookDisplay.setBook(&book1);

	std::vector<Book> testingBooks;

    testingBooks.push_back(book1);
    testingBooks.push_back(book2);
    testingBooks.push_back(book3);
    testingBooks.push_back(book4);
    testingBooks.push_back(book5);
    testingBooks.push_back(book6);
    testingBooks.push_back(book7);
	testingBooks.push_back(book8);
	testingBooks.push_back(book9);
	testingBooks.push_back(book10);
	testingBooks.push_back(book11);
	testingBooks.push_back(book12);

    _bookRowDisplay.setBooks(std::move(testingBooks));
}

HomePage::~HomePage()
{

}

void HomePage::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    //if (Button1.isMouseInButton(sf::Mouse::getPosition(window))) Button1.setButtonState(ButtonState::clicked);
    //else Button1.setButtonState(ButtonState::normal);

    //if (Button2.isMouseInButton(sf::Mouse::getPosition(window))) Button2.setButtonState(ButtonState::clicked);
    //else Button2.setButtonState(ButtonState::normal);

	_topBarButton1.handleEvent(event, window);
	_topBarButton2.handleEvent(event, window);
	_topBarButton3.handleEvent(event, window);
	_topBarButton4.handleEvent(event, window);
	_topBarButton5.handleEvent(event, window);
	_topBarButton6.handleEvent(event, window);

    _searchBar.handleEvent(event, window);
	//_bookDisplay.handleEvent(event, window);
	_bookRowDisplay.handleEvent(event, window);
}

void HomePage::update(sf::Time dt)
{
    _searchBar.update(dt);
}

void HomePage::render(sf::RenderWindow& window)
{
    window.clear(sf::Color::White);
    window.draw(mSprite);
    _topBarButton1.render(window);
	_topBarButton2.render(window);
	_topBarButton3.render(window);
	_topBarButton4.render(window);
	_topBarButton5.render(window);
	_topBarButton6.render(window);

    _searchBar.render(window);
	//_bookDisplay.render(window);
    _bookRowDisplay.render(window);

    //window.display() called in main.cpp
}