#include "InspectorWindow.h"
#include "Utility.h"
#include "Game.h"
#include "DebugMacro.h"

using namespace std;
using namespace sf;

void InspectorWindow::updateElementsWithVerticalOffset(float old) {
    float delta = verticalOffset - old;
	for (int i = 2; i < buttons.size(); i++)
		buttons[i].setPosition(buttons[i].getPosition() + Vector2f(0, delta));
	for (int i = 0; i < inputFields.size(); i++)
		inputFields[i].setPosition(inputFields[i].getPosition() + Vector2f(0, delta));
	for (int i = 0; i < texts.size(); i++)
		texts[i].setPosition(texts[i].getPosition() + Vector2f(0, delta));
	for (int i = 0; i < colors.size(); i++)
		colors[i].setPosition(colors[i].getPosition() + Vector2f(0, delta));
	for (int i = 0; i < imageFields.size(); i++)
		imageFields[i].setPosition(imageFields[i].getPosition() + Vector2f(0, delta));
	for (int i = 0; i < checkBoxes.size(); i++)
		checkBoxes[i].setPosition(checkBoxes[i].getPosition() + Vector2f(0, delta));
    for (int i = 0; i < keyBindFields.size(); i++)
        keyBindFields[i].setPosition(keyBindFields[i].getPosition() + Vector2f(0, delta));
}
void InspectorWindow::makeDefaultFields() {
    int yLevel = 0;
    for (int i = 0; i < 23; i++) {
        int type = Game::getCurrentScene()->getSelectedCustomType(i);

        if (i == 12) {
            //Make a label for the collider
            Text* tmp = new Text("Tmp", *Game::getFont(), 20);
            tmp->setString("Collider");
            tmp->setPosition(position.x + 10, position.y + title.getCharacterSize() + 10 + yLevel * 30);
            addText(*tmp);
            delete tmp;
            yLevel++;
        }

        if (i == 13) {
            Text* tmp = new Text("Tmp", *Game::getFont(), 15);
            tmp->setString("Collider Shape");
            tmp->setPosition(position.x + 10, position.y + title.getCharacterSize() + 10 + yLevel * 30);
            addText(*tmp);
            delete tmp;
            yLevel++;

            Button* tmpButton = new Button(*Game::getFont(), Vector2f(position.x + 10, position.y + title.getCharacterSize() + 10 + yLevel * 30), Vector2f(70, 20), "Square");
            tmpButton->setOnClick([]() {
                Game::addControlZScene();
                Game::getCurrentScene()->changeSelectedColliderType(0);
				});
            addButton(*tmpButton);
            delete tmpButton;

            tmpButton = new Button(*Game::getFont(), Vector2f(position.x + 90, position.y + title.getCharacterSize() + 10 + yLevel * 30), Vector2f(70, 20), "Circle");
            tmpButton->setOnClick([]() {
                Game::addControlZScene();
                Game::getCurrentScene()->changeSelectedColliderType(1);
                });
            addButton(*tmpButton);
            delete tmpButton;

            tmpButton = new Button(*Game::getFont(), Vector2f(position.x + 170, position.y + title.getCharacterSize() + 10 + yLevel * 30), Vector2f(70, 20), "Triangle");
            tmpButton->setOnClick([]() {
                Game::addControlZScene();
				Game::getCurrentScene()->changeSelectedColliderType(2);
				});
            addButton(*tmpButton);
            delete tmpButton;

            tmpButton = new Button(*Game::getFont(), Vector2f(position.x + 250, position.y + title.getCharacterSize() + 10 + yLevel * 30), Vector2f(70, 20), "Hexagon");
            tmpButton->setOnClick([]() {
                Game::addControlZScene();
                Game::getCurrentScene()->changeSelectedColliderType(3);
                });
            addButton(*tmpButton);

            delete tmpButton;
            yLevel++;
        }

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
            /*tmpField->setOnChange(&Scene::modifySelectedCustom);
            tmpField->setUpdateValue(&Scene::getSelectedCustom);*/
            tmpField->setOnChange([i](string value) {
				Game::getCurrentScene()->modifySelectedCustom(value, i);
				});
            tmpField->setUpdateValue([i]() {
				return Game::getCurrentScene()->getSelectedCustom(i);
				});
            if (type == 0)
                tmpField->setOnlyNumbers(false);
            else
                tmpField->setOnlyNumbers(true);
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
        else if (type == 4) {
            CheckBox* tmpCheck = new CheckBox(Vector2f(position.x + tmp->getGlobalBounds().width + 20, position.y + title.getCharacterSize() + 10 + yLevel * 30), Vector2f(20, 20));
            tmpCheck->setOnChange([i](bool isChecked) {
				Game::getCurrentScene()->modifySelectedCustom(to_string(isChecked), i);
				});
            tmpCheck->setUpdateValue([i]() {
                return Game::getCurrentScene()->getSelectedCustom(i) == "1" || Game::getCurrentScene()->getSelectedCustom(i) == "true";
                });
            checkBoxes.push_back(*tmpCheck);
            delete tmpCheck;
        }

        delete tmp;
        if (type != 5)
            yLevel++;
    }
}
//Inspector window constructor (makes input fields for the position, rotation, scale, and velocity of the selected object, a button to delete the selected object, and a button to change if the selected object is movable) will need to be expanded upon
InspectorWindow::InspectorWindow(const Font& font, const Vector2f& position, const Vector2f& size, const string& titleText) : EditorWindow(font, position, size, titleText), scriptAddDropdown(font, Vector2f(position.x + 10, position.y + size.y - 450), Vector2f(size.x / 2, 300)) {
    scriptAddDropdown.addElement("TestScript");
    scriptAddDropdown.addElement("FollowMouseScript");
    scriptAddDropdown.addElement("TextScript");
    scriptAddDropdown.addElement("KeyboardMoveScript");
    scriptAddDropdown.addElement("PongBallScript");
    scriptAddDropdown.addElement("SpawnerScript");

    Dropdown* sc = &scriptAddDropdown;

    scriptAddDropdown.setCallback([sc](int index) {
        if (Game::getCurrentScene()->getSelectedObjectIndex() != -1) {
            Game::addControlZScene();
			Game::getCurrentScene()->addScriptToSelectedObject(sc->getElementName(index));
			dynamic_cast<InspectorWindow*>(Game::getInspector())->makeCustomFields();
		}
		});

    //Delete button
    Button* deleteButton = new Button(font, Vector2f(position.x + 10, position.y + size.y - 40), Vector2f(size.x - 20, 30), "Delete Object");
    deleteButton->setOnClick(deleteObj); //Select the deleteObj function to be called when the button is clicked
    addButton(*deleteButton);
    delete deleteButton;

    //Add script button
    Button* addScriptButton = new Button(font, Vector2f(position.x + 10, position.y + size.y - 80), Vector2f(size.x - 20, 30), "Add Script");
    addScriptButton->setOnClick([sc]() {
                //cout<<"Add Script"<<sc<<endl;
        		sc->setActive(true);
		});
    addButton(*addScriptButton);
    delete addScriptButton;

    bottomBar.setSize(Vector2f(size.x, 100));
    bottomBar.setPosition(Vector2f(position.x, position.y + size.y - 100));

    //Change isMoveable button
    //Button* changeIsMoveableButton = new Button(font, Vector2f(position.x + 10, position.y + size.y - 80), Vector2f(size.x - 20, 30), "Change Moveable");
    //changeIsMoveableButton->setOnClick(changeSelectedIsMovable); //Select the changeSelectedIsMovable function to be called when the button is clicked
    //changeIsMoveableButton->setToggle(true); //Set the button to be a toggle button
    //addButton(*changeIsMoveableButton);
    //delete changeIsMoveableButton;
}
void InspectorWindow::makeCustomFields() { //make custom fields function (used to add custom fields to the inspector window)
    deleteFields();
    colors.clear();
    texts.clear();
    imageFields.clear();
    checkBoxes.clear();
    keyBindFields.clear();
    maxVerticalOffset = 0;
    //Remove all the buttons except for the first 2
    for (int i = 2; i < buttons.size(); i++) {
        buttons.erase(buttons.begin() + i);
        i--;
    }
    makeDefaultFields();
    if (Game::getCurrentScene()->getSelectedObjectIndex() != -1) {
        const GameObject* selectedObject = Game::getCurrentScene()->getObjectByIndex(Game::getCurrentScene()->getSelectedObjectIndex());
        InputField* tmp = NULL;
        Text* tmpText = NULL;
        Button* tmpButton = NULL;
        int cnt = 23;
        float extraOffset = 15;
        for (int i = 0; i < selectedObject->getScriptsCount(); i++) {
            if (texts.size() > 0)
                extraOffset = texts[texts.size() - 1].getCharacterSize() + texts[texts.size() - 1].getPosition().y + 15;
            //Add a text for the script name
            //extraOffset += 10;
            tmpText = new Text(selectedObject->getScriptName(i), *Game::getFont(), 20);
            tmpText->setFillColor(Color::White);
            tmpText->setPosition(Vector2f(position.x + 10, extraOffset));
            addText(*tmpText);
            //Add a button to delete the script on the right of the script name
            tmpButton = new Button(*Game::getFont(), Vector2f(position.x + size.x - 30, extraOffset), Vector2f(20, 20), "X");
            //Make a lambda function to delete the script
            tmpButton->setOnClick([i]() {
                Game::getCurrentScene()->removeScriptFromSelectedObject(i);
                dynamic_cast<InspectorWindow*>(Game::getInspector())->makeCustomFields();
                });
            addButton(*tmpButton);
            //extraOffset += 30;
            delete tmpButton;
            delete tmpText;
            for (int j = 0; j < selectedObject->getAttributeCountFromScripts(i); j++) {
                int type = selectedObject->getAttributeTypeFromScripts(i, j);
                string name = selectedObject->getAttributeNamesFromScripts(i, j);
                tmpText = new Text(name, *Game::getFont(), 15);
                tmpText->setFillColor(Color::White);
                tmpText->setPosition(Vector2f(position.x + 10, texts[texts.size() - 1].getPosition().y + 30));
                if (type != 6)
                    addText(*tmpText);
                if (type == 0 || type == 1 || type == 3 || type == 5 || type == 6) {
                    if (type == 5) {
                        //Add a label called X
                        tmpText->setPosition(position.x + 20 + tmpText->getGlobalBounds().width, tmpText->getPosition().y);
                        tmpText->setString("X");
                        addText(*tmpText);
                    }
                    else if (type == 6) { //Add a label called Y
                        tmpText->setPosition(inputFields[inputFields.size() - 1].getPosition().x + 110, tmpText->getPosition().y - 30);
                        tmpText->setString("Y");
                        addText(*tmpText);
                    }
                    tmp = new InputField(*Game::getFont(), Vector2f(position.x + 10, position.y + title.getCharacterSize() + 10), Vector2f(100, 20), "0");
                    tmp->setPosition(Vector2f(tmpText->getPosition().x + tmpText->getGlobalBounds().width + 10, tmpText->getPosition().y));
                    /*tmp->setOnChange(&Scene::modifySelectedCustom);
                    tmp->setUpdateValue(&Scene::getSelectedCustom);*/
                    tmp->setOnChange([cnt](string value) {
						Game::getCurrentScene()->modifySelectedCustom(value, cnt);
						});
                    tmp->setUpdateValue([cnt]() {
                        return Game::getCurrentScene()->getSelectedCustom(cnt);
                        });
                    if (type != 0)
                        tmp->setOnlyNumbers(true);
                    addInputField(*tmp);
                    delete tmp;
                    cnt++;
                }
                else if (type == 2) {
                    EditableColor* tmpColor = new EditableColor(Vector2f(position.x + 10, position.y + title.getCharacterSize() + 10), Vector2f(100, 20), Color::White, &Scene::modifySelectedCustom, &Scene::getSelectedCustom, cnt);
                    tmpColor->setCallIndex(cnt);
                    tmpColor->setPosition(Vector2f(position.x + tmpText->getGlobalBounds().width + 20, tmpText->getPosition().y));
                    tmpColor->setOnChange(&Scene::modifySelectedCustom);
                    tmpColor->setUpdateValue(&Scene::getSelectedCustom);
                    colors.push_back(*tmpColor);
                    delete tmpColor;
                    cnt++;
                }
                else if (type == 7) {
                    ImageField* tmpImage = new ImageField(Vector2f(position.x + 10, position.y + title.getCharacterSize() + 10), Vector2f(100, 20), "", *Game::getFont(), &Scene::modifySelectedCustom, &Scene::getSelectedCustom, cnt);
                    tmpImage->setPosition(Vector2f(position.x + tmpText->getGlobalBounds().width + 20, tmpText->getPosition().y));
                    imageFields.push_back(*tmpImage);
                    delete tmpImage;
                    cnt++;
                }
                else if (type == 4) {
                    CheckBox* tmpCheck = new CheckBox(Vector2f(position.x + 10, position.y + title.getCharacterSize() + 10), Vector2f(20, 20));
                    tmpCheck->setOnChange([cnt](bool isChecked) {
                        Game::getCurrentScene()->modifySelectedCustom(to_string(isChecked), cnt);
                        });
                    tmpCheck->setUpdateValue([cnt]() {
                        return Game::getCurrentScene()->getSelectedCustom(cnt) == "1" || Game::getCurrentScene()->getSelectedCustom(cnt) == "true";
                        });
                    tmpCheck->setPosition(Vector2f(position.x + tmpText->getGlobalBounds().width + 20, tmpText->getPosition().y));
                    checkBoxes.push_back(*tmpCheck);
                    delete tmpCheck;
                    cnt++;
                }
                else if (type == 8) {
					KeyBindField* tmpKeyBind = new KeyBindField(*Game::getFont(), Vector2f(position.x + 10, position.y + title.getCharacterSize() + 10), Vector2f(100, 20), "Unknown");
					tmpKeyBind->setPosition(Vector2f(position.x + tmpText->getGlobalBounds().width + 20, tmpText->getPosition().y));
                    tmpKeyBind->setOnChange([cnt](string value) {
						Game::getCurrentScene()->modifySelectedCustom(value, cnt);
						});
                    tmpKeyBind->setUpdateValue([cnt]() {
						return Game::getCurrentScene()->getSelectedCustom(cnt);
						});
                    keyBindFields.push_back(*tmpKeyBind);
					delete tmpKeyBind;
					cnt++;
                }
                delete tmpText;
            }
            //extraOffset += 30 * totalAttributes;
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
    scriptAddDropdown.update();
    if (Game::getCurrentScene()->getSelectedObjectIndex() != -1) {
        for (int i = 0; i < colors.size(); i++) {
            colors[i].update();
        }
        for (int i = 0; i < imageFields.size(); i++) {
            imageFields[i].update();
        }
        for (int i = 0; i < keyBindFields.size(); i++) {
            keyBindFields[i].update();
        }
    }
}
void InspectorWindow::handleEvent(Event& event) { //handle event function
    scriptAddDropdown.handleEvent(event);
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
        for (int i = 0; i < checkBoxes.size(); i++) {
            checkBoxes[i].handleEvent(event);
        }
        for (int i = 0; i < keyBindFields.size(); i++) {
			keyBindFields[i].handleEvent(event);
		}
    }
}
void InspectorWindow::draw(RenderWindow& window) const { //draw function
    if (!isActive)
        return;
    if (Game::getCurrentScene()->getSelectedObjectIndex() != -1) { //If an object is selected, draw the inspector window
        //EditorWindow::draw(window);
        window.draw(this->window);
        for (int i = 0; i < texts.size(); i++)
            window.draw(texts[i]);
        for (int i = 0; i < colors.size(); i++) {
            colors[i].draw(window);
        }
        for (int i = 0; i < imageFields.size(); i++) {
            imageFields[i].draw(window);
        }
        for (int i = 0; i < checkBoxes.size(); i++) {
			checkBoxes[i].draw(window);
		}
        for (int i = 0; i < keyBindFields.size(); i++) {
            keyBindFields[i].draw(window);
        }
        for(int i = 0; i < inputFields.size(); i++)
			inputFields[i].draw(window);
        for (int i = 2; i < buttons.size(); i++)
			buttons[i].draw(window);
        window.draw(topBar);
        window.draw(bottomBar);
        buttons[0].draw(window);
        buttons[1].draw(window);
        scriptAddDropdown.draw(window);
        window.draw(title);
    }
    else {
        window.draw(topBar);
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
