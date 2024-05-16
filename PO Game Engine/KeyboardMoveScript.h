#pragma once
#include "BehaviourScript.h"
#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"
#include "DebugMacro.h"

class KeyboardMoveScript : public BehaviourScript
{
private:
	sf::Vector2f moveSpeed;
	sf::Keyboard::Key upKey;
	sf::Keyboard::Key downKey;
	sf::Keyboard::Key leftKey;
	sf::Keyboard::Key rightKey;
public:
	KeyboardMoveScript();
	KeyboardMoveScript* clone() const;

	void start(GameObject& gameObject);
	void update(GameObject& gameObject);
	void collision(GameObject& gameObject, GameObject& collisionObject);
	void trigger(GameObject& gameObject, GameObject& triggerObject);
	void destroy(GameObject& gameObject);

	void drawScriptElements(const GameObject& gameObject) const;

	std::string getAttribute(int index) const;
	void setAttribute(int index, std::string value);

	std::string getScriptName() const;

	int getAttributeType(int index) const;
	std::string getAttributeName(int index) const;

	void read(std::istream& stream);
	void write(std::ostream& stream) const;

	~KeyboardMoveScript();
};