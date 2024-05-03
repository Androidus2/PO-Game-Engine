#pragma once
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"


class Scene { //Scene class
private:
    std::string sceneName;
    std::vector<GameObject*> sceneObjects; //Objects in the scene
    std::vector<sf::Vector2f> lastPositions;
    int sceneId;
    static int sceneIdCounter;
    int buildIndex;
    //TODO: Selection
    int selectedObjectIndex; //Change to int*

    Scene* sceneBeforePlaying;

    void addLastPosition(const sf::Vector2f& position);
    void eraseLastPosition(int index);
    void clearLastPositions();
public:
    Scene();
    Scene(const Scene& scene);
    Scene(const Scene& scene, int id);
    Scene& operator=(const Scene& scene);

    int getObjectsCount() const;

    std::string getName() const;
    void setName(std::string name);

    const std::vector<GameObject*>& getObjects() const;
    const GameObject* getObjectByIndex(int index) const;
    void setObjects(const std::vector<GameObject*>& objects);
    void setObjectByIndex(int index, const GameObject* object);
    void clearObjects();
    void addObject(const GameObject* object);
    void removeObjectByIndex(int index);
    void removeObjectById(int id);
    bool sceneHasObject(int id) const;
    int getIndexOfObject(int id) const;
    void removeSelectedObject();

    void moveSelectedObject(sf::Vector2f moveBy);

    void modifySelectedCustom(std::string value, int index);
    std::string getSelectedCustom(int index) const;

    std::string getSelectedCustomName(int index) const;
    int getSelectedCustomType(int index) const;

    void changeSelectedIsMovable();
    void setTextureToSelectedObject(const sf::Texture* tex);

    void setLastPositions(const std::vector<sf::Vector2f>& lastPositions);
    const std::vector<sf::Vector2f>& getLastPositions() const;
    void modifyLastPosition(int index, const sf::Vector2f& position);

    void startScene();
    void drawScene(bool drawColliders, sf::RenderWindow& window) const;
    void updateScene();
    void endScene();

    int getId() const;
    void setId(int id);

    int getBuildIndex() const;
    void setBuildIndex(int buildIndex);

    int getSelectedObjectIndex() const;
    void setSelectedObjectIndex(int index);

    std::istream& read(std::istream& in);
    std::ostream& write(std::ostream& out) const;

    ~Scene();
};

std::ostream& operator<<(std::ostream& out, const Scene& scene);
std::istream& operator>>(std::istream& in, Scene& scene);