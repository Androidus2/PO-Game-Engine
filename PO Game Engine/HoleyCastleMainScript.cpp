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
	maxHoles = 5;

	damageCostPerLevel = { 0, 100, 250, 400, 500 };
	sizeCostPerLevel = { 0, 100, 250, 400, 500 };
	holesCostPerLevel = { 0, 100, 250, 400, 500 };

	damageLevel = 0;
	sizeLevel = 0;
	holesLevel = 1;

	holeModelTag = "HoleModel";
	holeModel = nullptr;

	attributeCount = 5 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2 + maxHoles;
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
	if(index == 0)
		return holeModelTag;
	else if(index == 1)
		return floatToString(money, 0);
	else if(index == 2)
		return floatToString(damagePerLevel.size(), 0);
	else if(index >= 3 && index < 3 + damagePerLevel.size())
		return floatToString(damagePerLevel[index - 3]);
	else if(index >= 3 + damagePerLevel.size() && index < 3 + damagePerLevel.size() * 2)
		return floatToString(damageCostPerLevel[index - 3 - damagePerLevel.size()]);
	else if(index == 3 + damagePerLevel.size() * 2)
		return floatToString(sizePerLevel.size(), 0);
	else if(index >= 4 + damagePerLevel.size() * 2 && index < 4 + damagePerLevel.size() * 2 + sizePerLevel.size())
		return floatToString(sizePerLevel[index - 4 - damagePerLevel.size() * 2]);
	else if(index >= 4 + damagePerLevel.size() * 2 + sizePerLevel.size() && index < 4 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2)
		return floatToString(sizeCostPerLevel[index - 4 - damagePerLevel.size() * 2 - sizePerLevel.size()]);
	else if(index == 4 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2)
		return floatToString(maxHoles, 0);
	else if(index >= 5 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2 && index < maxHoles + 5 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2)
		return floatToString(holesCostPerLevel[index - 5 - damagePerLevel.size() * 2 - sizePerLevel.size() * 2]);
	return "";
}
void HoleyCastleMainScript::setAttribute(int index, string value) {
	if(index == 0)
		holeModelTag = value;
	else if (index == 1) {
		money = stoi(value);
		if (moneyText != nullptr)
			moneyText->setAttributeOnScripts(moneyText->scriptIndex("TextScript"), 0, "Money: " + value);
	}
	else if (index == 2) {
		damagePerLevel.resize(stoi(value));
		damageCostPerLevel.resize(stoi(value));
		attributeCount = 5 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2 + maxHoles;
		InspectorWindow* inspector = dynamic_cast<InspectorWindow*>(Game::getInspector());
		if (inspector)
			inspector->makeCustomFields();
	}
	else if (index >= 3 && index < 3 + damagePerLevel.size()) {
		damagePerLevel[index - 3] = stof(value);
	}
	else if (index >= 3 + damagePerLevel.size() && index < 3 + damagePerLevel.size() * 2) {
		damageCostPerLevel[index - 3 - damagePerLevel.size()] = stof(value);
	}
	else if (index == 3 + damagePerLevel.size() * 2) {
		sizePerLevel.resize(stoi(value));
		sizeCostPerLevel.resize(stoi(value));
		attributeCount = 5 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2 + maxHoles;
		InspectorWindow* inspector = dynamic_cast<InspectorWindow*>(Game::getInspector());
		if (inspector)
			inspector->makeCustomFields();
	}
	else if (index >= 4 + damagePerLevel.size() * 2 && index < 4 + damagePerLevel.size() * 2 + sizePerLevel.size()) {
		sizePerLevel[index - 4 - damagePerLevel.size() * 2] = stof(value);
	}
	else if (index >= 4 + damagePerLevel.size() * 2 + sizePerLevel.size() && index < 4 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2) {
		sizeCostPerLevel[index - 4 - damagePerLevel.size() * 2 - sizePerLevel.size()] = stof(value);
	}
	else if (index == 4 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2) {
		maxHoles = stoi(value);
		attributeCount = 5 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2 + maxHoles;
		InspectorWindow* inspector = dynamic_cast<InspectorWindow*>(Game::getInspector());
		if (inspector)
			inspector->makeCustomFields();
	}
	else if (index >= 5 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2 && index < maxHoles + 5 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2) {
		holesCostPerLevel[index - 5 - damagePerLevel.size() * 2 - sizePerLevel.size() * 2] = stof(value);
	}
}

