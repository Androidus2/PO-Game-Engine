#pragma once
#include <iostream>
#include "BehaviourScript.h"
#include "SFML\Graphics.hpp"

class TestScript : public BehaviourScript { //Test script for GameObjects (changes color when clicked)
private:
    sf::Color defaultColor;
    sf::Color pressedColor;
public:
    TestScript();
    TestScript(sf::Color a, sf::Color b);
    void setColors(sf::Color a, sf::Color b);
    TestScript* clone() const;
    void start(GameObject& gameObject);
    void update(GameObject& gameObject);
    void collision(GameObject& gameObject, GameObject& collisionObject);
    void trigger(GameObject& gameObject, GameObject& triggerObject);
    void destroy(GameObject& gameObject);

    std::string getAttribute(int index) const;
    void setAttribute(int index, std::string value);

    int getAttributeType(int index) const;
    std::string getAttributeName(int index) const;

    ~TestScript();
};