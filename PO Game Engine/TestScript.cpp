#include "TestScript.h"
#include "GameObject.h"
#include "Utility.h"

using namespace std;
using namespace sf;


TestScript::TestScript() { //default constructor
	defaultColor = Color::White;
	pressedColor = Color::Red;
	attributeCount = 2;
}
TestScript::TestScript(Color a, Color b) { //constructor
	defaultColor = a;
	pressedColor = b;
	attributeCount = 2;
}
void TestScript::setColors(Color a, Color b) { //set colors
	defaultColor = a;
	pressedColor = b;
}
TestScript* TestScript::clone() const { //clone function
	return new TestScript(*this);
}
void TestScript::start(GameObject& gameObject) { //start function
	cout << "Start function called on object with id " << gameObject.getId() << endl;
}
void TestScript::update(GameObject& gameObject) { //update function
	if (Mouse::isButtonPressed(Mouse::Left))
		gameObject.setFillColor(pressedColor);
	else
		gameObject.setFillColor(defaultColor);
	//cout << "Update function called on object with id " << gameObject.getId() << endl;
}
void TestScript::collision(GameObject& gameObject, GameObject& collisionObject) { //collision function
	cout << "Collision function called on object with id " << gameObject.getId() << endl;
}
void TestScript::trigger(GameObject& gameObject, GameObject& triggerObject) { //trigger function
	//cout << "Trigger function called on object with id " << gameObject.getId() << endl;
}
void TestScript::destroy(GameObject& gameObject) { //destroy function
	cout << "Destroy function called on object with id " << gameObject.getId() << endl;
}
string TestScript::getAttribute(int index) const { //get attribute
	if (index == 0)
		return ColorToString(defaultColor);
	if (index == 1)
		return ColorToString(pressedColor);
	return "";
}
void TestScript::setAttribute(int index, string value) { //set attribute
	if (index == 0) {
		defaultColor = stringToColor(value);
	}
	if (index == 1) {
		pressedColor = stringToColor(value);
	}
}
string TestScript::getScriptName() const { //get script name
	return "TestScript";
}
int TestScript::getAttributeType(int index) const { //get attribute type
	if (index == 0 || index == 1)
		return 2;
	return 0;
}
string TestScript::getAttributeName(int index) const { //get attribute name
	if (index == 0)
		return "Default Color";
	if (index == 1)
		return "Pressed Color";
	return "";
}
void TestScript::read(istream& stream) { //read function
	string a, b;
	stream >> a >> b;
	defaultColor = stringToColor(a);
	pressedColor = stringToColor(b);
}
void TestScript::write(ostream& stream) { //write function
	stream << ColorToString(defaultColor) << " ";
	stream << ColorToString(pressedColor) << " ";
}
TestScript::~TestScript() { //destructor
	cout << "Destructor called" << endl;
}
