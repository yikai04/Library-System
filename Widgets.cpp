#include "Widgets.hpp"
#include <iostream>


Button::Button(sf::Vector2f size, sf::Vector2f position, std::function<void()> onClickHandler, const sf::Color& backgroundColor) :
	_size(size),
	_position(position),
	_backgroundColor(backgroundColor),
	_onClickHandler(onClickHandler),
	_cursorType(sf::Cursor::Arrow),
	_textString(L"")
{
	_buttonShape.setSize(size);
	_buttonShape.setPosition(position);
	_buttonShape.setFillColor(_backgroundColor);
	_buttonState = ButtonState::normal;

	_buttonText.setString(_textString);
}

Button::Button(sf::Vector2f size, sf::Vector2f position, const sf::Color& backgroundColor, const std::string& text, const sf::Font& font, const int& fontSize, const sf::Color& fontColor, std::function<void()> onClickHandler) :
	_size(size),
	_position(position),
	_backgroundColor(backgroundColor),
	_onClickHandler(onClickHandler),
	_textString(std::wstring(text.begin(), text.end()))
{
	_buttonShape.setSize(size);
	_buttonShape.setPosition(position);
	_buttonShape.setFillColor(_backgroundColor);
	_buttonState = ButtonState::normal;

	_buttonText.setFont(font);
	_buttonText.setString(_textString);
	_buttonText.setCharacterSize(fontSize);
	_buttonText.setFillColor(fontColor);
	_buttonText.setStyle(sf::Text::Bold);

	_setTextPos();
}

Button::Button(sf::Vector2f size, sf::Vector2f position, const sf::Color& backgroundColor, const std::wstring& text, const sf::Font& font, const int& fontSize, const sf::Color& fontColor, std::function<void()> onClickHandler) :
	_size(size),
	_position(position),
	_backgroundColor(backgroundColor),
	_onClickHandler(onClickHandler),
	_textString(text)
{
	_buttonShape.setSize(size);
	_buttonShape.setPosition(position);
	_buttonShape.setFillColor(_backgroundColor);
	_buttonState = ButtonState::normal;

	_buttonText.setFont(font);
	_buttonText.setString(_textString);
	_buttonText.setCharacterSize(fontSize);
	_buttonText.setFillColor(fontColor);
	_buttonText.setStyle(sf::Text::Bold);

	_setTextPos();
}

Button::~Button()
{

}

bool Button::isMouseInButton(const sf::Vector2i& mousePosition)
{
	return _buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));
}

void Button::switchButtonState()
{
	if (_buttonState == ButtonState::normal)
	{
		_buttonState = ButtonState::clicked;
	}
	else if (_buttonState == ButtonState::clicked)
	{
		_buttonState = ButtonState::normal;
	}
}

void Button::setButtonState(ButtonState state)
{
	_buttonState = state;
}

void Button::setText(const std::wstring& text)
{
	if (_buttonText.getFont() != NULL) {
		_buttonText.setString(text);
	}
	_textString = text;
	_setTextPos();
}

void Button::setPosition(const sf::Vector2f& position)
{
	_buttonShape.setPosition(position);
	_setTextPos();
	_position = position;
}

void Button::setSize(const sf::Vector2f& size)
{
	_buttonShape.setSize(size);
	_size = size;
	_setTextPos();
}

void Button::setOnClickHandler(std::function<void()> onClickHandler)
{
	_onClickHandler = onClickHandler;
}

void Button::setBackgroundColor(const sf::Color backgroundColor)
{
	_backgroundColor = backgroundColor;
	_buttonShape.setFillColor(_backgroundColor);
}

sf::Vector2f Button::getSize()
{
	return _size;
}

sf::Vector2f Button::getPosition()
{
	return _position;
}

void Button::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	if (_buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
		if (_cursor.loadFromSystem(sf::Cursor::Hand)) {
			window.setMouseCursor(_cursor);
			_cursorType = sf::Cursor::Hand;
			setButtonState(ButtonState::clicked);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			/*if (_cursor.loadFromSystem(sf::Cursor::Wait)) {
				window.setMouseCursor(_cursor);
				_cursorType = sf::Cursor::Wait;
			}*/
			_onClickHandler();
			//setButtonState(ButtonState::normal);
			/*if (_cursor.loadFromSystem(sf::Cursor::Arrow)) {
				window.setMouseCursor(_cursor);
				_cursorType = sf::Cursor::Arrow;
			}*/
		}
	}
	else if (_cursorType != sf::Cursor::Arrow) {
		if (_cursor.loadFromSystem(sf::Cursor::Arrow)) {
			window.setMouseCursor(_cursor);
			_cursorType = sf::Cursor::Arrow;
			setButtonState(ButtonState::normal);
		}
	}
}

ButtonState Button::getButtonState()
{
	return _buttonState;
}

void Button::render(sf::RenderWindow& window) {
	window.draw(_buttonShape);
	if (_buttonText.getString() != "") {
		window.draw(_buttonText);
	}
}

void Button::_setTextPos()
{
	sf::FloatRect textRect = _buttonText.getLocalBounds();
	_buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	_buttonText.setPosition(
		_buttonShape.getPosition().x + _buttonShape.getSize().x / 2.0f,
		_buttonShape.getPosition().y + _buttonShape.getSize().y / 2.0f
	);
}



ToogleButton::ToogleButton(sf::Vector2f size, sf::Vector2f position, const sf::Color& normalStateColor, const sf::Color& clickedStateColor, std::function<void()> onClickHandler) :
	Button(size, position, onClickHandler, normalStateColor),
	_clickedStateColor(clickedStateColor)
{

}

ToogleButton::ToogleButton(sf::Vector2f size, sf::Vector2f position, const sf::Color& normalStateColor, const sf::Color& clickedStateColor, const std::string& text, const sf::Font& font, const int& fontSize, std::function<void()> onClickHandler) :
	Button(size, position, normalStateColor, text, font, fontSize, clickedStateColor, onClickHandler),
	_clickedStateColor(clickedStateColor)
{

}

ToogleButton::ToogleButton(sf::Vector2f size, sf::Vector2f position, const sf::Color& normalStateColor, const sf::Color& clickedStateColor, const std::wstring& text, const sf::Font& font, const int& fontSize, std::function<void()> onClickHandler) :
	Button(size, position, normalStateColor, text, font, fontSize, clickedStateColor, onClickHandler),
	_clickedStateColor(clickedStateColor)
{

}

ToogleButton::~ToogleButton()
{

}

void ToogleButton::switchButtonState()
{
	if (_buttonState == ButtonState::normal)
	{
		_buttonShape.setFillColor(_clickedStateColor);
		_buttonText.setFillColor(_backgroundColor);
		_buttonState = ButtonState::clicked;
	}
	else if (_buttonState == ButtonState::clicked)
	{
		_buttonShape.setFillColor(_backgroundColor);
		_buttonText.setFillColor(_clickedStateColor);
		_buttonState = ButtonState::normal;
	}
}

void ToogleButton::setButtonState(ButtonState state)
{
	if (state == ButtonState::normal)
	{
		_buttonShape.setFillColor(_backgroundColor);
		_buttonText.setFillColor(_clickedStateColor);
		_buttonState = ButtonState::normal;
	}
	else if (state == ButtonState::clicked)
	{
		_buttonShape.setFillColor(_clickedStateColor);
		_buttonText.setFillColor(_backgroundColor);
		_buttonState = ButtonState::clicked;
	}
}




TextToogleButton::TextToogleButton(sf::Vector2f maxSize, sf::Vector2f position, const sf::Color& backgroundColor, const std::string& text, const sf::Font& font, const int& normalFontSize, const int& clickedFontSize, const sf::Color& normalFontColor, const sf::Color& clickedFontColor, std::function<void()> onClickHandler, bool setSizeAccordingText) :
	Button(maxSize, position, backgroundColor, text, font, normalFontSize, normalFontColor, onClickHandler),
	_normalFontSize(normalFontSize),
	_clickedFontSize(clickedFontSize),
	_normalFontColor(normalFontColor),
	_clickedFontColor(clickedFontColor),
	_maxSize(maxSize),
	_setSizeAccordingText(setSizeAccordingText)
{
	_alignText();
	_setSuitableSize();
}

TextToogleButton::TextToogleButton(sf::Vector2f maxSize, sf::Vector2f position, const sf::Color& backgroundColor, const std::wstring& text, const sf::Font& font, const int& normalFontSize, const int& clickedFontSize, const sf::Color& normalFontColor, const sf::Color& clickedFontColor, std::function<void()> onClickHandler, bool setSizeAccordingText) :
	Button(maxSize, position, backgroundColor, text, font, normalFontSize, normalFontColor, onClickHandler),
	_normalFontSize(normalFontSize),
	_clickedFontSize(clickedFontSize),
	_normalFontColor(normalFontColor),
	_clickedFontColor(clickedFontColor),
	_maxSize(maxSize),
	_setSizeAccordingText(setSizeAccordingText)
{
	_alignText();
	_setSuitableSize();
}

TextToogleButton::~TextToogleButton()
{

}

void TextToogleButton::switchButtonState()
{
	if (_buttonState == ButtonState::normal)
	{
		_buttonText.setCharacterSize(_clickedFontSize);
		_buttonText.setFillColor(_clickedFontColor);
		_setTextPos();
		_buttonState = ButtonState::clicked;
	}
	else if (_buttonState == ButtonState::clicked)
	{
		_buttonText.setCharacterSize(_normalFontSize);
		_setTextPos();
		_buttonText.setFillColor(_normalFontColor);
		_buttonState = ButtonState::normal;
	}
}

void TextToogleButton::setButtonState(ButtonState state)
{
	if (state == ButtonState::normal)
	{
		_buttonText.setCharacterSize(_normalFontSize);
		_buttonText.setFillColor(_normalFontColor);
		_setTextPos();
		_buttonState = ButtonState::normal;
	}
	else if (state == ButtonState::clicked)
	{
		_buttonText.setCharacterSize(_clickedFontSize);
		_buttonText.setFillColor(_clickedFontColor);
		_setTextPos();
		_buttonState = ButtonState::clicked;
	}
}

void TextToogleButton::setText(const std::wstring& text)
{
	Button::setText(text);
	_buttonShape.setSize(_maxSize);
	_alignText();
	_setSuitableSize();

}

void TextToogleButton::_alignText()
{
	if (_buttonText.getGlobalBounds().width > _buttonShape.getGlobalBounds().width - 10.f) {
		_buttonText.setString("");
		for (wchar_t c : _textString)
		{
			_buttonText.setString(_buttonText.getString() + c);
			if (_buttonText.getGlobalBounds().width > _buttonShape.getGlobalBounds().width - 60.f) {
				_buttonText.setString(_buttonText.getString() + "...");
				break;
			}
		}
	}
	_setTextPos();
}

