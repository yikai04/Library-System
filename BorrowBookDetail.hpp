#pragma once
#include "Utils.hpp"

class BorrowBookDetail
{
	public:
		BorrowBookDetail();
		BorrowBookDetail(int id, int bookId, int userId, Date borrowDate, Date dueDate, Date returnDate);
		~BorrowBookDetail();
		
		void setId(int id);
		void setBookId(int bookId);
		void setUserId(int userId);
		void setBorrowDate(Date borrowDate);
		void setBorrowDate(std::string borrowDate);
		void setDueDate(Date dueDate);
		void setDueDate(std::string dueDate);
		void setReturnDate(Date returnDate);
		void setReturnDate(std::string returnDate);
		
		int getId();
		int getBookId();
		int getUserId();
		Date getBorrowDate();
		Date getDueDate();
		Date getReturnDate();

	private:
		int _id;
		int _bookId;
		int _userId;
		Date _borrowDate;
		Date _dueDate;
		Date _returnDate;
};