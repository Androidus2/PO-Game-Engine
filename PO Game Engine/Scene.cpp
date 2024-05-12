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
    sceneViewPositionBeforePlaying = Vector2f(0, 0);
    sceneViewZoomBeforePlaying = Vector2f(1, 1);
}
Scene::Scene(const Scene& scene) : sceneId(scene.sceneId) { //copy constructor
    sceneName = scene.sceneName;
    setObjects(scene.sceneObjects);
    buildIndex = scene.buildIndex;
    selectedObjectIndex = -1;
    sceneBeforePlaying = NULL;
    scenePath = scene.scenePath;
    sceneViewPositionBeforePlaying = scene.sceneViewPositionBeforePlaying;
    sceneViewZoomBeforePlaying = scene.sceneViewZoomBeforePlaying;
}
Scene::Scene(const Scene& scene, int id) : sceneId(id) { //copy constructor with sceneId
    sceneName = scene.sceneName;
    setObjects(scene.sceneObjects);
    buildIndex = scene.buildIndex;
    selectedObjectIndex = -1;
    sceneBeforePlaying = NULL;
    scenePath = scene.scenePath;
    sceneViewPositionBeforePlaying = scene.sceneViewPositionBeforePlaying;
    sceneViewZoomBeforePlaying = scene.sceneViewZoomBeforePlaying;
}
Scene& Scene::operator=(const Scene& scene) { //assignment operator
    if (this == &scene)
        return *this;
    sceneName = scene.sceneName;
    setObjects(scene.sceneObjects);
    buildIndex = scene.buildIndex;
    scenePath = scene.scenePath;
    sceneViewPositionBeforePlaying = scene.sceneViewPositionBeforePlaying;
    sceneViewZoomBeforePlaying = scene.sceneViewZoomBeforePlaying;
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
        sceneObjects[i] = NULL;
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
    if (index == 9) { //Change velocity.x
        sceneObjects[selectedObjectIndex]->setVelocity(stof(value), sceneObjects[selectedObjectIndex]->getVelocity().y);
        return;
    }
    if (index == 10) { //Change velocity.y
        sceneObjects[selectedObjectIndex]->setVelocity(sceneObjects[selectedObjectIndex]->getVelocity().x, stof(value));
        return;
    }
    if (index == 11) { //Change texture path
    	sceneObjects[selectedObjectIndex]->changeTexture(value);
    	return;
    }
    if (index == 12) { //Change colliderIsActive
    	sceneObjects[selectedObjectIndex]->setColliderIsActive((value == "1" || value == "true"));
    	return;
    }
    if (index == 13) { //Change colliderIsTrigger
    	sceneObjects[selectedObjectIndex]->setColliderIsTrigger((value == "1" || value == "true"));
    	return;
    }
    if (index == 14) { //Change isMovable
        sceneObjects[selectedObjectIndex]->setIsMovable((value == "1" || value == "true"));
    	return;
    }
    if (index == 15) { //Change mass
    	sceneObjects[selectedObjectIndex]->setMass(stof(value));
    	return;
    }
    if (index == 16) { //Change colliderOffset.x
    	sceneObjects[selectedObjectIndex]->setColliderOffset(Vector2f(stof(value), sceneObjects[selectedObjectIndex]->getColliderOffset().y));
        sceneObjects[selectedObjectIndex]->updateTransform(*sceneObjects[selectedObjectIndex]);
        return;
    }
    if (index == 17) { //Change colliderOffset.y
    	sceneObjects[selectedObjectIndex]->setColliderOffset(Vector2f(sceneObjects[selectedObjectIndex]->getColliderOffset().x, stof(value)));
        sceneObjects[selectedObjectIndex]->updateTransform(*sceneObjects[selectedObjectIndex]);
        return;
    }
    if (index == 18) { //Change colliderRotation
    	sceneObjects[selectedObjectIndex]->setColliderRotation(stof(value));
        sceneObjects[selectedObjectIndex]->updateTransform(*sceneObjects[selectedObjectIndex]);
    	return;
    }
    if (index == 19) { //Change colliderScale.x
    	sceneObjects[selectedObjectIndex]->setColliderScale(Vector2f(stof(value), sceneObjects[selectedObjectIndex]->getColliderScale().y));
        sceneObjects[selectedObjectIndex]->updateTransform(*sceneObjects[selectedObjectIndex]);
        return;
    }
    if (index == 20) { //Change colliderScale.y
    	sceneObjects[selectedObjectIndex]->setColliderScale(Vector2f(sceneObjects[selectedObjectIndex]->getColliderScale().x, stof(value)));
        sceneObjects[selectedObjectIndex]->updateTransform(*sceneObjects[selectedObjectIndex]);
        return;
    }
    if (index == 21) { //Change useGravity
    	sceneObjects[selectedObjectIndex]->setUseGravity((value == "1" || value == "true"));
    	return;
    }
    int poz = 22;
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
            return floatToString(sceneObjects[selectedObjectIndex]->getVelocity().x);
        if (index == 10)
            return floatToString(sceneObjects[selectedObjectIndex]->getVelocity().y);
        if (index == 11) {
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
        if (index == 12)
            return to_string(sceneObjects[selectedObjectIndex]->getColliderIsActive());
        if (index == 13)
            return to_string(sceneObjects[selectedObjectIndex]->getColliderIsTrigger());
        if (index == 14)
            return to_string(sceneObjects[selectedObjectIndex]->getIsMovable());
        if (index == 15)
            return floatToString(sceneObjects[selectedObjectIndex]->getMass());
        if (index == 16)
            return floatToString(sceneObjects[selectedObjectIndex]->getColliderOffset().x);
        if (index == 17)
            return floatToString(sceneObjects[selectedObjectIndex]->getColliderOffset().y);
        if (index == 18)
            return floatToString(sceneObjects[selectedObjectIndex]->getColliderRotation());
        if (index == 19)
            return floatToString(sceneObjects[selectedObjectIndex]->getColliderScale().x);
        if (index == 20)
            return floatToString(sceneObjects[selectedObjectIndex]->getColliderScale().y);
        if (index == 21)
            return to_string(sceneObjects[selectedObjectIndex]->getUseGravity());
        int poz = 22;
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
            return "Velocity";
        if (index == 10)
            return "Velocity";
        if (index == 11)
            return "Texture";
        if (index == 12)
            return "ColliderActive";
        if (index == 13)
            return "IsTrigger";
        if (index == 14)
            return "IsMovable";
        if (index == 15)
            return "Mass";
        if (index == 16)
            return "ColliderOffset";
        if (index == 17)
            return "ColliderOffset";
        if (index == 18)
            return "ColliderRotation";
        if (index == 19)
            return "ColliderScale";
        if (index == 20)
            return "ColliderScale";
        if (index == 21)
            return "UseGravity";
        int poz = 22;
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
            return 5;
        if (index == 10)
            return 6;
        if (index == 11)
            return 7;
        if (index == 12)
            return 4;
        if (index == 13)
            return 4;
        if (index == 14)
            return 4;
        if (index == 15)
            return 1;
        if (index == 16)
            return 5;
        if (index == 17)
            return 6;
        if (index == 18)
            return 1;
        if (index == 19)
            return 5;
        if (index == 20)
            return 6;
        if (index == 21)
            return 4;
        int poz = 22;
        for (int i = 0; i < sceneObjects[selectedObjectIndex]->getScriptsCount(); i++) {
            if (index >= poz && index < poz + sceneObjects[selectedObjectIndex]->getAttributeCountFromScripts(i))
                return sceneObjects[selectedObjectIndex]->getAttributeTypeFromScripts(i, index - poz);
            poz += sceneObjects[selectedObjectIndex]->getAttributeCountFromScripts(i);
        }
    }
    return -1;
}

