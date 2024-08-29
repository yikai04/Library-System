#pragma once
#include "PageBase.hpp"
#include "Widgets.hpp"

class SignupPage : public PageBase
{
    public:
        SignupPage(User& user, PageManager& pageManager);
        ~SignupPage();
        void handleEvent(const sf::Event& event, sf::RenderWindow& window);
        void update(sf::Time dt);
        void render(sf::RenderWindow& window);
        void onEnter();

    protected:
        void _logoutHandler();
		void _signupHandler();

    private:
        sf::Texture _backgroundTexture;
        sf::Sprite _sprite;

        TextToogleButton _topBarButton1;
        TextToogleButton _topBarButton2;
        TextToogleButton _topBarButton3;
        TextToogleButton _topBarButton4;
        TextToogleButton _topBarButton5;
        TextToogleButton _topBarButton6;

        TextBox _username;
		TextBox _password;
		TextBox _confirmPassword;
		TextBox _name;
        TextBox _email;
        TextBox _id;
		DropDown _role;
		DropDown _gender;
		Button _signupButton;
		TextToogleButton _loginButton;
};