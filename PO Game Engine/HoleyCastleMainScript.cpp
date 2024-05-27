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

	attributeCount = 9 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2 + maxHoles;
	timeSinceLastHole = 0;

	moneyTextTag = "MoneyText";
	moneyText = nullptr;

	holesLeft = holesLevel;

	health = 100;

	healthTextTag = "HealthText";
	healthText = nullptr;
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

	healthText = Game::getCurrentScene()->getObjectByTag(healthTextTag);
}
void HoleyCastleMainScript::update(GameObject& object) {
	//cout<<holesLeft<<endl;
	if (moneyText != nullptr)
		moneyText->setAttributeOnScripts(moneyText->scriptIndex("TextScript"), 0, "Money: " + floatToString(money, 0));
	if (healthText != nullptr) {
		if (health > 0)
			healthText->setAttributeOnScripts(healthText->scriptIndex("TextScript"), 0, "Health: " + floatToString(health, 0));
		else
			healthText->setAttributeOnScripts(healthText->scriptIndex("TextScript"), 0, "Game Over");
	}
	timeSinceLastHole += Singleton<GameTime>::getInstance().getData().getDeltaTime();
	if (timeSinceLastHole >= 0.4f) {
		//cout<<"Enough time has passed"<<endl;
		if (Mouse::isButtonPressed(Mouse::Left) && Game::getIsOverGameWindow() && holesLeft > 0 && holeModel != nullptr) {
			timeSinceLastHole = 0;
			//cout<<"Mouse is pressed"<<endl;
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
			timeSinceLastHole = 0;
			holesLeft = holesLevel;
			GameObject* tmp;
			do {
				tmp = Game::getCurrentScene()->getObjectByTag("Hole");
				if (tmp != nullptr) {
					Game::getCurrentScene()->removeObjectById(tmp->getId());
				}
			} while (tmp != nullptr);
		}

		//if we pressed 1, try to upgrade damage
		if (Keyboard::isKeyPressed(Keyboard::Num1)) {
			if (damageLevel < damageCostPerLevel.size() - 1 && money >= damageCostPerLevel[damageLevel + 1]) {
				timeSinceLastHole = 0;
				money -= damageCostPerLevel[damageLevel + 1];
				damageLevel++;
			}
		}

		//if we pressed 2, try to upgrade size
		if (Keyboard::isKeyPressed(Keyboard::Num2)) {
			if (sizeLevel < sizeCostPerLevel.size() - 1 && money >= sizeCostPerLevel[sizeLevel + 1]) {
				timeSinceLastHole = 0;
				money -= sizeCostPerLevel[sizeLevel + 1];
				sizeLevel++;

				GameObject* tmp;

				vector<GameObject*> modifiedObjects;
				do {
					tmp = Game::getCurrentScene()->getObjectByTag("Hole");
					if (tmp != nullptr) {
						tmp->setScale(sizePerLevel[sizeLevel], sizePerLevel[sizeLevel]);
						modifiedObjects.push_back(tmp);
						tmp->setTag("HoleScaled");
					}
				} while (tmp != nullptr);

				for (int i = 0; i < modifiedObjects.size(); i++)
					modifiedObjects[i]->setTag("Hole");
			}
		}

		//if we pressed 3, try to upgrade holes amount
		if (Keyboard::isKeyPressed(Keyboard::Num3)) {
			if (holesLevel < holesCostPerLevel.size() - 1 && money >= holesCostPerLevel[holesLevel + 1]) {
				timeSinceLastHole = 0;
				money -= holesCostPerLevel[holesLevel + 1];
				holesLevel++;
				holesLeft = holesLevel;
			}
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
	if (index == 0)
		return holeModelTag;
	else if (index == 1)
		return floatToString(money, 0);
	else if (index == 2)
		return floatToString(damageLevel, 0);
	else if (index == 3)
		return floatToString(sizeLevel, 0);
	else if (index == 4)
		return floatToString(holesLevel, 0);
	else if (index == 5)
		return floatToString(damagePerLevel.size(), 0);
	else if (index >= 6 && index < 6 + damagePerLevel.size())
		return floatToString(damagePerLevel[index - 6]);
	else if (index >= 6 + damagePerLevel.size() && index < 6 + damagePerLevel.size() * 2)
		return floatToString(damageCostPerLevel[index - 6 - damagePerLevel.size()]);
	else if (index == 6 + damagePerLevel.size() * 2)
		return floatToString(sizePerLevel.size(), 0);
	else if (index >= 7 + damagePerLevel.size() * 2 && index < 7 + damagePerLevel.size() * 2 + sizePerLevel.size())
		return floatToString(sizePerLevel[index - 7 - damagePerLevel.size() * 2]);
	else if (index >= 7 + damagePerLevel.size() * 2 + sizePerLevel.size() && index < 7 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2)
		return floatToString(sizeCostPerLevel[index - 7 - damagePerLevel.size() * 2 - sizePerLevel.size()]);
	else if (index == 7 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2)
		return floatToString(maxHoles, 0);
	else if (index >= 8 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2 && index < maxHoles + 8 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2)
		return floatToString(holesCostPerLevel[index - 8 - damagePerLevel.size() * 2 - sizePerLevel.size() * 2]);
	else if(index == 8 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2 + maxHoles)
		return floatToString(health);
	return "";
}
void HoleyCastleMainScript::setAttribute(int index, string value) {
	if (index == 0)
		holeModelTag = value;
	else if (index == 1) {
		money = stoi(value);
		//if (moneyText != nullptr)
		//	moneyText->setAttributeOnScripts(moneyText->scriptIndex("TextScript"), 0, "Money: " + value);
	}
	else if (index == 2)
		damageLevel = stoi(value);
	else if (index == 3)
		sizeLevel = stoi(value);
	else if (index == 4)
		holesLevel = stoi(value);
	else if (index == 5) {
		damagePerLevel.resize(stoi(value));
		damageCostPerLevel.resize(stoi(value));
		attributeCount = 9 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2 + maxHoles;
		InspectorWindow* inspector = dynamic_cast<InspectorWindow*>(Game::getInspector());
		if (inspector)
			inspector->makeCustomFields();
	}
	else if (index >= 6 && index < 6 + damagePerLevel.size()) {
		damagePerLevel[index - 6] = stof(value);
	}
	else if (index >= 6 + damagePerLevel.size() && index < 6 + damagePerLevel.size() * 2) {
		damageCostPerLevel[index - 6 - damagePerLevel.size()] = stof(value);
	}
	else if (index == 6 + damagePerLevel.size() * 2) {
		sizePerLevel.resize(stoi(value));
		sizeCostPerLevel.resize(stoi(value));
		attributeCount = 9 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2 + maxHoles;
		InspectorWindow* inspector = dynamic_cast<InspectorWindow*>(Game::getInspector());
		if (inspector)
			inspector->makeCustomFields();
	}
	else if (index >= 7 + damagePerLevel.size() * 2 && index < 7 + damagePerLevel.size() * 2 + sizePerLevel.size()) {
		sizePerLevel[index - 7 - damagePerLevel.size() * 2] = stof(value);
	}
	else if (index >= 7 + damagePerLevel.size() * 2 + sizePerLevel.size() && index < 7 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2) {
		sizeCostPerLevel[index - 7 - damagePerLevel.size() * 2 - sizePerLevel.size()] = stof(value);
	}
	else if (index == 7 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2) {
		maxHoles = stoi(value);
		attributeCount = 9 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2 + maxHoles;
		InspectorWindow* inspector = dynamic_cast<InspectorWindow*>(Game::getInspector());
		if (inspector)
			inspector->makeCustomFields();
	}
	else if (index >= 8 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2 && index < maxHoles + 8 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2) {
		holesCostPerLevel[index - 8 - damagePerLevel.size() * 2 - sizePerLevel.size() * 2] = stof(value);
	}
	else if(index == 8 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2 + maxHoles)
		health = stof(value);
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
	else if (index == 3)
		return 3;
	else if (index == 4)
		return 3;
	else if (index == 5)
		return 3;
	else if (index >= 6 && index < 6 + damagePerLevel.size())
		return 1;
	else if (index >= 6 + damagePerLevel.size() && index < 6 + damagePerLevel.size() * 2)
		return 1;
	else if (index == 6 + damagePerLevel.size() * 2)
		return 3;
	else if (index >= 7 + damagePerLevel.size() * 2 && index < 7 + damagePerLevel.size() * 2 + sizePerLevel.size())
		return 1;
	else if (index >= 7 + damagePerLevel.size() * 2 + sizePerLevel.size() && index < 7 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2)
		return 1;
	else if (index == 7 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2)
		return 3;
	else if (index >= 8 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2 && index < maxHoles + 8 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2)
		return 1;
	else if(index == 8 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2 + maxHoles)
		return 1;
	return -1;
}
string HoleyCastleMainScript::getAttributeName(int index) const {
	if (index == 0)
		return "Hole Model Tag";
	else if (index == 1)
		return "Money";
	else if (index == 2)
		return "Damage Level";
	else if (index == 3)
		return "Size Level";
	else if (index == 4)
		return "Holes Level";
	else if (index == 5)
		return "Damage Levels";
	else if (index >= 6 && index < 6 + damagePerLevel.size())
		return "Damage Level " + to_string(index - 5);
	else if (index >= 6 + damagePerLevel.size() && index < 6 + damagePerLevel.size() * 2)
		return "Damage Cost " + to_string(index - 6 - damagePerLevel.size());
	else if (index == 6 + damagePerLevel.size() * 2)
		return "Size Levels";
	else if (index >= 7 + damagePerLevel.size() * 2 && index < 7 + damagePerLevel.size() * 2 + sizePerLevel.size())
		return "Size Level " + to_string(index - 6 - damagePerLevel.size() * 2);
	else if (index >= 7 + damagePerLevel.size() * 2 + sizePerLevel.size() && index < 7 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2)
		return "Size Cost " + to_string(index - 6 - damagePerLevel.size() * 2 - sizePerLevel.size());
	else if (index == 7 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2)
		return "Max Holes";
	else if (index >= 8 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2 && index < maxHoles + 8 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2)
		return "Hole Cost " + to_string(index - 7 - damagePerLevel.size() * 2 - sizePerLevel.size() * 2);
	else if(index == 8 + damagePerLevel.size() * 2 + sizePerLevel.size() * 2 + maxHoles)
		return "Health";
	return "";
}

void HoleyCastleMainScript::read(istream& stream) {
	stream.get();
	getline(stream, holeModelTag);
	stream >> money;
	stream >> damageLevel;
	stream >> sizeLevel;
	stream >> holesLevel;

	stream >> health;
	stream.get();
	getline(stream, healthTextTag);

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

	stream << health << "\n";
	stream << healthTextTag << "\n";

	stream << damagePerLevel.size() << " ";
	for (int i = 0; i < damagePerLevel.size(); i++)
		stream << damagePerLevel[i] << " ";
	for (int i = 0; i < damageCostPerLevel.size(); i++)
		stream << damageCostPerLevel[i] << " ";
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