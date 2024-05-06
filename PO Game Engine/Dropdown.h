#pragma once
#include <iostream>
#include <vector>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "Button.h"

class Dropdown { //Dropdown class
private:
	sf::RectangleShape background;
	std::vector<Button> buttons;
	std::function<void(int)> callback;
	bool isActive;
public:
	Dropdown(const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size);
	void draw(sf::RenderWindow& window) const;
	void update();
	void handleEvent(sf::Event& event);
	void addElement(const std::string& name);
	void removeElement(int index);
	void setCallback(const std::function<void(int)>& callback);
	std::string getElementName(int index) const;
	void setPosition(const sf::Vector2f& position);
	void selectedElement(int index);
	void setActive(bool isActive);
	bool getActive() const;
};