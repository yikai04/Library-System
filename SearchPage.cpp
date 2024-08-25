#include "SearchPage.hpp"
#include "PageManager.hpp"

SearchPage::SearchPage(User& user, PageManager& pageManager) :
    PageBase(user,pageManager),
    Button1(sf::Vector2f(200, 100), sf::Vector2f(100, 400), sf::Color::Transparent, L"首页", _font, 25, 30, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_pageManager.setPage(Page::Home); }),
    _booksDisplay(_font),
    _searchBar(700.0, sf::Vector2f(650, 220), L"搜索", _font, 42)
{
    mBackgroundTexture.loadFromFile("Image/Background(1920x1080).png");

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

    _booksDisplay.setBooks(std::move(testingBooks));
}

SearchPage::~SearchPage()
{

}

void SearchPage::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    //if (Button1.isMouseInButton(sf::Mouse::getPosition(window))) Button1.setButtonState(ButtonState::clicked);
    //else Button1.setButtonState(ButtonState::normal);

    //if (Button2.isMouseInButton(sf::Mouse::getPosition(window))) Button2.setButtonState(ButtonState::clicked);
    //else Button2.setButtonState(ButtonState::normal);

    Button1.handleEvent(event, window);
	_booksDisplay.handleEvent(event, window);
    _searchBar.handleEvent(event, window);
}

void SearchPage::update(sf::Time dt)
{

}

void SearchPage::render(sf::RenderWindow& window)
{
    window.clear(sf::Color::White);
    window.draw(mSprite);
    Button1.render(window);
	_booksDisplay.render(window);
    _searchBar.render(window);

    //window.display() called in main.cpp
}