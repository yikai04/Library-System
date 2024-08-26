#include "BorrowBookDetail.hpp"

BorrowBookDetail::BorrowBookDetail():
	_id(-1),
	_bookId(-1),
	_userId(-1)
{

}

BorrowBookDetail::BorrowBookDetail(int id, int bookId, int userId, Date borrowDate, Date returnDate) :
	_id(id),
	_bookId(bookId),
	_userId(userId),
	_borrowDate(borrowDate),
	_returnDate(returnDate)
{

}

BorrowBookDetail::~BorrowBookDetail()
{

}

void BorrowBookDetail::setId(int id)
{
	_id = id;
}

void BorrowBookDetail::setBookId(int bookId)
{
	_bookId = bookId;
}

void BorrowBookDetail::setUserId(int userId)
{
	_userId = userId;
}

void BorrowBookDetail::setBorrowDate(Date borrowDate)
{
	_borrowDate = borrowDate;
}

void BorrowBookDetail::setBorrowDate(std::string borrowDate)
{
	_borrowDate.setDate(borrowDate);
}

void BorrowBookDetail::setReturnDate(Date returnDate)
{
	_returnDate = returnDate;
}

void BorrowBookDetail::setReturnDate(std::string returnDate)
{
	_returnDate.setDate(returnDate);
}

int BorrowBookDetail::getId()
{
	return _id;
}

int BorrowBookDetail::getBookId()
{
	return _bookId;
}

int BorrowBookDetail::getUserId()
{
	return _userId;
}

Date BorrowBookDetail::getBorrowDate()
{
	return _borrowDate;
}

Date BorrowBookDetail::getReturnDate()
{
	return _returnDate;
}