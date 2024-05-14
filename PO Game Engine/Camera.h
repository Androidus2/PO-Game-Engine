#pragma once
#include "GameObject.h"
#include "DebugMacro.h"

class Camera : public GameObject
{
public:
	Camera();
	Camera(const Camera& camera);
	Camera& operator=(const Camera& camera);
	GameObject* clone() const;

    void setTag(std::string tag) override;

    void setActive(bool isActive) override;

	void updateScripts() override;

    void setPosition(const sf::Vector2f& position) override;
    void setPosition(float x, float y) override;
    void move(const sf::Vector2f& position) override;
    void move(float x, float y) override;

    void setRotation(float angle) override;
    void rotate(float angle) override;

    void setScale(const sf::Vector2f& factors) override;
    void setScale(float x, float y) override;
    void scale(const sf::Vector2f& factors) override;
    void scale(float x, float y) override;

    std::ostream& write(std::ostream & out) const override;

	~Camera();
};