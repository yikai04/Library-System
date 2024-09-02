#pragma once
#include "PageBase.hpp"
#include "Widgets.hpp"

class UserManagementPage : public PageBase
{
    public:
        UserManagementPage(User& user, PageManager& pageManager);
        ~UserManagementPage();
        void handleEvent(const sf::Event& event, sf::RenderWindow& window);
        void update(sf::Time dt);
        void render(sf::RenderWindow& window);
        void onEnter();

    protected:
        void _logoutHandler();
        void _showUsersDetail();
		void _editUserHandler(UserInfo user);

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
};