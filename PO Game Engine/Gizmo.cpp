#include "Gizmo.h"
#include "Game.h"
#include "Utility.h"
#include "EditorWindow.h"

using namespace std;
using namespace sf;


void Gizmo::reposition() { //reposition function
    if (Game::getCurrentScene()->getSelectedObjectIndex() != -1) {
        int index = Game::getCurrentScene()->getSelectedObjectIndex();
        const GameObject* selectedObject = Game::getCurrentScene()->getObjectByIndex(index);
        if (type == 0) { //Move
            selectionBox.setSize(selectedObject->getGlobalBounds().getSize() + Vector2f(20.f, 20.f));
            selectionBox.setPosition(selectedObject->getPosition());
            selectionBox.setOrigin((selectedObject->getGlobalBounds().getSize() + Vector2f(20.f, 20.f)) / 2.f);
        }
        else if (type == 1) { //Rotate
            // Get the size of the selected object
            Vector2f size = selectedObject->getLocalBounds().getSize();

            // Calculate the radius as half the length of the diagonal of the object's bounding box
            float radius = sqrt(size.x * size.x + size.y * size.y) / 2.f;

            // Set the circle's radius
            rotationBox.setRadius(radius);

            // Set the circle's position to the object's position
            rotationBox.setPosition(selectedObject->getPosition());

            // Set the circle's origin to its center
            rotationBox.setOrigin(radius, radius);

        }
        else if (type == 2) { //Scale
            // Set the size and position of the scale box
            scaleBox.setSize(Vector2f(20.f, 20.f));
            scaleBox.setPosition(selectedObject->getPosition() + selectedObject->getLocalBounds().getSize() / 2.f);
            scaleBox.setOrigin(scaleBox.getSize() / 2.f);
        }
    }
}
Gizmo::Gizmo() {
    selectionBox.setSize(Vector2f(0, 0));
    selectionBox.setFillColor(Color(0, 0, 0, 0));
    selectionBox.setOutlineColor(Color::White);
    selectionBox.setOutlineThickness(2);

    dragging = false;
    dragStart = Vector2f(0, 0);
    type = 0; //0 = move, 1 = rotate, 2 = scale
    scaleBox.setSize(Vector2f(0, 0));
    scaleBox.setFillColor(Color::White);
    rotationBox.setRadius(0);
    rotationBox.setFillColor(Color(0, 0, 0, 0));
    rotationBox.setOutlineColor(Color::White);
    rotationBox.setOutlineThickness(2);

    initialScale = Vector2f(0, 0);
}
void Gizmo::draw(RenderWindow& window) const { //draw function
    if (Game::getCurrentScene()->getSelectedObjectIndex() != -1) {
        if (type == 0) {
            window.draw(selectionBox);
        }
        else if (type == 1) {
            window.draw(rotationBox);
        }
        else if (type == 2) {
            window.draw(scaleBox);
        }
    }
}
void Gizmo::handleEvent(Event& event) { //handle event function
    if (event.type == Event::MouseButtonPressed && !EditorWindow::getClickedUI() && !Game::getIsOverGameWindow()) {
        if (event.mouseButton.button == Mouse::Left) {
            int ind = Game::getCurrentScene()->getSelectedObjectIndex();
            if (ind != -1) {
                Vector2f mousePos = Vector2f(event.mouseButton.x, event.mouseButton.y);
                mousePos = Game::getWindow()->mapPixelToCoords(Vector2i(mousePos.x, mousePos.y), *Game::getSceneView());
                if (Game::getCurrentScene()->getObjectByIndex(ind)->getGlobalBounds().contains(mousePos)) {
                    if(!dragging)
                        Game::addControlZScene();
                    dragging = true;
                    dragStart = mousePos;
                    if (type == 2) {
                        initialScale = Game::getCurrentScene()->getObjectByIndex(Game::getCurrentScene()->getSelectedObjectIndex())->getScale();
                    }
                }
            }
		}
	}
}
void Gizmo::update() { //update function
    //Check dragging logic to use events so the gizmo won't be called when the mouse is over UI
    if (Mouse::isButtonPressed(Mouse::Left) && Game::getCurrentScene()->getSelectedObjectIndex() != -1 && !Game::getIsOverGameWindow()) {
        Vector2f mousePos = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
        mousePos = Game::getWindow()->mapPixelToCoords(Vector2i(mousePos.x, mousePos.y), *Game::getSceneView());
        if (dragging) {
            if (type == 0) {
                //Move the selected object
                Vector2f dragEnd = mousePos;
                Vector2f drag = dragEnd - dragStart;
                Game::getCurrentScene()->moveSelectedObject(drag);
                dragStart = dragEnd;

                //Move the selection box
                selectionBox.move(drag);
            }
            else if (type == 1) {
                // Get the current object's position
                Vector2f objectPos = Game::getCurrentScene()->getObjectByIndex(Game::getCurrentScene()->getSelectedObjectIndex())->getPosition();

                // Calculate the vectors from the object's position to the initial and current mouse positions
                Vector2f initialDirection = dragStart - objectPos;
                Vector2f currentDirection = mousePos - objectPos;

                // Calculate the angles of these vectors
                float initialAngle = atan2(initialDirection.y, initialDirection.x);
                float currentAngle = atan2(currentDirection.y, currentDirection.x);

                // Calculate the change in angle and convert it to degrees
                float deltaAngle = (currentAngle - initialAngle) * 180.f / 3.14159265f;

                // Add the change in angle to the current rotation
                float currentRotation = Game::getCurrentScene()->getObjectByIndex(Game::getCurrentScene()->getSelectedObjectIndex())->getRotation();
                float newAngle = currentRotation + deltaAngle;

                // Set the new rotation
                Game::getCurrentScene()->modifySelectedCustom(floatToString(newAngle), 5);

                // Rotate the rotation box
                rotationBox.setRotation(newAngle);

                // Update dragStart for the next mouse move event
                dragStart = mousePos;

            }
            else if (type == 2) {
                // Scale the selected object
                Vector2f dragEnd = mousePos;
                Vector2f drag = dragEnd - dragStart;

                float originalObjectAngle = Game::getCurrentScene()->getObjectByIndex(Game::getCurrentScene()->getSelectedObjectIndex())->getRotation();

                bool shouldCorrect = false;

                //Rotate drag vector by the object's angle
                float angle = originalObjectAngle;

                if (angle < 0)
                    angle += 360.f;

                if ((angle >= 90.f && angle < 180.f) || (angle >= 270.f && angle < 360.f))
                    shouldCorrect = true;

                angle = fmod(angle, 90.f);

                angle = -angle * 3.14159265f / 180.f;
                float x = drag.x * cos(angle) - drag.y * sin(angle);
                float y = drag.x * sin(angle) + drag.y * cos(angle);
                drag = Vector2f(x, y);

                Vector2f objectPos = Game::getCurrentScene()->getObjectByIndex(Game::getCurrentScene()->getSelectedObjectIndex())->getPosition();
                Vector2f dragStartRotated = dragStart - objectPos;

                x = dragStartRotated.x * cos(angle) - dragStartRotated.y * sin(angle);
                y = dragStartRotated.x * sin(angle) + dragStartRotated.y * cos(angle);
                dragStartRotated = Vector2f(x, y) + objectPos;


                float sideLengthX = Game::getCurrentScene()->getObjectByIndex(Game::getCurrentScene()->getSelectedObjectIndex())->getLocalBounds().getSize().x;
                float sideLengthY = Game::getCurrentScene()->getObjectByIndex(Game::getCurrentScene()->getSelectedObjectIndex())->getLocalBounds().getSize().y;

                // Get the current object's position

                if (dragStartRotated.x < objectPos.x)
                    drag.x = -drag.x;
                if (initialScale.x < 0)
                    drag.x = -drag.x;
                if (dragStartRotated.y > objectPos.y)
                    drag.y = -drag.y;
                if (initialScale.y > 0)
                    drag.y = -drag.y;

                if (shouldCorrect) {
                    drag = Vector2f(drag.y, drag.x);
                    if ((initialScale.x < 0 && initialScale.y > 0) || (initialScale.x > 0 && initialScale.y < 0))
                        drag = Vector2f(-drag.x, -drag.y);
                }

                float scX = (drag.x * 2 / (sideLengthX * initialScale.x) + 1) * initialScale.x;
                float scY = (drag.y * 2 / (sideLengthY * initialScale.y) + 1) * initialScale.y;

                Game::getCurrentScene()->modifySelectedCustom(floatToString(scX), 6);
                Game::getCurrentScene()->modifySelectedCustom(floatToString(scY), 7);

                //dragStart = dragEnd;

                // Move the scale box
                //scaleBox.move(drag);

            }
        }
        //If we are not dragging, check if the cursor is over the selected object and if it is start dragging
        /*else if (type == 0 && Game::getCurrentScene()->getObjectByIndex(Game::getCurrentScene()->getSelectedObjectIndex())->getGlobalBounds().contains(mousePos)) {
            dragging = true;
            dragStart = mousePos;
        }
        else if (type == 1 && Game::getCurrentScene()->getObjectByIndex(Game::getCurrentScene()->getSelectedObjectIndex())->getGlobalBounds().contains(mousePos)) {
            dragging = true;
            dragStart = mousePos;
        }
        else if (type == 2 && Game::getCurrentScene()->getObjectByIndex(Game::getCurrentScene()->getSelectedObjectIndex())->getGlobalBounds().contains(mousePos)) {
            dragging = true;
            initialScale = Game::getCurrentScene()->getObjectByIndex(Game::getCurrentScene()->getSelectedObjectIndex())->getScale();

            dragStart = mousePos;
        }*/
    }
    else
        dragging = false;
    if (Game::getCurrentScene()->getSelectedObjectIndex() != -1)
        reposition();
}
void Gizmo::setGizmoType(int type) { //set gizmo type function
    this->type = type;
    if (type == 0) {
        rotationBox.setRadius(0);
        scaleBox.setSize(Vector2f(0, 0));
    }
    else if (type == 1) {
        selectionBox.setSize(Vector2f(0, 0));
        scaleBox.setSize(Vector2f(0, 0));
    }
    else if (type == 2) {
        selectionBox.setSize(Vector2f(0, 0));
        rotationBox.setRadius(0);
    }
}