void TextToogleButton::_setSuitableSize()
{
	if (_setSizeAccordingText) {
		float x, y;
		if (_buttonText.getGlobalBounds().width - 20.f > _maxSize.x) {
			x = _maxSize.x;
		}
		else {
			x = _buttonText.getGlobalBounds().width + 20.f;
		}
		if (_buttonText.getGlobalBounds().height - 10.f > _maxSize.y) {
			y = _maxSize.y;
		}
		else {
			y = _buttonText.getGlobalBounds().height + 10.f;
		}
		setSize(sf::Vector2f(x, y));
	}
}




IconButton::IconButton(sf::Vector2f size, sf::Vector2f position, const std::string iconPath, std::function<void()> onClickHandler) :
	Button(size, position, onClickHandler),
	_iconPath(iconPath)
{
	setIcon(_iconPath);

	_iconSprite.setTexture(_iconTexture);
	_iconSprite.setPosition(position);
	//_iconSprite.setScale(
	//	size.x / _iconTexture.getSize().x,
	//	size.y / _iconTexture.getSize().y
	//);
}

IconButton::~IconButton()
{

}

void IconButton::setIcon(const std::string& iconPath)
{
	_iconPath = iconPath;
	_resizeIcon();
}

void IconButton::setPosition(const sf::Vector2f& position)
{
	Button::setPosition(position);
	_iconSprite.setPosition(position);
}

void IconButton::setSize(const sf::Vector2f& size)
{
	Button::setSize(size);

	_resizeIcon();
}

void IconButton::render(sf::RenderWindow& window)
{
	window.draw(_iconSprite);
}

void IconButton::_resizeIcon()
{
	sf::Image image;
	if (!image.loadFromFile(_iconPath)) {
		std::cerr << "Failed to load icon texture" << std::endl;
		return;
	}

	sf::Image resizedImage;
	resizedImage.create((unsigned int)_size.x, (unsigned int)_size.y);

	// Perform the resizing
	for (unsigned int y = 0; y < _size.y; ++y) {
		for (unsigned int x = 0; x < _size.x; ++x) {
			// Map the new image coordinates to the original image coordinates
			unsigned int originalX = static_cast<unsigned int>((x / static_cast<float>(_size.x)) * image.getSize().x);
			unsigned int originalY = static_cast<unsigned int>((y / static_cast<float>(_size.y)) * image.getSize().y);

			// Get the color from the original image
			sf::Color color = image.getPixel(originalX, originalY);
			resizedImage.setPixel(x, y, color);
		}
	}

	_iconTexture.loadFromImage(resizedImage);

	//_iconTexture.loadFromFile(_iconPath);
	_iconSprite.setTexture(_iconTexture);
	//_iconSprite.setScale(
	//	_size.x / _iconTexture.getSize().x,
	//	_size.y / _iconTexture.getSize().y
	//);
}




TextBox::TextBox(float width, sf::Vector2f position, const sf::Font& font, const int& fontSize, const std::wstring placeHolderText, const sf::Color& backgroundColor, bool isPassword, std::function<void()> onEnterHandler) :
	_caretVisible(false),
	_caretTimer(sf::Time::Zero),
	_caretPosition(0),
	_isActivated(false),
	_cursorType(sf::Cursor::Arrow),
	_isPassword(isPassword),
	_isMultiLine(false),
	_lineCount(0),
	_onEnterHandler(onEnterHandler)
{
	_lineLength.push_back(0);

	_textBox.setFillColor(backgroundColor);
	_textBox.setPosition(position);

	_inputText.setFont(font);
	_inputText.setCharacterSize(fontSize);
	_inputText.setFillColor(sf::Color::Black);
	_inputText.setPosition(_textBox.getPosition().x + 10.f, _textBox.getPosition().y + 5.f);

	_inputTextLenCounter.setFont(font);
	_inputTextLenCounter.setCharacterSize(fontSize);
	_inputTextLenCounter.setFillColor(sf::Color::Transparent);
	_inputTextLenCounter.setString(L"我");
	_singleWordHeight = _inputTextLenCounter.getGlobalBounds().height;

	_placeHolderText.setFont(font);
	_placeHolderText.setCharacterSize(fontSize);
	_placeHolderText.setFillColor(sf::Color(150, 150, 150));
	_placeHolderText.setString(placeHolderText);
	_placeHolderText.setPosition(_inputText.getPosition());

	_textBox.setSize(sf::Vector2f(width, _singleWordHeight + 20.f));

	_caret.setSize(sf::Vector2f(2.f, _singleWordHeight));
	_caret.setFillColor(sf::Color::Black);
	
	_displayString();
	_updateCaretPosition();
}

TextBox::TextBox(sf::Vector2f size, sf::Vector2f position, const sf::Font& font, const int& fontSize, const std::wstring placeHolderText, const sf::Color& backgroundColor, std::function<void()> onEnterHandler) :
	_caretVisible(false),
	_caretTimer(sf::Time::Zero),
	_caretPosition(0),
	_isActivated(false),
	_cursorType(sf::Cursor::Arrow),
	_isPassword(false),
	_isMultiLine(true),
	_lineCount(0),
	_onEnterHandler(onEnterHandler)
{
	_lineLength.push_back(0);

	_textBox.setFillColor(backgroundColor);
	_textBox.setPosition(position);
	_textBox.setSize(size);

	_inputText.setFont(font);
	_inputText.setCharacterSize(fontSize);
	_inputText.setFillColor(sf::Color::Black);
	_inputText.setPosition(_textBox.getPosition().x + 10.f, _textBox.getPosition().y + 5.f);

	_inputTextLenCounter.setFont(font);
	_inputTextLenCounter.setCharacterSize(fontSize);
	_inputTextLenCounter.setFillColor(sf::Color::Transparent);
	_inputTextLenCounter.setString(L"我");
	_singleWordHeight = _inputTextLenCounter.getGlobalBounds().height;

	_placeHolderText.setFont(font);
	_placeHolderText.setCharacterSize(fontSize);
	_placeHolderText.setFillColor(sf::Color(150, 150, 150));
	_placeHolderText.setString(placeHolderText);
	_placeHolderText.setPosition(_inputText.getPosition());

	_caret.setSize(sf::Vector2f(2.f, _singleWordHeight));
	_caret.setFillColor(sf::Color::Black);

	_displayString();
	_updateCaretPosition();
}

TextBox::~TextBox()
{

}

void TextBox::setText(std::wstring text)
{
	_inputString = text;
	_displayString();
}

void TextBox::setPlaceHolderText(std::wstring text)
{
	_placeHolderText.setString(text);
}

void TextBox::setPosition(const sf::Vector2f position)
{
	_textBox.setPosition(position);
	_inputText.setPosition(_textBox.getPosition().x + 10.f, _textBox.getPosition().y + 5.f);
	_placeHolderText.setPosition(_inputText.getPosition());
	_updateCaretPosition();
}

void TextBox::setFontSize(const int fontSize)
{
	_inputText.setCharacterSize(fontSize);
	_placeHolderText.setCharacterSize(fontSize);
	_inputTextLenCounter.setCharacterSize(fontSize);
	if (_inputTextLenCounter.getString() != L"") {
		_singleWordHeight = _inputTextLenCounter.getGlobalBounds().height;
	}
	else {
		_inputTextLenCounter.setString(L"我");
		_singleWordHeight = _inputTextLenCounter.getGlobalBounds().height;
		_inputTextLenCounter.setString(L"");
	}
	_caret.setSize(sf::Vector2f(2.f, _singleWordHeight));
	_textBox.setSize(sf::Vector2f(_textBox.getSize().x, _singleWordHeight + 20.f));
	_updateCaretPosition();
}

void TextBox::setBackgroundColor(const sf::Color backgroundColor)
{
	_textBox.setFillColor(backgroundColor);
}

void TextBox::setIsActivated(bool isActivated)
{
	_isActivated = isActivated;
	_caretPosition = 0;
}

std::wstring TextBox::getText()
{
	return _inputString;
}

bool TextBox::getIsActivated()
{
	return _isActivated;
}

void TextBox::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
	if (_textBox.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
		if (_cursor.loadFromSystem(sf::Cursor::Text)) {
			window.setMouseCursor(_cursor);
			_cursorType = sf::Cursor::Text;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			_setCaretPosition(sf::Mouse::getPosition(window));
			_isActivated = true;
		}
	}
	else {
		if (_cursorType != sf::Cursor::Arrow) {
			if (_cursor.loadFromSystem(sf::Cursor::Arrow)) {
				window.setMouseCursor(_cursor);
				_cursorType = sf::Cursor::Arrow;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			_isActivated = false;
		}
	}

	if (_isActivated) {
		if (event.type == sf::Event::TextEntered) {
			if (event.text.unicode == '\b' && _caretPosition != _inputString.size()) {
				if (!_inputString.empty()) {
					_inputString.erase(_inputString.end() - _caretPosition - 1);
				}
			}
			else if (event.text.unicode != '\b' && event.text.unicode != '\t') {
				if (_inputText.getGlobalBounds().width < _textBox.getSize().x - 40.f || _isMultiLine) {
					if (!_isMultiLine || _inputText.getGlobalBounds().height < _textBox.getSize().y - 20.f || _inputText.getGlobalBounds().width < _textBox.getSize().x - 40.f) {
						if (_caretPosition == 0) {
							_inputString += event.text.unicode;
						}
						else {
							_inputString.insert(_inputString.end() - _caretPosition, event.text.unicode);
						}
					}
				}
				else {

				}
			}
		}
		_displayString();

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Left) {
				if (_caretPosition < _inputString.size()) {
					_caretPosition++;
				}
			}
			else if (event.key.code == sf::Keyboard::Right) {
				if (_caretPosition > 0) {
					_caretPosition--;
				}
			}
			else if (event.key.code == sf::Keyboard::Delete) {
				if (_caretPosition != 0 && _inputString.size() != 0) {
					_inputString.erase(_inputString.end() - _caretPosition);
					_displayString();
					_caretPosition--;
				}
			}
			else if (event.key.code == sf::Keyboard::Enter) {
				_onEnterHandler();
			}
		}
	}
}

void TextBox::update(sf::Time dt)
{
	if (_isActivated) {
		_caretTimer += dt;
		if (_caretTimer >= sf::seconds(0.5f)) {
			_caretVisible = !_caretVisible;
			_caretTimer = sf::Time::Zero;
		}
		_updateCaretPosition();
	}
	else {
		_caretVisible = false;
	}
}

void TextBox::render(sf::RenderWindow& window) {
	window.draw(_textBox);
	if (_inputString.empty()) {
		window.draw(_placeHolderText);
	}
	else {
		window.draw(_inputText);
	}

	if (_isActivated && _caretVisible) {
		window.draw(_caret);
	}
}

