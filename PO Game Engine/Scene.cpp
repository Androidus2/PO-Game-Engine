#include <iostream>
#include <fstream>
#include "Scene.h"
#include "Utility.h"
#include "Collider.h"
#include "GameObject.h"
#include "HierarchyWindow.h"
#include "Game.h"

using namespace std;
using namespace sf;

istream& operator>>(istream& in, Scene& scene) { //input operator
    return scene.read(in);
}
ostream& operator<<(ostream& out, const Scene& scene) { //output operator
    return scene.write(out);
}

Scene::Scene() : sceneId(sceneIdCounter++) { //default constructor
    sceneName = "Scene" + sceneId;
    buildIndex = -1;
    selectedObjectIndex = -1;
    sceneBeforePlaying = NULL;
    scenePath = "GameFiles";
}
Scene::Scene(const Scene& scene) : sceneId(scene.sceneId) { //copy constructor
    sceneName = scene.sceneName;
    setObjects(scene.sceneObjects);
    buildIndex = scene.buildIndex;
    selectedObjectIndex = -1;
    sceneBeforePlaying = NULL;
    scenePath = scene.scenePath;
}
Scene::Scene(const Scene& scene, int id) : sceneId(id) { //copy constructor with sceneId
    sceneName = scene.sceneName;
    setObjects(scene.sceneObjects);
    buildIndex = scene.buildIndex;
    selectedObjectIndex = -1;
    sceneBeforePlaying = NULL;
    scenePath = scene.scenePath;
}
Scene& Scene::operator=(const Scene& scene) { //assignment operator
    if (this == &scene)
        return *this;
    sceneName = scene.sceneName;
    setObjects(scene.sceneObjects);
    buildIndex = scene.buildIndex;
    scenePath = scene.scenePath;
    return *this;
}

int Scene::getObjectsCount() const { //get the number of objects in the scene
    return sceneObjects.size();
}

string Scene::getName() const { //get the name of the scene
    return sceneName;
}
void Scene::setName(string name) { //set the name of the scene
    sceneName = name;
}

const vector<GameObject*>& Scene::getObjects() const { //get the objects in the scene
    return sceneObjects;
}
const GameObject* Scene::getObjectByIndex(int index) const { //get an object by index
    if (index < sceneObjects.size() && index >= 0)
        return sceneObjects[index];
    return NULL;
}
void Scene::setObjects(const vector<GameObject*>& objects) { //set the objects in the scene
    clearObjects();
    for (int i = 0; i < objects.size(); i++)
        addObject(objects[i]);
}
void Scene::setObjectByIndex(int index, const GameObject* object) { //set an object by index
    if (index < sceneObjects.size() && index >= 0) {
        delete sceneObjects[index];
        sceneObjects[index] = object->clone();
    }
}
void Scene::clearObjects() { //clear all objects in the scene
    for (int i = 0; i < sceneObjects.size(); i++) {
        delete sceneObjects[i];
        if (sceneId == getSelectedSceneId())
            removeTextFromHierarchy(i);
    }
    sceneObjects.clear();
    clearLastPositions();
    selectedObjectIndex = -1;
}
void Scene::addObject(const GameObject* object) { //add an object to the scene
    sceneObjects.push_back(object->clone());
    if (sceneId == getSelectedSceneId()) {
        addTextToHierarchy(object->getName());
    }
    addLastPosition(object->getPosition());
}
void Scene::removeObjectByIndex(int index) { //remove an object by index
    if (selectedObjectIndex == index)
        selectedObjectIndex = -1;
    if (index < sceneObjects.size() && index >= 0) {
        if (sceneId == getSelectedSceneId())
            removeTextFromHierarchy(index);
        delete sceneObjects[index];
        sceneObjects.erase(sceneObjects.begin() + index);
        eraseLastPosition(index);
    }
}
void Scene::removeObjectById(int id) { //remove an object by id
    if (selectedObjectIndex >= 0 && selectedObjectIndex < sceneObjects.size() && sceneObjects[selectedObjectIndex]->getId() == id) {
        selectedObjectIndex = -1;
    }
    for (int i = 0; i < sceneObjects.size(); i++) {
        if (sceneObjects[i]->getId() == id) {
            delete sceneObjects[i];
            sceneObjects.erase(sceneObjects.begin() + i);
            eraseLastPosition(i);
            if (sceneId == getSelectedSceneId())
                removeTextFromHierarchy(i);
            break;
        }
    }
}
bool Scene::sceneHasObject(int id) const { //check if the scene has an object with a certain id
    for (int i = 0; i < sceneObjects.size(); i++) {
        if (sceneObjects[i]->getId() == id)
            return true;
    }
    return false;
}
int Scene::getIndexOfObject(int id) const { //get the index of an object with a certain id
    for (int i = 0; i < sceneObjects.size(); i++) {
        if (sceneObjects[i]->getId() == id)
            return i;
    }
    return -1;
}
void Scene::removeSelectedObject() { //remove the selected object
    if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0) {
        delete sceneObjects[selectedObjectIndex];
        sceneObjects.erase(sceneObjects.begin() + selectedObjectIndex);
        eraseLastPosition(selectedObjectIndex);
        selectedObjectIndex = -1;
    }
}

