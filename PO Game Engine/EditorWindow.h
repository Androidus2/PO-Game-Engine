#pragma once
#include <iostream>
#include <vector>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "Button.h"
#include "InputField.h"



class EditorWindow { //Editor window class(used for the hierarchy and inspector windows and can be expanded upon), abstract class
protected:
    sf::RectangleShape window;
    sf::RectangleShape draggingArea;
    sf::Text title;
    std::vector<Button> buttons;
    std::vector<InputField> inputFields;
    std::vector<sf::Text> texts;
    sf::Vector2f position;
    sf::Vector2f size;
    bool isActive;
    bool isDragglable;
    bool isDragging;
    sf::Vector2f dragOffset;

    static bool clickedUI;
public:
    EditorWindow(const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size, const std::string& titleText = "");

    virtual void draw(sf::RenderWindow& window) const;
    virtual void update();
    virtual void handleEvent(sf::Event& event);

    virtual void mouseOver() = 0; //pure virtual function because it is completely different for the hierarchy and inspector windows
    virtual void drag(sf::Event& event);

    void addButton(const Button& button);
    void addInputField(const InputField& inputField);
    virtual void addText(const sf::Text& text);

    void changeText(int index, const std::string& text);
    virtual void deleteText(int index);
    void deleteFields();
    int getTextCount() const;

    void setTitle(const std::string& titleText);
    std::string getTitle() const;

    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;

    void setSize(const sf::Vector2f& size);
    sf::Vector2f getSize() const;

    virtual void setActive(bool isActive);
    bool getActive() const;

    bool isMouseOver() const;

    void deleteButton(int index);
    void deleteInputField(int index);

    static void setClickedUI(bool clickedUI);
    static bool getClickedUI();

    virtual ~EditorWindow();
};