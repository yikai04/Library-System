#pragma once
#include <string>
#include "BorrowBookDetail.hpp"

enum UserType
{
	Guest,
	Student, //学生
	Teacher, //教师
	Admin //管理员
};

UserType stringToUserType(const std::string& str);
std::string userTypeToString(UserType type);
std::wstring userTypeToWString(UserType type);

class UserInfo
{
	public:
		UserInfo();
		UserInfo(int userId);
		UserInfo(const UserInfo& userInfo);
		UserInfo& operator=(const UserInfo& userInfo);
		~UserInfo();

		void setUserId(int userId);

		int getUserId();
		std::wstring getUsername();
		std::wstring getName();
		std::wstring getEmail();
		UserType getRole();
		std::wstring getGender();
		int getBorrowVolume();
		Date getRegisterDate();

		bool changeUsername(std::wstring username);
		bool changeEmail(std::wstring email);
		bool changeName(std::wstring name);
		bool changeId(std::wstring id);
		bool changeGender(std::wstring gender);
		bool changeRole(std::wstring role);
		bool changePassword(std::wstring password);

		bool addBorrowVolume();

		std::vector<BorrowBookDetail> getBorrowedBooks();

		static bool checkUsernameValidaty(std::wstring username);
		static int checkIdValidaty(int id);
		static std::vector<UserInfo> getAllUsers();
	
	private:
		void _loadUserInfosFromDB();
		int _userId;
		std::wstring _username;
		std::wstring _email;
		std::wstring _name;
		UserType _role;
		std::wstring _gender;
		Date _registerDate;
		int _borrowVolume;
		int _delFlg;
};