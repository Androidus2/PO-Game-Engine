#include "Button.h"

using namespace std;
using namespace sf;


Button::Button() { //default constructor
    isPressed = false;
    isHovered = false;
    isActive = true;
    isToggle = false;
    isToggled = false;
    defaultColor = Color(100, 100, 100);
    pressedColor = Color(50, 50, 50);
    hoverColor = Color(150, 150, 150);
    textColor = Color::White;
    onClick = nullptr;
}
Button::Button(const Font& font, const Vector2f& position, const Vector2f& size, const string& buttonText) { //constructor
    button.setSize(size);
    button.setFillColor(Color(100, 100, 100));
    button.setOutlineColor(Color::Black);
    button.setOutlineThickness(1);
    button.setPosition(position);

    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(Color::White);
    text.setString(buttonText);
    text.setPosition(position.x + size.x / 2 - text.getLocalBounds().getSize().x / 2, position.y + size.y / 2 - text.getLocalBounds().getSize().y / 2);

    isPressed = false;
    isHovered = false;
    isActive = true;
    isToggle = false;
    isToggled = false;
    defaultColor = Color(100, 100, 100);
    pressedColor = Color(50, 50, 50);
    hoverColor = Color(150, 150, 150);
    textColor = Color::White;
    onClick = nullptr;
}
Button::Button(const Button& button) { //copy constructor
    this->button = button.button;
    this->text = button.text;
    this->isPressed = button.isPressed;
    this->isHovered = button.isHovered;
    this->isActive = button.isActive;
    this->isToggle = button.isToggle;
    this->isToggled = button.isToggled;
    this->defaultColor = button.defaultColor;
    this->pressedColor = button.pressedColor;
    this->hoverColor = button.hoverColor;
    this->textColor = button.textColor;
    this->onClick = button.onClick;
}
Button& Button::operator=(const Button& button) { //assignment operator
    if (this == &button)
        return *this;
    this->button = button.button;
    this->text = button.text;
    this->isPressed = button.isPressed;
    this->isHovered = button.isHovered;
    this->isActive = button.isActive;
    this->isToggle = button.isToggle;
    this->isToggled = button.isToggled;
    this->defaultColor = button.defaultColor;
    this->pressedColor = button.pressedColor;
    this->hoverColor = button.hoverColor;
    this->textColor = button.textColor;
    this->onClick = button.onClick;
    return *this;
}
void Button::draw(RenderWindow& window) const { //draw function
    window.draw(button);
    window.draw(text);
}
void Button::update() { //update function(Changes the color of the button based on if it is pressed, hovered, etc.)
    if (isActive) {
        if (isPressed || isToggled)
            button.setFillColor(pressedColor);
        else if (isHovered)
            button.setFillColor(hoverColor);
        else
            button.setFillColor(defaultColor);
    }
    else
        button.setFillColor(Color(50, 50, 50));
}
void Button::handleEvent(Event& event) { //handle event function
    if (isActive) { //If the button is active, handle events
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) { //If the left mouse button is pressed, check if the mouse is over the button and press it or toggle it
            Vector2f mousePosition = Vector2f(event.mouseButton.x, event.mouseButton.y);
            if (button.getGlobalBounds().contains(mousePosition) && !isPressed && !isToggle) {
                press();
            }
        }
        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) { //If the left mouse button is released, check if the mouse is over the button and release it or toggle it
            Vector2f mousePosition = Vector2f(event.mouseButton.x, event.mouseButton.y);
            if (isToggle && button.getGlobalBounds().contains(mousePosition))
                toggle();
            else if (isPressed)
                release();
        }
        if (event.type == Event::MouseMoved) { //If the mouse is moved, check if the mouse is over the button and hover it or unhover it
            Vector2f mousePosition = Vector2f(event.mouseMove.x, event.mouseMove.y);
            if (button.getGlobalBounds().contains(mousePosition)) {
                hover();
            }
            else {
                unhover();
            }
        }
    }
}
void Button::press() { //press function
    isPressed = true;
    if (onClick)
        onClick();
}
void Button::release() { //release function
    isPressed = false;
}
void Button::hover() { //hover function
    isHovered = true;
}
void Button::unhover() { //unhover function
    isHovered = false;
}
void Button::toggle() { //toggle function
    cout << "Toggled\n" << isToggled << endl;
    if (isToggled)
        button.setFillColor(defaultColor);
    else
        button.setFillColor(pressedColor);
    if (onClick)
        onClick();
    isToggled = !isToggled;
}
void Button::setToggle(bool isToggle) { //set if the button is toggle
    this->isToggle = isToggle;
}
bool Button::getToggle() const { //get if the button is toggle
    return isToggle;
}
bool Button::getToggled() const { //get if the button is toggled
    return isToggled;
}
void Button::setActive(bool isActive) { //set if the button is active
    this->isActive = isActive;
}
bool Button::getActive() const { //get if the button is active
    return isActive;
}
void Button::setText(const string& text) { //set the text of the button
    this->text.setString(text);
}
string Button::getText() const { //get the text of the button
    return text.getString();
}
void Button::setPosition(const Vector2f& position) { //set the position of the button
    button.setPosition(position);
    text.setPosition(position.x + button.getSize().x / 2 - text.getLocalBounds().getSize().x / 2, position.y + button.getSize().y / 2 - text.getCharacterSize());
}
Vector2f Button::getPosition() const { //get the position of the button
    return button.getPosition();
}
void Button::setDefaultColor(const Color& color) { //set the default color of the button
    defaultColor = color;
}
Color Button::getDefaultColor() const { //get the default color of the button
    return defaultColor;
}
void Button::setPressedColor(const Color& color) { //set the pressed color of the button
    pressedColor = color;
}
Color Button::getPressedColor() const { //get the pressed color of the button
    return pressedColor;
}
void Button::setHoverColor(const Color& color) { //set the hover color of the button
    hoverColor = color;
}
Color Button::getHoverColor() const { //get the hover color of the button
    return hoverColor;
}
void Button::setTextColor(const Color& color) { //set the text color of the button
    textColor = color;
    text.setFillColor(textColor);
}
Color Button::getTextColor() const { //get the text color of the button
    return textColor;
}
void Button::setOnClick(function<void()> onClick) { //set the onClick function
    this->onClick = onClick;
}
