#include "EditorWindow.h"
#include "Game.h"

using namespace std;
using namespace sf;


EditorWindow::EditorWindow(const Font& font, const Vector2f& position, const Vector2f& size, const string& titleText) { //constructor
	window.setPosition(position);
	window.setSize(size);
	window.setFillColor(Color(50, 50, 50));
	window.setOutlineColor(Color::Black);
	window.setOutlineThickness(3);

	draggingArea.setPosition(position);
	draggingArea.setSize(Vector2f(size.x, 25));
	draggingArea.setFillColor(Color(100, 100, 100));
	draggingArea.setOutlineColor(Color::Black);
	draggingArea.setOutlineThickness(1);

	title.setFont(font);
	title.setCharacterSize(20);
	title.setFillColor(Color::Cyan);
	title.setString(titleText);
	title.setOrigin(title.getLocalBounds().getSize().x / 2.f, 0.f);
	title.setPosition(position.x + size.x / 2.f, position.y);

	this->position = position;
	this->size = size;
	isActive = true;
	isDragglable = false;
	isDragging = false;
	dragOffset = Vector2f(0, 0);
}
void EditorWindow::draw(RenderWindow& window) const { //draw function
	if (!isActive)
		return;
	window.draw(this->window);
	if (isDragglable)
		window.draw(draggingArea);
	window.draw(title);
	for (int i = 0; i < texts.size(); i++)
		window.draw(texts[i]);
	for (int i = 0; i < buttons.size(); i++)
		buttons[i].draw(window);
	for (int i = 0; i < inputFields.size(); i++)
		inputFields[i].draw(window);
}
void EditorWindow::update() { //update function
	if (!isActive)
		return;
	for (int i = 0; i < buttons.size(); i++)
		buttons[i].update();
	for (int i = 0; i < inputFields.size(); i++) {
		inputFields[i].update();
		inputFields[i].changeBackground();
	}

}
void EditorWindow::handleEvent(Event& event) { //handle event function
	if (!isActive)
		return;

	//Check if we clicked on the window and update the clickedUI variable
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
		Vector2f mousePosition = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
		if (window.getGlobalBounds().contains(mousePosition))
			clickedUI = true;
	}

	drag(event);
	for (int i = 0; i < buttons.size(); i++)
		buttons[i].handleEvent(event);
	for (int i = 0; i < inputFields.size(); i++)
		inputFields[i].handleEvent(event);
}
void EditorWindow::drag(Event& event) { //drag function
	if (isDragglable) {
		Vector2f mousePosition = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
		if (isDragging) {
			Vector2f deltaMovedAmount = mousePosition - dragOffset - position;
			setPosition(mousePosition - dragOffset);
			draggingArea.setPosition(position);

			title.setPosition(position.x + size.x / 2.f, position.y);

			for (int i = 0; i < buttons.size(); i++)
				buttons[i].setPosition(buttons[i].getPosition() + deltaMovedAmount);
			for (int i = 0; i < inputFields.size(); i++)
				inputFields[i].setPosition(inputFields[i].getPosition() + deltaMovedAmount);
			for (int i = 0; i < texts.size(); i++)
				texts[i].setPosition(texts[i].getPosition() + deltaMovedAmount);
		}
		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && draggingArea.getGlobalBounds().contains(mousePosition)) {
			isDragging = true;
			dragOffset = mousePosition - position;
		}
		if (!Mouse::isButtonPressed(Mouse::Left)) {
			isDragging = false;
		}
	}
}
void EditorWindow::addButton(const Button& button) { //add a button to the window
	buttons.push_back(button);
}
void EditorWindow::addInputField(const InputField& inputField) { //add an input field to the window
	inputFields.push_back(inputField);
}
void EditorWindow::addText(const Text& text) { //add a text to the window
	texts.push_back(text);
}
void EditorWindow::changeText(int index, const string& text) { //change the text of a text in the window
	if (index < texts.size() && index >= 0)
		texts[index].setString(text);
}
void EditorWindow::deleteText(int index) { //delete a text from the window
	if (index < texts.size() && index >= 0)
		texts.erase(texts.begin() + index);
}
void EditorWindow::deleteFields() { //delete all the input fields from the window
	inputFields.clear();
}
int EditorWindow::getTextCount() const { //get the number of texts in the window
	return texts.size();
}
void EditorWindow::setTitle(const string& titleText) { //set the title of the window
	title.setString(titleText);
	title.setOrigin(title.getLocalBounds().getSize().x / 2.f, 0.f);
	title.setPosition(position.x + size.x / 2.f, position.y);
}
string EditorWindow::getTitle() const { //get the title of the window
	return title.getString();
}
void EditorWindow::setPosition(const Vector2f& position) { //set the position of the window
	window.setPosition(position);
	title.setPosition(position.x + size.x / 2.f, position.y);
	this->position = position;
}
Vector2f EditorWindow::getPosition() const { //get the position of the window
	return position;
}
void EditorWindow::setSize(const Vector2f& size) { //set the size of the window
	window.setSize(size);
	title.setPosition(position.x + size.x / 2.f, position.y);
	this->size = size;
}
Vector2f EditorWindow::getSize() const { //get the size of the window
	return size;
}
void EditorWindow::setActive(bool isActive) { //set if the window is active
	this->isActive = isActive;
}
bool EditorWindow::getActive() const { //get if the window is active
	return isActive;
}
bool EditorWindow::isMouseOver() const { //get if the mouse is over the window
	Vector2f mousePosition = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
	return window.getGlobalBounds().contains(mousePosition);
}
void EditorWindow::setClickedUI(bool clickedUI) { //set if the UI is clicked
	EditorWindow::clickedUI = clickedUI;
}
bool EditorWindow::getClickedUI() { //get if the UI is clicked
	return clickedUI;
}
EditorWindow::~EditorWindow() { //destructor
	buttons.clear();
	inputFields.clear();
	texts.clear();
}
