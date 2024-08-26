#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include <iostream>


enum class Page
{
    Home,
    Search,
    Login,
    Records,
	Statistics,
    Setting
};

class User;
class PageBase;

class PageManager
{
    public:
        PageManager(User& user);
        ~PageManager();
        void setPage(Page newPage);
        void handleEvent(const sf::Event& event, sf::RenderWindow& window);
        void update(sf::Time dt);
        void render(sf::RenderWindow& window);

    private:
        Page currentPage;
        std::unordered_map<Page, std::unique_ptr<PageBase>> pages;
};