﻿#pragma once
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

		Book getBookInfoById(int id);
		std::vector<Book> searchBooksInfo(std::wstring searchWord = L"", const std::wstring& category = L"全部");
		std::vector<Book> searchBooksInfoByName(std::wstring bookName = L"", const std::wstring& category = L"全部");
		std::vector<Book> searchBooksInfoByAuthor(std::wstring author = L"", const std::wstring& category = L"全部");
		std::vector<Book> searchBooksInfoByPublisher(std::wstring publisher = L"", const std::wstring& category = L"全部");

		bool borrowBook(int userId, int bookId);
		bool returnBook(int bookId);
		//void addBook(Book book);
		//void deleteBook(int bookId);
		//void updateBookInfo(Book book);


	private:
		sf::RenderWindow _window;
		sf::Clock _clock;
		PageManager _pageManager;

		UserInfo _userInfo;
};