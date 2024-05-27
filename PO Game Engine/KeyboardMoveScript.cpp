#include "KeyboardMoveScript.h"
#include "Utility.h"
#include "Singleton.h"
#include "GameTIme.h"
#include "GameObject.h"

using namespace std;
using namespace sf;

KeyboardMoveScript::KeyboardMoveScript()
{
	moveSpeed = Vector2f(100, 100);
	upKey = Keyboard::W;
	downKey = Keyboard::S;
	leftKey = Keyboard::A;
	rightKey = Keyboard::D;
	attributeCount = 6;
}
KeyboardMoveScript* KeyboardMoveScript::clone() const
{
	return new KeyboardMoveScript(*this);
}

void KeyboardMoveScript::start(GameObject& gameObject)
{
}
void KeyboardMoveScript::update(GameObject& gameObject)
{
	if (Keyboard::isKeyPressed(upKey))
	{
		gameObject.move(Vector2f(0, -moveSpeed.y * Singleton<GameTime>::getInstance().getData().getDeltaTime()));
	}
	if (Keyboard::isKeyPressed(downKey))
	{
		gameObject.move(Vector2f(0, moveSpeed.y * Singleton<GameTime>::getInstance().getData().getDeltaTime()));
	}
	if (Keyboard::isKeyPressed(leftKey))
	{
		gameObject.move(Vector2f(-moveSpeed.x * Singleton<GameTime>::getInstance().getData().getDeltaTime(), 0));
	}
	if (Keyboard::isKeyPressed(rightKey))
	{
		gameObject.move(Vector2f(moveSpeed.x * Singleton<GameTime>::getInstance().getData().getDeltaTime(), 0));
	}
}
void KeyboardMoveScript::collision(GameObject& gameObject, GameObject& collisionObject)
{
}
void KeyboardMoveScript::trigger(GameObject& gameObject, GameObject& triggerObject)
{
}
void KeyboardMoveScript::destroy(GameObject& gameObject)
{
}

void KeyboardMoveScript::drawScriptElements(const GameObject& gameObject) const
{
}

string KeyboardMoveScript::getAttribute(int index) const
{
	switch (index)
	{
	case 0:
		return floatToString(moveSpeed.x);
		break;
	case 1:
		return floatToString(moveSpeed.y);
		break;
	case 2:
		return keyToString(upKey);
		break;
	case 3:
		return keyToString(downKey);
		break;
	case 4:
		return keyToString(leftKey);
		break;
	case 5:
		return keyToString(rightKey);
		break;
	default:
		return "";
		break;
	}
}
void KeyboardMoveScript::setAttribute(int index, string value)
{
	switch (index)
	{
	case 0:
		moveSpeed.x = stof(value);
		break;
	case 1:
		moveSpeed.y = stof(value);
		break;
	case 2:
		upKey = stringToKey(value);
		break;
	case 3:
		downKey = stringToKey(value);
		break;
	case 4:
		leftKey = stringToKey(value);
		break;
	case 5:
		rightKey = stringToKey(value);
		break;
	default:
		break;
	}
}

string KeyboardMoveScript::getScriptName() const
{
	return "KeyboardMoveScript";
}
int KeyboardMoveScript::getAttributeType(int index) const
{
	switch (index)
	{
	case 0:
		return 5;
		break;
	case 1:
		return 6;
		break;
	case 2:
		return 8;
		break;
	case 3:
		return 8;
		break;
	case 4:
		return 8;
		break;
	case 5:
		return 8;
		break;
	default:
		return 0;
		break;
	}
}
string KeyboardMoveScript::getAttributeName(int index) const
{
	switch (index)
	{
	case 0:
		return "Move Speed";
		break;
	case 1:
		return "Move Speed";
		break;
	case 2:
		return "Up Key";
		break;
	case 3:
		return "Down Key";
		break;
	case 4:
		return "Left Key";
		break;
	case 5:
		return "Right Key";
		break;
	default:
		return "";
		break;
	}
}

void KeyboardMoveScript::read(istream& stream)
{
	string line;
	stream.get();
	getline(stream, line);
	moveSpeed.x = stof(line);
	getline(stream, line);
	moveSpeed.y = stof(line);
	getline(stream, line);
	upKey = stringToKey(line);
	getline(stream, line);
	downKey = stringToKey(line);
	getline(stream, line);
	leftKey = stringToKey(line);
	getline(stream, line);
	rightKey = stringToKey(line);
}
void KeyboardMoveScript::write(ostream& stream) const
{
	stream << moveSpeed.x << endl;
	stream << moveSpeed.y << endl;
	stream << keyToString(upKey) << endl;
	stream << keyToString(downKey) << endl;
	stream << keyToString(leftKey) << endl;
	stream << keyToString(rightKey) << endl;
}

KeyboardMoveScript::~KeyboardMoveScript()
{
}