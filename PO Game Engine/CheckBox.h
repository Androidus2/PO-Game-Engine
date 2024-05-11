#pragma once
#include <iostream>
#include <functional>
#include "SFML\Graphics.hpp"
#include "DebugMacro.h"

class CheckBox {
private:
	sf::RectangleShape box;
	bool isChecked;
	std::function<void(bool isChecked)> onChange;
	std::function<bool()> updateValue;
public:
	CheckBox(const sf::Vector2f& position, const sf::Vector2f& size);
	void draw(sf::RenderWindow& window) const;
	void handleEvent(sf::Event& event);
	void setChecked(bool isChecked);
	bool getChecked() const;
	bool getValue() const;
	void setPosition(const sf::Vector2f& position);
	sf::Vector2f getPosition() const;
	void setSize(const sf::Vector2f& size);
	sf::Vector2f getSize() const;
	void setFillColor(const sf::Color& color);
	void setOnChange(std::function<void(bool isChecked)> onChange);
	void setUpdateValue(std::function<bool()> updateValue);
};