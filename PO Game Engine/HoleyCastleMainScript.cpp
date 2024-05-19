#include "HoleyCastleMainScript.h"
#include "Game.h"
#include "Singleton.h"
#include "GameTime.h"
#include "Utility.h"
#include "InspectorWindow.h"

using namespace std;
using namespace sf;

HoleyCastleMainScript::HoleyCastleMainScript() {
	money = 0;
	holesLeft = 1;

	damagePerLevel = { 100, 150, 200, 250, 300 };
	sizePerLevel = { 1, 1.5, 2, 2.5, 3 };
	maxHoles = 30;

	damageLevel = 0;
	sizeLevel = 0;
	holesLevel = 1;

	holeModelTag = "HoleModel";
	holeModel = nullptr;

	attributeCount = 5 + damagePerLevel.size() + sizePerLevel.size();
	timeSinceLastHole = 0;

	moneyTextTag = "MoneyText";
	moneyText = nullptr;
}

HoleyCastleMainScript* HoleyCastleMainScript::clone() const {
	return new HoleyCastleMainScript(*this);
}

void HoleyCastleMainScript::start(GameObject& object) {
	money = 0;
	damageLevel = 0;
	sizeLevel = 0;
	holesLevel = 1;
	holesLeft = holesLevel;
	timeSinceLastHole = 1;

	holeModel = Game::getCurrentScene()->getObjectByTag(holeModelTag);

	moneyText = Game::getCurrentScene()->getObjectByTag(moneyTextTag);
}
void HoleyCastleMainScript::update(GameObject& object) {
	//cout<<holesLeft<<endl;
	if (moneyText != nullptr)
		moneyText->setAttributeOnScripts(moneyText->scriptIndex("TextScript"), 0, floatToString(money, 0));
	timeSinceLastHole += Singleton<GameTime>::getInstance().getDeltaTime();
	if (timeSinceLastHole >= 1) {
		//cout<<"Enough time has passed"<<endl;
		if (Mouse::isButtonPressed(Mouse::Left) && Game::getIsOverGameWindow() && holesLeft > 0 && holeModel != nullptr) {
			//cout<<"Mouse is pressed"<<endl;
			timeSinceLastHole = 0;
			Vector2f mousePosition = Game::getWindow()->mapPixelToCoords(Mouse::getPosition(*Game::getWindow()), *Game::getGameView());
			//cout<<"Hole model found"<<endl;
			GameObject* hole = holeModel->clone();
			hole->setPosition(mousePosition);
			hole->setScale(sizePerLevel[sizeLevel], sizePerLevel[sizeLevel]);
			hole->changeId();
			hole->setTag("Hole");
			hole->setActive(true);
			Game::getCurrentScene()->addObject(hole);
			holesLeft--;
			delete hole;
		}
		//if we pressed space, reset the holes
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			holesLeft = holesLevel;
			GameObject* tmp;
			do {
				tmp = Game::getCurrentScene()->getObjectByTag("Hole");
				if (tmp != nullptr) {
					Game::getCurrentScene()->removeObjectById(tmp->getId());
				}
			} while (tmp != nullptr);
		}
	}

}
void HoleyCastleMainScript::collision(GameObject& object, GameObject& collisionObject) {
}
void HoleyCastleMainScript::trigger(GameObject& object, GameObject& triggerObject) {
}
void HoleyCastleMainScript::destroy(GameObject& object) {
}

void HoleyCastleMainScript::drawScriptElements(const GameObject& object) const {
}

