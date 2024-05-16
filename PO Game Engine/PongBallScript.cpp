#include "PongBallScript.h"
#include "GameObject.h"
#include "Utility.h"
#include "DebugMacro.h"
#include "Game.h"

using namespace std;
using namespace sf;

PongBallScript::PongBallScript() {
	palleteTag = "Paleta";
	endTag = "End";
	scoreTextTag = "ScoreText";
	player1Score = 0;
	player2Score = 0;
	speed = 200;
	attributeCount = 4;
	scoreObject = nullptr;
	scoreObjectTextScriptIndex = -1;
}

PongBallScript* PongBallScript::clone() const {
	return new PongBallScript(*this);
}

void PongBallScript::start(GameObject& object) {
	object.setVelocity(speed, 0);
	cout<<"PongBallScript started " << object.getVelocity().x<<endl;
	Scene* sc = Game::getCurrentScene();
	if (sc) {
		scoreObject = sc->getObjectByTag(scoreTextTag);
		if (scoreObject) {
			scoreObjectTextScriptIndex = scoreObject->scriptIndex("TextScript");
		}
	}
}
void PongBallScript::update(GameObject& object) {
}
void PongBallScript::collision(GameObject& object, GameObject& collisionObject) {
	
}
void PongBallScript::trigger(GameObject& object, GameObject& triggerObject) {
	if (triggerObject.getTag() == palleteTag) {
		if(object.getVelocity().x > 0 && object.getPosition().x > triggerObject.getPosition().x)
			return;
		if (object.getVelocity().x < 0 && object.getPosition().x < triggerObject.getPosition().x)
			return;
		float relativeIntersectionY = -object.getPosition().y + triggerObject.getPosition().y;
		float normalizedRelativeIntersectionY = relativeIntersectionY / (object.getScale().y * 300);

		float bounceAngle = normalizedRelativeIntersectionY * 5.f * 3.1415926f / 12.f;

		Vector2f newVelocity = Vector2f(-cos(bounceAngle) * speed, -sin(bounceAngle) * speed);

		if(object.getVelocity().x < 0)
			newVelocity.x *= -1;

		/*newVelocity.x *= speed;
		newVelocity.y *= speed;*/

		object.setVelocity(newVelocity);
	}
	else if (triggerObject.getTag() == endTag) {
		Vector2f ballPosition = object.getPosition();
		Vector2f endPosition = triggerObject.getPosition();
		Vector2f endSize = triggerObject.getScale();

		float ballX = ballPosition.x;
		float endX = endPosition.x;
		float endWidth = endSize.x;

		object.setPosition(0, 0);
		if (ballX < endX) {
			player1Score++;
			object.setVelocity(-speed, 0);
		}
		else {
			player2Score++;
			object.setVelocity(speed, 0);
		}

		if (scoreObject && scoreObjectTextScriptIndex != -1) {
			scoreObject->setAttributeOnScripts(scoreObjectTextScriptIndex, 0, to_string(player1Score) + " - " + to_string(player2Score));
		}

	}
	else {
		if(object.getVelocity().y > 0 && object.getPosition().y > triggerObject.getPosition().y)
			return;
		if (object.getVelocity().y < 0 && object.getPosition().y < triggerObject.getPosition().y)
			return;
		Vector2f newVelocity = object.getVelocity();
		newVelocity.y *= -1;
		object.setVelocity(newVelocity);
	}

}
void PongBallScript::destroy(GameObject& object) {
}

void PongBallScript::drawScriptElements(const GameObject& object) const {
}

string PongBallScript::getAttribute(int index) const {
	switch (index) {
	case 0:
		return palleteTag;
	case 1:
		return endTag;
	case 2:
		return scoreTextTag;
	case 3:
		return floatToString(speed);
	default:
		return "";
	}
}
void PongBallScript::setAttribute(int index, string value) {
	switch (index) {
	case 0:
		palleteTag = value;
		break;
	case 1:
		endTag = value;
		break;
	case 2:
		scoreTextTag = value;
		break;
	case 3:
		speed = stof(value);
		break;
	}
}

string PongBallScript::getScriptName() const {
	return "PongBallScript";
}
int PongBallScript::getAttributeType(int index) const {
	switch (index) {
	case 0:
	case 1:
	case 2:
		return 0;
	case 3:
		return 1;
	default:
		return 0;
	}
}
string PongBallScript::getAttributeName(int index) const {
	switch (index) {
	case 0:
		return "Pallete tag";
	case 1:
		return "End tag";
	case 2:
		return "Score text tag";
	case 3:
		return "Speed";
	default:
		return "";
	}
}

void PongBallScript::read(istream& stream) {
	//stream >> palleteTag >> endTag >> scoreTextTag >> speed;
	string line;
	stream.get();
	getline(stream, line);
	palleteTag = line;
	getline(stream, line);
	endTag = line;
	getline(stream, line);
	scoreTextTag = line;
	getline(stream, line);
	speed = stof(line);
}
void PongBallScript::write(ostream& stream) const {
	stream << palleteTag << "\n" << endTag << "\n" << scoreTextTag << "\n" << speed << "\n";
}

PongBallScript::~PongBallScript() {
}