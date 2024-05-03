#pragma once
#include <iostream>
#include <functional>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Button.h"


class ImageField {
private:
	sf::RectangleShape imageField;
	sf::Text imageName;
	Button deleteButton;
	std::string imagePath;
	bool isSelected;
	std::function<void(Scene*, std::string, int)> onChange; // std::function to replace function pointer
	std::function<std::string(Scene*, int)> updateValue; // std::function to replace function pointer
	int callIndex;
public:
	ImageField() = default;
	ImageField(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& imagePath, const sf::Font& font, void (Scene::* onChange) (std::string str, int index), std::string(Scene::* updateValue)(int index) const, int callIndex);
	ImageField(const ImageField& imageField);
	ImageField& operator=(const ImageField& imageField);
	void draw(sf::RenderWindow& window) const;
	void update();
	void handleEvent(sf::Event& event);
	void mouseOver();
	void setSelected(bool isSelected);
	bool getSelected() const;
	void setImagePath(const std::string& imagePath);
	std::string getImagePath() const;
	void setPosition(const sf::Vector2f& position);
	sf::Vector2f getPosition() const;
	void setSize(const sf::Vector2f& size);
	sf::Vector2f getSize() const;
	void setOnChange(std::function<void(Scene*, std::string, int)> onChange);
	void setUpdateValue(std::function<std::string(Scene*, int)> updateValue);
	void setCallIndex(int callIndex);
	int getCallIndex() const;
};