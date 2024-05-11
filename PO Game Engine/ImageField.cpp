#include "ImageField.h"
#include "Game.h"
#include "EditorWindow.h"

using namespace std;
using namespace sf;


ImageField::ImageField(const Vector2f& position, const Vector2f& size, const string& imagePath, const Font& font, void (Scene::* onChange) (string str, int index), string(Scene::* updateValue)(int index) const, int callIndex) {
	imageField.setPosition(position);
	imageField.setSize(size);
	imageField.setFillColor(Color::White);
	imageField.setOutlineColor(Color::Black);
	imageField.setOutlineThickness(1);

	imageName.setFont(font);
	imageName.setCharacterSize(15);
	imageName.setFillColor(Color::White);
	imageName.setString(imagePath);
	imageName.setPosition(position.x + 5, position.y + 2);

	deleteButton = Button(font, Vector2f(position.x + imageField.getSize().x, position.y), Vector2f(20, 20), "X");
	deleteButton.setDefaultColor(Color::Red);
	deleteButton.setPressedColor(Color::Red);
	deleteButton.setHoverColor(Color::Red);
	deleteButton.setTextColor(Color::White);
	//Make a lambda function to delete the image path
	deleteButton.setOnClick([this]() {
		this->setImagePath("None");
		});

	this->imagePath = imagePath;
	this->onChange = onChange;
	this->updateValue = updateValue;
	this->callIndex = callIndex;
	isSelected = false;
}
ImageField::ImageField(const ImageField& imageField) {
	this->imageField = imageField.imageField;
	this->imageName = imageField.imageName;
	this->deleteButton = imageField.deleteButton;
	this->deleteButton.setOnClick([this]() {
		this->setImagePath("None");
		});
	this->imagePath = imageField.imagePath;
	this->isSelected = imageField.isSelected;
	this->onChange = imageField.onChange;
	this->updateValue = imageField.updateValue;
	this->callIndex = imageField.callIndex;
}
ImageField& ImageField::operator=(const ImageField& imageField) {
	if (this == &imageField)
		return *this;
	this->imageField = imageField.imageField;
	this->imageName = imageField.imageName;
	this->deleteButton = imageField.deleteButton;
	this->deleteButton.setOnClick([this]() {
		this->setImagePath("None");
		});
	this->imagePath = imageField.imagePath;
	this->isSelected = imageField.isSelected;
	this->onChange = imageField.onChange;
	this->updateValue = imageField.updateValue;
	this->callIndex = imageField.callIndex;
	return *this;
}
void ImageField::draw(RenderWindow& window) const { //draw function
	window.draw(imageField);
	window.draw(imageName);
	deleteButton.draw(window);
}
void ImageField::update() { //update function
	if (isSelected) {
		imageField.setFillColor(Color::Black);
	}
	else {
		imageField.setFillColor(Color(150, 150, 150));
		if (updateValue) {
			imagePath = updateValue(Game::getCurrentScene(), callIndex);
			imageName.setString(imagePath);
		}
	}
	deleteButton.update();
}
void ImageField::handleEvent(Event& event) { //handle event function
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && Game::getInspector()->isMouseOver()) {
		Vector2f mousePos = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
		if (imageField.getGlobalBounds().contains(mousePos) && !Game::getBlockClick()) {
			isSelected = true;
			Game::setBlockClick(true);
		}
		else if(isSelected)
			isSelected = false;
	}
	deleteButton.handleEvent(event);
}
void ImageField::mouseOver() { //mouse over function
}
void ImageField::setSelected(bool isSelected) { //set if the image field is selected
	this->isSelected = isSelected;
}
bool ImageField::getSelected() const { //get if the image field is selected
	return isSelected;
}
void ImageField::setImagePath(const string& imagePath) { //set the image path of the image field
	this->imagePath = imagePath;
	string str = "";
	//Change str to be the name of the file (without the path)
	for (int i = imagePath.size() - 1; i >= 0; i--) {
		if (imagePath[i] == '/') {
			str = imagePath.substr(i + 1);
			break;
		}
	}
	imageName.setString(str);
	if (onChange)
		onChange(Game::getCurrentScene(), imagePath, callIndex);
}
string ImageField::getImagePath() const { //get the image path of the image field
	return imagePath;
}
void ImageField::setPosition(const Vector2f& position) { //set the position of the image field
	imageField.setPosition(position);
	imageName.setPosition(position.x + 5, position.y);
	deleteButton.setPosition(Vector2f(position.x + imageField.getSize().x, position.y));
}
Vector2f ImageField::getPosition() const { //get the position of the image field
	return imageField.getPosition();
}
void ImageField::setSize(const Vector2f& size) { //set the size of the image field
	imageField.setSize(size);
	imageName.setPosition(imageField.getPosition().x + 5, imageField.getPosition().y + size.y / 2 - imageName.getLocalBounds().getSize().y / 2);
	deleteButton.setPosition(Vector2f(imageField.getPosition().x + size.x - 25, imageField.getPosition().y + size.y / 2 - 10));
}
Vector2f ImageField::getSize() const { //get the size of the image field
	return imageField.getSize();
}
void ImageField::setOnChange(function<void(Scene*, string, int)> onChange) { //set the onChange function
	this->onChange = onChange;
}
void ImageField::setUpdateValue(function<string(Scene*, int)> updateValue) { //set the updateValue function
	this->updateValue = updateValue;
}
void ImageField::setCallIndex(int callIndex) { //set the call index
	this->callIndex = callIndex;
}
int ImageField::getCallIndex() const { //get the call index
	return callIndex;
}
