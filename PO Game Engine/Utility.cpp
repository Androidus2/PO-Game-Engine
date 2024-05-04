#include <sstream>
#include <iomanip>
#include <cmath>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "Utility.h"
#include "Game.h"
#include "EditorWindow.h"

#include "TestScript.h"
#include "FollowMouseScript.h"

using namespace std;
using namespace sf;

float Utility::magnitude(const Vector2f& source) //magnitude of a vector
{
    return sqrt((source.x * source.x) + (source.y * source.y));
}
float Utility::dotProduct(const Vector2f& source1, const Vector2f& source2) //dot product of 2 vectors
{
    return source1.x * source2.x + source1.y * source2.y;
}
Vector2f Utility::normalize(const Vector2f& source) //normalize a vector
{
    float length = magnitude(source);
    if (length != 0)
    {
        return Vector2f(source.x / length, source.y / length);
    }
    return source;
}
Vector2f Utility::calculateNormal(const Vector2f& source) //calculate normal of a vector
{
    return normalize(Vector2f(source.y, -source.x));
}
Vector2f Utility::direction(const Vector2f& source, const Vector2f& target) //direction from source to target
{
    return normalize(Vector2f(target.x - source.x, target.y - source.y));
}
Vector2f Utility::rotateVector(const Vector2f& source, float angle) //rotate a vector
{
    float x = source.x * cos(angle) - source.y * sin(angle);
    float y = source.x * sin(angle) + source.y * cos(angle);
    return Vector2f(x, y);
}


string floatToString(float f, int precision) { //for input fields
    stringstream ss;
    ss << fixed << setprecision(precision) << f;
    return ss.str();
}

string keyToString(Keyboard::Key key) { //for saving key bindings
    switch (key) {
    case Keyboard::A: return "A";
    case Keyboard::B: return "B";
    case Keyboard::C: return "C";
    case Keyboard::D: return "D";
    case Keyboard::E: return "E";
    case Keyboard::F: return "F";
    case Keyboard::G: return "G";
    case Keyboard::H: return "H";
    case Keyboard::I: return "I";
    case Keyboard::J: return "J";
    case Keyboard::K: return "K";
    case Keyboard::L: return "L";
    case Keyboard::M: return "M";
    case Keyboard::N: return "N";
    case Keyboard::O: return "O";
    case Keyboard::P: return "P";
    case Keyboard::Q: return "Q";
    case Keyboard::R: return "R";
    case Keyboard::S: return "S";
    case Keyboard::T: return "T";
    case Keyboard::U: return "U";
    case Keyboard::V: return "V";
    case Keyboard::W: return "W";
    case Keyboard::X: return "X";
    case Keyboard::Y: return "Y";
    case Keyboard::Z: return "Z";
    case Keyboard::Num0: return "0";
    case Keyboard::Num1: return "1";
    case Keyboard::Num2: return "2";
    case Keyboard::Num3: return "3";
    case Keyboard::Num4: return "4";
    case Keyboard::Num5: return "5";
    case Keyboard::Num6: return "6";
    case Keyboard::Num7: return "7";
    case Keyboard::Num8: return "8";
    case Keyboard::Num9: return "9";
    case Keyboard::Escape: return "Escape";
    case Keyboard::LControl: return "Left-Control";
    case Keyboard::LShift: return "Left-Shift";
    case Keyboard::LAlt: return "Left-Alt";
    case Keyboard::RControl: return "Right-Control";
    case Keyboard::RShift: return "Right-Shift";
    case Keyboard::RAlt: return "Right-Alt";
    case Keyboard::Space: return "Space";
    case Keyboard::Left: return "Left";
    case Keyboard::Right: return "Right";
    case Keyboard::Up: return "Up";
    case Keyboard::Down: return "Down";
    default: return "Unknown";
    }
}

Keyboard::Key stringToKey(string s) { //for loading key bindings
    if (s == "A") return Keyboard::A;
    if (s == "B") return Keyboard::B;
    if (s == "C") return Keyboard::C;
    if (s == "D") return Keyboard::D;
    if (s == "E") return Keyboard::E;
    if (s == "F") return Keyboard::F;
    if (s == "G") return Keyboard::G;
    if (s == "H") return Keyboard::H;
    if (s == "I") return Keyboard::I;
    if (s == "J") return Keyboard::J;
    if (s == "K") return Keyboard::K;
    if (s == "L") return Keyboard::L;
    if (s == "M") return Keyboard::M;
    if (s == "N") return Keyboard::N;
    if (s == "O") return Keyboard::O;
    if (s == "P") return Keyboard::P;
    if (s == "Q") return Keyboard::Q;
    if (s == "R") return Keyboard::R;
    if (s == "S") return Keyboard::S;
    if (s == "T") return Keyboard::T;
    if (s == "U") return Keyboard::U;
    if (s == "V") return Keyboard::V;
    if (s == "W") return Keyboard::W;
    if (s == "X") return Keyboard::X;
    if (s == "Y") return Keyboard::Y;
    if (s == "Z") return Keyboard::Z;
    if (s == "0") return Keyboard::Num0;
    if (s == "1") return Keyboard::Num1;
    if (s == "2") return Keyboard::Num2;
    if (s == "3") return Keyboard::Num3;
    if (s == "4") return Keyboard::Num4;
    if (s == "5") return Keyboard::Num5;
    if (s == "6") return Keyboard::Num6;
    if (s == "7") return Keyboard::Num7;
    if (s == "8") return Keyboard::Num8;
    if (s == "9") return Keyboard::Num9;
    if (s == "Escape") return Keyboard::Escape;
    if (s == "Left-Control") return Keyboard::LControl;
    if (s == "Left-Shift") return Keyboard::LShift;
    if (s == "Left-Alt") return Keyboard::LAlt;
    if (s == "Right-Control") return Keyboard::RControl;
    if (s == "Right-Shift") return Keyboard::RShift;
    if (s == "Right-Alt") return Keyboard::RAlt;
    if (s == "Space") return Keyboard::Space;
    if (s == "Left") return Keyboard::Left;
    if (s == "Right") return Keyboard::Right;
    if (s == "Up") return Keyboard::Up;
    if (s == "Down") return Keyboard::Down;
    return Keyboard::Unknown;
}