void Scene::moveSelectedObject(Vector2f moveBy) { //move the selected object
    if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0) {
        sceneObjects[selectedObjectIndex]->move(moveBy);
        modifyLastPosition(selectedObjectIndex, sceneObjects[selectedObjectIndex]->getPosition());
    }
}

void Scene::modifySelectedCustom(string value, int index) { //modify a custom value of the selected object
    if (index < 0)
        return;
    if (index == 0) {
        //Change name
        sceneObjects[selectedObjectIndex]->setName(value);
        return;
    }
    if (index == 1) {
        //Change tag
        sceneObjects[selectedObjectIndex]->setTag(value);
        return;
    }
    if (index == 2) { //Change position.x
        sceneObjects[selectedObjectIndex]->setPosition(stof(value), sceneObjects[selectedObjectIndex]->getPosition().y);
        return;
    }
    if (index == 3) { //Change position.y
        sceneObjects[selectedObjectIndex]->setPosition(sceneObjects[selectedObjectIndex]->getPosition().x, stof(value));
        return;
    }
    if (index == 4) { //Change rotation
        sceneObjects[selectedObjectIndex]->setRotation(stof(value));
        return;
    }
    if (index == 5) { //Change scale.x
        sceneObjects[selectedObjectIndex]->setScale(stof(value), sceneObjects[selectedObjectIndex]->getScale().y);
        return;
    }
    if (index == 6) { //Change scale.y
        sceneObjects[selectedObjectIndex]->setScale(sceneObjects[selectedObjectIndex]->getScale().x, stof(value));
        return;
    }
    if (index == 7) { //Change color
        sceneObjects[selectedObjectIndex]->setFillColor(stringToColor(value));
        return;
    }
    if (index == 8) { //Change zLayer
        sceneObjects[selectedObjectIndex]->setZLayer(stoi(value));
        return;
    }
    if (index == 9) { //Change mass
        sceneObjects[selectedObjectIndex]->setMass(stof(value));
        return;
    }
    if (index == 10) { //Change velocity.x
        sceneObjects[selectedObjectIndex]->setVelocity(stof(value), sceneObjects[selectedObjectIndex]->getVelocity().y);
        return;
    }
    if (index == 11) { //Change velocity.y
        sceneObjects[selectedObjectIndex]->setVelocity(sceneObjects[selectedObjectIndex]->getVelocity().x, stof(value));
        return;
    }
    if (index == 12) { //Change texture path
    	sceneObjects[selectedObjectIndex]->changeTexture(value);
    	return;
    }
    if (index == 13) { //Change isMovable
        sceneObjects[selectedObjectIndex]->setIsMovable((value == "1" || value == "true"));
    	return;
    }
    int poz = 14;
    for (int i = 0; i < sceneObjects[selectedObjectIndex]->getScriptsCount(); i++) {
        if (index >= poz && index < poz + sceneObjects[selectedObjectIndex]->getAttributeCountFromScripts(i)) {
            sceneObjects[selectedObjectIndex]->setAttributeOnScripts(i, index - poz, value);
            break;
        }
        poz += sceneObjects[selectedObjectIndex]->getAttributeCountFromScripts(i);
    }
}
string Scene::getSelectedCustom(int index) const { //get a custom value of the selected object
    if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0) {
        if (index == 0)
            return sceneObjects[selectedObjectIndex]->getName();
        if(index == 1)
            return sceneObjects[selectedObjectIndex]->getTag();
        if (index == 2)
            return floatToString(sceneObjects[selectedObjectIndex]->getPosition().x);
        if (index == 3)
            return floatToString(sceneObjects[selectedObjectIndex]->getPosition().y);
        if (index == 4)
            return floatToString(sceneObjects[selectedObjectIndex]->getRotation());
        if (index == 5)
            return floatToString(sceneObjects[selectedObjectIndex]->getScale().x);
        if (index == 6)
            return floatToString(sceneObjects[selectedObjectIndex]->getScale().y);
        if (index == 7)
            return ColorToString(sceneObjects[selectedObjectIndex]->getFillColor());
        if (index == 8)
            return floatToString(sceneObjects[selectedObjectIndex]->getZLayer());
        if (index == 9)
            return floatToString(sceneObjects[selectedObjectIndex]->getMass());
        if (index == 10)
            return floatToString(sceneObjects[selectedObjectIndex]->getVelocity().x);
        if (index == 11)
            return floatToString(sceneObjects[selectedObjectIndex]->getVelocity().y);
        if (index == 12) {
            string ret = sceneObjects[selectedObjectIndex]->getTexturePath();
            if (ret == "")
				return "None";
            //Remove the path to the texture
            for (int i = ret.size() - 1; i >= 0; i--) {
                if (ret[i] == '/') {
					ret = ret.substr(i + 1);
					break;
				}
			}
            return ret;
        }
        if (index == 13)
            return to_string(sceneObjects[selectedObjectIndex]->getIsMovable());
        int poz = 14;
        for (int i = 0; i < sceneObjects[selectedObjectIndex]->getScriptsCount(); i++) {
            if (index >= poz && index < poz + sceneObjects[selectedObjectIndex]->getAttributeCountFromScripts(i)) {
                return sceneObjects[selectedObjectIndex]->getAttributeFromScripts(i, index - poz);
            }
            poz += sceneObjects[selectedObjectIndex]->getAttributeCountFromScripts(i);
        }
    }
    return "";
}

