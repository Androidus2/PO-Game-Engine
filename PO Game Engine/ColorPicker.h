#pragma once
#include <iostream>
#include "EditorWindow.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "DebugMacro.h"


class ColorPicker : public EditorWindow {
private:
    sf::VertexArray colorsDisplay;
    sf::VertexArray hueBarDisplay;
    sf::VertexArray alphaBarDisplay;
    sf::RectangleShape alphaBarBackground;
    sf::CircleShape colorsCursor;
    sf::CircleShape hueBarCursor;
    sf::CircleShape alphaBarCursor;
    sf::Color selectedColor;
    int selected;

    sf::Vector2f colorsOffset;
    sf::Vector2f hueBarOffset;
    sf::Vector2f alphaBarOffset;

    void drawHSV(sf::Vertex& point, double h, double s, double v, double alpha);
    void modulate(sf::VertexArray& points, double hue);
    void accuratePosition(int& x, int& y, int xLimit, int yLimit);
    void setCursorsBasedOnColor();
    void reposition();
public:
    ColorPicker(sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size, const std::string& title);
    void handleEvent(sf::Event& event) override;
    void draw(sf::RenderWindow& window) const override;
    void update() override;
    void mouseOver() override;
    void drag(sf::Event& event) override;
    sf::Color getSelectedColor() const;
    void setSelectedColor(const sf::Color& color);
    void setActive(bool active) override;
    ~ColorPicker() override;
};