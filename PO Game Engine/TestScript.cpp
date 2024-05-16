#include "TestScript.h"
#include "GameObject.h"
#include "Utility.h"

using namespace std;
using namespace sf;


TestScript::TestScript() { //default constructor
	defaultColor = Color::White;
	pressedColor = Color::Red;
	attributeCount = 3;
	key = Keyboard::Key::Unknown;
}
TestScript::TestScript(Color a, Color b) { //constructor
	defaultColor = a;
	pressedColor = b;
	attributeCount = 3;
	key = Keyboard::Key::Unknown;
}
void TestScript::setColors(Color a, Color b) { //set colors
	defaultColor = a;
	pressedColor = b;
}
TestScript* TestScript::clone() const { //clone function
	return new TestScript(*this);
}
void TestScript::start(GameObject& gameObject) { //start function
	//cout << "Start function called on object with id " << gameObject.getId() << endl;
}
void TestScript::update(GameObject& gameObject) { //update function
	if (Mouse::isButtonPressed(Mouse::Left))
		gameObject.setFillColor(pressedColor);
	else
		gameObject.setFillColor(defaultColor);
	//cout << "Update function called on object with id " << gameObject.getId() << endl;
}
void TestScript::collision(GameObject& gameObject, GameObject& collisionObject) { //collision function
	//cout << "Collision function called on object with id " << gameObject.getId() << endl;
}
void TestScript::trigger(GameObject& gameObject, GameObject& triggerObject) { //trigger function
	//cout << "Trigger function called on object with id " << gameObject.getId() << endl;
}
void TestScript::destroy(GameObject& gameObject) { //destroy function
	//cout << "Destroy function called on object with id " << gameObject.getId() << endl;
}
string TestScript::getAttribute(int index) const { //get attribute
	if (index == 0)
		return ColorToString(defaultColor);
	if (index == 1)
		return ColorToString(pressedColor);
	if (index == 2)
		return keyToString(key);
	return "";
}
void TestScript::setAttribute(int index, string value) { //set attribute
	if (index == 0) {
		defaultColor = stringToColor(value);
	}
	if (index == 1) {
		pressedColor = stringToColor(value);
	}
	if (index == 2) {
		key = stringToKey(value);
	}
}
string TestScript::getScriptName() const { //get script name
	return "TestScript";
}
int TestScript::getAttributeType(int index) const { //get attribute type
	if (index == 0 || index == 1)
		return 2;
	if (index == 2)
		return 8;
	return 0;
}
string TestScript::getAttributeName(int index) const { //get attribute name
	if (index == 0)
		return "Default Color";
	if (index == 1)
		return "Pressed Color";
	if (index == 2)
		return "Key";
	return "";
}
void TestScript::read(istream& stream) { //read function
	string a, b, c;
	stream >> a >> b >> c;
	defaultColor = stringToColor(a);
	pressedColor = stringToColor(b);
	key = stringToKey(c);
}
void TestScript::write(ostream& stream) const { //write function
	stream << ColorToString(defaultColor) << " ";
	stream << ColorToString(pressedColor) << " ";
	stream << keyToString(key) << " ";
}
TestScript::~TestScript() { //destructor
	//cout << "Destructor called" << endl;
}
