#pragma once
#include "PageBase.hpp"
#include "Widgets.hpp"

class RecordsPage : public PageBase
{
    public:
        RecordsPage(User& user, PageManager& pageManager);
        ~RecordsPage();
        void handleEvent(const sf::Event& event, sf::RenderWindow& window);
        void update(sf::Time dt);
        void render(sf::RenderWindow& window);
        void onEnter();

    protected:
		void _showBorrowRecords();
        void _logoutHandler();
		void _openBorrowBookPopUp();
		void _openReturnBookPopUp();
		bool _borrowBookHandler();
		bool _returnBookHandler();
        void _bookDetailPopUpHandler(Book* book);
    
    private:
        sf::Texture _backgroundTexture;
        sf::Sprite _sprite;

        TextToogleButton _topBarButton1;
        TextToogleButton _topBarButton2;
        TextToogleButton _topBarButton3;
        TextToogleButton _topBarButton4;
        TextToogleButton _topBarButton5;
        TextToogleButton _topBarButton6;

        Table _table;
		ToogleButton _borrowBookButton;
		ToogleButton _returnBookButton;
        BookDetailPopUp _bookDetailPopUp;
		PopUpMsg _popUpMsg;
};