string HoleyCastleMainScript::getAttribute(int index) const {
	switch (index) {
	case 0:
		return holeModelTag;
	case 1:
		return floatToString(money, 0);
	case 2:
		return floatToString(damagePerLevel.size(), 0);
	case 3:
		return floatToString(sizePerLevel.size(), 0);
	case 4:
		return floatToString(maxHoles, 0);
	default:
		if (index >= 5 && index < 5 + damagePerLevel.size()) {
			return floatToString(damagePerLevel[index - 5]);
		}
		else if (index >= 5 + damagePerLevel.size() && index < 5 + damagePerLevel.size() + sizePerLevel.size()) {
			return floatToString(sizePerLevel[index - 5 - damagePerLevel.size()]);
		}
		else {
			return "";
		}
	}
}
void HoleyCastleMainScript::setAttribute(int index, string value) {
	switch (index) {
	case 0:
		holeModelTag = value;
		break;
	case 1:
		money = stof(value);
		break;
	case 2:
		damagePerLevel.resize(stoi(value));
		break;
	case 3:
		sizePerLevel.resize(stoi(value));
		break;
	case 4:
		maxHoles = stoi(value);
		break;
	default:
		if (index >= 5 && index < 5 + damagePerLevel.size()) {
			damagePerLevel[index - 5] = stof(value);
		}
		else if (index >= 5 + damagePerLevel.size() && index < 5 + damagePerLevel.size() + sizePerLevel.size()) {
			sizePerLevel[index - 5 - damagePerLevel.size()] = stof(value);
		}
		break;
	}
}

string HoleyCastleMainScript::getScriptName() const {
	return "HoleyCastleMainScript";
}
int HoleyCastleMainScript::getAttributeType(int index) const {
	switch (index) {
	case 0:
		return 0;
	case 1:
	case 2:
	case 3:
	case 4:
		return 1;
	default:
		if (index >= 5 && index < 5 + damagePerLevel.size()) {
			return 1;
		}
		else if (index >= 5 + damagePerLevel.size() && index < 5 + damagePerLevel.size() + sizePerLevel.size()) {
			return 1;
		}
		else {
			return -1;
		}
	}
}
string HoleyCastleMainScript::getAttributeName(int index) const {
	switch (index) {
	case 0:
		return "Hole Model Tag";
	case 1:
		return "Money";
	case 2:
		return "Damage Levels";
	case 3:
		return "Size Levels";
	case 4:
		return "Max Holes";
	default:
		if (index >= 5 && index < 5 + damagePerLevel.size()) {
			return "Damage Level " + to_string(index - 5);
		}
		else if (index >= 5 + damagePerLevel.size() && index < 5 + damagePerLevel.size() + sizePerLevel.size()) {
			return "Size Level " + to_string(index - 5 - damagePerLevel.size());
		}
		else {
			return "";
		}
	}
}

void HoleyCastleMainScript::read(istream& stream) {
	stream.get();
	getline(stream, holeModelTag);
	stream >> money;
	stream >> maxHoles;
	stream >> damageLevel;
	stream >> sizeLevel;
	stream >> holesLevel;

	damagePerLevel.clear();
	sizePerLevel.clear();
	int damagePerLevelSize;
	int sizePerLevelSize;
	stream >> damagePerLevelSize;
	for (int i = 0; i < damagePerLevelSize; i++) {
		float damage;
		stream >> damage;
		damagePerLevel.push_back(damage);
	}
	stream >> sizePerLevelSize;
	for (int i = 0; i < sizePerLevelSize; i++) {
		float size;
		stream >> size;
		sizePerLevel.push_back(size);
	}
}
void HoleyCastleMainScript::write(ostream& stream) const {
	stream << holeModelTag << "\n";
	stream << money << "\n";
	stream << maxHoles << "\n";
	stream << damageLevel << "\n";
	stream << sizeLevel << "\n";
	stream << holesLevel << "\n";

	stream << damagePerLevel.size() << " ";
	for (int i = 0; i < damagePerLevel.size(); i++) {
		stream << damagePerLevel[i] << " ";
	}
	stream << "\n";

	stream << sizePerLevel.size() << " ";
	for (int i = 0; i < sizePerLevel.size(); i++) {
		stream << sizePerLevel[i] << " ";
	}
	stream << "\n";
}

HoleyCastleMainScript::~HoleyCastleMainScript() {
}