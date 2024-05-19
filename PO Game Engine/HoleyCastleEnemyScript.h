#pragma once
#include "BehaviourScript.h"
#include "GameObject.h"
#include <set>

class HoleyCastleEnemyScript : public BehaviourScript {
private:
	float speed;
	float health;
	float damage;

	int moneyOnDeath;

	std::string holeyCastleTag;

	std::set<int> collisionIds; //ids of objects that have already collided with this object
public:
	HoleyCastleEnemyScript();
	HoleyCastleEnemyScript* clone() const override;

	void start(GameObject& object) override;
	void update(GameObject& object) override;
	void collision(GameObject& object, GameObject& collisionObject) override;
	void trigger(GameObject& object, GameObject& collisionObject) override;
	void destroy(GameObject& object) override;

	void drawScriptElements(const GameObject& object) const override;

	std::string getAttribute(int index) const override;
	void setAttribute(int index, std::string value) override;

	std::string getScriptName() const override;

	int getAttributeType(int index) const override;
	std::string getAttributeName(int index) const override;

	void read(std::istream& stream) override;
	void write(std::ostream& stream) const override;

	~HoleyCastleEnemyScript();
};