#include "SpawnerScript.h"
#include "Game.h"
#include "Singleton.h"
#include "GameTime.h"
#include "Utility.h"
#include "InspectorWindow.h"

using namespace std;
using namespace sf;

SpawnerScript::SpawnerScript() {
	minPosition = Vector2f(0, 0);
	maxPosition = Vector2f(0, 0);
	spawnRate = 1;
	timeSinceLastSpawn = 0;
	attributeCount = 6;
}
SpawnerScript* SpawnerScript::clone() const {
	return new SpawnerScript(*this);
}

void SpawnerScript::start(GameObject& object) {
	//initialize the entities reference
	for (int i = 0; i < entityTags.size(); i++) {
		entitiesReference.push_back(Game::getCurrentScene()->getObjectByTag(entityTags[i]));
	}
	timeSinceLastSpawn = 0;
}
void SpawnerScript::update(GameObject& object) {
	//spawn entities
	timeSinceLastSpawn += Singleton<GameTime>::getInstance().getDeltaTime();
	if (timeSinceLastSpawn >= 1 / spawnRate) {
		timeSinceLastSpawn = 0;
		bool ok = true;
		for (int i = 0; i < entityTags.size(); i++) {
			if(entitiesReference[i] == nullptr || !ok)
				continue;
			for (int j = 0; j < entityCounts[i]; j++) {
				GameObject* entity = entitiesReference[i]->clone();
				int maxX = (maxPosition.x - minPosition.x);
				int maxY = (maxPosition.y - minPosition.y);
				if(maxX != 0)
					maxX = rand() % maxX;
				if(maxY != 0)
					maxY = rand() % maxY;
				entity->setPosition(Vector2f(maxX + minPosition.x, maxY + minPosition.y));
				Game::getCurrentScene()->addObject(entity);
				delete entity;
				entityCounts[i]--;
				ok = false;
			}
		}
	}
}
void SpawnerScript::collision(GameObject& object, GameObject& collisionObject) {
}
void SpawnerScript::trigger(GameObject& object, GameObject& triggerObject) {
}
void SpawnerScript::destroy(GameObject& object) {
}

void SpawnerScript::drawScriptElements(const GameObject& object) const {
}

string SpawnerScript::getAttribute(int index) const {
	if (index == 0) {
		return floatToString(minPosition.x);
	}
	else if (index == 1) {
		return floatToString(minPosition.y);
	}
	else if (index == 2) {
		return floatToString(maxPosition.x);
	}
	else if (index == 3) {
		return floatToString(maxPosition.y);
	}
	else if (index == 4) {
		return floatToString(spawnRate);
	}
	else if (index == 5) {
		return floatToString(entityTags.size(), 0);
	}
	else {
		int cnt = 6;
		for (int i = 0; i < entityTags.size(); i++) {
			if (index == cnt) {
				return entityTags[i];
			}
			cnt++;
		}
		for (int i = 0; i < entityCounts.size(); i++) {
			if (index == cnt) {
				return floatToString(entityCounts[i], 0);
			}
			cnt++;
		}
		return "";
	}
}
void SpawnerScript::setAttribute(int index, string value) {
	if (index == 0) {
		minPosition.x = stof(value);
	}
	else if (index == 1) {
		minPosition.y = stof(value);
	}
	else if (index == 2) {
		maxPosition.x = stof(value);
	}
	else if (index == 3) {
		maxPosition.y = stof(value);
	}
	else if (index == 4) {
		spawnRate = stof(value);
	}
	else if (index == 5) {
		int size = stoi(value);
		if(size < 0)
			size = 0;
		if(size == entityTags.size())
			return;
		//Remove the extra tags
		if (entityTags.size() > size) {
			entityTags.erase(entityTags.begin() + size, entityTags.end());
		}
		if (entityCounts.size() > size)
			entityCounts.erase(entityCounts.begin() + size, entityCounts.end());
		//Add the new tags
		for (int i = entityTags.size(); i < size; i++) {
			entityTags.push_back("");
		}
		for (int i = entityCounts.size(); i < size; i++) {
			entityCounts.push_back(1);
		}
		attributeCount = 6 + entityTags.size() + entityCounts.size();
		InspectorWindow* inspector = dynamic_cast<InspectorWindow*>(Game::getInspector());
		if (inspector) {
			inspector->makeCustomFields();
		}
	}
	else {
		int cnt = 6;
		for (int i = 0; i < entityTags.size(); i++) {
			if (index == cnt) {
				entityTags[i] = value;
				return;
			}
			cnt++;
		}
		for (int i = 0; i < entityCounts.size(); i++) {
			if (index == cnt) {
				entityCounts[i] = stoi(value);
				return;
			}
			cnt++;
		}
	}
}

string SpawnerScript::getScriptName() const {
	return "SpawnerScript";
}
int SpawnerScript::getAttributeType(int index) const {
	if (index == 0 || index == 2)
		return 5;
	else if (index == 1 || index == 3)
		return 6;
	if (index == 4) {
		return 1;
	}
	else if (index == 5) {
		return 3;
	}
	else {
		int cnt = 6;
		for (int i = 0; i < entityTags.size(); i++) {
			if (index == cnt) {
				return 0;
			}
			cnt++;
		}
		for (int i = 0; i < entityCounts.size(); i++) {
			if (index == cnt) {
				return 1;
			}
			cnt++;
		}
	}
}
string SpawnerScript::getAttributeName(int index) const {
	if (index == 0) {
		return "Min Position";
	}
	else if (index == 1) {
		return "Min Position";
	}
	else if (index == 2) {
		return "Max Position";
	}
	else if (index == 3) {
		return "Max Position";
	}
	else if (index == 4) {
		return "Spawn Rate";
	}
	else if (index == 5) {
		return "Entity Tags Size";
	}
	else {
		int cnt = 6;
		for (int i = 0; i < entityTags.size(); i++) {
			if (index == cnt) {
				return "Entity Tag " + to_string(i);
			}
			cnt++;
		}
		for (int i = 0; i < entityCounts.size(); i++) {
			if (index == cnt) {
				return "Entity Count " + to_string(i);
			}
			cnt++;
		}
	}
}

void SpawnerScript::read(istream& stream) {
	stream >> minPosition.x >> minPosition.y >> maxPosition.x >> maxPosition.y >> spawnRate;
	int size;
	stream >> size;
	entityTags.clear();
	entityCounts.clear();
	for (int i = 0; i < size; i++) {
		string tag;
		stream.get();
		getline(stream, tag);
		entityTags.push_back(tag);
		int count;
		stream >> count;
		entityCounts.push_back(count);
	}
	attributeCount = 6 + entityTags.size() + entityCounts.size();
}
void SpawnerScript::write(ostream& stream) const {
	stream << minPosition.x << " " << minPosition.y << "\n" << maxPosition.x << " " << maxPosition.y << "\n" << spawnRate << "\n" << entityTags.size() << "\n";
	for (int i = 0; i < entityTags.size(); i++) {
		stream << entityTags[i] << "\n" << entityCounts[i] << "\n";
	}
}

SpawnerScript::~SpawnerScript() {
}