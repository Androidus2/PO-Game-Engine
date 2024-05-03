#pragma once
#include <iostream>
#include "SFML\System.hpp"

class GameObject;

class Utility { //for vector calculations
public:
    static float magnitude(const sf::Vector2f& source);
    static float dotProduct(const sf::Vector2f& source1, const sf::Vector2f& source2);
    static sf::Vector2f normalize(const sf::Vector2f& source);
    static sf::Vector2f calculateNormal(const sf::Vector2f& source);
    static sf::Vector2f direction(const sf::Vector2f& source, const sf::Vector2f& target);
    static sf::Vector2f rotateVector(const sf::Vector2f& source, float angle);
};

std::string floatToString(float f, int precision = 2);
std::string keyToString(sf::Keyboard::Key key);
sf::Keyboard::Key stringToKey(std::string s);
std::string ColorToString(sf::Color color);
sf::Color stringToColor(std::string inp);
bool isColorFormat(std::string s);

void addTextToHierarchy(const std::string& obName);
void removeTextFromHierarchy(int index);
int getSelectedSceneId();
GameObject* makeObjFromString(const std::string& obj);

void makeObj(GameObject& ob, const sf::Vector2f& position, float sideLen);
void changeSelectedIsMovable();

sf::Text* updateHierarchy(sf::Text* objectTexts, const sf::RectangleShape& hierarchy, const sf::Font& font, const sf::Text& hierarchyTitle);

void createObj();
void deleteObj();

void addTextToHierarchy(const std::string& text);
void removeTextFromHierarchy(int index);