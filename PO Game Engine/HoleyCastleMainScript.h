#pragma once
#include "BehaviourScript.h"
#include "GameObject.h"
#include <vector>

class HoleyCastleMainScript : public BehaviourScript {
private:
	int money;
	int holesLeft;

	std::vector<float> damagePerLevel;
	std::vector<float> sizePerLevel;
	int maxHoles;

	int damageLevel;
	int sizeLevel;
	int holesLevel;

	std::string holeModelTag;
	GameObject* holeModel;

	std::string moneyTextTag;
	GameObject* moneyText;

	float timeSinceLastHole;

public:
	HoleyCastleMainScript();
	HoleyCastleMainScript* clone() const override;

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

	~HoleyCastleMainScript();
};