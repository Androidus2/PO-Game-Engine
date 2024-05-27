#include "InputField.h"
#include "Game.h"
#include "GameTime.h"

using namespace std;
using namespace sf;


InputField::InputField(const Font& font, const Vector2f& position, const Vector2f& size, const string& defaultText) { //constructor
    field.setSize(size);
    field.setFillColor(Color(100, 100, 100));
    field.setOutlineColor(Color::Black);
    field.setOutlineThickness(1);
    field.setPosition(position);

    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(Color::White);
    text.setString(defaultText);
    text.setPosition(position.x + 10, position.y);

    isSelected = false;
    cursorIndex = 0;
    onlyNumbers = false;
    str = defaultText;
    onChange = NULL;
    updateValue = NULL;
    finishEdit = NULL;
}
void InputField::draw(RenderWindow& window) const { //draw function
    window.draw(field);
    window.draw(text);
}
void InputField::update() { //update function
    if (isSelected) { //If the input field is selected, show the cursor
        float t = fmod(Singleton<GameTime>::getInstance().getData().getTime(), 1.0f);
        if (t < 0.7f) {
            string tmp = str;
            tmp.insert(cursorIndex, "|");
            text.setString(tmp);
        }
        else {
            text.setString(str);
        }
    }
    else {
        if (updateValue) str = updateValue();
        text.setString(str);
    }
}
void InputField::handleEvent(Event& event) { //handle event function
    if (isSelected) {
        if (event.type == Event::TextEntered) {
            if (onlyNumbers) { //If only numbers are allowed, only allow numbers, a single decimal point and a single minus sign
                if (event.text.unicode == 8) {
                    if (str.size() > 0 && cursorIndex > 0) {
                        str = str.substr(0, cursorIndex - 1) + str.substr(cursorIndex);
                        cursorIndex--;
                    }
                }
                else if (event.text.unicode == 13) {
                    deselect();
                }
                else if (event.text.unicode == 46) {
                    if (str.find('.') == string::npos) {
                        if (str.size() > 0 && cursorIndex == 0 && str[0] == '-')
                            cursorIndex++;
                        str = str.substr(0, cursorIndex) + '.' + str.substr(cursorIndex);
                        cursorIndex++;
                    }
                }
                else if (event.text.unicode == 45) {
                    if (str[0] != '-') {
                        str = '-' + str;
                        cursorIndex++;
                    }
                    else {
                        str = str.substr(1);
                        cursorIndex--;
                    }
                }
                else if (event.text.unicode >= 48 && event.text.unicode <= 57) {
                    if (str.size() > 0 && cursorIndex == 0 && str[0] == '-')
                        cursorIndex++;
                    str = str.substr(0, cursorIndex) + event.text.unicode + str.substr(cursorIndex);
                    cursorIndex++;
                }
            }
            else { //If all characters are allowed
                if (event.text.unicode == 8) {
                    if (str.size() > 0 && cursorIndex > 0) {
                        str = str.substr(0, cursorIndex - 1) + str.substr(cursorIndex);
                        cursorIndex--;
                    }
                }
                else if (event.text.unicode == 13) {
                    deselect();
                }
                else {
                    str = str.substr(0, cursorIndex) + event.text.unicode + str.substr(cursorIndex);
                    cursorIndex++;
                }
            }
            if (onChange) onChange(processText()); //Call the onChange function
        }
        if (event.type == Event::KeyPressed) { //Handle arrow keys and copy-paste
            if (event.key.code == Keyboard::Left) {
                cursorIndex--;
            }
            if (event.key.code == Keyboard::Right) {
                cursorIndex++;
            }
            if (cursorIndex < 0)
                cursorIndex = 0;
            if (cursorIndex > str.size())
                cursorIndex = str.size();

            if (event.key.control && event.key.code == Keyboard::V) {
                string tmp = Clipboard::getString();
                cout << "The inputed string has " << tmp.size() << " characters\n";
                str = "";
                if (onlyNumbers) {
                    for (int i = 0; i < tmp.size(); i++) {
                        if (tmp[i] == 46 && str.find('.') == string::npos) {
                            str += tmp[i];
                        }
                        else if (tmp[i] == 45 && str.find('-') == string::npos && i == 0) {
                            str += tmp[i];
                        }
                        else if (tmp[i] >= 48 && tmp[i] <= 57) {
                            str += tmp[i];
                        }
                    }
                }
                else {
                    str = tmp;
                }
                str = processText();
                cursorIndex = str.size();
                if (onChange) onChange(processText()); //Call the onChange function
            }
            if (event.key.control && event.key.code == Keyboard::C) {
                Clipboard::setString(str);
            }
        }
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) { //Handle mouse clicks
            int x = Mouse::getPosition(*Game::getWindow()).x - field.getPosition().x;
            cout << x << " " << text.findCharacterPos(0).x << endl;
            cursorIndex = x * 2 / text.getCharacterSize();
            if (cursorIndex > str.size())
                cursorIndex = str.size();
            if (cursorIndex < 0)
                cursorIndex = 0;
        }
    }
}
void InputField::select() { //select function
    isSelected = true;
    cursorIndex = str.size();

    //Very poor implementation but I don't want to spend time on this
    if(!finishEdit)
        Game::addControlZScene();
}
void InputField::deselect() { //deselect function

    str = processText();

    text.setString(str);
    if (finishEdit && isSelected) finishEdit(str); //Call the finishEdit function
    isSelected = false;
}
bool InputField::getSelected() const { //get if the input field is selected
    return isSelected;
}
string InputField::getText() const { //get the text of the input field
    return str;
}
void InputField::setText(const string& text) { //set the text of the input field
    str = text;
    str = processText();
    cursorIndex = str.size();
    this->text.setString(str);
}
void InputField::clear() { //clear the input field
    str = "";
    cursorIndex = 0;
    if (onlyNumbers) {
        str = "0";
        cursorIndex = 1;
    }
    text.setString(str);
}
void InputField::setPosition(const Vector2f& position) { //set the position of the input field
    field.setPosition(position);
    text.setPosition(position.x + 10, position.y);
}
Vector2f InputField::getPosition() const { //get the position of the input field
    return field.getPosition();
}
void InputField::setOnlyNumbers(bool onlyNumbers) { //set if only numbers are allowed
    this->onlyNumbers = onlyNumbers;
}
bool InputField::getOnlyNumbers() const { //get if only numbers are allowed
    return onlyNumbers;
}
void InputField::checkMouseClick() { //check if the input field is clicked, and select it if it is
    Vector2f mousePosition = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
    if (field.getGlobalBounds().contains(mousePosition) && !Game::getBlockClick()) {
        Game::setBlockClick(true);
        if (!isSelected)
            select();
    }
    else {
        deselect();
    }
}
void InputField::changeBackground() { //change the background of the input field based on if it is selected
    if (isSelected) {
        field.setFillColor(Color::Black);
    }
    else {
        field.setFillColor(Color(150, 150, 150));
    }
}
void InputField::setOnChange(function<void(string)> onChange) { //set the onChange function
    this->onChange = onChange;
}
void InputField::setUpdateValue(function<string()> updateValue) { //set the updateValue function
    this->updateValue = updateValue;
}
void InputField::setFinishEdit(function<void(string)> finishEdit) { //set the finishEdit function
	this->finishEdit = finishEdit;
}
string InputField::processText() { //process the text of the input field
    string ret = str;
    if (onlyNumbers) { //If only numbers are allowed, make sure the text is a valid number (no multiple decimal points, no multiple minus signs, etc.)
        if (ret.size() > 0 && ret[0] == '-')
            ret = ret.substr(1);
        while (ret.size() > 1 && ret[0] == '0' && ret[1] != '.')
            ret = ret.substr(1);
        if (!ret.empty() && ret[ret.size() - 1] == '.')
            ret.pop_back();
        if (!ret.empty() && ret[0] == '.')
            ret = "0" + ret;
        if (ret.empty())
            ret = "0";
        while (ret.size() > 2 && ret[ret.size() - 1] == '0' && ret.find('.') != string::npos)
            ret.pop_back();
        if (!ret.empty() && ret[ret.size() - 1] == '.')
            ret.pop_back();
        if (ret != "0" && str.size() > 0 && str[0] == '-')
            ret = "-" + ret;
    }
    return ret;
}