string Scene::getSelectedCustomName(int index) const { //get the name of a custom value of the selected object
    if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0) {
        if (index == 0)
            return "Name";
        if(index == 1)
            return "Tag";
        if (index == 2)
            return "Position";
        if (index == 3)
            return "Position";
        if (index == 4)
            return "Rotation";
        if (index == 5)
            return "Scale";
        if (index == 6)
            return "Scale";
        if (index == 7)
            return "Color";
        if (index == 8)
            return "ZLayer";
        if (index == 9)
            return "Mass";
        if (index == 10)
            return "Velocity";
        if (index == 11)
            return "Velocity";
        if (index == 12)
            return "Texture";
        if (index == 13)
            return "IsMovable";
        int poz = 14;
        for (int i = 0; i < sceneObjects[selectedObjectIndex]->getScriptsCount(); i++) {
            if (index >= poz && index < poz + sceneObjects[selectedObjectIndex]->getAttributeCountFromScripts(i))
                return sceneObjects[selectedObjectIndex]->getAttributeNamesFromScripts(i, index - poz);
            poz += sceneObjects[selectedObjectIndex]->getAttributeCountFromScripts(i);
        }
    }
    return "";
}
int Scene::getSelectedCustomType(int index) const {
    //get the type of a custom value of the selected object
    //0 - string, 1 - float, 2 - color, 3 - int, 4 - bool, 5 - Vector2f.x, 6 - Vector2f.y, 7 - Texture path
    if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0) {
        if (index == 0)
            return 0;
        if (index == 1)
            return 0;
        if (index == 2)
            return 5;
        if (index == 3)
            return 6;
        if (index == 4)
            return 1;
        if (index == 5)
            return 5;
        if (index == 6)
            return 6;
        if (index == 7)
            return 2;
        if (index == 8)
            return 3;
        if (index == 9)
            return 1;
        if (index == 10)
            return 5;
        if (index == 11)
            return 6;
        if (index == 12)
            return 7;
        if (index == 13)
            return 4;
        int poz = 14;
        for (int i = 0; i < sceneObjects[selectedObjectIndex]->getScriptsCount(); i++) {
            if (index >= poz && index < poz + sceneObjects[selectedObjectIndex]->getAttributeCountFromScripts(i))
                return sceneObjects[selectedObjectIndex]->getAttributeTypeFromScripts(i, index - poz);
            poz += sceneObjects[selectedObjectIndex]->getAttributeCountFromScripts(i);
        }
    }
    return -1;
}

string Scene::getNameOfScriptOnSelectedObject(int scriptIndex) const { //get the name of a script on the selected object
    if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0) {
		return sceneObjects[selectedObjectIndex]->getScriptName(scriptIndex);
	}
	return "";
}
void Scene::addScriptToSelectedObject(const string& scriptName) { //add a script to the selected object
    if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0) {
        try {
            BehaviourScript* script = makeScriptFromString(scriptName);
            sceneObjects[selectedObjectIndex]->addScript(script);
        }
        catch (const exception& e) {
			cout << e.what() << endl;
		}
    }
}
void Scene::removeScriptFromSelectedObject(int scriptIndex) { //remove a script from the selected object
	if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0)
		sceneObjects[selectedObjectIndex]->removeScript(scriptIndex);
}

void Scene::changeSelectedIsMovable() { //change if the selected object is movable
    if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0)
        sceneObjects[selectedObjectIndex]->setIsMovable(!sceneObjects[selectedObjectIndex]->getIsMovable());
}
void Scene::setTextureToSelectedObject(const Texture* tex) { //set a texture to the selected object
    if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0)
        sceneObjects[selectedObjectIndex]->setTexture(tex, true);
}

