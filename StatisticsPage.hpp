#pragma once
#include "PageBase.hpp"
#include "Widgets.hpp"

class StatisticsPage : public PageBase
{
public:
    StatisticsPage(User& user, PageManager& pageManager);
    ~StatisticsPage();
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void update(sf::Time dt);
    void render(sf::RenderWindow& window);

private:
    sf::Texture _backgroundTexture;
    sf::Sprite _sprite;

    TextToogleButton _topBarButton1;
    TextToogleButton _topBarButton2;
    TextToogleButton _topBarButton3;
    TextToogleButton _topBarButton4;
    TextToogleButton _topBarButton5;
    TextToogleButton _topBarButton6;


};