#include "HoleyCastleEnemyScript.h"
#include "Game.h"
#include "Singleton.h"
#include "GameTime.h"
#include "Utility.h"

using namespace std;
using namespace sf;

HoleyCastleEnemyScript::HoleyCastleEnemyScript() {
	speed = 100;
	health = 100;
	damage = 5;
	moneyOnDeath = 10;
	holeyCastleTag = "HoleyCastle";
	attributeCount = 5;
}

HoleyCastleEnemyScript* HoleyCastleEnemyScript::clone() const {
	return new HoleyCastleEnemyScript(*this);
}

void HoleyCastleEnemyScript::start(GameObject& object) {
	object.setVelocity(speed, 0);
}
void HoleyCastleEnemyScript::update(GameObject& object) {
}
void HoleyCastleEnemyScript::collision(GameObject& object, GameObject& collisionObject) {
}
void HoleyCastleEnemyScript::trigger(GameObject& object, GameObject& triggerObject) {
	//Check for the collision
	if (triggerObject.getTag() == "Hole") {
		//Check if the object has already collided with this object
		if (collisionIds.find(triggerObject.getId()) == collisionIds.end()) {
			//Add the object to the collisionIds set
			collisionIds.insert(triggerObject.getId());
			//Decrease the health of the object
			GameObject* mainScriptObject = Game::getCurrentScene()->getObjectByTag(holeyCastleTag);
			if (mainScriptObject != nullptr) {
				int dmgLevel = stoi(mainScriptObject->getAttributeFromScripts(mainScriptObject->scriptIndex("HoleyCastleMainScript"), 2));
				float damage = stof(mainScriptObject->getAttributeFromScripts(mainScriptObject->scriptIndex("HoleyCastleMainScript"), 6 + dmgLevel));
				health -= damage;
			};
			//Check if the health is less than or equal to 0
			if (health <= 0) {
				//Destroy the object
				
				if (mainScriptObject != nullptr) {
					mainScriptObject->setAttributeOnScripts(mainScriptObject->scriptIndex("HoleyCastleMainScript"), 1, floatToString(stof(mainScriptObject->getAttributeFromScripts(mainScriptObject->scriptIndex("HoleyCastleMainScript"), 1)) + moneyOnDeath));
				}
				Game::getCurrentScene()->removeObjectById(object.getId());
			}
		}
	}

	if (triggerObject.getTag() == "Castle") {
		if(collisionIds.find(triggerObject.getId()) == collisionIds.end()) {
			collisionIds.insert(triggerObject.getId());
			GameObject* mainScriptObject = Game::getCurrentScene()->getObjectByTag(holeyCastleTag);
			if(mainScriptObject != nullptr) {
				int mainScriptAttributeCount = mainScriptObject->getAttributeCountFromScripts(mainScriptObject->scriptIndex("HoleyCastleMainScript"));
				mainScriptObject->setAttributeOnScripts(mainScriptObject->scriptIndex("HoleyCastleMainScript"), mainScriptAttributeCount - 1, floatToString(stof(mainScriptObject->getAttributeFromScripts(mainScriptObject->scriptIndex("HoleyCastleMainScript"), mainScriptAttributeCount - 1)) - damage));
				Game::getCurrentScene()->removeObjectById(object.getId());
			}
		}
	}
}
void HoleyCastleEnemyScript::destroy(GameObject& object) {
}

void HoleyCastleEnemyScript::drawScriptElements(const GameObject& object) const {
}

string HoleyCastleEnemyScript::getAttribute(int index) const {
	switch (index) {
	case 0:
		return floatToString(speed);
	case 1:
		return floatToString(health);
	case 2:
		return floatToString(damage);
	case 3:
		return floatToString(moneyOnDeath, 0);
	case 4:
		return holeyCastleTag;
	default:
		return "";
	}
}
void HoleyCastleEnemyScript::setAttribute(int index, string value) {
	switch (index) {
	case 0:
		speed = stof(value);
		break;
	case 1:
		health = stof(value);
		break;
	case 2:
		damage = stof(value);
		break;
	case 3:
		moneyOnDeath = stoi(value);
		break;
	case 4:
		holeyCastleTag = value;
		break;
	}
}

string HoleyCastleEnemyScript::getScriptName() const {
	return "HoleyCastleEnemyScript";
}
int HoleyCastleEnemyScript::getAttributeType(int index) const {
	switch (index) {
	case 0:
	case 1:
	case 2:
		return 1;
	case 3:
		return 3;
	case 4:
		return 0;
	default:
		return -1;
	}
}
string HoleyCastleEnemyScript::getAttributeName(int index) const {
	switch (index) {
	case 0:
		return "Speed";
	case 1:
		return "Health";
	case 2:
		return "Damage";
	case 3:
		return "Money On Death";
	case 4:
		return "Holey Castle Tag";
	default:
		return "";
	}
}

void HoleyCastleEnemyScript::read(istream& stream) {
	stream >> speed >> health >> damage >> moneyOnDeath;
	stream.get();
	getline(stream, holeyCastleTag);
}
void HoleyCastleEnemyScript::write(ostream& stream) const {
	stream << speed << " " << health << " " << damage << " " << moneyOnDeath << "\n";
	stream << holeyCastleTag << "\n";
}

HoleyCastleEnemyScript::~HoleyCastleEnemyScript() {
}