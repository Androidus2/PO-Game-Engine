#pragma once
#include <iostream>
#include <vector>
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "DebugMacro.h"

class GameObject;

class Collider { //Collider class for collision detection
protected:
    sf::Vector2f colliderOffset;
    float colliderRotation;
    sf::Vector2f colliderScale;
    sf::Shape* colliderShape;
    bool colliderIsCircle;
    bool colliderIsActive;
    bool colliderIsTrigger;
    float mass;
    bool isMovable;
    bool useGravity;

    void cleanShape(sf::Vector2f& position, float& rotation, sf::Vector2f& scale);
    void fixShape(sf::Vector2f& position, float& rotation, sf::Vector2f& scale);

    virtual std::istream& pRead(std::istream& in); //for polymorphic reading
    virtual std::ostream& pWrite(std::ostream& out) const; //for polymorphic writing

private:
    static bool findMinSeparation(const GameObject& collider1, const GameObject& collider2, sf::Vector2f& sep); //SAT collision detection
    static void moveCollidersInCollision(GameObject& collider1, GameObject& collider2, const sf::Vector2f& displacement); //move the colliders
    static bool polygonCollision(GameObject& collider1, GameObject& collider2); //check if 2 polygons are colliding
    static bool circleCollision(GameObject& collider1, GameObject& collider2); //check if 2 circles are colliding

public:
    Collider();
    Collider(const sf::Vector2f& colliderOffset, float colliderRotation, const sf::Vector2f& colliderScale,
        sf::Shape* colliderShape, bool colliderIsCircle, bool colliderIsActive, bool colliderIsTrigger,
        float mass, bool isMovable, bool useGravity);
    Collider(const Collider& collider);
    Collider& operator=(const Collider& collider);

    sf::Vector2f getColliderOffset() const;
    void setColliderOffset(const sf::Vector2f& colliderOffset);

    float getColliderRotation() const;
    void setColliderRotation(float colliderRotation);

    sf::Vector2f getColliderScale() const;
    void setColliderScale(const sf::Vector2f& colliderScale);

    const sf::Shape* getColliderShape() const;
    void setColliderShape(sf::Shape* colliderShape, bool isCircle);

    bool getColliderIsCircle() const;

    bool getColliderIsActive() const;
    void setColliderIsActive(bool colliderIsActive);

    bool getColliderIsTrigger() const;
    void setColliderIsTrigger(bool colliderIsTrigger);

    float getMass() const;
    void setMass(float mass);

    bool getIsMovable() const;
    void setIsMovable(bool isMovable);

    bool getUseGravity() const;
    void setUseGravity(bool useGravity);

    void makeSquareCollider(float sideLength);
    void makeCircleCollider(float radius);
    void makeTriangleCollider(float sideLength);
    void makeHexagonCollider(float sideLength);

    void test() { std::cout << colliderShape->getPosition().x << " " << colliderShape->getPosition().y << std::endl; }

    void updateTransform(const sf::Vector2f& colliderOffset, float colliderRotation, const sf::Vector2f& colliderScale);
    void updateTransform(const sf::Transformable& transform);

    static bool collision(GameObject& collider1, GameObject& collider2);
    static void handleAllCollisions(const std::vector<GameObject*>& objects, const std::vector<sf::Vector2f>& lastPositions);

    virtual std::istream& read(std::istream& in);
    virtual std::ostream& write(std::ostream& out) const;

    virtual ~Collider();
};

std::istream& operator>>(std::istream& in, Collider& collider);
std::ostream& operator<<(std::ostream& out, const Collider& collider);