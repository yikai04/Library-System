#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "User.hpp"

class PageManager;

class PageBase
{
    public:
        PageBase(User& user, PageManager& pageManager);
        virtual ~PageBase() = default;
        virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) = 0;
        virtual void update(sf::Time dt) = 0;
        virtual void render(sf::RenderWindow& window) = 0;

    protected:
        sf::Font _font;
        User& _user;
        PageManager& _pageManager;
};