string ColorToString(Color color) {
    char hex[16];
    sprintf_s(hex, "%02X%02X%02X%02X", color.r, color.g, color.b, color.a);
    string ret(hex);
    return ret;
}

Color stringToColor(string inp) {
    //return Color::Black;
    //Clean up the string
    string s = "";
    for (int i = 0; i < inp.size(); i++)
        if ((inp[i] >= '0' && inp[i] <= '9') || (inp[i] >= 'a' && inp[i] <= 'f') || (inp[i] >= 'A' && inp[i] <= 'F'))
            s += inp[i];
    for (int i = s.size(); i < 8; i++)
        s += "F";
    Color color;
    color.r = stoi(s.substr(0, 2), nullptr, 16);
    color.g = stoi(s.substr(2, 2), nullptr, 16);
    color.b = stoi(s.substr(4, 2), nullptr, 16);
    color.a = stoi(s.substr(6, 2), nullptr, 16);
    return color;
}

bool isColorFormat(string s) {
    if (s.size() != 8)
        return false;
    for (int i = 0; i < s.size(); i++)
        if (!((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f') || (s[i] >= 'A' && s[i] <= 'F')))
            return false;
    return true;

}

int getSelectedSceneId() {
    if (Game::getCurrentScene() == NULL)
        return -1;
    return Game::getCurrentScene()->getId();
}

void makeObj(GameObject& ob, const Vector2f& position, float sideLen) { //make a square object
    ob.setPointCount(4);
    ob.setPoint(0, Vector2f(0, 0));
    ob.setPoint(1, Vector2f(sideLen, 0));
    ob.setPoint(2, Vector2f(sideLen, sideLen));
    ob.setPoint(3, Vector2f(0, sideLen));
    ob.setOrigin(ob.getGlobalBounds().getSize() / 2.f);
    ob.setPosition(position);
    ob.makeSquareCollider(sideLen);
}

void changeSelectedIsMovable() { //change if the selected object is movable
    cout << "FUnction called\n";
    Game::getCurrentScene()->changeSelectedIsMovable();
}

Text* updateHierarchy(Text* objectTexts, const RectangleShape& hierarchy, const Font& font, const Text& hierarchyTitle) { //update the hierarchy window
    if (objectTexts)
        delete[] objectTexts;
    const vector<GameObject*>& objects = Game::getCurrentScene()->getObjects();
    objectTexts = new Text[objects.size()];
    float objectHeight = (hierarchy.getSize().y - hierarchyTitle.getCharacterSize() * 2) / objects.size();
    for (int i = 0; i < objects.size(); i++) {
        objectTexts[i].setFont(font); //Fake warning
        objectTexts[i].setCharacterSize(15);
        objectTexts[i].setFillColor(Color::White);
        objectTexts[i].setString(objects[i]->getName());
        objectTexts[i].setPosition(hierarchy.getPosition().x + 10, hierarchy.getPosition().y + i * objectHeight + hierarchyTitle.getCharacterSize() + 10);
    }
    return objectTexts;
}

void createObj() { //Create object function (it is called when the create object button is clicked)
    GameObject* ob = new GameObject();
    makeObj(*ob, Vector2f(400, 100), 100.f);
    Game::getCurrentScene()->addObject(ob);
    delete ob;
}

void deleteObj() { //Delete object function (it is called when the delete object button is clicked)
    Game::getHierarchy()->deleteText(Game::getCurrentScene()->getSelectedObjectIndex());
    Game::getCurrentScene()->removeSelectedObject();
}

void addTextToHierarchy(const string& text) { //Add text to hierarchy function
    Text* tmp = new Text(text, *Game::getFont(), 15);
    Game::getHierarchy()->addText(*tmp);
    delete tmp;
}

void removeTextFromHierarchy(int index) { //Remove text from hierarchy function
    if (index < Game::getHierarchy()->getTextCount() && index >= 0)
        Game::getHierarchy()->deleteText(index);
}


GameObject* makeObjFromString(const string& obj) { //Make object from string function (used to know which variant of GameObject to create when reading a scene from a file)
    return new GameObject();
}

BehaviourScript* makeScriptFromString(const string& script) { //Make script from string function (used to know which variant of BehaviourScript to create when reading a scene from a file)
	if (script == "TestScript")
		return new TestScript();
	if (script == "FollowMouseScript")
		return new FollowMouseScript();
    throw runtime_error("Script not found");
}