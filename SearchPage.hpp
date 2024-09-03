#pragma once
#include "PageBase.hpp"
#include "Widgets.hpp"

class SearchPage : public PageBase
{
    public:
        SearchPage(User& user, PageManager& pageManager);
        ~SearchPage();
		void search(std::wstring searchText);
        void handleEvent(const sf::Event& event, sf::RenderWindow& window);
        void update(sf::Time dt);
        void render(sf::RenderWindow& window);
        void onEnter();

    protected:
        void _searchBarHandler();
        void _logoutHandler();
        void _bookDetailPopUpHandler(Book* book);
		bool _editBookHandler(Book* book);
		void _deleteBookHandler(Book* book);
		void _newBookHandler();

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
        BookDetailPopUp _bookDetailPopUp;
		TextToogleButton _newBookButton;
        PopUpMsg _popUpMsg;

        bool _isNewBookButtonClicked;
        bool _isCalledSearch;
		//IconButton _newBookButton2;
};