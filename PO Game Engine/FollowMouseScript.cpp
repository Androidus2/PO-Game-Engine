#include "FollowMouseScript.h"
#include "Game.h"
#include "Utility.h"
#include "GameTIme.h"

using namespace std;
using namespace sf;

FollowMouseScript::FollowMouseScript(bool applySmoothness, float smoothnessSpeed) { //constructor
	this->applySmoothness = applySmoothness;
	this->smoothnessSpeed = smoothnessSpeed;
	attributeCount = 2;
	cout<<"Created FollowMouseScript" << endl;
}
FollowMouseScript* FollowMouseScript::clone() const { //clone function
	return new FollowMouseScript(*this);
}
void FollowMouseScript::start(GameObject& gameObject) { //start function (does nothing)

}
void FollowMouseScript::update(GameObject& gameObject) { //update function
	//Get the mouse position and make the object follow it
	if (!Game::getIsOverGameWindow())
		return;
	Vector2f mousePosition = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
	mousePosition = Game::getWindow()->mapPixelToCoords(Vector2i(mousePosition.x, mousePosition.y), *Game::getGameView());
	if (applySmoothness)
		mousePosition = gameObject.getPosition() + (-gameObject.getPosition() + mousePosition) * Singleton<GameTime>::getInstance().getData().getDeltaTime() * smoothnessSpeed;
	//cout << mousePosition.x<<" "<<mousePosition.y <<" "<< GameTime::getInstance()->getDeltaTime() << endl;
	gameObject.setPosition(mousePosition);
}
void FollowMouseScript::collision(GameObject& gameObject, GameObject& collisionObject) { //collision function (does nothing)

}
void FollowMouseScript::trigger(GameObject& gameObject, GameObject& triggerObject) { //trigger function (does nothing)

}
void FollowMouseScript::destroy(GameObject& gameObject) { //destroy function (does nothing)

}
string FollowMouseScript::getAttribute(int index) const { //get attribute
	if (index == 0)
		return applySmoothness ? "true" : "false";
	if (index == 1)
		return floatToString(smoothnessSpeed);
	return "";
}
void FollowMouseScript::setAttribute(int index, string value) { //set attribute
	if (index == 0) {
		applySmoothness = (value == "true" || value == "1");
	}
	if (index == 1) {
		smoothnessSpeed = stof(value);
	}
}
string FollowMouseScript::getScriptName() const { //get script name
	return "FollowMouseScript";
}
int FollowMouseScript::getAttributeType(int index) const { //get attribute type
	if (index == 0)
		return 4;
	if (index == 1)
		return 1;
	return -1;
}
string FollowMouseScript::getAttributeName(int index) const { //get attribute name
	if (index == 0)
		return "Apply Smoothness";
	if (index == 1)
		return "Smoothness Speed";
	return "";
}
void FollowMouseScript::read(istream& stream) { //read function
	//Read the applySmoothness and smoothnessSpeed variables from the file
	stream >> applySmoothness;
	stream >> smoothnessSpeed;
	cout<<"Read the values: " << applySmoothness << " " << smoothnessSpeed << endl;
}
void FollowMouseScript::write(ostream& stream) const { //write function
	//Write the applySmoothness and smoothnessSpeed variables to the file
	stream << applySmoothness << " ";
	stream << smoothnessSpeed << " ";
}
FollowMouseScript::~FollowMouseScript() { //destructor (does nothing)

}