void TextBox::_displayString()
{
	if (!_isPassword) {
		if (!_isMultiLine) {
			_inputText.setString(_inputString);
			_inputTextLenCounter.setString(_inputString);
		}
		else {
			_inputText.setString("");
			_inputTextLenCounter.setString("");
			_lineLength.clear();
			_lineLength.push_back(0);
			int lineLengthIndex = 0;
			for (size_t i = 0; i < _inputString.size(); i++) {
				_inputText.setString(_inputText.getString() + _inputString[i]);
				_inputTextLenCounter.setString(_inputTextLenCounter.getString() + _inputString[i]);
				_lineLength[lineLengthIndex]++;
				if (_inputTextLenCounter.getGlobalBounds().width > _textBox.getSize().x - 30.f) {
					_inputText.setString(_inputText.getString() + "\n");
					_inputTextLenCounter.setString("");
					_lineLength.push_back(_lineLength.back());
					lineLengthIndex++;
				}
			}
		}
	}
	else {
		_inputText.setString("");
		for (size_t i = 0; i < _inputString.size(); i++) {
			_inputText.setString(_inputText.getString() + "*");
		}
	}
}

void TextBox::_updateCaretPosition()
{
	if (_isMultiLine) {
		int i = 0;
		int temp = _inputString.size() - _caretPosition;
		_lineCount = 0;
		while (temp > _lineLength[i]) {
			i++;
			_lineCount++;
		}
	}

	sf::FloatRect textRect = _inputText.getGlobalBounds();
	sf::FloatRect textCounterRect = _inputTextLenCounter.getGlobalBounds();
	sf::FloatRect caretRect = _caret.getLocalBounds();
	_caret.setOrigin(caretRect.left + caretRect.width / 2.0f, caretRect.top + caretRect.height / 2.0f);
	int searchTextLen = _inputString.size();
	if (searchTextLen != 0) {
		if (!_isMultiLine) {
			_caret.setPosition(
				textRect.left + textRect.width + 1.f - textRect.width / searchTextLen * _caretPosition,
				_textBox.getPosition().y + _textBox.getSize().y / 2.0f
			);
		}
		else {
			if (_lineCount > 0) {
				if (_lineCount == _lineLength.size() - 1) {
					_caret.setPosition(
						textRect.left + textCounterRect.width + 1.f - textCounterRect.width / (_lineLength[_lineCount] - _lineLength[_lineCount - 1]) * (_caretPosition + _lineLength[_lineCount] - _inputString.size()),
						_textBox.getPosition().y + _singleWordHeight / 2.0f + 10.f + _lineCount * (_singleWordHeight + 3.f)
					);
				}
				else {
					_caret.setPosition(
						textRect.left + textRect.width + 1.f - textRect.width / (_lineLength[_lineCount] - _lineLength[_lineCount - 1]) * (_caretPosition + _lineLength[_lineCount] - _inputString.size()),
						_textBox.getPosition().y + _singleWordHeight / 2.0f + 10.f + _lineCount * (_singleWordHeight + 3.f)
					);
				}
			}
			else {
				_caret.setPosition(
					textRect.left + textRect.width + 1.f - textRect.width / _lineLength[_lineCount] * (_caretPosition + _lineLength[_lineCount] - _inputString.size()),
					_textBox.getPosition().y + _singleWordHeight / 2.0f + 10.f + _lineCount * (_singleWordHeight + 3.f)
				);
			}
		}
	}
	else {
		if (!_isMultiLine) {
			_caret.setPosition(
				textRect.left + textRect.width + 2.f,
				_textBox.getPosition().y + _textBox.getSize().y / 2.0f
			);
		}
		else {
			_caret.setPosition(
				textRect.left + textRect.width + 2.f,
				_textBox.getPosition().y + _singleWordHeight / 2.0f + 10.f
			);
		}
	}
}

void TextBox::_setCaretPosition(sf::Vector2i mousePosition)
{
	int searchTextLen = _inputString.size();
	if (searchTextLen != 0) {
		sf::FloatRect textRect = _inputText.getGlobalBounds();
		float textWidth = textRect.width;
		float textLeft = textRect.left;
		float textRight = textRect.left + textRect.width;
		float mousePosX = static_cast<float>(mousePosition.x);

		if (_isMultiLine) {
			float mousePosY = static_cast<float>(mousePosition.y);
			float textTop = textRect.top;
			_lineCount = static_cast<int>((mousePosY - textTop) / (_singleWordHeight + 3.f));
			if (_lineCount >= _lineLength.size()) {
				_lineCount = _lineLength.size() - 1;
			}

			if (mousePosX < textLeft) {
				if (_lineCount == 0) {
					_caretPosition = searchTextLen;
				}
				else {
					_caretPosition = searchTextLen - _lineLength[_lineCount - 1] - 1;
				}
			}
			else if (mousePosX > textRight) {
				_caretPosition = searchTextLen - _lineLength[_lineCount];
			}
			else {
				if (_lineCount == 0) {
					_caretPosition = static_cast<int>((textRight - mousePosX) / textWidth * _lineLength[_lineCount]);
				}
				else {
					_caretPosition = static_cast<int>((textRight - mousePosX) / textWidth * (_lineLength[_lineCount] - _lineLength[_lineCount - 1]));
				}
			}

			_caretPosition += (_inputString.size() - _lineLength[_lineCount]);
		}
		else
		{
			if (mousePosX < textLeft) {
				_caretPosition = searchTextLen;
			}
			else if (mousePosX > textRight) {
				_caretPosition = 0;
			}
			else {
				_caretPosition = static_cast<int>((textRight - mousePosX) / textWidth * searchTextLen);
			}
		}
	}
	else {
		_caretPosition = 0;
	}
}



TextDisplay::TextDisplay(sf::Vector2f size, sf::Vector2f position, const sf::Font& font, const int& fontSize, sf::Color backgroundColor, const std::wstring placeHolderText, const std::wstring text, bool isEditable, std::function<bool()> editHandler) :
	_textBox(size, position, font, fontSize, placeHolderText, backgroundColor),
	_editButton(sf::Vector2f(50.f, 50.f), sf::Vector2f(position.x + size.x, position.y), "Icon/editIcon(Grey).png", [&]() {_editButtonOnClickHandler(); }),
	_isEditable(isEditable),
	_isEditing(false),
	_editHandler(editHandler)
{
	_textBox.setText(text);
}

TextDisplay::~TextDisplay()
{

}

void TextDisplay::setText(std::wstring text)
{
	_textBox.setText(text);
}

void TextDisplay::setEditable(bool isEditable)
{
	_isEditable = isEditable;
}

std::wstring TextDisplay::getText()
{
	return _textBox.getText();
}

void TextDisplay::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	if (_isEditable) {
		_editButton.handleEvent(event, window);
		if (_isEditing) {
			_textBox.handleEvent(event, window);
		}
	}
}

void TextDisplay::update(sf::Time dt)
{
	if (_isEditing) {
		_textBox.update(dt);
	}
}

void TextDisplay::render(sf::RenderWindow& window)
{
	_textBox.render(window);
	if (_isEditable) {
		_editButton.render(window);
	}
}

void TextDisplay::_editButtonOnClickHandler()
{
	_isEditing = true;
	_editButton.setIcon("Icon/tickIcon.png");
	_editButton.setOnClickHandler([&]() {_tickButtonOnClickHandler(); });
}

void TextDisplay::_tickButtonOnClickHandler()
{
	if (_editHandler()) {
		_isEditing = false;
		_editButton.setIcon("Icon/editIcon(Grey).png");
		_editButton.setOnClickHandler([&]() {_editButtonOnClickHandler(); });
	}
}




DropDown::DropDown(sf::Vector2f size, sf::Vector2f position, const sf::Color& backgroundColor, const sf::Font& font, const int& fontSize, const std::wstring defaultOption, bool isActivate) :
	_dropDownButton(size, position, backgroundColor, defaultOption, font, fontSize, sf::Color::Black, [&]() {this->dropDownButtonOnClickHandler(); }),
	_selectedOption(defaultOption),
	_isDropDownVisible(false),
	_isActivate(isActivate),
	_font(font),
	_fontSize(fontSize),
	_backgroundColor(backgroundColor)
{
	if (_isActivate) {
		_dropDownButton.setText(defaultOption + L"▼");
	}
}

DropDown::~DropDown()
{
	_deleteOptionButtons();
}

void DropDown::setOptions(std::vector<std::wstring> options)
{
	_deleteOptionButtons();

	_options = options;

	_createOptionButtons();
}

bool DropDown::isDropDownVisible()
{
	return _isDropDownVisible;
}

void DropDown::setDropDownVisible(bool isVisible)
{
	_isDropDownVisible = isVisible;
}

void DropDown::setSelectOption(const std::wstring& option)
{

	_selectedOption = option;
	if (_isActivate) {
		_dropDownButton.setText(option + L"▼");
	}
	else {
		_dropDownButton.setText(option);
	}

	_deleteOptionButtons();
	_createOptionButtons();
}

void DropDown::setActivate(bool isActivate)
{
	_isActivate = isActivate;
	if (_isActivate) {
		_dropDownButton.setText(_selectedOption + L"▼");
	}
	else {
		_dropDownButton.setText(_selectedOption);
	}
}

void DropDown::setBackgroudColor(const sf::Color backgroundColor)
{
	_backgroundColor = backgroundColor;
	_dropDownButton.setBackgroundColor(_backgroundColor);

	_deleteOptionButtons();
	_createOptionButtons();
}

std::wstring DropDown::getSelectedOption()
{
	return _selectedOption;
}

bool DropDown::getVisibility()
{
	return _isDropDownVisible;
}

void DropDown::dropDownButtonOnClickHandler()
{
	_isDropDownVisible = !_isDropDownVisible;
}

void DropDown::optionButtonOnClickHandler(std::wstring option)
{
	setDropDownVisible(false);
	setSelectOption(option);
}

void DropDown::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	_dropDownButton.handleEvent(event, window);
	if (_isDropDownVisible) {
		sf::FloatRect floatRect(_dropDownButton.getPosition(), _dropDownButton.getSize());
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !floatRect.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))) ) {
			setDropDownVisible(false);
		}
		
		if (!_optionButtons.empty()) {
			for (TextToogleButton* optionButton : _optionButtons) {
				optionButton->handleEvent(event, window);
			}
		}
	}
}

void DropDown::render(sf::RenderWindow& window)
{
	_dropDownButton.render(window);
	if (_isDropDownVisible && !_optionButtons.empty()) {
		for (TextToogleButton* optionButton : _optionButtons) {
			optionButton->render(window);
		}
	}
}

void DropDown::_createOptionButtons()
{
	//_optionButtons.clear();
	int positionIndex = 1;
	for (size_t i = 0; i < _options.size(); i++) {
		if (_options[i] != _selectedOption) {
			std::wstring text(_options[i]);
			TextToogleButton* optionButton = new TextToogleButton(_dropDownButton.getSize(), sf::Vector2f(_dropDownButton.getPosition().x, _dropDownButton.getPosition().y + _dropDownButton.getSize().y * positionIndex), _backgroundColor, text, _font, _fontSize, _fontSize, sf::Color::Black, sf::Color(203, 140, 63, 255), [=]() {this->optionButtonOnClickHandler(text); }, false);
			_optionButtons.push_back(optionButton);
			positionIndex++;
		}
	}
}

