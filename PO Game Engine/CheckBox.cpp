#include "CheckBox.h"

using namespace std;
using namespace sf;

CheckBox::CheckBox(const Vector2f& position, const Vector2f& size) { //constructor
	box.setPosition(position);
	box.setSize(size);
	box.setFillColor(Color::White);
	box.setOutlineColor(Color::Black);
	box.setOutlineThickness(1);

	isChecked = false;
}
void CheckBox::draw(RenderWindow& window) const { //draw the checkbox
	window.draw(box);
}
void CheckBox::handleEvent(Event& event) { //handle the event
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
		Vector2f mousePos = Vector2f(event.mouseButton.x, event.mouseButton.y);
		if (box.getGlobalBounds().contains(mousePos)) {
			isChecked = !isChecked;
			if (isChecked)
				box.setFillColor(Color::Green);
			else
				box.setFillColor(Color::Black);
			if (onChange)
				onChange(isChecked);
		}
	}
}
void CheckBox::setChecked(bool isChecked) { //set if the checkbox is checked
	this->isChecked = isChecked;
}
bool CheckBox::getChecked() const { //get if the checkbox is checked
	return isChecked;
}
bool CheckBox::getValue() const { //get the value of the checkbox
	return updateValue();
}
void CheckBox::setPosition(const Vector2f& position) { //set the position of the checkbox
	box.setPosition(position);
}
Vector2f CheckBox::getPosition() const { //get the position of the checkbox
	return box.getPosition();
}
void CheckBox::setSize(const Vector2f& size) { //set the size of the checkbox
	box.setSize(size);
}
Vector2f CheckBox::getSize() const { //get the size of the checkbox
	return box.getSize();
}
void CheckBox::setFillColor(const Color& color) { //set the fill color of the checkbox
	box.setFillColor(color);
}
void CheckBox::setOnChange(function<void(bool isChecked)> onChange) { //set the onChange function
	this->onChange = onChange;
}
void CheckBox::setUpdateValue(function<bool()> updateValue) { //set the updateValue function
	this->updateValue = updateValue;
	isChecked = updateValue();
	if(isChecked)
		box.setFillColor(Color::Green);
	else
		box.setFillColor(Color::Black);
}
