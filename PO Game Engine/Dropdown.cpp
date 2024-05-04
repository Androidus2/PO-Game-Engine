#include "Dropdown.h"
#include "Game.h"

using namespace std;
using namespace sf;

Dropdown::Dropdown(const Font& font, const Vector2f& position, const Vector2f& size) { //constructor
	background.setSize(size);
	background.setPosition(position);
	background.setFillColor(Color(50, 50, 50));
	background.setOutlineColor(Color::White);
	background.setOutlineThickness(1);

	isActive = false;
}
void Dropdown::draw(RenderWindow& window) const { //draw function
	//cout<<"isActiveDropdownDraw: "<<isActive<<" "<<this << endl;
	if (isActive) {
		window.draw(background);
		for (int i = 0; i < buttons.size(); i++) {
			buttons[i].draw(window);
		}
	}
}
void Dropdown::update() { //update function
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].update();
	}
}
void Dropdown::handleEvent(Event& event) { //handle event function
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].handleEvent(event);
	}
	if (event.type == Event::MouseButtonPressed) {
		isActive = false;
	}
}
void Dropdown::addElement(const string& name) { //add element function
	float ySize = background.getSize().y / (buttons.size() + 1);
	Button button(*Game::getFont(), Vector2f(background.getPosition().x, background.getPosition().y + ySize * buttons.size()), Vector2f(background.getSize().x, ySize), name);
	button.setOnClick([this, i = buttons.size()]() {selectedElement(i); });
	buttons.push_back(button);
	//Loop through all buttons and set their position and size
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].setPosition(Vector2f(background.getPosition().x, background.getPosition().y + ySize * i));
		buttons[i].setSize(Vector2f(background.getSize().x, ySize));
	}
}
void Dropdown::removeElement(int index) { //remove element function
	if(index >= 0 && index < buttons.size())
		buttons.erase(buttons.begin() + index);
}
void Dropdown::setCallback(const function<void(int)>& callback) { //set callback function
	this->callback = callback;
}
string Dropdown::getElementName(int index) const { //get element name function
	if (index >= 0 && index < buttons.size())
		return buttons[index].getText();
	return "";
}
void Dropdown::selectedElement(int index) { //selected element function
	if (callback)
		callback(index);
}
void Dropdown::setActive(bool isActive) { //set active function
	this->isActive = isActive;
	cout<<"isActive: "<<isActive<<endl;
}
bool Dropdown::getActive() const { //get active function
	return isActive;
}