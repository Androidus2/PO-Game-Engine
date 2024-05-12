#include "HierarchyWindow.h"
#include "Game.h"
#include "InspectorWindow.h"
#include "Utility.h"

using namespace std;
using namespace sf;


void HierarchyWindow::repositionTexts() { //reposition the texts in the hierarchy window
    if (texts.size() > 0)
        texts[0].setPosition(window.getPosition().x + 10, window.getPosition().y + title.getCharacterSize() + 10 + verticalOffset);
    for (int i = 1; i < texts.size(); i++)
        texts[i].setPosition(window.getPosition().x + 10, texts[i - 1].getPosition().y + texts[i - 1].getCharacterSize() + 10);
}
void HierarchyWindow::updateElementsWithVerticalOffset(float old) { //update the elements with the vertical offset
	float delta = verticalOffset - old;
    for (int i = 0; i < texts.size(); i++)
		texts[i].setPosition(texts[i].getPosition() + Vector2f(0, delta));
}
//Hierarchy window constructor (makes a button to create objects and adds texts for the objects in the hierarchy)
HierarchyWindow::HierarchyWindow(const Font& font, const Vector2f& position, const Vector2f& size, const string& titleText) : EditorWindow(font, position, size, titleText) {
    setTitle("Hierarchy");
    Button* createButton = new Button(font, Vector2f(position.x + 10, position.y + size.y - 40), Vector2f(size.x - 20, 30), "Create Object");
    createButton->setOnClick(createObj);
    addButton(*createButton);
    delete createButton;

    //Adding texts for the objects in the hierarchy
    Text* tmp = new Text("Tmp", font, 15);
    for (int i = 0; i < Game::getCurrentScene()->getObjects().size(); i++) {
        tmp->setString(Game::getCurrentScene()->getObjectByIndex(i)->getName());
        tmp->setPosition(position.x + 10, position.y + i * 30 + tmp->getCharacterSize() + 10);
        addText(*tmp);
    }
    delete tmp;

    Game::setHierarchy(this);
}
void HierarchyWindow::draw(RenderWindow& window) const { //draw function
	if (!isActive)
		return;
	window.draw(this->window);
	for (int i = 0; i < texts.size(); i++)
		window.draw(texts[i]);
    window.draw(topBar);
    window.draw(bottomBar);
	buttons[0].draw(window);
	window.draw(title);
}
void HierarchyWindow::update() { //update the texts in the hierarchy window
    EditorWindow::update();
    for (int i = 0; i < Game::getCurrentScene()->getObjects().size(); i++) {
        texts[i].setString(Game::getCurrentScene()->getObjectByIndex(i)->getName());
    }
}
void HierarchyWindow::handleEvent(Event& event) { //handle event function
    if (isActive) {
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && !clickedUI) {
            Vector2f mousePos = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
            if (window.getGlobalBounds().contains(mousePos)) {
                int newSelectedIndex = -1;
                for (int i = 0; i < Game::getCurrentScene()->getObjectsCount(); i++) {
                    if (texts[i].getGlobalBounds().contains(mousePos)) {
                        newSelectedIndex = i;
                        break;
                    }
                }
                changeSelectedObject(newSelectedIndex);
            }
            else if(!Game::getIsOverGameWindow()){
                mousePos = Game::getWindow()->mapPixelToCoords(Vector2i(mousePos.x, mousePos.y), *Game::getSceneView());
                int newSelectedIndex = -1;
                //Loop through the objects in the scene and check if the mouse is over them
                vector<GameObject*> objects = Game::getCurrentScene()->getObjects();
                sort(objects.begin(), objects.end(), [](GameObject* a, GameObject* b) { return a->getZLayer() < b->getZLayer(); });
                int selectedIndex = Game::getCurrentScene()->getSelectedObjectIndex();
                for (int i = 0; i < objects.size(); i++) {
                    if (objects[i]->getGlobalBounds().contains(mousePos)) {
                        newSelectedIndex = i;
                        if (selectedIndex != -1 && objects[i]->getId() == Game::getCurrentScene()->getObjectByIndex(selectedIndex)->getId()) {
                            newSelectedIndex = -2;
                            break;
                        }
                    }
                }
                if (newSelectedIndex != -2) {
                    if (newSelectedIndex != -1) {
                        for (int i = 0; i < objects.size(); i++) {
                            if (Game::getCurrentScene()->getObjectByIndex(i)->getId() == objects[newSelectedIndex]->getId()) {
								newSelectedIndex = i;
								break;
							}
						}
                    }
                    changeSelectedObject(newSelectedIndex);
                }
            }
        }
        if (event.type == Event::KeyReleased && event.key.control && event.key.code == Keyboard::D) {
            //If an object is selected, duplicate it and select the duplicated object
            if (Game::getCurrentScene()->getSelectedObjectIndex() != -1) {
                GameObject* tmp = Game::getCurrentScene()->getObjectByIndex(Game::getCurrentScene()->getSelectedObjectIndex())->clone();
                tmp->changeId();
                Game::getCurrentScene()->addObject(tmp);
                delete tmp;
                changeSelectedObject(Game::getCurrentScene()->getObjectsCount() - 1);
            }
        }
    }
    EditorWindow::handleEvent(event);
}
void HierarchyWindow::mouseOver() { //mouse over function (responsible for selecting objects in the hierarchy window)

}
void HierarchyWindow::changeSelectedObject(int newSelectedIndex) {
    if (newSelectedIndex != Game::getCurrentScene()->getSelectedObjectIndex()) {
        if (Game::getCurrentScene()->getSelectedObjectIndex() != -1)
            texts[Game::getCurrentScene()->getSelectedObjectIndex()].setFillColor(Color::White);
        Game::getCurrentScene()->setSelectedObjectIndex(newSelectedIndex);
        InspectorWindow* tmp = dynamic_cast<InspectorWindow*>(Game::getInspector());
        if (tmp)
            tmp->makeCustomFields();
        if (Game::getCurrentScene()->getSelectedObjectIndex() != -1)
            texts[Game::getCurrentScene()->getSelectedObjectIndex()].setFillColor(Color::Cyan);
    }
}
void HierarchyWindow::addText(const Text& text) { //add a text to the hierarchy window
    texts.push_back(text);
    texts[texts.size()-1].move(0, verticalOffset);
    repositionTexts();
    for (int i = 0; i < texts.size(); i++) {
        if (texts[i].getPosition().y + texts[i].getCharacterSize() + 10 - bottomBar.getPosition().y - verticalOffset > maxVerticalOffset)
            maxVerticalOffset = texts[i].getPosition().y + texts[i].getCharacterSize() + 10 - bottomBar.getPosition().y - verticalOffset;
    }
}
void HierarchyWindow::deleteText(int index) { //delete a text from the hierarchy window
    if (index < texts.size() && index >= 0) {
        texts.erase(texts.begin() + index);
        repositionTexts();
        maxVerticalOffset = 0;
        for (int i = 0; i < texts.size(); i++) {
            if (texts[i].getPosition().y + texts[i].getCharacterSize() + 10 - bottomBar.getPosition().y - verticalOffset > maxVerticalOffset)
                maxVerticalOffset = texts[i].getPosition().y + texts[i].getCharacterSize() + 10 - bottomBar.getPosition().y - verticalOffset;
        }
        if(verticalOffset < -maxVerticalOffset)
			verticalOffset = -maxVerticalOffset;
        repositionTexts();
    }
}
void HierarchyWindow::clearTexts() { //clear all texts from the hierarchy window
	texts.clear();
    maxVerticalOffset = 0;
    verticalOffset = 0;
}