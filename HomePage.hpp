#pragma once
#include "PageBase.hpp"
#include "Widgets.hpp"

class HomePage : public PageBase
{
	public:
		HomePage(User& user, PageManager& pageManager);
		~HomePage();
		void handleEvent(const sf::Event& event, sf::RenderWindow& window);
		void update(sf::Time dt);
		void render(sf::RenderWindow& window);
	private:
		sf::Texture mBackgroundTexture;
		sf::Sprite mSprite;

		TextToogleButton _topBarButton1;
		TextToogleButton _topBarButton2;
		TextToogleButton _topBarButton3;
		TextToogleButton _topBarButton4;
		TextToogleButton _topBarButton5;
		TextToogleButton _topBarButton6;
		SearchBar _searchBar;

		BookDisplay _bookDisplay;
		BooksDisplayInRow _bookRowDisplay;
};