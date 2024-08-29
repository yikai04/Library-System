#include "Book.hpp"

Book::Book() :
	_id(-1),
	_bookName(L""),
	_author(L""),
	_publisher(L""),
	_category(Others),
	_publishDate(),
	_pages(0),
	_totalBook(0),
	_remainBook(0),
	_price(0),
	_description(L""),
	_imgUrl(""),
	_borrowVolume(0),
	_delFlg(false)
{

}

Book::Book(int id, std::wstring bookName, std::wstring author, std::wstring publisher, BookCategory category, Date publishDate, int pages, int totalBook, int remainBook, double price, std::wstring _description, std::string img_url, int borrowVolume, bool del_flg) :
	_id(id),
	_bookName(bookName),
	_author(author),
	_publisher(publisher),
	_category(category),
	_publishDate(publishDate),
	_pages(pages),
	_totalBook(totalBook),
	_remainBook(remainBook),
	_price(price),
	_description(_description),
	_imgUrl(img_url),
	_borrowVolume(borrowVolume),
	_delFlg(del_flg)
{

}

Book::~Book()
{

}

int Book::getId()
{
	return _id;
}

std::wstring Book::getBookName()
{
	return _bookName;
}

std::wstring Book::getAuthor()
{
	return _author;
}

std::wstring Book::getPublisher()
{
	return _publisher;
}

BookCategory Book::getCategory()
{
	return _category;
}

std::wstring Book::getCategoryName()
{
	switch (_category)
	{
	case Fiction:
		return L"小说类";
	case BiographiesMemoirs:
		return L"传记与回忆录";
	case HistoryCulture:
		return L"历史与文化";
	case ScienceNature:
		return L"科学与自然";
	case BusinessEconomics:
		return L"商业与经济";
	case HealthLifestyle:
		return L"健康与生活方式";
	case ArtDesign:
		return L"艺术与设计";
	case LanguageLiterature:
		return L"语言与文学";
	case ReferenceManuals:
		return L"参考手册";
	case ChildrensBooks:
		return L"儿童读物";
	case Others:
		return L"其他";
	default:
		return L"其他";
	}
}

Date Book::getPublishDate()
{
	return _publishDate;
}

int Book::getPages()
{
	return _pages;
}

int Book::getTotalBook()
{
	return _totalBook;
}

int Book::getRemainBook()
{
	return _remainBook;
}

double Book::getPrice()
{
	return _price;
}

std::wstring Book::getDescription()
{
	return _description;
}

std::string Book::getImgUrl()
{
	return _imgUrl;
}

int Book::getBorrowVolume()
{
	return _borrowVolume;
}

bool Book::getDelFlg()
{
	return _delFlg;
}

void Book::setId(int id)
{
	_id = id;
}

void Book::setBookName(std::wstring bookName)
{
	_bookName = bookName;
}

void Book::setAuthor(std::wstring author)
{
	_author = author;
}

void Book::setPublisher(std::wstring publisher)
{
	_publisher = publisher;
}

void Book::setCategory(BookCategory category)
{
	_category = category;
}

void Book::setCategory(std::wstring categoryName)
{
	if (categoryName == L"小说类")
	{
		_category = Fiction;
	}
	else if (categoryName == L"传记与回忆录")
	{
		_category = BiographiesMemoirs;
	}
	else if (categoryName == L"历史与文化")
	{
		_category = HistoryCulture;
	}
	else if (categoryName == L"科学与自然")
	{
		_category = ScienceNature;
	}
	else if (categoryName == L"商业与经济")
	{
		_category = BusinessEconomics;
	}
	else if (categoryName == L"健康与生活方式")
	{
		_category = HealthLifestyle;
	}
	else if (categoryName == L"艺术与设计")
	{
		_category = ArtDesign;
	}
	else if (categoryName == L"语言与文学")
	{
		_category = LanguageLiterature;
	}
	else if (categoryName == L"参考手册")
	{
		_category = ReferenceManuals;
	}
	else if (categoryName == L"儿童读物")
	{
		_category = ChildrensBooks;
	}
	else
	{
		_category = Others;
	}
}

void Book::setPublishDate(Date publishDate)
{
	_publishDate = publishDate;
}

void Book::setPublishDate(std::string publishDate)
{
	_publishDate.setDate(publishDate);
}

void Book::setPages(int pages)
{
	_pages = pages;
}

void Book::setTotalBooks(int totalBook)
{
	_totalBook = totalBook;
}

void Book::setAvailableBooks(int remainBook)
{
	_remainBook = remainBook;
}

void Book::setPrice(double price)
{
	_price = price;
}

void Book::setDescription(std::wstring description)
{
	_description = description;
}

void Book::setImgUrl(std::string imgUrl)
{
	_imgUrl = "BookImage/" + imgUrl;
}

void Book::setBorrowVolume(int borrowVolume)
{
	_borrowVolume = borrowVolume;
}

void Book::setDelFlg(bool delFlg)
{
	_delFlg = delFlg;
}