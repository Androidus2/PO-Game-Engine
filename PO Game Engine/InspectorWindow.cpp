#include "InspectorWindow.h"
#include "Utility.h"
#include "Game.h"

using namespace std;
using namespace sf;


void InspectorWindow::makeDefaultFields() {
    int yLevel = 0;
    for (int i = 0; i < 12; i++) {
        int type = Game::getCurrentScene()->getSelectedCustomType(i);
        Text* tmp = new Text("Tmp", *Game::getFont(), 15);
        tmp->setString(Game::getCurrentScene()->getSelectedCustomName(i));
        tmp->setPosition(position.x + 10, position.y + title.getCharacterSize() + 10 + yLevel * 30);
        if (type != 6)
            addText(*tmp);

        if (type == 0 || type == 1 || type == 3 || type == 5 || type == 6) {
            if (type == 5) { //Add a label called X
                tmp->setPosition(position.x + 20 + tmp->getGlobalBounds().width, position.y + title.getCharacterSize() + 10 + yLevel * 30);
                tmp->setString("X");
                addText(*tmp);
            }
            else if (type == 6) { //Add a label called Y
                tmp->setPosition(inputFields[inputFields.size() - 1].getPosition().x + 110, position.y + title.getCharacterSize() + 10 + yLevel * 30);
                tmp->setString("Y");
                addText(*tmp);
            }
            InputField* tmpField = new InputField(*Game::getFont(), Vector2f(tmp->getPosition().x + tmp->getGlobalBounds().width + 10, tmp->getPosition().y), Vector2f(100, 20), "0");
            tmpField->setOnChange(&Scene::modifySelectedCustom);
            tmpField->setUpdateValue(&Scene::getSelectedCustom);
            if (type == 0)
                tmpField->setOnlyNumbers(false);
            else
                tmpField->setOnlyNumbers(true);
            tmpField->setCallIndex(i);
            addInputField(*tmpField);
            delete tmpField;
        }
        else if (type == 2) {
            EditableColor* tmpColor = new EditableColor(Vector2f(position.x + tmp->getGlobalBounds().width + 20, position.y + title.getCharacterSize() + 10 + yLevel * 30), Vector2f(100, 20), Color::White, &Scene::modifySelectedCustom, &Scene::getSelectedCustom, i);
            tmpColor->setCallIndex(i);
            tmpColor->setOnChange(&Scene::modifySelectedCustom);
            tmpColor->setUpdateValue(&Scene::getSelectedCustom);
            colors.push_back(*tmpColor);
            delete tmpColor;
        }
        else if (type == 7) {
            ImageField* tmpImage = new ImageField(Vector2f(position.x + tmp->getGlobalBounds().width + 20, position.y + title.getCharacterSize() + 10 + yLevel * 30), Vector2f(100, 20), "", *Game::getFont(), &Scene::modifySelectedCustom, &Scene::getSelectedCustom, i);
            imageFields.push_back(*tmpImage);
            delete tmpImage;
        }

        delete tmp;
        if (type != 5)
            yLevel++;
    }
}
//Inspector window constructor (makes input fields for the position, rotation, scale, and velocity of the selected object, a button to delete the selected object, and a button to change if the selected object is movable) will need to be expanded upon
InspectorWindow::InspectorWindow(const Font& font, const Vector2f& position, const Vector2f& size, const string& titleText) : EditorWindow(font, position, size, titleText) {
    //Delete button
    Button* deleteButton = new Button(font, Vector2f(position.x + 10, position.y + size.y - 40), Vector2f(size.x - 20, 30), "Delete Object");
    deleteButton->setOnClick(deleteObj); //Select the deleteObj function to be called when the button is clicked
    addButton(*deleteButton);
    delete deleteButton;

    //Change isMoveable button
    Button* changeIsMoveableButton = new Button(font, Vector2f(position.x + 10, position.y + size.y - 80), Vector2f(size.x - 20, 30), "Change Moveable");
    changeIsMoveableButton->setOnClick(changeSelectedIsMovable); //Select the changeSelectedIsMovable function to be called when the button is clicked
    changeIsMoveableButton->setToggle(true); //Set the button to be a toggle button
    addButton(*changeIsMoveableButton);
    delete changeIsMoveableButton;
}
void InspectorWindow::makeCustomFields() { //make custom fields function (used to add custom fields to the inspector window)
    deleteFields();
    colors.clear();
    texts.clear();
    imageFields.clear();
    makeDefaultFields();
    if (Game::getCurrentScene()->getSelectedObjectIndex() != -1) {
        const GameObject* selectedObject = Game::getCurrentScene()->getObjectByIndex(Game::getCurrentScene()->getSelectedObjectIndex());
        InputField* tmp = NULL;
        Text* tmpText = NULL;
        int cnt = 12;
        float extraOffset = 15;
        if (texts.size() > 0)
            extraOffset += texts[texts.size() - 1].getCharacterSize() + texts[texts.size() - 1].getPosition().y;
        for (int i = 0; i < selectedObject->getScriptsCount(); i++) {
            for (int j = 0; j < selectedObject->getAttributeCountFromScripts(i); j++) {
                int type = selectedObject->getAttributeTypeFromScripts(i, j);
                string name = selectedObject->getAttributeNamesFromScripts(i, j);
                tmpText = new Text(name, *Game::getFont(), 15);
                tmpText->setFillColor(Color::White);
                tmpText->setPosition(Vector2f(position.x + 10, extraOffset + 30 * (i * selectedObject->getScriptsCount() + j)));
                addText(*tmpText);
                if (type == 0 || type == 1) { //Needs support for the rest of the types
                    tmp = new InputField(*Game::getFont(), Vector2f(position.x + 10, position.y + title.getCharacterSize() + 10), Vector2f(100, 20), "0");
                    tmp->setPosition(Vector2f(position.x + tmpText->getGlobalBounds().width + 20, extraOffset + 30 * (i * selectedObject->getScriptsCount() + j)));
                    tmp->setOnChange(&Scene::modifySelectedCustom);
                    tmp->setUpdateValue(&Scene::getSelectedCustom);
                    tmp->setCallIndex(cnt);
                    if (type == 1)
                        tmp->setOnlyNumbers(true);
                    addInputField(*tmp);
                    delete tmp;
                    cnt++;
                }
                else if (type == 2) {
                    EditableColor* tmpColor = new EditableColor(Vector2f(position.x + 10, position.y + title.getCharacterSize() + 10), Vector2f(100, 20), Color::White, &Scene::modifySelectedCustom, &Scene::getSelectedCustom, cnt);
                    tmpColor->setCallIndex(cnt);
                    tmpColor->setPosition(Vector2f(position.x + tmpText->getGlobalBounds().width + 20, extraOffset + 30 * (i * selectedObject->getScriptsCount() + j)));
                    tmpColor->setOnChange(&Scene::modifySelectedCustom);
                    tmpColor->setUpdateValue(&Scene::getSelectedCustom);
                    colors.push_back(*tmpColor);
                    delete tmpColor;
                    cnt++;
                }
                delete tmpText;
            }
        }
    }

    //Make an image field for the selected object
    /*if (Game::getCurrentScene()->getSelectedObjectIndex() != -1) {
        ImageField* tmp = new ImageField(Vector2f(position.x + 10, position.y + title.getCharacterSize() + 10), Vector2f(100, 20), "", *Game::getFont(), &Scene::modifySelectedCustom, &Scene::getSelectedCustom, 11);
        tmp->setPosition(Vector2f(position.x + 10, 700));
        imageFields.push_back(*tmp);
        delete tmp;
    }*/
}
void InspectorWindow::update() { //update function
    EditorWindow::update();
    if (Game::getCurrentScene()->getSelectedObjectIndex() != -1) {
        for (int i = 0; i < colors.size(); i++) {
            colors[i].update();
        }
        for (int i = 0; i < imageFields.size(); i++) {
            imageFields[i].update();
        }
    }
}
void InspectorWindow::handleEvent(Event& event) { //handle event function
    EditorWindow::handleEvent(event);
    if (isActive) {
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            Vector2f mousePos = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
            if (window.getGlobalBounds().contains(mousePos)) {
                for (int i = 0; i < colors.size(); i++)
                    colors[i].setSelected(false);
                for (int i = 0; i < inputFields.size(); i++) {
                    inputFields[i].checkMouseClick();
                }
            }
        }
        for (int i = 0; i < colors.size(); i++)
            colors[i].handleEvent(event);
        for (int i = 0; i < imageFields.size(); i++) {
            imageFields[i].handleEvent(event);
        }
    }
}
void InspectorWindow::draw(RenderWindow& window) const { //draw function
    if (!isActive)
        return;
    if (Game::getCurrentScene()->getSelectedObjectIndex() != -1) { //If an object is selected, draw the inspector window
        EditorWindow::draw(window);
        for (int i = 0; i < colors.size(); i++) {
            colors[i].draw(window);
        }
        for (int i = 0; i < imageFields.size(); i++) {
            imageFields[i].draw(window);
        }
    }
    else {
        window.draw(this->window);
        window.draw(title);
    }
}
void InspectorWindow::changeImage(const string& path) { //change image function (used to change the image of the selected object)
    if (Game::getCurrentScene()->getSelectedObjectIndex() != -1) {
        //Loop through the image fields and check if any of them are selected
        for (int i = 0; i < imageFields.size(); i++) {
            if (imageFields[i].getSelected()) {
                imageFields[i].setImagePath(path);
                break;
            }
        }
    }
}
void InspectorWindow::mouseOver() { //mouse over function (used to check if the mouse is over the inspector window and to check the input fields)

}
