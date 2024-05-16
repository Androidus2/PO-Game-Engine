#include "KeyBindField.h"
#include "Game.h"
#include "Utility.h"

using namespace std;
using namespace sf;

KeyBindField::KeyBindField(const Font& font, const Vector2f& position, const Vector2f& size, const string& defaultText) {
	field.setSize(size);
	field.setPosition(position);
	field.setFillColor(Color::Black);
	field.setOutlineColor(Color::Black);
	field.setOutlineThickness(1);
	text.setFont(font);
	text.setCharacterSize(15);
	text.setFillColor(Color::White);
	text.setString(defaultText);
	text.setPosition(position.x + 5, position.y);
	isSelected = false;
}

void KeyBindField::draw(RenderWindow& window) const {
	window.draw(field);
	window.draw(text);
}
void KeyBindField::update() {
	if (isSelected) {
		field.setFillColor(Color::Black);
	}
	else {
		field.setFillColor(Color(150, 150, 150));
		if (updateValue) {
			key = updateValue();
			text.setString(key);
		}
	}
}
void KeyBindField::handleEvent(Event& event) {
	if (isSelected) {
		if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::Key::BackSpace) {
				key = "";
				text.setString(key);
				if (onChange) {
					onChange(key);
				}
				if (finishEdit) {
					finishEdit(key);
				}
				isSelected = false;
			}
			else {
				key = keyToString(event.key.code);
				text.setString(key);
				if (onChange) {
					onChange(key);
				}
				if (finishEdit) {
					finishEdit(key);
				}
				isSelected = false;
			}
		}

		if (event.type == Event::MouseButtonPressed) {
			if (!field.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
				if (finishEdit) {
					finishEdit(key);
				}
				isSelected = false;
			}
		}
	}
	else {
		if (event.type == Event::MouseButtonPressed) {
			if (field.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
				select();
			}
		}
	}
}

void KeyBindField::select() {
	isSelected = true;
	Game::addControlZScene();
}
void KeyBindField::deselect() {
	isSelected = false;
}
bool KeyBindField::getSelected() const {
	return isSelected;
}

string KeyBindField::getText() const {
	return text.getString();
}
void KeyBindField::setText(const string& text) {
	key = text;
	this->text.setString(text);
}
void KeyBindField::clear() {
	text.setString("");
	key = "";
}

void KeyBindField::setPosition(const Vector2f& position) {
	field.setPosition(position);
	text.setPosition(position.x + 5, position.y);
}
Vector2f KeyBindField::getPosition() const {
	return field.getPosition();
}

void KeyBindField::setOnChange(function<void(string)> onChange) {
	this->onChange = onChange;
}
void KeyBindField::setUpdateValue(function<string()> updateValue) {
	this->updateValue = updateValue;
}
void KeyBindField::setFinishEdit(function<void(string)> finishEdit) {
	this->finishEdit = finishEdit;
}