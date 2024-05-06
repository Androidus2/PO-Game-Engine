#pragma once
#include <iostream>
#include "BehaviourScript.h"


class FollowMouseScript : public BehaviourScript { //Script that makes an object follow the mouse
private:
    bool applySmoothness;
    float smoothnessSpeed;
public:
    FollowMouseScript(bool applySmoothness = false, float smoothnessSpeed = 5.f);
    FollowMouseScript* clone() const;
    void start(GameObject& gameObject);
    void update(GameObject& gameObject);
    void collision(GameObject& gameObject, GameObject& collisionObject);
    void trigger(GameObject& gameObject, GameObject& triggerObject);
    void destroy(GameObject& gameObject);

    std::string getAttribute(int index) const;
    void setAttribute(int index, std::string value);

    std::string getScriptName() const;

    int getAttributeType(int index) const;
    std::string getAttributeName(int index) const;

    void read(std::istream& stream);
    void write(std::ostream& stream);

    ~FollowMouseScript();
};