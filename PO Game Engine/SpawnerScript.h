#pragma once
#include "BehaviourScript.h"
#include <SFML/Graphics.hpp>
#include <vector>

class SpawnerScript : public BehaviourScript
{
private:
	sf::Vector2f minPosition;
	sf::Vector2f maxPosition;
	std::vector<std::string> entityTags;
	std::vector<int> entityCounts;
	float spawnRate; //how many entities to spawn per second

	float timeSinceLastSpawn;

	std::vector<GameObject*> entitiesReference;
public:
	SpawnerScript();
	SpawnerScript* clone() const override;

	void start(GameObject& object);
	void update(GameObject& object);
	void collision(GameObject& object, GameObject& collisionObject);
	void trigger(GameObject& object, GameObject& triggerObject);
	void destroy(GameObject& object);

	void drawScriptElements(const GameObject& object) const;

	std::string getAttribute(int index) const;
	void setAttribute(int index, std::string value);

	std::string getScriptName() const;

	int getAttributeType(int index) const;
	std::string getAttributeName(int index) const;

	void read(std::istream& stream);
	void write(std::ostream& stream) const;

	~SpawnerScript();
};