#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "Book.hpp"

enum ButtonState
{
	normal,
	clicked
};

enum Alignment
{
	left,
	center,
	right
};

class Button
{
	public:
		Button(sf::Vector2f size, sf::Vector2f position, std::function<void()> onClickHandler = []() {}, const sf::Color& backgroundColor = sf::Color::White);
		Button(sf::Vector2f size, sf::Vector2f position, const sf::Color& backgroundColor, const std::string& text, const sf::Font& font, const int& fontSize, const sf::Color& fontColor, std::function<void()> onClickHandler = []() {});
		Button(sf::Vector2f size, sf::Vector2f position, const sf::Color& backgroundColor, const std::wstring& text, const sf::Font& font, const int& fontSize, const sf::Color& fontColor, std::function<void()> onClickHandler = []() {});
		~Button();
		bool isMouseInButton(const sf::Vector2i& mousePosition);
		virtual void switchButtonState();
		virtual void setButtonState(ButtonState state);
		void setText(const std::wstring& text);
		void setPosition(const sf::Vector2f& position);
		void setSize(const sf::Vector2f& size);
		void setOnClickHandler(std::function<void()> onClickHandler);
		sf::Vector2f getSize();
		sf::Vector2f getPosition();
		void handleEvent(const sf::Event& event, sf::RenderWindow& window);
		ButtonState getButtonState();
		void render(sf::RenderWindow& window);

	protected:
		void _setTextPos();
		sf::Vector2f _size;
		sf::Vector2f _position;
		std::wstring _textString;
		sf::RectangleShape _buttonShape;
		sf::Text _buttonText;
		sf::Cursor _cursor;
		sf::Cursor::Type _cursorType;
		sf::Color _backgroundColor;
		ButtonState _buttonState;
		std::function<void()> _onClickHandler;
};

class ToogleButton : public Button
{
	public:
		ToogleButton(sf::Vector2f size, sf::Vector2f position, const sf::Color& normalStateColor, const sf::Color& clickedStateColor, std::function<void()> onClickHandler = []() {});
		ToogleButton(sf::Vector2f size, sf::Vector2f position, const sf::Color& normalStateColor, const sf::Color& clickedStateColor, const std::string& text, const sf::Font& font, const int& fontSize, std::function<void()> onClickHandler = []() {});
		ToogleButton(sf::Vector2f size, sf::Vector2f position, const sf::Color& normalStateColor, const sf::Color& clickedStateColor, const std::wstring& text, const sf::Font& font, const int& fontSize, std::function<void()> onClickHandler = []() {});
		~ToogleButton();
		void switchButtonState();
		void setButtonState(ButtonState state);

	protected:
		sf::Color _clickedStateColor;
};

class TextToogleButton : public Button
{
	public:
		TextToogleButton(sf::Vector2f maxSize, sf::Vector2f position, const sf::Color& backgroundColor, const std::string& text, const sf::Font& font, const int& normalFontSize, const int& clickedFontSize, const sf::Color& normalFontColor, const sf::Color& clickedFontColor, std::function<void()> onClickHandler = []() {}, bool setSizeAccordingText = true);
		TextToogleButton(sf::Vector2f maxSize, sf::Vector2f position, const sf::Color& backgroundColor, const std::wstring& text, const sf::Font& font, const int& normalFontSize, const int& clickedFontSize,const sf::Color& normalFontColor, const sf::Color& clickedFontColor, std::function<void()> onClickHandler = []() {}, bool setSizeAccordingText = true);
		~TextToogleButton();
		void switchButtonState();
		void setButtonState(ButtonState state);
		void setText(const std::wstring& text);
		
	protected:
		void _alignText();
		void _setSuitableSize();
		int _normalFontSize;
		int _clickedFontSize;
		sf::Color _normalFontColor;
		sf::Color _clickedFontColor;
		sf::Vector2f _maxSize;
		bool _setSizeAccordingText;
};

class IconButton : public Button
{
	public:
		IconButton(sf::Vector2f size, sf::Vector2f position, const std::string iconPath, std::function<void()> onClickHandler = []() {});
		~IconButton();
		void setIcon(const std::string iconPath);
		void setPosition(const sf::Vector2f& position);
		void setSize(const sf::Vector2f& size);
		void render(sf::RenderWindow& window);

	protected:
		void _resizeIcon();
		std::string _iconPath;
		sf::Texture _iconTexture;
		sf::Sprite _iconSprite;
};

