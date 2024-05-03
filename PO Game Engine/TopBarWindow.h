#pragma once
#include "EditorWindow.h" //Include EditorWindow.h


class TopBarWindow : public EditorWindow { //Top bar window class (derived from EditorWindow)
public:
	TopBarWindow(const sf::Font & font, const sf::Vector2f& position, const sf::Vector2f& size, const std::string& title);
	void handleEvent(sf::Event& event) override;
	void mouseOver() override;
	void draw(sf::RenderWindow& window) const override;

};