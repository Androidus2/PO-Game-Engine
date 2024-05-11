#pragma once
#include <SFML/Graphics.hpp>
#include "DebugMacro.h"


class Gizmo {
private:
    sf::RectangleShape selectionBox;
    sf::CircleShape rotationBox;
    sf::RectangleShape scaleBox;
    int type;
    bool dragging;
    sf::Vector2f dragStart;

    sf::Vector2f initialScale;
    void reposition();
public:
    Gizmo();
    void draw(sf::RenderWindow& window) const;
    void handleEvent(sf::Event& event);
    void update();
    void setGizmoType(int type);
};