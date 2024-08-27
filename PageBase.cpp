#include "PageBase.hpp"

PageBase::PageBase(User& user, PageManager& pageManager):
	_user(user),
	_pageManager(pageManager)
{
    if (!_font.loadFromFile("Font/simhei.ttf")) {
        std::cerr << "Error loading font\n";
    }
}