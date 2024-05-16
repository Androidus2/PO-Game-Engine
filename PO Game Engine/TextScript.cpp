#include "TextScript.h"
#include "Game.h"
#include "Utility.h"
#include "DebugMacro.h"

using namespace std;
using namespace sf;

TextScript::TextScript()
{
	text.setFont(*Game::getFont());
	text.setCharacterSize(24);
	text.setFillColor(Color::White);
	text.setString("Text");
	text.setPosition(0, 0);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setRotation(0);
	text.setScale(1, 1);
	attributeCount = 11;

	positionOffset = Vector2f(0, 0);
	rotationOffset = 0;
	scaleOffset = Vector2f(1, 1);
	relativeToObject = false;
}
TextScript* TextScript::clone() const
{
	return new TextScript(*this);
}

void TextScript::start(GameObject& gameObject)
{
	//Set position, rotation, scale
	if (relativeToObject)
	{
		text.setPosition(gameObject.getPosition() + positionOffset);
		text.setRotation(gameObject.getRotation() + rotationOffset);
		text.setScale(gameObject.getScale().x * scaleOffset.x, gameObject.getScale().y * scaleOffset.y);
	}
	else
	{
		text.setPosition(positionOffset);
		text.setRotation(rotationOffset);
		text.setScale(scaleOffset);
	}
}
void TextScript::update(GameObject& gameObject)
{
	//Set position, rotation, scale
	if (relativeToObject)
	{
		text.setPosition(gameObject.getPosition() + positionOffset);
		text.setRotation(gameObject.getRotation() + rotationOffset);
		text.setScale(gameObject.getScale().x * scaleOffset.x, gameObject.getScale().y * scaleOffset.y);
	}
	else
	{
		text.setPosition(positionOffset);
		text.setRotation(rotationOffset);
		text.setScale(scaleOffset);
	}
}
void TextScript::collision(GameObject& gameObject, GameObject& collisionObject)
{
}
void TextScript::trigger(GameObject& gameObject, GameObject& triggerObject)
{
}
void TextScript::destroy(GameObject& gameObject)
{
}

void TextScript::drawScriptElements(const GameObject& gameObject) const
{
	Game::getWindow()->draw(text);
}

string TextScript::getAttribute(int index) const
{
	switch (index)
	{
	case 0:
		return text.getString();
	case 1:
		return floatToString(positionOffset.x);
	case 2:
		return floatToString(positionOffset.y);
	case 3:
		return ColorToString(text.getFillColor());
	case 4:
		return floatToString(rotationOffset);
	case 5:
		return floatToString(scaleOffset.x);
	case 6:
		return floatToString(scaleOffset.y);
	case 7:
		return floatToString(text.getCharacterSize());
	case 8:
		return to_string(relativeToObject);
	case 9:
		return ColorToString(text.getOutlineColor());
	case 10:
		return floatToString(text.getOutlineThickness());
	default:
		return "";
	}
}
void TextScript::setAttribute(int index, string value)
{
	switch (index)
	{
	case 0:
		text.setString(value);
		break;
	case 1:
		positionOffset.x = stof(value);
		text.setPosition(stof(value), text.getPosition().y);
		break;
	case 2:
		positionOffset.y = stof(value);
		text.setPosition(text.getPosition().x, stof(value));
		break;
	case 3:
		text.setFillColor(stringToColor(value));
		break;
	case 4:
		rotationOffset = stof(value);
		text.setRotation(stof(value));
		break;
	case 5:
		scaleOffset.x = stof(value);
		text.setScale(stof(value), text.getScale().y);
		break;
	case 6:
		scaleOffset.y = stof(value);
		text.setScale(text.getScale().x, stof(value));
		break;
	case 7:
		text.setCharacterSize(stoi(value));
		break;
	case 8:
		relativeToObject = (value == "1" || value == "true");
		break;
	case 9:
		text.setOutlineColor(stringToColor(value));
		break;
	case 10:
		text.setOutlineThickness(stof(value));
		break;
	}
}
string TextScript::getScriptName() const
{
	return "TextScript";
}
int TextScript::getAttributeType(int index) const
{
	switch (index)
	{
	case 0:
		return 0;
	case 1:
		return 5;
	case 2:
		return 6;
	case 3:
		return 2;
	case 4:
		return 1;
	case 5:
		return 5;
	case 6:
		return 6;
	case 7:
		return 3;
	case 8:
		return 4;
	case 9:
		return 2;
	case 10:
		return 1;
	default:
		return 0;
	}
}
string TextScript::getAttributeName(int index) const
{
	switch (index)
	{
	case 0:
		return "Text";
	case 1:
		return "Position";
	case 2:
		return "Position";
	case 3:
		return "Color";
	case 4:
		return "Rotation";
	case 5:
		return "Scale";
	case 6:
		return "Scale";
	case 7:
		return "Character Size";
	case 8:
		return "IsRelativeToObject";
	case 9:
		return "Outline Color";
	case 10:
		return "Outline Thickness";
	default:
		return "";
	}
}

void TextScript::read(istream& stream)
{
	string line;
	stream.get();
	getline(stream, line);
	text.setString(line);
	getline(stream, line);
	positionOffset.x = stof(line);
	getline(stream, line);
	positionOffset.y = stof(line);
	getline(stream, line);
	text.setFillColor(stringToColor(line));
	getline(stream, line);
	rotationOffset = stof(line);
	getline(stream, line);
	scaleOffset.x = stof(line);
	getline(stream, line);
	scaleOffset.y = stof(line);
	getline(stream, line);
	text.setCharacterSize(stoi(line));
	getline(stream, line);
	relativeToObject = (line == "1" || line == "true");
	getline(stream, line);
	text.setOutlineColor(stringToColor(line));
	getline(stream, line);
	text.setOutlineThickness(stof(line));

	//Set position, rotation, scale
	text.setPosition(positionOffset);
	text.setRotation(rotationOffset);
	text.setScale(scaleOffset);
}
void TextScript::write(ostream& stream) const
{
	string st = text.getString();
	stream << st << endl;
	stream << positionOffset.x << endl;
	stream << positionOffset.y << endl;
	stream << ColorToString(text.getFillColor()) << endl;
	stream << rotationOffset << endl;
	stream << scaleOffset.x << endl;
	stream << scaleOffset.y << endl;
	stream << text.getCharacterSize() << endl;
	stream << relativeToObject << endl;
	stream << ColorToString(text.getOutlineColor()) << endl;
	stream << text.getOutlineThickness() << endl;
}

TextScript::~TextScript()
{
	//cout<<"TextScript destroyed"<<endl;
}