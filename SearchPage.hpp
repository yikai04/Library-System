#pragma once
#include "PageBase.hpp"
#include "Widgets.hpp"

class SearchPage : public PageBase
{
    public:
        SearchPage(User& user, PageManager& pageManager);
        ~SearchPage();
        void handleEvent(const sf::Event& event, sf::RenderWindow& window);
        void update(sf::Time dt);
        void render(sf::RenderWindow& window);
        void onEnter();

    protected:
        void _searchBarHandler();
        void _logoutHandler();

    private:
        sf::Texture _backgroundTexture;
        sf::Sprite _sprite;

        TextToogleButton _topBarButton1;
        TextToogleButton _topBarButton2;
        TextToogleButton _topBarButton3;
        TextToogleButton _topBarButton4;
        TextToogleButton _topBarButton5;
        TextToogleButton _topBarButton6;

		BooksDisplayInPage _booksDisplay;
        SearchBar _searchBar;
};