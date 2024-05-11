#pragma once
#include <iostream>
#include <functional>
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "DebugMacro.h"



class Button { //Button class
private:
    sf::RectangleShape button;
    sf::Text text;
    bool isPressed;
    bool isHovered;
    bool isActive;
    bool isToggle;
    bool isToggled;
    sf::Color defaultColor;
    sf::Color pressedColor;
    sf::Color hoverColor;
    sf::Color textColor;
    std::function<void()> onClick; //Function pointer to a function that takes no arguments and returns void (used to call a function when the button is clicked)
public:
    Button();
    Button(const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size, const std::string& buttonText = "");
    Button(const Button& button);
    Button& operator=(const Button& button);
    void draw(sf::RenderWindow& window) const;
    void update();
    void handleEvent(sf::Event& event);
    void press();
    void release();
    void hover();
    void unhover();
    void toggle();
    void setToggle(bool isToggle);
    bool getToggle() const;
    bool getToggled() const;
    void setActive(bool isActive);
    bool getActive() const;
    void setText(const std::string& text);
    std::string getText() const;
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    void setSize(const sf::Vector2f& size);
    sf::Vector2f getSize() const;
    void setDefaultColor(const sf::Color& color);
    sf::Color getDefaultColor() const;
    void setPressedColor(const sf::Color& color);
    sf::Color getPressedColor() const;
    void setHoverColor(const sf::Color& color);
    sf::Color getHoverColor() const;
    void setTextColor(const sf::Color& color);
    sf::Color getTextColor() const;
    void setOnClick(std::function<void()>);
};