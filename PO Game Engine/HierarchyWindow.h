#pragma once
#include "EditorWindow.h"


class HierarchyWindow : public EditorWindow { //Hierarchy window class
private:
    void repositionTexts();
public:
    HierarchyWindow(const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size, const std::string& titleText = "");
    void update() override;
    void handleEvent(sf::Event& event) override;
    void mouseOver();
    void changeSelectedObject(int index);
    void addText(const sf::Text& text) override;
    void deleteText(int index) override;
};