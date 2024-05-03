#pragma once
#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Scene.h"


class EditableColor {
private:
	sf::RectangleShape colorBox;
	std::function<void(Scene*, std::string, int)> onChange; // std::function to replace function pointer
	std::function<std::string(Scene*, int)> updateValue; // std::function to replace function pointer
	int callIndex;
	bool isSelected;
public:
	EditableColor(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, std::function<void(Scene*, std::string, int)> onChange, std::function<std::string(Scene*, int)> updateValue, int callIndex);
	void draw(sf::RenderWindow& window) const;
	void update();
	void handleEvent(sf::Event& event);
	void mouseOver();
	void setSelected(bool isSelected);
	bool getSelected() const;
	void setColor(const sf::Color& color);
	sf::Color getColor() const;
	void setPosition(const sf::Vector2f& position);
	sf::Vector2f getPosition() const;
	void setSize(const sf::Vector2f& size);
	sf::Vector2f getSize() const;
	void setOnChange(std::function<void(Scene*, std::string, int)> onChange);
	void setUpdateValue(std::function<std::string(Scene*, int)> updateValue);
	void setCallIndex(int callIndex);
	int getCallIndex() const;
};