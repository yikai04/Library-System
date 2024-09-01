#pragma once
#include <string>
#include "Utils.hpp"

enum BookCategory{
	Fiction, //小说类
	BiographiesMemoirs, //传记与回忆录
	HistoryCulture, //历史与文化
	ScienceNature, //科学与自然
	BusinessEconomics, //商业与经济
	HealthLifestyle, //健康与生活方式
	ArtDesign, //艺术与设计
	LanguageLiterature, //语言与文学
	ReferenceManuals, //参考手册
	ChildrensBooks, //儿童读物
	Others //其他
};

BookCategory getCategoryByName(std::wstring categoryName);
std::wstring getCategoryNameByCategory(BookCategory category);

class Book
{
	public:
		Book();
		Book(int id);
		Book(const Book& book);
		Book& operator=(const Book& book);
		~Book();
		int getBookId();
		std::wstring getBookName();
		std::wstring getAuthor();
		std::wstring getPublisher();
		BookCategory getCategory();
		std::wstring getCategoryName();
		Date getPublishDate();
		int getPages();
		int getTotalBook();
		int getRemainBook();
		double getPrice();
		std::wstring getDescription();
		std::string getImgUrl();
		int getBorrowVolume();
		bool getDelFlg();

		bool changeBookId(std::wstring id);
		bool changeBookName(std::wstring bookName);
		bool changeAuthor(std::wstring author);
		bool changePublisher(std::wstring publisher);
		bool changeCategory(std::wstring category);
		bool changePublishDate(Date publishDate);
		bool changePages(std::wstring pages);
		bool changeTotalBook(std::wstring totalBook);
		bool changeRemainBook(std::wstring remainBook);
		bool changePrice(std::wstring price);
		bool changeDescription(std::wstring description);
		bool changeImgUrl(std::string imgUrl);

		bool addBorrowVolume();

		static std::vector<Book> getBooksByCategory(BookCategory category);
		static std::vector<Book> getAllBooks();
		static std::vector<Book> searchBooksInfo(std::wstring searchWord = L"", const std::wstring& category = L"全部");
		static std::vector<Book> searchBooksInfoByName(std::wstring bookName = L"", const std::wstring& category = L"全部");
		static std::vector<Book> searchBooksInfoByAuthor(std::wstring author = L"", const std::wstring& category = L"全部");
		static std::vector<Book> searchBooksInfoByPublisher(std::wstring publisher = L"", const std::wstring& category = L"全部");

	private:
		bool _checkBookIdValidaty(int id);
		void _loadBookInfosFromDB();
		int _id;
		std::wstring _bookName;
		std::wstring _author;
		std::wstring _publisher;
		BookCategory _category;
		Date _publishDate;
		int _pages;
		int _totalBook;
		int _remainBook;
		double _price;
		std::wstring _description;	
		std::string _imgUrl;
		int _borrowVolume;
		bool _delFlg;
};