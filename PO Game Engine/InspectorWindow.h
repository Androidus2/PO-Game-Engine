#pragma once
#include "EditorWindow.h"
#include "EditableColor.h"
#include "ImageField.h"
#include "CheckBox.h"
#include "Dropdown.h"


class InspectorWindow : public EditorWindow { //Inspector window class
private:
    Dropdown scriptAddDropdown;
    std::vector<EditableColor> colors;
    std::vector<ImageField> imageFields;
    std::vector<CheckBox> checkBoxes;
    void makeDefaultFields();
    void updateElementsWithVerticalOffset(float old) override;
public:
    InspectorWindow(const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size, const std::string& titleText = "");
    void makeCustomFields();
    void update() override;
    void handleEvent(sf::Event& event) override;
    void draw(sf::RenderWindow& window) const;
    void changeImage(const std::string& path);
    void mouseOver();
};