void DropDown::_deleteOptionButtons()
{
	while (!_optionButtons.empty()) {
		TextToogleButton* optionButton = _optionButtons.back();
		delete optionButton;
		_optionButtons.pop_back();
	}
}



TextDisplayDropDown::TextDisplayDropDown(sf::Vector2f size, sf::Vector2f position, const sf::Font& font, const int& fontSize, sf::Color backgroundColor, const std::wstring text, std::vector<std::wstring> options, bool isEditable, std::function<bool()> editHandler) :
	_dropDown(size, position, backgroundColor, font, fontSize, text, false),
	_editButton(sf::Vector2f(50.f, 50.f), sf::Vector2f(position.x + size.x, position.y), "Icon/editIcon(Grey).png", [&]() {_editButtonOnClickHandler(); }),
	_isEditable(isEditable),
	_isEditing(false),
	_editHandler(editHandler)
{
	_dropDown.setOptions(options);
}

TextDisplayDropDown::~TextDisplayDropDown()
{

}

void TextDisplayDropDown::setText(std::wstring text)
{
	_dropDown.setSelectOption(text);
}

void TextDisplayDropDown::setEditable(bool isEditable)
{
	_isEditable = isEditable;
}

void TextDisplayDropDown::setOptions(std::vector<std::wstring> options)
{
	_dropDown.setOptions(options);
}

std::wstring TextDisplayDropDown::getText()
{
	return _dropDown.getSelectedOption();
}

void TextDisplayDropDown::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	if (_isEditable) {
		_editButton.handleEvent(event, window);
		if (_isEditing) {
			_dropDown.handleEvent(event, window);
		}
	}
}

void TextDisplayDropDown::update(sf::Time dt)
{
	
}

void TextDisplayDropDown::render(sf::RenderWindow& window)
{
	_dropDown.render(window);
	if (_isEditable) {
		_editButton.render(window);
	}
}

void TextDisplayDropDown::_editButtonOnClickHandler()
{
	_isEditing = true;
	_changeDropDownColor();
	_dropDown.setActivate(true);
	_editButton.setIcon("Icon/tickIcon.png");
	_editButton.setOnClickHandler([&]() {_tickButtonOnClickHandler(); });
}

void TextDisplayDropDown::_tickButtonOnClickHandler()
{
	if (_editHandler()) {
		_isEditing = false;
		_changeDropDownColor();
		_dropDown.setActivate(false);
		_editButton.setIcon("Icon/editIcon(Grey).png");
		_editButton.setOnClickHandler([&]() {_editButtonOnClickHandler(); });
	}
}

void TextDisplayDropDown::_changeDropDownColor()
{
	if (_isEditing) {
		_dropDown.setBackgroudColor(sf::Color(203, 140, 63, 255));
	}
	else {
		_dropDown.setBackgroudColor(sf::Color::Transparent);
	}
}



SearchBar::SearchBar(float width, sf::Vector2f position, const std::wstring placeHolderText, const sf::Font& font, const int& fontSize, std::function<void()> searchHandler) :
	TextBox(width, position, font, fontSize, placeHolderText, sf::Color::White, false, searchHandler),
	_searchButton(sf::Vector2f(_textBox.getSize().y, _textBox.getSize().y), sf::Vector2f(_textBox.getPosition().x + _textBox.getSize().x, _textBox.getPosition().y), "Icon/searchIcon.png", searchHandler),
	_bookCategoryDropDown(sf::Vector2f(350.f, _textBox.getSize().y), sf::Vector2f(_textBox.getPosition().x - 350.f, _textBox.getPosition().y), sf::Color(200,200,200,255), font, fontSize, L"全部"),
	_searchTypeDropDown(sf::Vector2f(200.f, _textBox.getSize().y), sf::Vector2f(_textBox.getPosition().x + width + _textBox.getSize().y, _textBox.getPosition().y), sf::Color(200, 200, 200, 255), font, fontSize, L"全部"),
	_searchHandler(searchHandler),
	_isDropDownActivated(true)
{
	_bookCategoryDropDown.setOptions({ L"全部", L"小说类", L"传记与回忆录", L"历史与文化", L"科学与自然", L"商业与经济", L"健康与生活方式", L"艺术与设计", L"语言与文学", L"参考手册", L"儿童读物", L"其他"});
	_searchTypeDropDown.setOptions({ L"全部", L"书名", L"作者", L"出版社"});
}

SearchBar::~SearchBar()
{

}

std::wstring SearchBar::getCategory()
{
	return _bookCategoryDropDown.getSelectedOption();
}

std::wstring SearchBar::getFilter()
{
	return _searchTypeDropDown.getSelectedOption();
}

std::wstring SearchBar::getSearchWord()
{
	return TextBox::getText();
}

bool SearchBar::getDropDownVisibility()
{
	return _bookCategoryDropDown.getVisibility() || _searchTypeDropDown.getVisibility();
}

void SearchBar::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	TextBox::handleEvent(event, window);
	_searchButton.handleEvent(event, window);
	_bookCategoryDropDown.handleEvent(event, window);
	_searchTypeDropDown.handleEvent(event, window);
}

void SearchBar::update(sf::Time dt)
{
	TextBox::update(dt);
	//_searchButton.update(dt);
}

void SearchBar::render(sf::RenderWindow& window)
{
	TextBox::render(window);
	_searchButton.render(window);
	_bookCategoryDropDown.render(window);
	_searchTypeDropDown.render(window);
}



PageNumber::PageNumber(sf::Vector2f position, const sf::Font& font, int fontSize, std::function<void(int)> changePageHandler) :
	TextBox(70.f, position, font, fontSize, L"页数", sf::Color::White, false, [&]() {_setPageNumber(); }),
	_changePageHandler(changePageHandler)
{
	_totalPage.setFont(font);
	_totalPage.setCharacterSize(fontSize);
	_totalPage.setFillColor(sf::Color::Black);
	_totalPage.setPosition(_textBox.getPosition().x + _textBox.getSize().x, _textBox.getPosition().y + 5.f);
}

PageNumber::~PageNumber()
{

}

void PageNumber::setCurrentPage(int currentPage)
{
	_inputString = std::to_wstring(currentPage);
	_inputText.setString(_inputString);
}

void PageNumber::setTotalPage(int totalPage)
{
	_totalPage.setString(L"/" + std::to_wstring(totalPage));
}

void PageNumber::setPosition(const sf::Vector2f position)
{
	TextBox::setPosition(position);
	_totalPage.setPosition(_textBox.getPosition().x + _textBox.getSize().x, _textBox.getPosition().y + 5.f);
}

void PageNumber::setFontSize(const int fontSize)
{
	TextBox::setFontSize(fontSize);
	_totalPage.setCharacterSize(fontSize);
}

void PageNumber::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	TextBox::handleEvent(event, window);
}

void PageNumber::update(sf::Time dt)
{
	TextBox::update(dt);
}

void PageNumber::render(sf::RenderWindow& window)
{
	TextBox::render(window);
	window.draw(_totalPage);
}

void PageNumber::_setPageNumber()
{
	_changePageHandler(std::stoi(_inputString));
}



BookDisplay::BookDisplay(sf::Vector2f bookCoverSize, sf::Vector2f position, const sf::Font& font, const int& fontSize, bool isVisible, std::function<void()> onClickHandler) :
	_bookCover(bookCoverSize, position, "Icon/blankBook.jpg", onClickHandler),
	_bookName(sf::Vector2f(bookCoverSize.x, 50), sf::Vector2f(position.x, position.y + bookCoverSize.y + 20.f), sf::Color::Transparent, L"书名", font, fontSize, fontSize, sf::Color::Black, sf::Color::Blue, onClickHandler),
	_isVisible(isVisible),
	_book(NULL)
{

}

BookDisplay::~BookDisplay()
{

}

void BookDisplay::setBook(Book* book)
{
	_book = book;
	if (_book->getImgUrl() != "")
		_bookCover.setIcon(_book->getImgUrl());

	if (_book->getBookName() != L"")
		_bookName.setText(_book->getBookName());
}

void BookDisplay::setBookCover(const std::string& bookCoverPath)
{
	_bookCover.setIcon(bookCoverPath);
}

void BookDisplay::setBookName(const std::wstring& bookName)
{
	_bookName.setText(bookName);
}

void BookDisplay::setPosition(const sf::Vector2f& position)
{
	_bookCover.setPosition(position);
	_bookName.setPosition(sf::Vector2f(position.x, position.y + _bookCover.getSize().y + 20.f));
}

void BookDisplay::setOnClickHandler(std::function<void()> onClickHandler)
{
	_bookCover.setOnClickHandler(onClickHandler);
	_bookName.setOnClickHandler(onClickHandler);
}

void BookDisplay::setVisiblity(bool isVisible)
{
	_isVisible = isVisible;
}

void BookDisplay::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	if (_isVisible) {
		_bookCover.handleEvent(event, window);
		_bookName.handleEvent(event, window);
	}
}

void BookDisplay::render(sf::RenderWindow& window)
{
	if (_isVisible) {
		_bookCover.render(window);
		_bookName.render(window);
	}
}



BooksDisplayInRow::BooksDisplayInRow(float postionY, const sf::Font& font, std::function<void(Book*)> onClickHandler) :
	_bookDisplay1(sf::Vector2f(200, 250), sf::Vector2f(260, postionY), font, 25),
	_bookDisplay2(sf::Vector2f(200, 250), sf::Vector2f(560, postionY), font, 25),
	_bookDisplay3(sf::Vector2f(200, 250), sf::Vector2f(860, postionY), font, 25),
	_bookDisplay4(sf::Vector2f(200, 250), sf::Vector2f(1160, postionY), font, 25),
	_bookDisplay5(sf::Vector2f(200, 250), sf::Vector2f(1460, postionY), font, 25),
	_leftArrow(sf::Vector2f(70, 70), sf::Vector2f(70, postionY + 100.f), "Icon/leftSideArrowIcon.jpg", [&]() {this->switchLeftDisplay(); }),
	_rightArrow(sf::Vector2f(70, 70), sf::Vector2f(1780, postionY + 100.f), "Icon/rightSideArrowIcon.jpg", [&]() {this->switchRightDisplay(); }),
	_currentDisplayPage(0),
	_maxBooksIndex(0),
	_onClickHandler(onClickHandler)
{

}

BooksDisplayInRow::~BooksDisplayInRow()
{

}

void BooksDisplayInRow::setBooks(std::vector<Book>&& books)
{
	_books = std::move(books);

	_currentDisplayPage = 0;
	_maxBooksIndex = _books.size();
	_updateDisplay();
}

