#pragma once
#include "BehaviourScript.h"

class PongBallScript : public BehaviourScript {
private:
	std::string palleteTag;
	std::string endTag;
	std::string scoreTextTag;

	float speed;

	GameObject* scoreObject;
	int scoreObjectTextScriptIndex;

	int player1Score;
	int player2Score;

public:
	PongBallScript();
	PongBallScript* clone() const override;

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

	~PongBallScript();
};