#include "Camera.h"
#include "Game.h"

using namespace std;
using namespace sf;

Camera::Camera() : GameObject()
{
	setName("Camera");
	tag = "Camera";
	setActive(true);
	colliderIsActive = false;
	zLayer = 0;
	setPosition(0, 0);
	setRotation(0);
	setScale(1920, 1080);
}
Camera::Camera(const Camera& camera) : GameObject(camera)
{
}
Camera& Camera::operator=(const Camera& camera)
{
	if(this == &camera)
		return *this;
	GameObject::operator=(camera);
	return *this;
}
GameObject* Camera::clone() const
{
	return new Camera(*this);
}

void Camera::setTag(string tag)
{
	//Do nothing, camera tag is always "Camera"
}

void Camera::setActive(bool isActive)
{
	//Do nothing, camera is always active
}

void Camera::updateScripts()
{
	GameObject::updateScripts();
	Game::getGameView()->setCenter(getPosition());
	Game::getGameView()->setRotation(getRotation());
	Game::getGameView()->setSize(getScale());
}

void Camera::setPosition(const Vector2f& position)
{
	GameObject::setPosition(position);
	Game::getGameView()->setCenter(getPosition());
}
void Camera::setPosition(float x, float y)
{
	GameObject::setPosition(x, y);
	Game::getGameView()->setCenter(getPosition());
}
void Camera::move(const Vector2f& position)
{
	GameObject::move(position);
	Game::getGameView()->setCenter(getPosition());
}
void Camera::move(float x, float y)
{
	GameObject::move(x, y);
	Game::getGameView()->setCenter(getPosition());
}

void Camera::setRotation(float angle)
{
	GameObject::setRotation(angle);
	Game::getGameView()->setRotation(getRotation());
}
void Camera::rotate(float angle)
{
	GameObject::rotate(angle);
	Game::getGameView()->setRotation(getRotation());
}

void Camera::setScale(const Vector2f& factors)
{
	GameObject::setScale(factors);
	Game::getGameView()->setSize(getScale());
}
void Camera::setScale(float x, float y)
{
	GameObject::setScale(x, y);
	Game::getGameView()->setSize(getScale());
}

void Camera::scale(const Vector2f& factors)
{
	GameObject::scale(factors);
	Game::getGameView()->setSize(getScale());
}
void Camera::scale(float x, float y)
{
	GameObject::scale(x, y);
	Game::getGameView()->setSize(getScale());
}

ostream& Camera::write(ostream& out) const
{
	out << "Camera" << endl;
	pWrite(out);
	return out;
}

Camera::~Camera()
{
	//Camera destructor, does nothing since Camera does not have any dynamic memory
}