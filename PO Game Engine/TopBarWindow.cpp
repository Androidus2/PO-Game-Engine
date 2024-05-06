#include "TopBarWindow.h"
#include "Game.h"
#include "Gizmo.h"

using namespace std;
using namespace sf;


TopBarWindow::TopBarWindow(const Font& font, const Vector2f& position, const Vector2f& size, const string& title) : EditorWindow(font, position, size, title) {
	Button moveToolButton(font, Vector2f(position.x + 10, position.y + 10), Vector2f(30, 30), "M");
	moveToolButton.setOnClick([]() {
		Game::getGizmo()->setGizmoType(0);
		});
	buttons.push_back(moveToolButton);

	Button rotateToolButton(font, Vector2f(position.x + 50, position.y + 10), Vector2f(30, 30), "R");
	rotateToolButton.setOnClick([]() {
		Game::getGizmo()->setGizmoType(1);
		});
	buttons.push_back(rotateToolButton);

	Button scaleToolButton(font, Vector2f(position.x + 90, position.y + 10), Vector2f(30, 30), "S");
	scaleToolButton.setOnClick([]() {
		Game::getGizmo()->setGizmoType(2);
		});
	buttons.push_back(scaleToolButton);

	Button playButton(font, Vector2f(position.x + size.x - 40, position.y + 10), Vector2f(30, 30), "P");
	playButton.setOnClick([]() {
		Game::setIsPlaying(!Game::getIsPlaying());
		});
	playButton.setToggle(true);
	playButton.setDefaultColor(Color::Green);
	playButton.setHoverColor(Color(150, 255, 150));
	playButton.setPressedColor(Color::Red);
	buttons.push_back(playButton);

	Button saveButton(font, Vector2f(position.x + size.x - 150, position.y + 10), Vector2f(50, 30), "Save");
	saveButton.setOnClick([]() {
		if(Game::getCurrentScene() != nullptr && Game::getCurrentScene()->getName() != "" && !Game::getIsPlaying())
			Game::getCurrentScene()->saveScene();
		});
	buttons.push_back(saveButton);
}
void TopBarWindow::handleEvent(Event& event) { //handle event function
	EditorWindow::handleEvent(event);
}
void TopBarWindow::mouseOver() { //mouse over function
	//EditorWindow::mouseOver();
}
void TopBarWindow::draw(RenderWindow& window) const { //draw function
	EditorWindow::draw(window);
}