void BooksDisplayInRow::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	_bookDisplay1.handleEvent(event, window);
	_bookDisplay2.handleEvent(event, window);
	_bookDisplay3.handleEvent(event, window);
	_bookDisplay4.handleEvent(event, window);
	_bookDisplay5.handleEvent(event, window);
	if (_currentDisplayPage != 0) {
		_leftArrow.handleEvent(event, window);
	}
	if (_currentDisplayPage * 5 + 5 < _maxBooksIndex) {
		_rightArrow.handleEvent(event, window);
	}
}

void BooksDisplayInRow::update(sf::Time dt)
{

}

void BooksDisplayInRow::render(sf::RenderWindow& window)
{
	_bookDisplay1.render(window);
	_bookDisplay2.render(window);
	_bookDisplay3.render(window);
	_bookDisplay4.render(window);
	_bookDisplay5.render(window);
	if (_currentDisplayPage != 0) {
		_leftArrow.render(window);
	}
	if (_currentDisplayPage * 5 + 5 < _maxBooksIndex) {
		_rightArrow.render(window);
	}
}

void BooksDisplayInRow::switchLeftDisplay()
{
	if (_currentDisplayPage > 0) {
		_currentDisplayPage--;
		_bookDisplay1.setBook(&_books[_currentDisplayPage * 5]);
		_bookDisplay2.setBook(&_books[_currentDisplayPage * 5 + 1]);
		_bookDisplay3.setBook(&_books[_currentDisplayPage * 5 + 2]);
		_bookDisplay4.setBook(&_books[_currentDisplayPage * 5 + 3]);
		_bookDisplay5.setBook(&_books[_currentDisplayPage * 5 + 4]);

		_bookDisplay1.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 5]); });
		_bookDisplay2.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 5 + 1]); });
		_bookDisplay3.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 5 + 2]); });
		_bookDisplay4.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 5 + 3]); });
		_bookDisplay5.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 5 + 4]); });
		
		_bookDisplay1.setVisiblity(true);
		_bookDisplay2.setVisiblity(true);
		_bookDisplay3.setVisiblity(true);
		_bookDisplay4.setVisiblity(true);
		_bookDisplay5.setVisiblity(true);
	}

}

void BooksDisplayInRow::switchRightDisplay()
{
	_currentDisplayPage++;
	_updateDisplay();
}

void BooksDisplayInRow::_updateDisplay()
{
	if (_currentDisplayPage * 5 < _maxBooksIndex) {
		_bookDisplay1.setBook(&_books[_currentDisplayPage * 5]);
		_bookDisplay1.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 5]); });
		_bookDisplay1.setVisiblity(true);
	}
	else {
		_bookDisplay1.setVisiblity(false);
	}
	if (_currentDisplayPage * 5 + 1 < _maxBooksIndex) {
		_bookDisplay2.setBook(&_books[_currentDisplayPage * 5 + 1]);
		_bookDisplay2.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 5 + 1]); });
		_bookDisplay2.setVisiblity(true);
	}
	else {
		_bookDisplay2.setVisiblity(false);
	}
	if (_currentDisplayPage * 5 + 2 < _maxBooksIndex) {
		_bookDisplay3.setBook(&_books[_currentDisplayPage * 5 + 2]);
		_bookDisplay3.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 5 + 2]); });
		_bookDisplay3.setVisiblity(true);
	}
	else {
		_bookDisplay3.setVisiblity(false);
	}
	if (_currentDisplayPage * 5 + 3 < _maxBooksIndex) {
		_bookDisplay4.setBook(&_books[_currentDisplayPage * 5 + 3]);
		_bookDisplay4.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 5 + 3]); });
		_bookDisplay4.setVisiblity(true);
	}
	else {
		_bookDisplay4.setVisiblity(false);
	}
	if (_currentDisplayPage * 5 + 4 < _maxBooksIndex) {
		_bookDisplay5.setBook(&_books[_currentDisplayPage * 5 + 4]);
		_bookDisplay5.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 5 + 4]); });
		_bookDisplay5.setVisiblity(true);
	}
	else {
		_bookDisplay5.setVisiblity(false);
	}
}


#define ROW_ONE_Y 350
#define ROW_TWO_Y 720
BooksDisplayInPage::BooksDisplayInPage(const sf::Font& font, std::function<void(Book*)> onClickHandler) :
	_bookDisplay1(sf::Vector2f(200, 250), sf::Vector2f(260, ROW_ONE_Y), font, 25),
	_bookDisplay2(sf::Vector2f(200, 250), sf::Vector2f(560, ROW_ONE_Y), font, 25),
	_bookDisplay3(sf::Vector2f(200, 250), sf::Vector2f(860, ROW_ONE_Y), font, 25),
	_bookDisplay4(sf::Vector2f(200, 250), sf::Vector2f(1160, ROW_ONE_Y), font, 25),
	_bookDisplay5(sf::Vector2f(200, 250), sf::Vector2f(1460, ROW_ONE_Y), font, 25),
	_bookDisplay6(sf::Vector2f(200, 250), sf::Vector2f(260, ROW_TWO_Y), font, 25),
	_bookDisplay7(sf::Vector2f(200, 250), sf::Vector2f(560, ROW_TWO_Y), font, 25),
	_bookDisplay8(sf::Vector2f(200, 250), sf::Vector2f(860, ROW_TWO_Y), font, 25),
	_bookDisplay9(sf::Vector2f(200, 250), sf::Vector2f(1160, ROW_TWO_Y), font, 25),
	_bookDisplay10(sf::Vector2f(200, 250), sf::Vector2f(1460, ROW_TWO_Y), font, 25),
	_leftArrow(sf::Vector2f(70, 70), sf::Vector2f(70, 650), "Icon/leftSideArrowIcon.jpg", [&]() {this->switchLeftDisplay(); }),
	_rightArrow(sf::Vector2f(70, 70), sf::Vector2f(1780, 650), "Icon/rightSideArrowIcon.jpg", [&]() {this->switchRightDisplay(); }),
	_currentDisplayPage(0),
	_maxBooksIndex(0),
	_onClickHandler(onClickHandler)
{

}

BooksDisplayInPage::~BooksDisplayInPage()
{

}

void BooksDisplayInPage::setBooks(std::vector<Book>&& books)
{
	_books = std::move(books);

	_maxBooksIndex = _books.size();
	_currentDisplayPage = 0;
	_updateDisplay();
}

void BooksDisplayInPage::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	_bookDisplay1.handleEvent(event, window);
	_bookDisplay2.handleEvent(event, window);
	_bookDisplay3.handleEvent(event, window);
	_bookDisplay4.handleEvent(event, window);
	_bookDisplay5.handleEvent(event, window);
	_bookDisplay6.handleEvent(event, window);
	_bookDisplay7.handleEvent(event, window);
	_bookDisplay8.handleEvent(event, window);
	_bookDisplay9.handleEvent(event, window);
	_bookDisplay10.handleEvent(event, window);

	if (_currentDisplayPage != 0) {
		_leftArrow.handleEvent(event, window);
	}
	if (_currentDisplayPage * 10 + 10 < _maxBooksIndex) {
		_rightArrow.handleEvent(event, window);
	}
}

void BooksDisplayInPage::update(sf::Time dt)
{

}

void BooksDisplayInPage::render(sf::RenderWindow& window)
{
	_bookDisplay1.render(window);
	_bookDisplay2.render(window);
	_bookDisplay3.render(window);
	_bookDisplay4.render(window);
	_bookDisplay5.render(window);
	_bookDisplay6.render(window);
	_bookDisplay7.render(window);
	_bookDisplay8.render(window);
	_bookDisplay9.render(window);
	_bookDisplay10.render(window);

	if (_currentDisplayPage != 0) {
		_leftArrow.render(window);
	}
	if (_currentDisplayPage * 10 + 10 < _maxBooksIndex) {
		_rightArrow.render(window);
	}
}

void BooksDisplayInPage::switchLeftDisplay()
{
	if (_currentDisplayPage > 0) {
		_currentDisplayPage--;
		_bookDisplay1.setBook(&_books[_currentDisplayPage * 10]);
		_bookDisplay2.setBook(&_books[_currentDisplayPage * 10 + 1]);
		_bookDisplay3.setBook(&_books[_currentDisplayPage * 10 + 2]);
		_bookDisplay4.setBook(&_books[_currentDisplayPage * 10 + 3]);
		_bookDisplay5.setBook(&_books[_currentDisplayPage * 10 + 4]);
		_bookDisplay6.setBook(&_books[_currentDisplayPage * 10 + 5]);
		_bookDisplay7.setBook(&_books[_currentDisplayPage * 10 + 6]);
		_bookDisplay8.setBook(&_books[_currentDisplayPage * 10 + 7]);
		_bookDisplay9.setBook(&_books[_currentDisplayPage * 10 + 8]);
		_bookDisplay10.setBook(&_books[_currentDisplayPage * 10 + 9]);

		_bookDisplay1.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 10]); });
		_bookDisplay2.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 10 + 1]); });
		_bookDisplay3.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 10 + 2]); });
		_bookDisplay4.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 10 + 3]); });
		_bookDisplay5.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 10 + 4]); });
		_bookDisplay6.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 10 + 5]); });
		_bookDisplay7.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 10 + 6]); });
		_bookDisplay8.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 10 + 7]); });
		_bookDisplay9.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 10 + 8]); });
		_bookDisplay10.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 10 + 9]); });

		_bookDisplay1.setVisiblity(true);
		_bookDisplay2.setVisiblity(true);
		_bookDisplay3.setVisiblity(true);
		_bookDisplay4.setVisiblity(true);
		_bookDisplay5.setVisiblity(true);
		_bookDisplay6.setVisiblity(true);
		_bookDisplay7.setVisiblity(true);
		_bookDisplay8.setVisiblity(true);
		_bookDisplay9.setVisiblity(true);
		_bookDisplay10.setVisiblity(true);
	}

}

void BooksDisplayInPage::switchRightDisplay()
{
	_currentDisplayPage++;
	_updateDisplay();
}