class TextBox
{
	public:
		TextBox(float width, sf::Vector2f position, const sf::Font& font, const int& fontSize, const std::wstring placeHolderText = L"输入框", const sf::Color& backgroundColor = sf::Color::White, bool isPassword = false);
		TextBox(sf::Vector2f size, sf::Vector2f position, const sf::Font& font, const int& fontSize, const std::wstring placeHolderText = L"输入框", const sf::Color& backgroundColor = sf::Color::White);
		~TextBox();
		void setText(std::wstring text);
		std::wstring getText();
		void handleEvent(const sf::Event& event, sf::RenderWindow& window);
		void update(sf::Time dt);
		void render(sf::RenderWindow& window);
	
	protected:
		void _displayString();
		void _updateCaretPosition();
		void _setCaretPosition(sf::Vector2i mousePosition);

		sf::RectangleShape _textBox;
		sf::Text _inputText;
		sf::Text _inputTextLenCounter;
		sf::Text _placeHolderText;
		sf::Cursor _cursor;
		sf::Cursor::Type _cursorType;
		std::wstring _inputString;

		sf::RectangleShape _caret;
		bool _caretVisible;
		unsigned int _caretPosition;
		sf::Time _caretTimer;

		bool _isActivated;
		bool _isPassword;
		bool _isMultiLine;
		int _lineCount;
		std::vector<int> _lineLength;
		float _singleWordHeight;
};

class TextDisplay
{
	public:
		TextDisplay(sf::Vector2f size, sf::Vector2f position, const sf::Font& font, const int& fontSize, sf::Color backgroundColor = sf::Color::White, const std::wstring placeHolderText = L"输入框", const std::wstring text = L"", bool isEditable = false, std::function<bool()> editHandler = []() {return true; });
		~TextDisplay();
		void setText(std::wstring text);
		std::wstring getText();
		void handleEvent(const sf::Event& event, sf::RenderWindow& window);
		void update(sf::Time dt);
		void render(sf::RenderWindow& window);


	protected:
		void _editButtonOnClickHandler();
		void _tickButtonOnClickHandler();
		TextBox _textBox;
		IconButton _editButton;
		bool _isEditable;
		bool _isEditing;
		std::function<bool()> _editHandler;
};

class DropDown
{
	public:
		DropDown(sf::Vector2f size, sf::Vector2f position, const sf::Color& backgroundColor, const sf::Font& font, const int& fontSize, const std::wstring defaultOption = L"", bool isActivate = true);
		~DropDown();
		void setOptions(std::vector<std::wstring> options);
		bool isDropDownVisible();
		void setDropDownVisible(bool isVisible);
		void setSelectOption(const std::wstring& option);
		void setActivate(bool isActivate);
		std::wstring getSelectedOption();
		bool getVisibility();
		void dropDownButtonOnClickHandler();
		void optionButtonOnClickHandler(std::wstring option);
		void handleEvent(const sf::Event& event, sf::RenderWindow& window);
		void render(sf::RenderWindow& window);

	protected:
		void _createOptionButtons();
		void _deleteOptionButtons();
		Button _dropDownButton;
		std::wstring _selectedOption;
		std::vector<std::wstring> _options;
		std::vector<TextToogleButton*> _optionButtons;
		bool _isDropDownVisible;
		bool _isActivate;
		sf::Font _font;
		int _fontSize;
		sf::Color _backgroundColor;
};

class TextDisplayDropDown
{
	public:
		TextDisplayDropDown(sf::Vector2f size, sf::Vector2f position, const sf::Font& font, const int& fontSize, sf::Color backgroundColor = sf::Color::White, const std::wstring text = L"", std::vector<std::wstring> options = {L""}, bool isEditable = false, std::function<bool()> editHandler = []() {return true; });
		~TextDisplayDropDown();
		void setText(std::wstring text);
		std::wstring getText();
		void handleEvent(const sf::Event& event, sf::RenderWindow& window);
		void update(sf::Time dt);
		void render(sf::RenderWindow& window);


	protected:
		void _editButtonOnClickHandler();
		void _tickButtonOnClickHandler();
		DropDown _dropDown;
		IconButton _editButton;
		bool _isEditable;
		bool _isEditing;
		std::function<bool()> _editHandler;
};

class SearchBar : public TextBox
{
	public:
		SearchBar(float width, sf::Vector2f position, const std::wstring placeHolderText, const sf::Font& font, const int& fontSize, std::function<void()> searchHandler = []() {});
		~SearchBar();
		std::wstring getCategory();
		std::wstring getFilter();
		std::wstring getSearchWord();
		bool getDropDownVisibility();
		void handleEvent(const sf::Event& event, sf::RenderWindow& window);
		void update(sf::Time dt);
		void render(sf::RenderWindow& window);
	
	protected:
		IconButton _searchButton;
		DropDown _bookCategoryDropDown;
		DropDown _searchTypeDropDown;
		std::function<void()> _searchHandler;
};

