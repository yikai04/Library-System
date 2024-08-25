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
    private:
        sf::Texture mBackgroundTexture;
        sf::Sprite mSprite;
	    TextToogleButton Button1;
		BooksDisplayInPage _booksDisplay;
        SearchBar _searchBar;
};