void BooksDisplayInPage::_updateDisplay()
{
	if (_currentDisplayPage * 10 < _maxBooksIndex) {
		_bookDisplay1.setBook(&_books[_currentDisplayPage * 10]);
		_bookDisplay1.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 10]); });
		_bookDisplay1.setVisiblity(true);
	}
	else {
		_bookDisplay1.setVisiblity(false);
	}
	if (_currentDisplayPage * 10 + 1 < _maxBooksIndex) {
		_bookDisplay2.setBook(&_books[_currentDisplayPage * 10 + 1]);
		_bookDisplay2.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 10 + 1]); });
		_bookDisplay2.setVisiblity(true);
	}
	else {
		_bookDisplay2.setVisiblity(false);
	}
	if (_currentDisplayPage * 10 + 2 < _maxBooksIndex) {
		_bookDisplay3.setBook(&_books[_currentDisplayPage * 10 + 2]);
		_bookDisplay3.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 10 + 2]); });
		_bookDisplay3.setVisiblity(true);
	}
	else {
		_bookDisplay3.setVisiblity(false);
	}
	if (_currentDisplayPage * 10 + 3 < _maxBooksIndex) {
		_bookDisplay4.setBook(&_books[_currentDisplayPage * 10 + 3]);
		_bookDisplay4.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 10 + 3]); });
		_bookDisplay4.setVisiblity(true);
	}
	else {
		_bookDisplay4.setVisiblity(false);
	}
	if (_currentDisplayPage * 10 + 4 < _maxBooksIndex) {
		_bookDisplay5.setBook(&_books[_currentDisplayPage * 10 + 4]);
		_bookDisplay5.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 10 + 4]); });
		_bookDisplay5.setVisiblity(true);
	}
	else {
		_bookDisplay5.setVisiblity(false);
	}
	if (_currentDisplayPage * 10 + 5 < _maxBooksIndex) {
		_bookDisplay6.setBook(&_books[_currentDisplayPage * 10 + 5]);
		_bookDisplay6.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 10 + 5]); });
		_bookDisplay6.setVisiblity(true);
	}
	else {
		_bookDisplay6.setVisiblity(false);
	}
	if (_currentDisplayPage * 10 + 6 < _maxBooksIndex) {
		_bookDisplay7.setBook(&_books[_currentDisplayPage * 10 + 6]);
		_bookDisplay7.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 10 + 6]); });
		_bookDisplay7.setVisiblity(true);
	}
	else {
		_bookDisplay7.setVisiblity(false);
	}
	if (_currentDisplayPage * 10 + 7 < _maxBooksIndex) {
		_bookDisplay8.setBook(&_books[_currentDisplayPage * 10 + 7]);
		_bookDisplay8.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 10 + 7]); });
		_bookDisplay8.setVisiblity(true);
	}
	else {
		_bookDisplay8.setVisiblity(false);
	}
	if (_currentDisplayPage * 10 + 8 < _maxBooksIndex) {
		_bookDisplay9.setBook(&_books[_currentDisplayPage * 10 + 8]);
		_bookDisplay9.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 10 + 8]); });
		_bookDisplay9.setVisiblity(true);
	}
	else {
		_bookDisplay9.setVisiblity(false);
	}
	if (_currentDisplayPage * 10 + 9 < _maxBooksIndex) {
		_bookDisplay10.setBook(&_books[_currentDisplayPage * 10 + 9]);
		_bookDisplay10.setOnClickHandler([&]() {_onClickHandler(&_books[_currentDisplayPage * 10 + 9]); });
		_bookDisplay10.setVisiblity(true);
	}
	else {
		_bookDisplay10.setVisiblity(false);
	}
}



Table::Table(sf::Vector2f size, sf::Vector2f position, const sf::Font& font, const int& fontSize, std::vector<std::wstring>&& headers, std::vector<float>&& rowWidth, const float& rowHeight, sf::Color headerColor, sf::Color rowColor1, sf::Color rowColor2, bool isScrollable, std::function<void(Book*)> bookOnClickHandler, std::function<void(UserInfo*)> userOnClickHandler, int bookButtonIndex, int userButtonIndex) :
	_view(sf::FloatRect(position, size)),
	_font(font),
	_fontSize(fontSize),
	_headers(std::move(headers)),
	_headerColor(headerColor),
	_rowColor1(rowColor1),
	_rowColor2(rowColor2),
	_position(position),
	_rowWidth(std::move(rowWidth)),
	_rowHeight(rowHeight),
	_isScrollable(isScrollable),
	_pageNumber(sf::Vector2f(1700, 970), font, fontSize, [&](int page) {_setPageNumber(page); }),
	_leftArrow(sf::Vector2f(70, 70), sf::Vector2f(1500, 950), "Icon/leftSideArrowIcon.jpg", [&]() {_previousPage(); }),
	_rightArrow(sf::Vector2f(70, 70), sf::Vector2f(1600, 950), "Icon/rightSideArrowIcon.jpg", [&]() {_nextPage(); }),
	_currentDisplayPage(0),
	_bookOnClickHandler(bookOnClickHandler),
	_userOnClickHandler(userOnClickHandler),
	_bookButtonIndex(bookButtonIndex),
	_userButtonIndex(userButtonIndex)
{
	_totalRows = size.y / rowHeight - 1;
	_updateHeaders();
	_pageNumber.setCurrentPage(_currentDisplayPage + 1);
}

Table::~Table()
{
	while (!_headerButtons.empty()) {
		TextToogleButton* headerButton = _headerButtons.back();
		delete headerButton;
		_headerButtons.pop_back();
	}

	while (!_rowDisplay.empty()) {
		_row* row = _rowDisplay.back();
		delete row;
		_rowDisplay.pop_back();
	}
}

void Table::setHeaders(std::vector<std::wstring>&& headers, std::vector<float>&& rowWidth)
{
	_headers = std::move(headers);
	_rowWidth = std::move(rowWidth);

	_updateHeaders();
}

void Table::setRows(std::vector<std::vector<std::wstring>>&& rowsData, std::vector<Book>&& books, std::vector<UserInfo>&& users)
{
	_rowsData = std::move(rowsData);
	_books = std::move(books);
	_users = std::move(users);

	_updateRows();
}

void Table::setLeftArrowPosition(const sf::Vector2f position)
{
	_leftArrow.setPosition(position);
}

void Table::setLeftArrowSize(const sf::Vector2f size)
{
	_leftArrow.setSize(size);
}

void Table::setRightArrowPosition(const sf::Vector2f position)
{
	_rightArrow.setPosition(position);
}

void Table::setRightArrowSize(const sf::Vector2f size)
{
	_rightArrow.setSize(size);
}

void Table::setPageNumberPosition(const sf::Vector2f position)
{
	_pageNumber.setPosition(position);
}

void Table::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	for (TextToogleButton* headerButton : _headerButtons) {
		headerButton->handleEvent(event, window);
	}

	if (_isScrollable) {
		for (_row* row : _rowDisplay) {
			row->handleEvent(event, window);
		}
	}
	else {
		_pageNumber.handleEvent(event, window);
		if (_currentDisplayPage > 0) {
			_leftArrow.handleEvent(event, window);
		}
		if (_currentDisplayPage * _totalRows + _totalRows < _rowDisplay.size()) {
			_rightArrow.handleEvent(event, window);
		}

		for (size_t i = 0; i < _totalRows; i++) {
			if (i + _currentDisplayPage * _totalRows < _rowDisplay.size()) {
				_row* row = _rowDisplay[i + _currentDisplayPage * _totalRows];
				row->handleEvent(event, window);
			}
		}
	}
}

void Table::update(sf::Time dt)
{
	_pageNumber.update(dt);
}

void Table::render(sf::RenderWindow& window)
{
	for (TextToogleButton* headerButton : _headerButtons) {
		headerButton->render(window);
	}

	if (_isScrollable) {
		for (_row* row : _rowDisplay) {
			row->render(window);
		}
	}
	else {
		_pageNumber.render(window);
		if (_currentDisplayPage > 0) {
			_leftArrow.render(window);
		}
		if (_currentDisplayPage * _totalRows + _totalRows < _rowDisplay.size()) {
			_rightArrow.render(window);
		}

		for (size_t i = 0; i < _totalRows; i++) {
			if (i + _currentDisplayPage * _totalRows < _rowDisplay.size()) {
				_row* row = _rowDisplay[i + _currentDisplayPage * _totalRows];
				row->render(window);
			}
		}
	}
}

Table::_row::_row(sf::Vector2f position, const sf::Font& font, const int& fontSize, std::vector<std::wstring> rowData, std::vector<float> rowWidth, float rowHeight, sf::Color backgroundColor) :
	_rowData(rowData),
	_rowWidth(rowWidth),
	_rowHeight(rowHeight),
	_bookButtonIndex(-1),
	_userButtonIndex(-1)
{
	float positionX = position.x;
	for (size_t i = 0; i < _rowData.size(); i++) {
		TextToogleButton* colomnButton = new TextToogleButton(sf::Vector2f(_rowWidth[i], _rowHeight), sf::Vector2f(positionX, position.y), backgroundColor, _rowData[i], font, fontSize, fontSize, sf::Color::Black, sf::Color::Black, [&]() {}, false);
		_rowButtons.push_back(colomnButton);
		positionX += _rowWidth[i];
	}
}

Table::_row::~_row()
{
	while (!_rowButtons.empty()) {
		TextToogleButton* rowButton = _rowButtons.back();
		delete rowButton;
		_rowButtons.pop_back();
	}
}

void Table::_row::setBookOnClickHandler(int bookButtonIndex, Book* book, std::function<void(Book*)> bookOnClickHandler)
{
	_bookButtonIndex = bookButtonIndex;
	if (_bookButtonIndex == ALL_COLUMNS) {
		for (TextToogleButton* rowButton : _rowButtons) {
			rowButton->setOnClickHandler([=]() {bookOnClickHandler(book); });
		}
	}
	else {
		if (bookButtonIndex > -1) {
			_rowButtons[bookButtonIndex]->setOnClickHandler([=]() {bookOnClickHandler(book); });
		}
	}
}

void Table::_row::setUserOnClickHandler(int userButtonIndex, UserInfo* user, std::function<void(UserInfo*)> userOnClickHandler)
{
	_userButtonIndex = userButtonIndex;
	if (_userButtonIndex == ALL_COLUMNS) {
		for (TextToogleButton* rowButton : _rowButtons) {
			rowButton->setOnClickHandler([=]() {userOnClickHandler(user); });
		}
	}
	else {
		if (userButtonIndex > -1) {
			_rowButtons[userButtonIndex]->setOnClickHandler([=]() {userOnClickHandler(user); });
		}
	}
}

void Table::_row::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	if (_bookButtonIndex == ALL_COLUMNS || _userButtonIndex == ALL_COLUMNS) {
		for (TextToogleButton* rowButton : _rowButtons) {
			rowButton->handleEvent(event, window);
		}
	}
	else {
		for (size_t i = 0; i < _rowButtons.size(); i++) {
			if (i == _bookButtonIndex || i == _userButtonIndex) {
				_rowButtons[i]->handleEvent(event, window);
			}
		}
	}
}

void Table::_row::render(sf::RenderWindow& window)
{
	for (TextToogleButton* rowButton : _rowButtons) {
		rowButton->render(window);
	}
}

