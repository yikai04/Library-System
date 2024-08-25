#pragma once
#include <SFML/Graphics.hpp>
#include "PageManager.hpp"
#include "Book.hpp"

enum UserType
{
	Guest,
	Normal,
	Admin
};

class User
{
	public:
		User();
		~User();
		void run();
		//bool login(std::wstring username, std::wstring password);
		//void logout();
		//void registerAccount(std::wstring username, std::wstring password);
		//void deleteAccount();
		//void changeUsername(std::wstring newUsername);
		//void changePassword(std::wstring newPassword);

		Book getBookInfoById(int id);
		std::vector<Book> searchBooksInfo(std::wstring searchWord = L"", const std::wstring& category = L"全部");
		std::vector<Book> searchBooksInfoByName(std::wstring bookName = L"", const std::wstring& category = L"全部");
		std::vector<Book> searchBooksInfoByAuthor(std::wstring author = L"", const std::wstring& category = L"全部");
		std::vector<Book> searchBooksInfoByPublisher(std::wstring publisher = L"", const std::wstring& category = L"全部");
		//std::vector<Book> searchBooksInfoByDescription(std::wstring description);

		//void borrowBook(int bookId);
		//void returnBook(int bookId);
		//void addBook(Book book);
		//void deleteBook(int bookId);
		//void updateBookInfo(Book book);


	private:
		sf::RenderWindow _window;
		sf::Clock _clock;
		UserType _userType;
		PageManager _pageManager;

		int _userId;

};