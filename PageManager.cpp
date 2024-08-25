#include "PageManager.hpp"
#include "HomePage.hpp"
#include "SearchPage.hpp"
#include "LoginPage.hpp"


PageManager::PageManager(User& user):
    currentPage(Page::Home)
{
    // Initialize the pages
    pages[Page::Home] = std::make_unique<HomePage>(user,*this);
	pages[Page::Search] = std::make_unique<SearchPage>(user,*this);
	pages[Page::Login] = std::make_unique<LoginPage>(user, *this);
}

PageManager::~PageManager()
{

}

void PageManager::setPage(Page newPage)
{
    currentPage = newPage;
}

void PageManager::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    if (pages[currentPage]) {
        pages[currentPage]->handleEvent(event,window);
    }
}

void PageManager::update(sf::Time dt)
{
    if (pages[currentPage]) {
        pages[currentPage]->update(dt);
    }
}

void PageManager::render(sf::RenderWindow& window)
{
    if (pages[currentPage]) {
        pages[currentPage]->render(window);
    }
}