void Table::_updateRows()
{
	while (!_rowDisplay.empty()) {
		_row* row = _rowDisplay.back();
		delete row;
		_rowDisplay.pop_back();
	}

	int currentRow = 0;
	float positionY = _position.y + _rowHeight;
	for (size_t i = 0; i < _rowsData.size(); i++) {
		_row* row = new _row(sf::Vector2f(_position.x, positionY), _font, _fontSize, _rowsData[i], _rowWidth, _rowHeight, i % 2 == 0 ? _rowColor1 : _rowColor2);
		if (_bookButtonIndex != -1) {
			row->setBookOnClickHandler(_bookButtonIndex, &_books[i], _bookOnClickHandler);
		}
		
		if (_userButtonIndex != -1) {
			row->setUserOnClickHandler(_userButtonIndex, &_users[i], _userOnClickHandler);
		}

		_rowDisplay.push_back(row);
		positionY += _rowHeight;
		currentRow++;
		if (!_isScrollable && currentRow >= _totalRows) {
			positionY = _position.y + _rowHeight;
			currentRow = 0;
		}
	}

	if (_rowDisplay.size() % _totalRows == 0) {
		_pageNumber.setTotalPage(_rowDisplay.size() / _totalRows);
	}
	else {
		_pageNumber.setTotalPage(_rowDisplay.size() / _totalRows + 1);
	}
}

void Table::_updateHeaders()
{
	while (!_headerButtons.empty()) {
		TextToogleButton* headerButton = _headerButtons.back();
		delete headerButton;
		_headerButtons.pop_back();
	}

	float positionX = _position.x;
	for (size_t i = 0; i < _headers.size(); i++) {
		TextToogleButton* headerButton = new TextToogleButton(sf::Vector2f(_rowWidth[i], _rowHeight), sf::Vector2f(positionX, _position.y), _headerColor, _headers[i], _font, _fontSize, _fontSize, sf::Color::Black, sf::Color::Black, [&]() {}, false);
		_headerButtons.push_back(headerButton);
		positionX += _rowWidth[i];
	}
}

void Table::_previousPage()
{
	if (_currentDisplayPage > 0) {
		_currentDisplayPage--;
		_pageNumber.setCurrentPage(_currentDisplayPage + 1);
	}
}

void Table::_nextPage()
{
	if (_currentDisplayPage * _totalRows + _totalRows < _rowDisplay.size()) {
		_currentDisplayPage++;
		_pageNumber.setCurrentPage(_currentDisplayPage + 1);
	}
}

void Table::_setPageNumber(int pageNumber)
{
	pageNumber--;
	if (pageNumber >= 0 && pageNumber < _rowDisplay.size() / _totalRows + 1) {
		_currentDisplayPage = pageNumber;
	}
}



PopUpMsg::PopUpMsg(const sf::Font& font) :
	_msg1TextBox(500.f, sf::Vector2f(710, 500), font, 30, L"", sf::Color(240, 240, 240, 255), false),
	_msg2TextBox(500.f, sf::Vector2f(710, 570), font, 30, L"", sf::Color(240, 240, 240, 255), false),
	_confirmButton(sf::Vector2f(50, 70), sf::Vector2f(1130, 640), sf::Color::Transparent, L"OK", font, 35, 38, sf::Color::Black, sf::Color(203, 140, 63, 255), [&]() {_confirmButtonOnClickHandler(); }),
	_closeButton(sf::Vector2f(60, 60), sf::Vector2f(1200, 390), "Icon/closeButton.png", [&]() {_closePopUp(); }),
	_isEditable(false),
	_isMsg2TextBoxUsed(false),
	_isPopUp(false),
	_confirmButtonHandler([]() {return true; })
{
	_mask.setSize(sf::Vector2f(1920, 1080));
	_mask.setPosition(sf::Vector2f(0, 0));
	_mask.setFillColor(sf::Color(200, 200, 200, 200));

	_popup.setSize(sf::Vector2f(600, 300));
	_popup.setPosition(sf::Vector2f(660, 390));
	_popup.setFillColor(sf::Color(255, 255, 255, 255));

	_title.setFont(font);
	_title.setString(L"");
	_title.setCharacterSize(45);
	_title.setFillColor(sf::Color::Black);
	_title.setPosition(sf::Vector2f(710, 420));
}

PopUpMsg::~PopUpMsg()
{

}

void PopUpMsg::OpenPopUp(std::wstring title, std::wstring msg1, std::wstring msg2, bool isEditable, std::function<bool()> confirmButtonHandler)
{
	_msg1TextBox.setText(L"");
	_msg1TextBox.setPlaceHolderText(L"");
	_msg2TextBox.setText(L"");
	_msg2TextBox.setPlaceHolderText(L"");

	if (isEditable) {
		_msg1TextBox.setPlaceHolderText(msg1);
		_msg2TextBox.setPlaceHolderText(msg2);
	}
	else {
		_msg1TextBox.setText(msg1);
		_msg2TextBox.setText(msg2);
	}

	if (isEditable) {
		_msg1TextBox.setBackgroundColor(sf::Color(240, 240, 240, 255));
		_msg2TextBox.setBackgroundColor(sf::Color(240, 240, 240, 255));
	}
	else {
		_msg1TextBox.setBackgroundColor(sf::Color::Transparent);
		_msg2TextBox.setBackgroundColor(sf::Color::Transparent);
	}

	if (msg2 == L"")
	{
		_msg1TextBox.setFontSize(36);
		_msg2TextBox.setBackgroundColor(sf::Color::Transparent);
		_isMsg2TextBoxUsed = false;
	}
	else {
		_msg1TextBox.setFontSize(30);
		_isMsg2TextBoxUsed = true;
	}

	_isEditable = isEditable;
	_confirmButtonHandler = confirmButtonHandler;
	_title.setString(title);
	_isPopUp = true;
}

bool PopUpMsg::getPopUpVisiblity()
{
	return _isPopUp;
}

std::wstring PopUpMsg::getMsg1()
{
	return _msg1TextBox.getText();
}

std::wstring PopUpMsg::getMsg2()
{
	return _msg2TextBox.getText();
}

void PopUpMsg::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	if (_isPopUp) {
		_closeButton.handleEvent(event, window);
		_confirmButton.handleEvent(event, window);
		if (_isEditable) {
			_msg1TextBox.handleEvent(event, window);
			if (_isMsg2TextBoxUsed) {
				_msg2TextBox.handleEvent(event, window);

				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Tab) {
						if (_msg1TextBox.getIsActivated()) {
							_msg1TextBox.setIsActivated(false);
							_msg2TextBox.setIsActivated(true);
						}
					}
				}
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Enter) {
					_confirmButtonHandler();
				}
			}
		}
	}
}

void PopUpMsg::update(sf::Time dt)
{
	if (_isPopUp && _isEditable) {
		_msg1TextBox.update(dt);
		if (_isMsg2TextBoxUsed) {
			_msg2TextBox.update(dt);
		}
	}
}

void PopUpMsg::render(sf::RenderWindow& window)
{
	if (_isPopUp) {
		window.draw(_mask);
		window.draw(_popup);
		window.draw(_title);

		_msg1TextBox.render(window);
		_msg2TextBox.render(window);
		_confirmButton.render(window);
		_closeButton.render(window);
	}
}

void PopUpMsg::_closePopUp()
{
	_isPopUp = false;
}

void PopUpMsg::_confirmButtonOnClickHandler()
{
	if (_confirmButtonHandler()) {
		_isPopUp = false;
	}
}



BookDetailPopUp::BookDetailPopUp(const sf::Font& font, bool isPopUp, bool isEditable, bool isNewMode, std::function<bool(Book*)> editFunction, std::function<void(Book*)> deleteFunction, std::function<void()> closeFunction) :
	_bookName(sf::Vector2f(600, 50), sf::Vector2f(600, 200), font, 40, L"书名", sf::Color::Transparent),
	_bookAuthorTitle(sf::Vector2f(100, 50), sf::Vector2f(600, 280), font, 20, sf::Color::Transparent, L"作者", L"", false),
	_bookAuthor(sf::Vector2f(300, 50), sf::Vector2f(700, 280), font, 20, L"作者", sf::Color::Transparent),
	_bookPublisherTitle(sf::Vector2f(100, 50), sf::Vector2f(600, 330), font, 20, sf::Color::Transparent, L"出版社", L"", false),
	_bookPublisher(sf::Vector2f(300, 50), sf::Vector2f(700, 330), font, 20, L"出版社", sf::Color::Transparent),
	_publishDateTitle(sf::Vector2f(100, 50), sf::Vector2f(600, 380), font, 20, sf::Color::Transparent, L"出版日期", L"", false),
	_publishDate(sf::Vector2f(300, 50), sf::Vector2f(700, 380), font, 20, L"出版日期", sf::Color::Transparent),
	_bookAvailableStockTitle(sf::Vector2f(100, 50), sf::Vector2f(600, 430), font, 20, sf::Color::Transparent, L"剩余量", L"", false),
	_bookAvailableStock(sf::Vector2f(300, 50), sf::Vector2f(700, 430), font, 20, L"剩余量", sf::Color::Transparent),
	_bookIdTitle(sf::Vector2f(100, 50), sf::Vector2f(1300, 230), font, 20, sf::Color::Transparent, L"书籍编号", L"", false),
	_bookId(sf::Vector2f(300, 50), sf::Vector2f(1400, 230), font, 20, L"书籍编号", sf::Color::Transparent),
	_bookCategoryTitle(sf::Vector2f(100, 50), sf::Vector2f(1100, 280), font, 20, sf::Color::Transparent, L"类别", L"", false),
	_bookCategory(sf::Vector2f(150, 50), sf::Vector2f(1200, 280), sf::Color::Transparent, font, 20, L"类别", isEditable),
	_totalPageTitle(sf::Vector2f(100, 50), sf::Vector2f(1100, 330), font, 20, sf::Color::Transparent, L"总页数", L"", false),
	_totalPage(sf::Vector2f(300, 50), sf::Vector2f(1200, 330), font, 20, L"总页数", sf::Color::Transparent),
	_bookPriceTitle(sf::Vector2f(100, 50), sf::Vector2f(1100, 380), font, 20, sf::Color::Transparent, L"价格", L"", false),
	_bookPrice(sf::Vector2f(300, 50), sf::Vector2f(1200, 380), font, 20, L"价格", sf::Color::Transparent),
	_bookTotalStockTitle(sf::Vector2f(100, 50), sf::Vector2f(1100, 430), font, 20, sf::Color::Transparent, L"总量", L"", false),
	_bookTotalStock(sf::Vector2f(300, 50), sf::Vector2f(1200, 430), font, 20, L"总量", sf::Color::Transparent),
	_bookDescriptionTitle(sf::Vector2f(100, 50), sf::Vector2f(300, 570), font, 20, sf::Color::Transparent, L"简述", L"", false),
	_bookDescription(sf::Vector2f(1300, 270), sf::Vector2f(300, 620), font, 20, L"简述", sf::Color::Transparent),
	_bookImage(sf::Vector2f(270, 350), sf::Vector2f(300, 200), "Icon/blankBook.jpg", [&]() {_imageButtonOnClickHandler(); }),
	_closeButton(sf::Vector2f(100, 100), sf::Vector2f(1600, 120), "Icon/closeButton.png", [&]() {_closePopUp(); }),
	_editButton(sf::Vector2f(50, 50), sf::Vector2f(1440, 150), "Icon/editIcon(White).png", [&]() {_editButtonOnClickHandler(); }),
	_deleteButton(sf::Vector2f(50, 50), sf::Vector2f(1520, 150), "Icon/deleteIcon.png", [&]() {_deleteButtonOnClickHandler(); }),
	_popUpMsg(font),
	_editFunction(editFunction),
	_deleteFunction(deleteFunction),
	_closeFunction(closeFunction),
	_isPopUp(isPopUp),
	_isEditable(isEditable),
	_isNewMode(isNewMode),
	_isEditing(false),
	_book(nullptr)
{
	_mask.setSize(sf::Vector2f(1920, 1080));
	_mask.setPosition(sf::Vector2f(0, 0));
	_mask.setFillColor(sf::Color(200, 200, 200, 200));

	_popup.setSize(sf::Vector2f(1500,800));
	_popup.setPosition(sf::Vector2f(210, 120));
	_popup.setFillColor(sf::Color(255, 255, 255, 255));

	_bookCategory.setOptions({ L"小说类", L"传记与回忆录", L"历史与文化", L"科学与自然", L"商业与经济", L"健康与生活方式", L"艺术与设计", L"语言与文学", L"参考手册", L"儿童读物", L"其他" });
}

