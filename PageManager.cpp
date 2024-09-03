#include "PageManager.hpp"
#include "HomePage.hpp"
#include "SearchPage.hpp"
#include "RecordsPage.hpp"
#include "StatisticsPage.hpp"
#include "SettingPage.hpp"
#include "LoginPage.hpp"
#include "SignupPage.hpp"
#include "UserManagementPage.hpp"


PageManager::PageManager(User& user):
    currentPage(Page::Home),
	lastPage(Page::Home)
{
    // Initialize the pages
    pages[Page::Home] = std::make_unique<HomePage>(user,*this);
	pages[Page::Search] = std::make_unique<SearchPage>(user,*this);
	pages[Page::Records] = std::make_unique<RecordsPage>(user, *this);
	pages[Page::Statistics] = std::make_unique<StatisticsPage>(user, *this);
	pages[Page::Setting] = std::make_unique<SettingPage>(user, *this);
	pages[Page::Login] = std::make_unique<LoginPage>(user, *this);
	pages[Page::Signup] = std::make_unique<SignupPage>(user, *this);
	pages[Page::UserManagement] = std::make_unique<UserManagementPage>(user, *this);
}

PageManager::~PageManager()
{

}

void PageManager::setPage(Page newPage)
{
	lastPage = currentPage;
    currentPage = newPage;
	if (pages[currentPage]) {
		pages[currentPage]->onEnter();
	}
}

Page PageManager::getLastPage()
{
	return lastPage;
}

void PageManager::homePageSearch(std::wstring searchText)
{
	if (pages[Page::Search]) {
		pages[Page::Search]->search(searchText);
	}
}

void PageManager::userManagementPageSearch(std::wstring searchText)
{
	if (pages[Page::Setting]) {
		pages[Page::Setting]->search(searchText);
	}
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