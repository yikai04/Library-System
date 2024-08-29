﻿#pragma once
#include <SFML/Graphics.hpp>
#include "PageManager.hpp"
#include "Book.hpp"
#include "BorrowBookDetail.hpp"

enum UserType
{
	Guest,
	Student,
	Teacher,
	Admin
};

class User
{
	public:
		User();
		~User();
		void run();
		int login(std::wstring username, std::wstring password);
		void logout();
		UserType getUserType();
		std::wstring getId();
		std::wstring getUsername();
		std::wstring getName();
		Date getRegisterDate();
		std::wstring getEmail();
		std::wstring getGender();

		bool changeUsername(std::wstring username);
		bool changeEmail(std::wstring email);
		bool changeName(std::wstring name);
		bool changeId(int id);
		bool changeGender(std::wstring gender);
		bool changeRole(std::wstring role);
		bool changePassword(std::wstring password);

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

		std::vector<BorrowBookDetail> getBorrowedBooks();
		//void borrowBook(int bookId);
		//void returnBook(int bookId);
		//void addBook(Book book);
		//void deleteBook(int bookId);
		//void updateBookInfo(Book book);


	private:
		void _setUserType(std::string type);
		void _setUserDetail();
		bool _checkUsernameValidaty(std::wstring username);
		bool _checkIdValidaty(int id);
		sf::RenderWindow _window;
		sf::Clock _clock;
		UserType _userType;
		PageManager _pageManager;

		int _userId;
		std::wstring _username;
		std::wstring _name;
		Date _registerDate;
		std::wstring _email;
		std::wstring _gender;
};