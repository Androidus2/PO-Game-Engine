#pragma once
#include <iostream>
#include <vector>
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "Collider.h"

class BehaviourScript;

class GameObject : public Collider, public sf::ConvexShape { //GameObject class
protected:
    std::string name;
    std::string texturePath;
    bool isActive;
    int zLayer;
    sf::Vector2f velocity;
    int id;
    static int idCounter;
    std::vector<BehaviourScript*> attachedScripts; //Scripts attached to the GameObject

    std::istream& pRead(std::istream& in) override;
    std::ostream& pWrite(std::ostream& out) const override;
public:
    GameObject();
    GameObject(const GameObject& gameObject);
    GameObject& operator=(const GameObject& gameObject);
    virtual GameObject* clone() const;

    std::string getName() const;
    void setName(std::string name);

    bool getActive() const;
    void setActive(bool isActive);

    int getId() const;

    int getZLayer() const;
    void setZLayer(int layer);

    sf::Vector2f getVelocity() const;
    void setVelocity(const sf::Vector2f& velocity);
    void setVelocity(float x, float y);

    void addScript(BehaviourScript* script);
    int scriptIndex(BehaviourScript* script) const;
    void removeScript(BehaviourScript* script);
    void removeScript(int index);
    void removeAllScripts();
    int getScriptsCount() const;

    virtual void startScripts();
    virtual void updateScripts();
    virtual void triggerScripts(GameObject& trigger);
    virtual void collisionScripts(GameObject& collision);
    virtual void destroyScripts();

    void setAttributeOnScripts(int scriptIndex, int attributeIndex, std::string value);
    std::string getAttributeFromScripts(int scriptIndex, int attributeIndex) const;

    std::string getAttributeNamesFromScripts(int scriptIndex, int attributeIndex) const;
    int getAttributeTypeFromScripts(int scriptIndex, int attributeIndex) const;

    std::string getScriptName(int scriptIndex) const;

    int getAttributeCountFromScripts(int scriptIndex) const;

    void setPosition(const sf::Vector2f& position);
    void setPosition(float x, float y);
    void move(const sf::Vector2f& position);
    void move(float x, float y);

    void changeId();

    void changeTexture(const std::string& texturePath);
    std::string getTexturePath() const;

    std::istream& read(std::istream& in) override;
    std::ostream& write(std::ostream& out) const override;

    virtual ~GameObject();
};