string HoleyCastleMainScript::getScriptName() const {
	return "HoleyCastleMainScript";
}
int HoleyCastleMainScript::getAttributeType(int index) const {
	if (index == 0)
		return 0;
	else if (index == 1)
		return 1;
	else if (index == 2)
		return 3;
	else if(index >= 3 && index < 3 + damagePerLevel.size())
		return 1;
	else if(index >= 3 + damagePerLevel.size() && index < 3 + damagePerLevel.size() * 2)
		return 1;
	else if(index == 3 + damagePerLevel.size() * 2)
		return 3;
	else if(index >= 4 + damagePerLevel.size() * 2 && index < 4 + damagePerLevel.size() * 2 + sizePerLevel.size())
		return 1;
	else if(index >= 4 + damagePerLevel.size() * 2 + sizePerLevel.size() && index < 4 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2)
		return 1;
	else if(index == 4 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2)
		return 3;
	else if(index >= 5 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2 && index < maxHoles + 5 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2)
		return 1;
	return -1;
}
string HoleyCastleMainScript::getAttributeName(int index) const {
	if(index == 0)
		return "Hole Model Tag";
	else if(index == 1)
		return "Money";
	else if(index == 2)
		return "Damage Levels";
	else if(index >= 3 && index < 3 + damagePerLevel.size())
		return "Damage Level " + to_string(index - 2);
	else if(index >= 3 + damagePerLevel.size() && index < 3 + damagePerLevel.size() * 2)
		return "Damage Cost " + to_string(index - 2 - damagePerLevel.size());
	else if(index == 3 + damagePerLevel.size() * 2)
		return "Size Levels";
	else if(index >= 4 + damagePerLevel.size() * 2 && index < 4 + damagePerLevel.size() * 2 + sizePerLevel.size())
		return "Size Level " + to_string(index - 3 - damagePerLevel.size() * 2);
	else if(index >= 4 + damagePerLevel.size() * 2 + sizePerLevel.size() && index < 4 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2)
		return "Size Cost " + to_string(index - 3 - damagePerLevel.size() * 2 - sizePerLevel.size());
	else if(index == 4 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2)
		return "Max Holes";
	else if(index >= 5 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2 && index < maxHoles + 5 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2)
		return "Hole Cost " + to_string(index - 4 - damagePerLevel.size() * 2 - sizePerLevel.size() * 2);
	return "";
}

void HoleyCastleMainScript::read(istream& stream) {
	stream >> holeModelTag;
	stream >> money;
	stream >> damageLevel;
	stream >> sizeLevel;
	stream >> holesLevel;

	int size;
	stream >> size;
	damagePerLevel.resize(size);
	damageCostPerLevel.resize(size);
	for (int i = 0; i < size; i++)
		stream >> damagePerLevel[i];
	for (int i = 0; i < size; i++)
		stream >> damageCostPerLevel[i];

	stream >> size;
	sizePerLevel.resize(size);
	sizeCostPerLevel.resize(size);
	for (int i = 0; i < size; i++)
		stream >> sizePerLevel[i];
	for (int i = 0; i < size; i++)
		stream >> sizeCostPerLevel[i];

	stream >> maxHoles;
	holesCostPerLevel.resize(maxHoles);
	for (int i = 0; i < maxHoles; i++)
		stream >> holesCostPerLevel[i];
}
void HoleyCastleMainScript::write(ostream& stream) const {
	stream << holeModelTag << "\n";
	stream << money << "\n";
	stream << damageLevel << "\n";
	stream << sizeLevel << "\n";
	stream << holesLevel << "\n";

	stream << damagePerLevel.size() << " ";
	for (int i = 0; i < damagePerLevel.size(); i++)
		stream << damagePerLevel[i] << " ";
	for (int i = 0; i < damageCostPerLevel.size(); i++)
		stream<<damageCostPerLevel[i]<<" ";
	stream << "\n";

	stream << sizePerLevel.size() << " ";
	for (int i = 0; i < sizePerLevel.size(); i++)
		stream << sizePerLevel[i] << " ";
	for (int i = 0; i < sizeCostPerLevel.size(); i++)
		stream << sizeCostPerLevel[i] << " ";

	stream << maxHoles << " ";
	for (int i = 0; i < holesCostPerLevel.size(); i++)
		stream << holesCostPerLevel[i] << " ";
	stream << "\n";
}

HoleyCastleMainScript::~HoleyCastleMainScript() {
}