void Scene::changeSelectedColliderType(int type) { //change the collider type of the selected object
    if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0) {
		if (type == 0)
			sceneObjects[selectedObjectIndex]->makeSquareCollider(100);
		if (type == 1)
			sceneObjects[selectedObjectIndex]->makeCircleCollider(50);
		if (type == 2)
			sceneObjects[selectedObjectIndex]->makeTriangleCollider(100);
		if (type == 3)
			sceneObjects[selectedObjectIndex]->makeHexagonCollider(50);
	}
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
            delete script;
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
    sceneViewPositionBeforePlaying = Game::getSceneView()->getCenter();
    sceneViewZoomBeforePlaying = Game::getSceneView()->getSize();
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
            if (drawColliders || (selectedObjectIndex != -1 && sortedObjects[i]->getId() == sceneObjects[selectedObjectIndex]->getId())) {
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
    //cout<<"End scene\n";
    for (int i = 0; i < sceneObjects.size(); i++) {
        if (sceneObjects[i]->getActive())
            sceneObjects[i]->destroyScripts();
    }
    //cout<<"Ended the scripts\n";
    clearObjects();
    //cout<<"Deleted the objects\n";
    if (sceneBeforePlaying) {
        int ids = getId();
        while (Game::getHierarchy()->getTextCount() > 0)
            removeTextFromHierarchy(0);
        //cout<<"Removed the texts\n";
        //sceneObjects = sceneBeforePlaying->sceneObjects;
        setObjects(sceneBeforePlaying->sceneObjects);
        lastPositions = sceneBeforePlaying->lastPositions;
        sceneViewPositionBeforePlaying = sceneBeforePlaying->sceneViewPositionBeforePlaying;
        sceneViewZoomBeforePlaying = sceneBeforePlaying->sceneViewZoomBeforePlaying;
        Game::getSceneView()->setCenter(sceneViewPositionBeforePlaying);
        Game::getSceneView()->setSize(sceneViewZoomBeforePlaying);
        /*cout<<"Restored the objects\n"<<sceneObjects.size()<<'\n';
        cout << "Before loop: " << Game::getHierarchy()->getTextCount() << '\n';
        for (int i = 0; i < sceneObjects.size(); i++) {
            addTextToHierarchy(sceneObjects[i]->getName());
            cout<<"Added the text " << i << " of " << sceneObjects.size() << "\n";
        }
        cout<<"After loop: " << Game::getHierarchy()->getTextCount() << '\n';*/
            //addTextToHierarchy("Nume");
        //cout<<"Added the texts\n";
        setId(ids);
        delete sceneBeforePlaying;
        sceneBeforePlaying = NULL;
        //cout<<"Deleted the sceneBeforePlaying\n";
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
    getline(in, sceneName);
    in >> buildIndex;
    in>> sceneViewPositionBeforePlaying.x >> sceneViewPositionBeforePlaying.y >> sceneViewZoomBeforePlaying.x >> sceneViewZoomBeforePlaying.y;
    Game::getSceneView()->setCenter(sceneViewPositionBeforePlaying);
    Game::getSceneView()->setSize(sceneViewZoomBeforePlaying);
    //cout<<"Values read" << sceneViewPositionBeforePlaying.x << " " << sceneViewPositionBeforePlaying.y << " " << sceneViewZoomBeforePlaying.x << " " << sceneViewZoomBeforePlaying.y << endl;
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
    out << sceneName << "\n" << buildIndex << endl;
    out << Game::getSceneView()->getCenter().x << " " << Game::getSceneView()->getCenter().y << " " << Game::getSceneView()->getSize().x << " " << Game::getSceneView()->getSize().y << endl;
    out<< getObjectsCount() << endl;
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

Scene::~Scene() {
    clearObjects();
	if (sceneBeforePlaying)
		delete sceneBeforePlaying;
} //destructor
