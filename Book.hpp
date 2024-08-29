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

class Book
{
	public:
		Book();
		Book(int id, std::wstring bookName, std::wstring author, std::wstring publisher, BookCategory category, Date publishDate, int pages, int totalBook, int remainBook, double price, std::wstring _description, std::string img_url, int borrowVolume, bool del_flg);
		~Book();
		int getId();
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

		void setId(int id);
		void setBookName(std::wstring bookName);
		void setAuthor(std::wstring author);
		void setPublisher(std::wstring publisher);
		void setCategory(BookCategory category);
		void setCategory(std::wstring categoryName);
		void setPublishDate(Date publishDate);
		void setPublishDate(std::string publishDate);
		void setPages(int pages);
		void setTotalBooks(int totalBook);
		void setAvailableBooks(int remainBook);
		void setPrice(double price);
		void setDescription(std::wstring description);
		void setImgUrl(std::string imgUrl);
		void setBorrowVolume(int borrowVolume);
		void setDelFlg(bool delFlg);

	private:
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