BookDetailPopUp::~BookDetailPopUp()
{

}

void BookDetailPopUp::setBook(Book* book)
{
	_book = book;
	_bookId.setText(std::to_wstring(book->getBookId()));
	_bookName.setText(book->getBookName());
	_bookAuthor.setText(book->getAuthor());
	_bookPublisher.setText(book->getPublisher());
	_bookCategory.setSelectOption(book->getCategoryName());
	_totalPage.setText(std::to_wstring(book->getPages()));
	_publishDate.setText(book->getPublishDate().getWDate());
	_bookPrice.setText(std::to_wstring(book->getPrice()));
	_bookAvailableStock.setText(std::to_wstring(book->getRemainBook()));
	_bookTotalStock.setText(std::to_wstring(book->getTotalBook()));
	_bookDescription.setText(book->getDescription());
	_bookImage.setIcon(book->getImgUrl());
}

void BookDetailPopUp::setPopUpVisiblity(bool isVisible, bool isNewMode)
{
	_isPopUp = isVisible;
	_isNewMode = isNewMode;

	if (_isNewMode) {
		_editButtonOnClickHandler();
	}
}

void BookDetailPopUp::setEditable(bool isEditable)
{
	_isEditable = isEditable;
}

bool BookDetailPopUp::getPopUpVisiblity()
{
	return _isPopUp;
}

void BookDetailPopUp::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	if (_popUpMsg.getPopUpVisiblity())
	{
		_popUpMsg.handleEvent(event, window);
		return;
	}

	if (_isPopUp) {
		_closeButton.handleEvent(event, window);

		if (_isEditable) {
			_editButton.handleEvent(event, window);
			if (!_isNewMode) {
				_deleteButton.handleEvent(event, window);
			}

			if (_isEditing) {
				if (_isNewMode) {
					_bookId.handleEvent(event, window);
				}
				_bookName.handleEvent(event, window);
				_bookAuthor.handleEvent(event, window);
				_bookPublisher.handleEvent(event, window);
				_bookCategory.handleEvent(event, window);
				_totalPage.handleEvent(event, window);
				_publishDate.handleEvent(event, window);
				_bookPrice.handleEvent(event, window);
				_bookAvailableStock.handleEvent(event, window);
				_bookTotalStock.handleEvent(event, window);
				_bookDescription.handleEvent(event, window);
				_bookImage.handleEvent(event, window);
			}
		}
	}
}

void BookDetailPopUp::update(sf::Time dt)
{
	if (_popUpMsg.getPopUpVisiblity()) {
		_popUpMsg.update(dt);
		return;
	}

	if (_isPopUp && _isEditable && _isEditing) {
		_bookId.update(dt);
		_bookName.update(dt);
		_bookAuthor.update(dt);
		_bookPublisher.update(dt);
		_totalPage.update(dt);
		_publishDate.update(dt);
		_bookPrice.update(dt);
		_bookAvailableStock.update(dt);
		_bookTotalStock.update(dt);
		_bookDescription.update(dt);
	}
}

void BookDetailPopUp::render(sf::RenderWindow& window)
{
	if (_isPopUp) {
		window.draw(_mask);
		window.draw(_popup);
		_bookId.render(window);
		_bookName.render(window);
		_bookAuthor.render(window);
		_bookPublisher.render(window);
		_totalPage.render(window);
		_publishDate.render(window);
		_bookPrice.render(window);
		_bookAvailableStock.render(window);
		_bookTotalStock.render(window);
		_bookDescription.render(window);
		_bookImage.render(window);
		_bookCategory.render(window);

		_bookIdTitle.render(window);
		_bookAuthorTitle.render(window);
		_bookPublisherTitle.render(window);
		_totalPageTitle.render(window);
		_publishDateTitle.render(window);
		_bookPriceTitle.render(window);
		_bookAvailableStockTitle.render(window);
		_bookTotalStockTitle.render(window);
		_bookDescriptionTitle.render(window);
		_bookCategoryTitle.render(window);

		_closeButton.render(window);
		if (_isEditable) {
			_editButton.render(window);
			_deleteButton.render(window);
		}
	}
	_popUpMsg.render(window);
}

void BookDetailPopUp::_closePopUp()
{
	_isPopUp = false;
	_closeFunction();
}

void BookDetailPopUp::_editButtonOnClickHandler()
{
	_isEditing = true;
	_bookCategory.setBackgroudColor(sf::Color(230, 230, 230, 255));
	_editButton.setIcon("Icon/doneIcon.png");
	_editButton.setOnClickHandler([&]() {_doneButtonOnClickHandler(); });

	if (_isNewMode) {
		_bookId.setBackgroundColor(sf::Color(240, 240, 240, 255));
	}
	_bookName.setBackgroundColor(sf::Color(240, 240, 240, 255));
	_bookAuthor.setBackgroundColor(sf::Color(240, 240, 240, 255));
	_bookPublisher.setBackgroundColor(sf::Color(240, 240, 240, 255));
	_totalPage.setBackgroundColor(sf::Color(240, 240, 240, 255));
	_publishDate.setBackgroundColor(sf::Color(240, 240, 240, 255));
	_bookPrice.setBackgroundColor(sf::Color(240, 240, 240, 255));
	_bookAvailableStock.setBackgroundColor(sf::Color(240, 240, 240, 255));
	_bookTotalStock.setBackgroundColor(sf::Color(240, 240, 240, 255));
	_bookDescription.setBackgroundColor(sf::Color(240, 240, 240, 255));
}

void BookDetailPopUp::_doneButtonOnClickHandler()
{
	if (!_book->setBookId(_bookId.getText())) {
		_popUpMsg.OpenPopUp(L"提示", L"书籍编号格式错误", L"", false);
		return;
	}

	if (!_book->setBookName(_bookName.getText())) {
		_popUpMsg.OpenPopUp(L"提示", L"书名格式错误", L"", false);
		return;
	}

	if (!_book->setAuthor(_bookAuthor.getText())) {
		_popUpMsg.OpenPopUp(L"提示", L"作者格式错误", L"", false);
		return;
	}

	if (!_book->setPublisher(_bookPublisher.getText())) {
		_popUpMsg.OpenPopUp(L"提示", L"出版社格式错误", L"", false);
		return;
	}

	if (!_book->setCategory(_bookCategory.getSelectedOption())) {
		_popUpMsg.OpenPopUp(L"提示", L"类别格式错误", L"", false);
		return;
	}

	if (!_book->setPages(_totalPage.getText())) {
		_popUpMsg.OpenPopUp(L"提示", L"总页数格式错误", L"", false);
		return;
	}

	if (!_book->setPublishDate(_publishDate.getText())) {
		_popUpMsg.OpenPopUp(L"提示", L"出版日期格式错误", L"", false);
		return;
	}

	if (!_book->setPrice(_bookPrice.getText())) {
		_popUpMsg.OpenPopUp(L"提示", L"价格格式错误", L"", false);
		return;
	}

	if (!_book->setTotalBook(_bookTotalStock.getText())) {
		_popUpMsg.OpenPopUp(L"提示", L"总量格式错误", L"", false);
		return;
	}
	
	if (!_book->setRemainBook(_bookAvailableStock.getText())) {
		_popUpMsg.OpenPopUp(L"提示", L"剩余量格式错误", L"", false);
		return;
	}

	if (!_book->setDescription(_bookDescription.getText())) {
		_popUpMsg.OpenPopUp(L"提示", L"简述格式错误", L"", false);
		return;
	}

	if (_editFunction(_book)) {
		_isEditing = false;
		_bookCategory.setBackgroudColor(sf::Color::Transparent);
		_editButton.setIcon("Icon/editIcon(White).png");
		_editButton.setOnClickHandler([&]() {_editButtonOnClickHandler(); });

		if (_isNewMode) {
			_bookId.setBackgroundColor(sf::Color::Transparent);
		}
		_bookName.setBackgroundColor(sf::Color::Transparent);
		_bookAuthor.setBackgroundColor(sf::Color::Transparent);
		_bookPublisher.setBackgroundColor(sf::Color::Transparent);
		_totalPage.setBackgroundColor(sf::Color::Transparent);
		_publishDate.setBackgroundColor(sf::Color::Transparent);
		_bookPrice.setBackgroundColor(sf::Color::Transparent);
		_bookAvailableStock.setBackgroundColor(sf::Color::Transparent);
		_bookTotalStock.setBackgroundColor(sf::Color::Transparent);
		_bookDescription.setBackgroundColor(sf::Color::Transparent);
	}
}

void BookDetailPopUp::_deleteButtonOnClickHandler()
{
	_deleteFunction(_book);
	_isPopUp = false;
}

void BookDetailPopUp::_imageButtonOnClickHandler()
{
	_popUpMsg.OpenPopUp(L"设置书的封面", L"图片的路径", L"", true, [&]() {return _setImageHandler(); });
}

bool BookDetailPopUp::_setImageHandler()
{
	sf::Image img;
	if (!img.loadFromFile(wstring_to_string(_popUpMsg.getMsg1()))) {
		_popUpMsg.OpenPopUp(L"提示", L"图片路径错误", L"可输入由本项目的目录的相对路径", false);
		return false;
	}

	if (_book->setImgUrl(_popUpMsg.getMsg1())) {
		_bookImage.setIcon(wstring_to_string(_popUpMsg.getMsg1()));
		return true;
	}
	else {
		_popUpMsg.OpenPopUp(L"提示", L"图片格式错误", L"", false);
		return false;
	}
}