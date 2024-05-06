#pragma once
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "Scene.h"
#include <functional>


class InputField { //Input field class
private:
    sf::RectangleShape field;
    sf::Text text;
    bool isSelected;
    int cursorIndex;
    bool onlyNumbers;
    std::string str;
    std::function<void(std::string)> onChange;
    std::function<std::string()> updateValue;
    std::function<void(std::string)> finishEdit;

public:
    InputField(const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size, const std::string& defaultText = "");
    void draw(sf::RenderWindow& window) const;
    void update();
    void handleEvent(sf::Event& event);
    void select();
    void deselect();
    bool getSelected() const;
    std::string getText() const;
    void setText(const std::string& text);
    void clear();
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    void setOnlyNumbers(bool onlyNumbers);
    bool getOnlyNumbers() const;
    void checkMouseClick();
    void changeBackground();
    void setOnChange(std::function<void(std::string)> onChange);
    void setUpdateValue(std::function<std::string()> updateValue);
    void setFinishEdit(std::function<void(std::string)> finishEdit);
    std::string processText();
};