void Scene::setLastPositions(const vector<Vector2f>& lastPositions) { //set the last positions of the objects
    this->lastPositions = lastPositions;
}
const vector<Vector2f>& Scene::getLastPositions() const { //get the last positions of the objects
    return lastPositions;
}
void Scene::modifyLastPosition(int index, const Vector2f& position) { //modify the last position of an object
    if (index < lastPositions.size() && index >= 0)
        lastPositions[index] = position;
}
void Scene::addLastPosition(const Vector2f& position) { //add a last position
    lastPositions.push_back(position);
}
void Scene::eraseLastPosition(int index) { //erase a last position
    if (index < lastPositions.size() && index >= 0)
        lastPositions.erase(lastPositions.begin() + index);
}
void Scene::clearLastPositions() { //clear all last positions
    lastPositions.clear();
}

void Scene::startScene() { //start the scene
    if (sceneBeforePlaying)
        delete sceneBeforePlaying;
    sceneBeforePlaying = new Scene(*this, -500);
    for (int i = 0; i < sceneObjects.size(); i++) {
        if (sceneObjects[i]->getActive())
            sceneObjects[i]->startScripts();
    }
}
void Scene::drawScene(bool drawColliders, RenderWindow& window) const { //draw the scene
    vector<GameObject*> sortedObjects = sceneObjects;
    sort(sortedObjects.begin(), sortedObjects.end(), [](const GameObject* a, const GameObject* b) {
        return a->getZLayer() < b->getZLayer();
        });
    for (int i = 0; i < sortedObjects.size(); i++) {
        if (sortedObjects[i]->getActive()) {
            if (drawColliders) {
                if (sortedObjects[i]->getColliderIsActive()) {
                    window.draw(*sortedObjects[i]->getColliderShape());
                }
            }
            window.draw(*sortedObjects[i]);
        }
    }
}
void Scene::updateScene() { //update the scene
    for (int i = 0; i < sceneObjects.size(); i++) {
        if (sceneObjects[i]->getActive())
            sceneObjects[i]->updateScripts();
    }
    Collider::handleAllCollisions(sceneObjects, lastPositions);
    lastPositions.clear();
    for (int i = 0; i < sceneObjects.size(); i++)
        addLastPosition(sceneObjects[i]->getPosition()); //Last positions are used to reset the velocity of objects when they collide (to prevent them from going through each other)
}
void Scene::endScene() { //end the scene
    for (int i = 0; i < sceneObjects.size(); i++) {
        if (sceneObjects[i]->getActive())
            sceneObjects[i]->destroyScripts();
    }
    if (sceneBeforePlaying) {
        int ids = getId();
        for (int i = 0; i < sceneObjects.size(); i++)
            removeTextFromHierarchy(0);
        sceneObjects = sceneBeforePlaying->sceneObjects;
        lastPositions = sceneBeforePlaying->lastPositions;
        for (int i = 0; i < sceneObjects.size(); i++)
            addTextToHierarchy(sceneObjects[i]->getName());
        setId(ids);
        delete sceneBeforePlaying;
        sceneBeforePlaying = NULL;
        int sel = getSelectedObjectIndex();
        HierarchyWindow* hierarchy = dynamic_cast<HierarchyWindow*>(Game::getHierarchy());
        if (hierarchy) {
            hierarchy->changeSelectedObject(-1);
            hierarchy->changeSelectedObject(sel);
        }
    }
}

int Scene::getId() const { //get the id of the scene
    return sceneId;
}
void Scene::setId(int id) { //set the id of the scene
    sceneId = id;
}

int Scene::getBuildIndex() const { //get the build index of the scene
    return buildIndex;
}
void Scene::setBuildIndex(int buildIndex) { //set the build index of the scene
    this->buildIndex = buildIndex;
}

int Scene::getSelectedObjectIndex() const { //get the index of the selected object
    return selectedObjectIndex;
}
void Scene::setSelectedObjectIndex(int index) { //set the index of the selected object
    selectedObjectIndex = index;
}

istream& Scene::read(istream& in) { //read function
    in >> sceneName >> buildIndex;
    int objectsCount;
    in >> objectsCount;
    clearObjects();
    GameObject* tmp;
    for (int i = 0; i < objectsCount; i++) {
        string type;
        in >> type;
        tmp = makeObjFromString(type);
        in >> *tmp;
        addObject(tmp);
        delete tmp;
    }
    return in;
}
ostream& Scene::write(ostream& out) const { //write function
    out << sceneName << " " << buildIndex << " " << getObjectsCount() << endl;
    for (int i = 0; i < getObjectsCount(); i++)
        out << *sceneObjects[i];
    return out;
}

void Scene::setScenePath(const string& path) { //set the path of the scene
	scenePath = path;
}

void Scene::saveScene() { //save the scene to its path
	ofstream out(scenePath + "/" + sceneName + ".poscene");
	out << *this;
	out.close();
}

Scene::~Scene() {} //destructor
