#include "EditableColor.h"
#include "Game.h"
#include "ColorPicker.h"
#include "Utility.h"

using namespace std;
using namespace sf;


EditableColor::EditableColor(const Vector2f& position, const Vector2f& size, const Color& color, function<void(Scene*, string, int)> onChange, function<string(Scene*, int)> updateValue, int callIndex) {
	colorBox.setPosition(position);
	colorBox.setSize(size);
	colorBox.setFillColor(color);
	colorBox.setOutlineColor(Color::Black);
	colorBox.setOutlineThickness(1);

	this->onChange = onChange;
	this->updateValue = updateValue;
	this->callIndex = callIndex;
	isSelected = false;
}
void EditableColor::draw(RenderWindow& window) const { //draw function
	window.draw(colorBox);
}
void EditableColor::update() { //update function
	if (isSelected) {
		ColorPicker* colorPicker = dynamic_cast<ColorPicker*>(Game::getColorPicker());
		if (colorPicker) {
			colorBox.setFillColor(colorPicker->getSelectedColor());
			if (onChange)
				onChange(Game::getCurrentScene(), ColorToString(colorBox.getFillColor()), callIndex);
			if (!colorPicker->getActive())
				isSelected = false;
		}
	}
	else {
		if (updateValue) {
			colorBox.setFillColor(stringToColor(updateValue(Game::getCurrentScene(), callIndex)));
			if (onChange)
				onChange(Game::getCurrentScene(), updateValue(Game::getCurrentScene(), callIndex), callIndex);
		}
	}
}
void EditableColor::handleEvent(Event& event) { //handle event function
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
		Vector2f mousePos = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
		if (colorBox.getGlobalBounds().contains(mousePos)) {
			isSelected = true;
			ColorPicker* colorPicker = dynamic_cast<ColorPicker*>(Game::getColorPicker());
			if (colorPicker) {
				colorPicker->setActive(true);
				//colorBox.setFillColor(Game::getCurrentScene()->getObjectByIndex(Game::getCurrentScene()->getSelectedObjectIndex())->getFillColor());
				cout << "Tanta " << ColorToString(colorBox.getFillColor()) << endl;
				colorPicker->setSelectedColor(colorBox.getFillColor());
			}
		}
	}
}
void EditableColor::mouseOver() { //mouse over function
}
void EditableColor::setSelected(bool isSelected) { //set if the color is selected
	this->isSelected = isSelected;
}
bool EditableColor::getSelected() const { //get if the color is selected
	return isSelected;
}
void EditableColor::setColor(const Color& color) { //set the color of the color box
	colorBox.setFillColor(color);
}
Color EditableColor::getColor() const { //get the color of the color box
	return colorBox.getFillColor();
}
void EditableColor::setPosition(const Vector2f& position) { //set the position of the color box
	colorBox.setPosition(position);
}
Vector2f EditableColor::getPosition() const { //get the position of the color box
	return colorBox.getPosition();
}
void EditableColor::setSize(const Vector2f& size) { //set the size of the color box
	colorBox.setSize(size);
}
Vector2f EditableColor::getSize() const { //get the size of the color box
	return colorBox.getSize();
}
void EditableColor::setOnChange(function<void(Scene*, string, int)> onChange) { //set the onChange function
	this->onChange = onChange;
}
void EditableColor::setUpdateValue(function<string(Scene*, int)> updateValue) { //set the updateValue function
	this->updateValue = updateValue;
}
void EditableColor::setCallIndex(int callIndex) { //set the call index
	this->callIndex = callIndex;
}
int EditableColor::getCallIndex() const { //get the call index
	return callIndex;
}
