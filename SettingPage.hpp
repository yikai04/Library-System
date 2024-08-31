#pragma once
#include "PageBase.hpp"
#include "Widgets.hpp"

class SettingPage : public PageBase
{
    public:
        SettingPage(User& user, PageManager& pageManager);
        ~SettingPage();
        void handleEvent(const sf::Event& event, sf::RenderWindow& window);
        void update(sf::Time dt);
        void render(sf::RenderWindow& window);
        void onEnter();

    protected:
        void _logoutHandler();
        void _showUserInfo();
		void _deleteAccountHandler();
		bool _updateUsername();
		bool _updateEmail();
		bool _updateName();
		bool _updateId();
		bool _updateGender();
		bool _updateRole();
		void _updatePassword();

    private:
        sf::Texture _backgroundTexture;
        sf::Sprite _sprite;

        TextToogleButton _topBarButton1;
        TextToogleButton _topBarButton2;
        TextToogleButton _topBarButton3;
        TextToogleButton _topBarButton4;
        TextToogleButton _topBarButton5;
        TextToogleButton _topBarButton6;

		TextDisplay _username;
		TextDisplay _email;
        TextDisplay _name;
        TextDisplay _id;
        TextDisplay _registerDate;
        TextDisplayDropDown _gender;
		TextDisplayDropDown _role;
		TextBox _password;
		TextBox _confirmPassword;
		IconButton _changePasswordButton;
		TextToogleButton _deleteAccountButton;
};