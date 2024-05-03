#pragma once
#include <iostream>

class GameObject;

class BehaviourScript { //Base class for all scripts that can be attached to GameObjects (interface)
protected:
    int attributeCount;
public:
    virtual BehaviourScript* clone() const = 0;
    virtual void start(GameObject& gameObject) = 0;
    virtual void update(GameObject& gameObject) = 0;
    virtual void collision(GameObject& gameObject, GameObject& collisionObject) = 0;
    virtual void trigger(GameObject& gameObject, GameObject& triggerObject) = 0;
    virtual void destroy(GameObject& gameObject) = 0;

    virtual int getAttributeCount() const { return attributeCount; }
    virtual std::string getAttributeName(int index) const = 0;
    virtual int getAttributeType(int index) const = 0;

    virtual std::string getAttribute(int index) const = 0;
    virtual void setAttribute(int index, std::string value) = 0;

    virtual ~BehaviourScript() {}
};