class PageNumber : TextBox
{
	public:
		PageNumber(sf::Vector2f position, const sf::Font& font);
		~PageNumber();
		void setCurrentPage(int currentPage);
		void setTotalPage(int totalPage);
		void handleEvent(const sf::Event& event, sf::RenderWindow& window);
		void update(sf::Time dt);
		void render(sf::RenderWindow& window);

	protected:
		sf::Text _totalPage;
};

class BookDisplay
{
	public:
		BookDisplay(sf::Vector2f bookCoverSize, sf::Vector2f position, const sf::Font& font, const int& fontSize, bool isVisible = true);
		~BookDisplay();
		void setBook(Book* book);
		void setBookCover(const std::string& bookCoverPath);
		void setBookName(const std::wstring& bookName);
		//void setAuthor(const std::wstring& author);
		void setPosition(const sf::Vector2f& position);
		void setVisiblity(bool isVisible);
		void handleEvent(const sf::Event& event, sf::RenderWindow& window);
		void render(sf::RenderWindow& window);

	protected:
		IconButton _bookCover;
		TextToogleButton _bookName;
		Book* _book;
		bool _isVisible;

		////Popup
		//sf::RectangleShape _mask;
		//sf::RectangleShape _popup;

};

class BooksDisplayInRow
{
	public:
		BooksDisplayInRow(float postionY, const sf::Font& font);
		~BooksDisplayInRow();
		void setBooks(std::vector<Book>&& books);
		void handleEvent(const sf::Event& event, sf::RenderWindow& window);
		void update(sf::Time dt);
		void render(sf::RenderWindow& window);
		void switchLeftDisplay();
		void switchRightDisplay();

	protected:
		void _updateDisplay();
		std::vector<Book> _books;
		BookDisplay _bookDisplay1;
		BookDisplay _bookDisplay2;
		BookDisplay _bookDisplay3;
		BookDisplay _bookDisplay4;
		BookDisplay _bookDisplay5;
		IconButton _leftArrow;
		IconButton _rightArrow;
		int _currentDisplayPage;
		int _maxBooksIndex;
};

class BooksDisplayInPage
{
	public:
		BooksDisplayInPage(const sf::Font& font);
		~BooksDisplayInPage();
		void setBooks(std::vector<Book>&& books);
		void handleEvent(const sf::Event& event, sf::RenderWindow& window);
		void update(sf::Time dt);
		void render(sf::RenderWindow& window);
		void switchLeftDisplay();
		void switchRightDisplay();

	protected:
		void _updateDisplay();
		std::vector<Book> _books;
		BookDisplay _bookDisplay1;
		BookDisplay _bookDisplay2;
		BookDisplay _bookDisplay3;
		BookDisplay _bookDisplay4;
		BookDisplay _bookDisplay5;
		BookDisplay _bookDisplay6;
		BookDisplay _bookDisplay7;
		BookDisplay _bookDisplay8;
		BookDisplay _bookDisplay9;
		BookDisplay _bookDisplay10;
		IconButton _leftArrow;
		IconButton _rightArrow;
		int _currentDisplayPage;
		int _maxBooksIndex;
};

class Table
{
public:
	Table(sf::Vector2f size, sf::Vector2f position, const sf::Font& font, const int& fontSize, std::vector<std::wstring>&& headers, std::vector<float>&& rowWidth, const float& rowHeight, sf::Color headerColor, sf::Color rowColor1, sf::Color rowColor2);
	~Table();
	void setHeaders(std::vector<std::wstring>&& headers);
	void setRows(std::vector<std::vector<std::wstring>>&& rows, std::vector<Book>&& books);
	void handleEvent(const sf::Event& event, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);

protected:
	class _row {
		public:
			_row(sf::Vector2f position, const sf::Font& font, const int& fontSize, std::vector<std::wstring> rowData, std::vector<float> rowWidth, float rowHeight, sf::Color backgroundColor);
			~_row();
			void handleEvent(const sf::Event& event, sf::RenderWindow& window);
			void render(sf::RenderWindow& window);

		private:
			std::vector<TextToogleButton*> _rowButtons;
			std::vector<std::wstring> _rowData;
			std::vector<float> _rowWidth;
			float _rowHeight;
	};
	void _updateRows();
	void _updateHeaders();
	std::vector<std::vector<std::wstring>> _rowsData;
	std::vector<Book> _books;
	std::vector<std::wstring> _headers;
	std::vector<TextToogleButton*> _headerButtons;
	std::vector<_row*> _rowDisplay;
	std::vector<float> _rowWidth;
	float _rowHeight;
	sf::View _view;
	sf::Font _font;
	sf::Color _headerColor;
	sf::Color _rowColor1;
	sf::Color _rowColor2;
	sf::Vector2f _position;
	int _fontSize;
};