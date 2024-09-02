#pragma once
#include <SFML/Graphics.hpp>
#include "PageManager.hpp"
#include "Book.hpp"
#include "BorrowBookDetail.hpp"
#include "UserInfo.hpp"

class User
{
	public:
		User();
		~User();
		void run();
		int login(std::wstring username, std::wstring password);
		void logout();

		UserInfo& getSelfUserInfo();
		void deleteAccount(UserInfo& user);
		int registerAccount(std::wstring username, std::wstring password, std::wstring email, std::wstring name, std::wstring id, std::wstring role, std::wstring gender);

		bool borrowBook(int userId, int bookId);
		bool returnBook(int bookId);

	private:
		sf::RenderWindow _window;
		sf::Clock _clock;
		PageManager _pageManager;

		UserInfo _userSelfInfo;
};