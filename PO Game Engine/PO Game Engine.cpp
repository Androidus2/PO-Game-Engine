#include <iostream>
#include <iomanip>
#include <sstream>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"


using namespace sf;
using namespace std;


class Utility {
public:
    static float magnitude(const Vector2f& source);
    static float dotProduct(const Vector2f& source1, const Vector2f& source2);
    static Vector2f normalize(const Vector2f& source);
    static Vector2f calculateNormal(const Vector2f& source);
    static Vector2f direction(const Vector2f& source, const Vector2f& target);
};

float Utility::magnitude(const Vector2f& source)
{
    return sqrt((source.x * source.x) + (source.y * source.y));
}
float Utility::dotProduct(const Vector2f& source1, const Vector2f& source2)
{
    return source1.x * source2.x + source1.y * source2.y;
}
Vector2f Utility::normalize(const Vector2f& source)
{
    float length = magnitude(source);
    if (length != 0)
    {
        return Vector2f(source.x / length, source.y / length);
    }
    return source;
}
Vector2f Utility::calculateNormal(const Vector2f& source)
{
    return normalize(Vector2f(source.y, -source.x));
}
Vector2f Utility::direction(const Vector2f& source, const Vector2f& target)
{
    return normalize(Vector2f(target.x - source.x, target.y - source.y));
}

class GameTime {
private:
    Clock clock;
    float deltaTime;
    float time;
    static GameTime* instance;
public:
    GameTime();
    void update();
    float getDeltaTime() const;
    float getTime() const;
    static GameTime* getInstance();
};
GameTime::GameTime() {
    deltaTime = 0;
    time = 0;
}
void GameTime::update() {
    deltaTime = clock.restart().asSeconds();
    time += deltaTime;
}
float GameTime::getDeltaTime() const {
    return deltaTime;
}
float GameTime::getTime() const {
    return time;
}
GameTime* GameTime::getInstance() {
    if (instance == NULL)
        instance = new GameTime();
    return instance;
}


class GameObject;

class Collider {
protected:
    Vector2f colliderOffset;
    float colliderRotation;
    Vector2f colliderScale;
    Shape* colliderShape;
    bool colliderIsCircle;
    bool colliderIsActive;
    bool colliderIsTrigger;
    float mass;
    bool isMovable;
    bool useGravity;

    void cleanShape(Vector2f& position, float& rotation, Vector2f& scale);
    void fixShape(Vector2f& position, float& rotation, Vector2f& scale);

private:
    static bool findMinSeparation(const GameObject& collider1, const GameObject& collider2, Vector2f& sep);
    static void moveCollidersInCollision(GameObject& collider1, GameObject& collider2, const Vector2f& displacement);
    static bool polygonCollision(GameObject& collider1, GameObject& collider2);
    static bool circleCollision(GameObject& collider1, GameObject& collider2);

public:
    Collider();
    Collider(const Vector2f& colliderOffset, float colliderRotation, const Vector2f& colliderScale,
        Shape* colliderShape, bool colliderIsCircle, bool colliderIsActive, bool colliderIsTrigger,
        float mass, bool isMovable, bool useGravity);
    Collider(const Collider& collider);
    Collider& operator=(const Collider& collider);

    Vector2f getColliderOffset() const;
    void setColliderOffset(const Vector2f& colliderOffset);

    float getColliderRotation() const;
    void setColliderRotation(float colliderRotation);

    Vector2f getColliderScale() const;
    void setColliderScale(const Vector2f& colliderScale);

    const Shape* getColliderShape() const;
    void setColliderShape(Shape* colliderShape, bool isCircle);

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

    void test() { cout << colliderShape->getPosition().x << " " << colliderShape->getPosition().y << endl; }

    void updateTransform(const Vector2f& colliderOffset, float colliderRotation, const Vector2f& colliderScale);
    void updateTransform(const Transformable& transform);

    static bool collision(GameObject& collider1, GameObject& collider2);
    static void handleAllCollisions(const vector<GameObject*>& objects, const vector<Vector2f>& lastPositions);

    ~Collider();
};

Collider::Collider() {
    colliderShape = new CircleShape(50.f);
    colliderOffset = Vector2f();
    colliderRotation = 0.f;
    colliderScale = Vector2f(1.f, 1.f);
    colliderShape->setOrigin(colliderShape->getLocalBounds().getSize() / 2.f);
    colliderIsCircle = true;
    colliderIsActive = true;
    colliderIsTrigger = false;
    mass = 1.f;
    isMovable = true;
    useGravity = false;
}
Collider::Collider(const Vector2f& colliderOffset, float colliderRotation, const Vector2f& colliderScale, Shape* colliderShape, bool colliderIsCircle, bool colliderIsActive, bool colliderIsTrigger, float mass, bool isMovable, bool useGravity) {
    this->colliderIsCircle = colliderIsCircle;
    this->colliderOffset = colliderOffset;
    this->colliderRotation = colliderRotation;
    this->colliderScale = colliderScale;
    this->mass = mass;
    this->isMovable = isMovable;
    this->useGravity = useGravity;

    if (colliderIsCircle)
        this->colliderShape = new CircleShape(static_cast<CircleShape&>(*colliderShape));
    else
        this->colliderShape = new ConvexShape(static_cast<ConvexShape&>(*colliderShape));

    this->colliderShape->move(this->colliderOffset);
    this->colliderShape->rotate(this->colliderRotation);
    this->colliderShape->scale(this->colliderScale);
    this->colliderShape->setOrigin(this->colliderShape->getLocalBounds().getSize() / 2.f);

    this->colliderIsActive = colliderIsActive;
    this->colliderIsTrigger = colliderIsTrigger;

    if (this->mass < 0.01f)
        this->mass = 0.01f;
}
Collider::Collider(const Collider& collider) {
    colliderIsCircle = collider.colliderIsCircle;
    colliderIsActive = collider.colliderIsActive;
    colliderIsTrigger = collider.colliderIsTrigger;
    colliderOffset = collider.colliderOffset;
    colliderRotation = collider.colliderRotation;
    colliderScale = collider.colliderScale;
    mass = collider.mass;
    isMovable = collider.isMovable;
    useGravity = collider.useGravity;

    if (colliderIsCircle)
        colliderShape = new CircleShape(static_cast<CircleShape&>(*collider.colliderShape));
    else
        colliderShape = new ConvexShape(static_cast<ConvexShape&>(*collider.colliderShape));

    colliderShape->move(colliderOffset);
    colliderShape->rotate(colliderRotation);
    colliderShape->scale(colliderScale);
    colliderShape->setOrigin(colliderShape->getLocalBounds().getSize() / 2.f);

    if (this->mass < 0.01f)
        this->mass = 0.01f;
}
Collider& Collider::operator=(const Collider& collider) {
    if (this == &collider)
        return *this;

    if (colliderShape != NULL)
        delete colliderShape;

    colliderIsCircle = collider.colliderIsCircle;
    colliderIsActive = collider.colliderIsActive;
    colliderIsTrigger = collider.colliderIsTrigger;
    colliderOffset = collider.colliderOffset;
    colliderRotation = collider.colliderRotation;
    colliderScale = collider.colliderScale;
    mass = collider.mass;
    isMovable = collider.isMovable;
    useGravity = collider.useGravity;

    if (colliderIsCircle)
        colliderShape = new CircleShape(static_cast<CircleShape&>(*collider.colliderShape));
    else
        colliderShape = new ConvexShape(static_cast<ConvexShape&>(*collider.colliderShape));

    colliderShape->move(colliderOffset);
    colliderShape->rotate(colliderRotation);
    colliderShape->scale(colliderScale);
    colliderShape->setOrigin(colliderShape->getLocalBounds().getSize() / 2.f);

    if (this->mass < 0.01f)
        this->mass = 0.01f;

    return *this;
}

void Collider::cleanShape(Vector2f& position, float& rotation, Vector2f& scale) {
    position = this->colliderOffset;
    rotation = this->colliderRotation;
    scale = this->colliderScale;
    if (this->colliderShape) {
        position = this->colliderShape->getPosition();
        rotation = this->colliderShape->getRotation();
        scale = this->colliderShape->getScale();
        delete this->colliderShape;
    }
}
void Collider::fixShape(Vector2f& position, float& rotation, Vector2f& scale) {
    this->colliderShape->setRotation(rotation);
    this->colliderShape->setScale(scale);
    this->colliderShape->setOrigin(this->colliderShape->getLocalBounds().getSize() / 2.f);
    this->colliderShape->setPosition(position);
}

Vector2f Collider::getColliderOffset() const {
    return colliderOffset;
}
void Collider::setColliderOffset(const Vector2f& colliderOffset) {
    this->colliderOffset = colliderOffset;
}

float Collider::getColliderRotation() const {
    return colliderRotation;
}
void Collider::setColliderRotation(float colliderRotation) {
    this->colliderRotation = colliderRotation;
}

Vector2f Collider::getColliderScale() const {
    return colliderScale;
}
void Collider::setColliderScale(const Vector2f& colliderScale) {
    this->colliderScale = colliderScale;
}

const Shape* Collider::getColliderShape() const {
    return colliderShape;
}
void Collider::setColliderShape(Shape* colliderShape, bool isCircle) {
    if (!colliderShape)
        return;
    if (this->colliderShape != NULL)
        delete this->colliderShape;

    this->colliderIsCircle = isCircle;
    if (isCircle) {
        this->colliderShape = new CircleShape(static_cast<CircleShape&>(*colliderShape));
        this->colliderIsCircle = true;
    }
    else {
        this->colliderShape = new ConvexShape(static_cast<ConvexShape&>(*colliderShape));
        this->colliderIsCircle = false;
    }

    this->colliderShape->move(colliderOffset);
    this->colliderShape->rotate(colliderRotation);
    this->colliderShape->scale(colliderScale);
    this->colliderShape->setOrigin(this->colliderShape->getLocalBounds().getSize() / 2.f);
}

bool Collider::getColliderIsCircle() const {
    return colliderIsCircle;
}

bool Collider::getColliderIsActive() const {
    return colliderIsActive;
}
void Collider::setColliderIsActive(bool colliderIsActive) {
    this->colliderIsActive = colliderIsActive;
}

bool Collider::getColliderIsTrigger() const {
    return colliderIsTrigger;
}
void Collider::setColliderIsTrigger(bool colliderIsTrigger) {
    this->colliderIsTrigger = colliderIsTrigger;
}

float Collider::getMass() const {
    return mass;
}
void Collider::setMass(float mass) {
    this->mass = mass;
    if (this->mass < 0.01f)
        this->mass = 0.01f;
}

bool Collider::getIsMovable() const {
    return isMovable;
}
void Collider::setIsMovable(bool isMovable) {
    this->isMovable = isMovable;
}

bool Collider::getUseGravity() const {
    return useGravity;
}
void Collider::setUseGravity(bool useGravity) {
    this->useGravity = useGravity;
}

void Collider::makeCircleCollider(float radius) {
    this->colliderIsCircle = true;
    Vector2f position, scale;
    float rotation;
    cleanShape(position, rotation, scale);
    this->colliderShape = new CircleShape(radius);
    fixShape(position, rotation, scale);
}

void Collider::makeSquareCollider(float sideLength) {
    this->colliderIsCircle = false;
    Vector2f position, scale;
    float rotation;
    cleanShape(position, rotation, scale);

    ConvexShape* tmp = new ConvexShape();
    tmp->setPointCount(4);
    tmp->setPoint(0, Vector2f(0, 0));
    tmp->setPoint(1, Vector2f(sideLength, 0));
    tmp->setPoint(2, Vector2f(sideLength, sideLength));
    tmp->setPoint(3, Vector2f(0, sideLength));
    this->colliderShape = tmp;

    fixShape(position, rotation, scale);
}

void Collider::makeTriangleCollider(float sideLength) {
    this->colliderIsCircle = false;
    Vector2f position, scale;
    float rotation;
    cleanShape(position, rotation, scale);

    float height = sideLength * sqrt(3) / 2.f;
    ConvexShape* tmp = new ConvexShape();
    tmp->setPointCount(3);
    tmp->setPoint(0, Vector2f(sideLength / 2.f, 0));
    tmp->setPoint(1, Vector2f(sideLength, height));
    tmp->setPoint(2, Vector2f(0, height));
    this->colliderShape = tmp;

    fixShape(position, rotation, scale);
}

void Collider::makeHexagonCollider(float sideLength) {
    this->colliderIsCircle = false;
    Vector2f position, scale;
    float rotation;
    cleanShape(position, rotation, scale);

    float height = sideLength * sqrt(3) / 2.f;
    ConvexShape* tmp = new ConvexShape();
    tmp->setPointCount(6);
    tmp->setPoint(0, Vector2f(sideLength * 0.5f, 0));
    tmp->setPoint(1, Vector2f(sideLength * 1.5f, 0));
    tmp->setPoint(2, Vector2f(sideLength * 2.f, height));
    tmp->setPoint(3, Vector2f(sideLength * 1.5f, height * 2));
    tmp->setPoint(4, Vector2f(sideLength * 0.5f, height * 2));
    tmp->setPoint(5, Vector2f(0, height));
    this->colliderShape = tmp;

    fixShape(position, rotation, scale);
}

void Collider::updateTransform(const Vector2f& position, float colliderRotation, const Vector2f& colliderScale) {
    colliderShape->setPosition(position + colliderOffset);
    colliderShape->setRotation(colliderRotation + this->colliderRotation);
    colliderShape->setScale(colliderScale.x * this->colliderScale.x, colliderScale.y * this->colliderScale.y);
}
void Collider::updateTransform(const Transformable& transform) {
    colliderShape->setPosition(transform.getPosition() + colliderOffset);
    colliderShape->setRotation(transform.getRotation() + this->colliderRotation);
    colliderShape->setScale(transform.getScale().x * this->colliderScale.x, transform.getScale().y * this->colliderScale.y);
}

Collider::~Collider() {
    if (colliderShape != NULL)
        delete colliderShape;
}


class BehaviourScript {
public:
    virtual BehaviourScript* clone() const = 0;
    virtual void start(GameObject& gameObject) = 0;
    virtual void update(GameObject& gameObject) = 0;
    virtual void collision(GameObject& gameObject, GameObject& collisionObject) = 0;
    virtual void trigger(GameObject& gameObject, GameObject& triggerObject) = 0;
    virtual void destroy(GameObject& gameObject) = 0;
    virtual ~BehaviourScript() {}
};


class GameObject : public Collider, public ConvexShape {
private:
    string name;
    bool isActive;
    int zLayer;
    Vector2f velocity;
    int id;
    static int idCounter;
    vector<BehaviourScript*> attachedScripts;
public:
    GameObject();
    GameObject(const GameObject& gameObject);
    GameObject& operator=(const GameObject& gameObject);

    string getName() const;
    void setName(string name);

    bool getActive() const;
    void setActive(bool isActive);

    int getId() const;

    int getZLayer() const;
    void setZLayer(int layer);

    Vector2f getVelocity() const;
    void setVelocity(const Vector2f& velocity);
    void setVelocity(float x, float y);

    void addScript(BehaviourScript* script);
    int scriptIndex(BehaviourScript* script) const;
    void removeScript(BehaviourScript* script);
    void removeScript(int index);
    void removeAllScripts();
    int getScriptsCount() const;

    void startScripts();
    void updateScripts();
    void triggerScripts(GameObject& trigger);
    void collisionScripts(GameObject& collision);
    void destroyScripts();

    void setPosition(const Vector2f& position);
    void setPosition(float x, float y);
    void move(const Vector2f& position);
    void move(float x, float y);

    ~GameObject();
};

GameObject::GameObject() : Collider(), ConvexShape(), id(idCounter++) {
    this->name = "Object";
    this->isActive = true;
    this->zLayer = 0;
}
GameObject::GameObject(const GameObject& gameObject) : Collider(gameObject), ConvexShape(gameObject), id(gameObject.id) {
    this->name = gameObject.name;
    this->isActive = gameObject.isActive;
    this->zLayer = gameObject.zLayer;
    this->velocity = gameObject.velocity;
    for (int i = 0; i < gameObject.attachedScripts.size(); i++)
        this->attachedScripts.push_back(gameObject.attachedScripts[i]->clone());
}
GameObject& GameObject::operator=(const GameObject& gameObject) {
    if (this == &gameObject)
        return *this;
    Collider::operator=(gameObject);
    ConvexShape::operator=(gameObject);
    this->name = gameObject.name;
    this->isActive = gameObject.isActive;
    this->zLayer = gameObject.zLayer;
    this->velocity = gameObject.velocity;

    removeAllScripts();
    for (int i = 0; i < gameObject.attachedScripts.size(); i++)
        this->attachedScripts.push_back(gameObject.attachedScripts[i]->clone());

    return *this;
}

string GameObject::getName() const {
    return this->name;
}
void GameObject::setName(string name) {
    this->name = name;
}

bool GameObject::getActive() const {
    return this->isActive;
}
void GameObject::setActive(bool isActive) {
    this->isActive = isActive;
}

int GameObject::getId() const {
    return id;
}

int GameObject::getZLayer() const {
    return zLayer;
}
void GameObject::setZLayer(int zLayer) {
    this->zLayer = zLayer;
}

Vector2f GameObject::getVelocity() const {
    return this->velocity;
}
void GameObject::setVelocity(const Vector2f& velocity) {
    this->velocity = velocity;
}
void GameObject::setVelocity(float x, float y) {
    this->velocity.x = x;
    this->velocity.y = y;
}

void GameObject::addScript(BehaviourScript* script) {
    if (scriptIndex(script) == -1)
        this->attachedScripts.push_back(script->clone());
}
int GameObject::scriptIndex(BehaviourScript* script) const {
    return -1; //Has to be implemented
}
void GameObject::removeScript(BehaviourScript* script) {
    removeScript(scriptIndex(script));
}
void GameObject::removeScript(int index) {
    if (index < attachedScripts.size() && index >= 0) {
        delete attachedScripts[index];
        attachedScripts.erase(attachedScripts.begin() + index);
    }
}
void GameObject::removeAllScripts() {
    int i = attachedScripts.size();
    while (i > 0) {
        if (attachedScripts[i - 1])
            delete attachedScripts[i - 1];
        --i;
        attachedScripts.pop_back();
    }
}
int GameObject::getScriptsCount() const {
    return attachedScripts.size();
}

void GameObject::startScripts() {
    for (int i = 0; i < attachedScripts.size(); i++)
        attachedScripts[i]->start(*this);
}
void GameObject::updateScripts() {
    float dt = GameTime::getInstance()->getDeltaTime();
    move(velocity * dt);
    if (useGravity) {
        move(dt * dt * Vector2f(0, 9.81f * 10) / 2.f);
        velocity += dt * Vector2f(0, 9.81f * 10);
    }
    for (int i = 0; i < attachedScripts.size(); i++)
        attachedScripts[i]->update(*this);
}
void GameObject::triggerScripts(GameObject& trigger) {
    for (int i = 0; i < attachedScripts.size(); i++)
        attachedScripts[i]->trigger(*this, trigger);
}
void GameObject::collisionScripts(GameObject& collision) {
    for (int i = 0; i < attachedScripts.size(); i++)
        attachedScripts[i]->collision(*this, collision);
}
void GameObject::destroyScripts() {
    for (int i = 0; i < attachedScripts.size(); i++)
        attachedScripts[i]->destroy(*this);
}

void GameObject::setPosition(const Vector2f& position) {
    ConvexShape::setPosition(position);
    Collider::updateTransform(*this);
}
void GameObject::setPosition(float x, float y) {
    ConvexShape::setPosition(x, y);
    Collider::updateTransform(*this);
}
void GameObject::move(const Vector2f& position) {
    ConvexShape::move(position);
    Collider::updateTransform(*this);
}
void GameObject::move(float x, float y) {
    ConvexShape::move(x, y);
    Collider::updateTransform(*this);
}

GameObject::~GameObject() {
    removeAllScripts();
}


class TestScript : public BehaviourScript {
private:
    Color defaultColor;
    Color pressedColor;
public:
    TestScript(Color a, Color b) {
        setColors(a, b);
    }
    void setColors(Color a, Color b) {
        defaultColor = a;
        pressedColor = b;
    }
    TestScript* clone() const;
    void start(GameObject& gameObject);
    void update(GameObject& gameObject);
    void collision(GameObject& gameObject, GameObject& collisionObject);
    void trigger(GameObject& gameObject, GameObject& triggerObject);
    void destroy(GameObject& gameObject);
    ~TestScript();
};

TestScript* TestScript::clone() const {
    return new TestScript(*this);
}
void TestScript::start(GameObject& gameObject) {
    cout << "Start function called on object with id " << gameObject.getId() << endl;
}
void TestScript::update(GameObject& gameObject) {
    if (Mouse::isButtonPressed(Mouse::Left))
        gameObject.setFillColor(pressedColor);
    else
        gameObject.setFillColor(defaultColor);
    //cout << "Update function called on object with id " << gameObject.getId() << endl;
}
void TestScript::collision(GameObject& gameObject, GameObject& collisionObject) {
    cout << "Collision function called on object with id " << gameObject.getId() << endl;
}
void TestScript::trigger(GameObject& gameObject, GameObject& triggerObject) {
    cout << "Trigger function called on object with id " << gameObject.getId() << endl;
}
void TestScript::destroy(GameObject& gameObject) {
    cout << "Destroy function called on object with id " << gameObject.getId() << endl;
}
TestScript::~TestScript() {
    cout << "Destructor called" << endl;
}





class Scene {
private:
    string sceneName;
    vector<GameObject*> sceneObjects;
    vector<Vector2f> lastPositions;
    int sceneId;
    static int sceneIdCounter;
    int buildIndex;
    //TODO: Selection
    int selectedObjectIndex; //Change to int*

    void addLastPosition(const Vector2f& position);
    void eraseLastPosition(int index);
    void clearLastPositions();
public:
    Scene();
    Scene(const Scene& scene);
    Scene& operator=(const Scene& scene);

    int getObjectsCount() const;

    string getName() const;
    void setName(string name);

    const vector<GameObject*>& getObjects() const;
    const GameObject* getObjectByIndex(int index) const;
    void setObjects(const vector<GameObject*>& objects);
    void setObjectByIndex(int index, const GameObject* object);
    void clearObjects();
    void addObject(const GameObject* object);
    void removeObjectByIndex(int index);
    void removeObjectById(int id);
    bool sceneHasObject(int id) const;
    void removeSelectedObject();

    void modifySelectedName(string name);
    void modifySelectedRotation(string rotation);
    void modifySelectedScaleX(string scaleX);
    void modifySelectedScaleY(string scaleY);
    void modifySelectedPositionX(string positionX);
    void modifySelectedPositionY(string positionY);
    void modifySelectedVelocityX(string velocityX);
    void modifySelectedVelocityY(string velocityY);

    string getSelectedName() const;
    string getSelectedRotation() const;
    string getSelectedScaleX() const;
    string getSelectedScaleY() const;
    string getSelectedPositionX() const;
    string getSelectedPositionY() const;
    string getSelectedVelocityX() const;
	string getSelectedVelocityY() const;

    void setLastPositions(const vector<Vector2f>& lastPositions);
    const vector<Vector2f>& getLastPositions() const;
    void modifyLastPosition(int index, const Vector2f& position);

    void updateScene();

    int getId() const;

    int getBuildIndex() const;
    void setBuildIndex(int buildIndex);

    int getSelectedObjectIndex() const;
    void setSelectedObjectIndex(int index);

    ~Scene();
};

Scene::Scene() : sceneId(sceneIdCounter++) {
    sceneName = "Scene " + sceneId;
    buildIndex = -1;
    selectedObjectIndex = -1;
}
Scene::Scene(const Scene& scene) : sceneId(scene.sceneId) {
    sceneName = scene.sceneName;
    setObjects(scene.sceneObjects);
    buildIndex = scene.buildIndex;
}
Scene& Scene::operator=(const Scene& scene) {
    if (this == &scene)
        return *this;
    sceneName = scene.sceneName;
    setObjects(scene.sceneObjects);
    buildIndex = scene.buildIndex;
    return *this;
}

int Scene::getObjectsCount() const {
    return sceneObjects.size();
}

string Scene::getName() const {
    return sceneName;
}
void Scene::setName(string name) {
    sceneName = name;
}

const vector<GameObject*>& Scene::getObjects() const {
    return sceneObjects;
}
const GameObject* Scene::getObjectByIndex(int index) const {
    if (index < sceneObjects.size() && index >= 0)
        return sceneObjects[index];
    return NULL;
}
void Scene::setObjects(const vector<GameObject*>& objects) {
    clearObjects();
    for (int i = 0; i < objects.size(); i++)
        addObject(objects[i]);
}
void Scene::setObjectByIndex(int index, const GameObject* object) {
    if (index < sceneObjects.size() && index >= 0) {
        delete sceneObjects[index];
        sceneObjects[index] = new GameObject(*object);
    }
}
void Scene::clearObjects() {
    for (int i = 0; i < sceneObjects.size(); i++)
        delete sceneObjects[i];
    sceneObjects.clear();
    clearLastPositions();
    selectedObjectIndex = -1;
}
void Scene::addObject(const GameObject* object) {
    sceneObjects.push_back(new GameObject(*object));
    addLastPosition(object->getPosition());
}
void Scene::removeObjectByIndex(int index) {
    if (selectedObjectIndex == index)
        selectedObjectIndex = -1;
    if (index < sceneObjects.size() && index >= 0) {
        delete sceneObjects[index];
        sceneObjects.erase(sceneObjects.begin() + index);
        eraseLastPosition(index);
    }
}
void Scene::removeObjectById(int id) {
    if (selectedObjectIndex >= 0 && selectedObjectIndex < sceneObjects.size() && sceneObjects[selectedObjectIndex]->getId() == id) {
        selectedObjectIndex = -1;
    }
    for (int i = 0; i < sceneObjects.size(); i++) {
        if (sceneObjects[i]->getId() == id) {
            delete sceneObjects[i];
            sceneObjects.erase(sceneObjects.begin() + i);
            eraseLastPosition(i);
            break;
        }
    }
}
bool Scene::sceneHasObject(int id) const {
    for (int i = 0; i < sceneObjects.size(); i++) {
        if (sceneObjects[i]->getId() == id)
            return true;
    }
    return false;
}
void Scene::removeSelectedObject() {
    if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0) {
        delete sceneObjects[selectedObjectIndex];
        sceneObjects.erase(sceneObjects.begin() + selectedObjectIndex);
        eraseLastPosition(selectedObjectIndex);
        selectedObjectIndex = -1;
    }
}

void Scene::modifySelectedName(string name) {
	if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0)
		sceneObjects[selectedObjectIndex]->setName(name);
}
void Scene::modifySelectedRotation(string rotation) {
	if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0)
		sceneObjects[selectedObjectIndex]->setRotation(stof(rotation));
}
void Scene::modifySelectedScaleX(string scaleX) {
	if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0)
		sceneObjects[selectedObjectIndex]->setScale(stof(scaleX), sceneObjects[selectedObjectIndex]->getScale().y);
}
void Scene::modifySelectedScaleY(string scaleY) {
	if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0)
		sceneObjects[selectedObjectIndex]->setScale(sceneObjects[selectedObjectIndex]->getScale().x, stof(scaleY));
}
void Scene::modifySelectedPositionX(string positionX) {
	if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0)
		sceneObjects[selectedObjectIndex]->setPosition(stof(positionX), sceneObjects[selectedObjectIndex]->getPosition().y);
}
void Scene::modifySelectedPositionY(string positionY) {
	if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0)
		sceneObjects[selectedObjectIndex]->setPosition(sceneObjects[selectedObjectIndex]->getPosition().x, stof(positionY));
}
void Scene::modifySelectedVelocityX(string velocityX) {
	if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0)
		sceneObjects[selectedObjectIndex]->setVelocity(stof(velocityX), sceneObjects[selectedObjectIndex]->getVelocity().y);
}
void Scene::modifySelectedVelocityY(string velocityY) {
	if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0)
		sceneObjects[selectedObjectIndex]->setVelocity(sceneObjects[selectedObjectIndex]->getVelocity().x, stof(velocityY));
}

string Scene::getSelectedName() const {
	if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0)
		return sceneObjects[selectedObjectIndex]->getName();
	return "";
}
string Scene::getSelectedRotation() const {
	if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0)
		return to_string(sceneObjects[selectedObjectIndex]->getRotation());
	return "";
}
string Scene::getSelectedScaleX() const {
	if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0)
		return to_string(sceneObjects[selectedObjectIndex]->getScale().x);
	return "";
}
string Scene::getSelectedScaleY() const {
	if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0)
		return to_string(sceneObjects[selectedObjectIndex]->getScale().y);
	return "";
}
string Scene::getSelectedPositionX() const {
	if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0)
		return to_string(sceneObjects[selectedObjectIndex]->getPosition().x);
	return "";
}
string Scene::getSelectedPositionY() const {
	if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0)
		return to_string(sceneObjects[selectedObjectIndex]->getPosition().y);
	return "";
}
string Scene::getSelectedVelocityX() const {
	if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0)
		return to_string(sceneObjects[selectedObjectIndex]->getVelocity().x);
	return "";
}
string Scene::getSelectedVelocityY() const {
	if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0)
		return to_string(sceneObjects[selectedObjectIndex]->getVelocity().y);
	return "";
}

void Scene::setLastPositions(const vector<Vector2f>& lastPositions) {
    this->lastPositions = lastPositions;
}
const vector<Vector2f>& Scene::getLastPositions() const {
    return lastPositions;
}
void Scene::modifyLastPosition(int index, const Vector2f& position) {
    if (index < lastPositions.size() && index >= 0)
        lastPositions[index] = position;
}
void Scene::addLastPosition(const Vector2f& position) {
    lastPositions.push_back(position);
}
void Scene::eraseLastPosition(int index) {
    if (index < lastPositions.size() && index >= 0)
        lastPositions.erase(lastPositions.begin() + index);
}
void Scene::clearLastPositions() {
    lastPositions.clear();
}

void Scene::updateScene() {
    for (int i = 0; i < sceneObjects.size(); i++) {
        if (sceneObjects[i]->getActive())
            sceneObjects[i]->updateScripts();
    }
    Collider::handleAllCollisions(sceneObjects, lastPositions);
    lastPositions.clear();
    for (int i = 0; i < sceneObjects.size(); i++)
        addLastPosition(sceneObjects[i]->getPosition());
}

int Scene::getId() const {
    return sceneId;
}

int Scene::getBuildIndex() const {
    return buildIndex;
}
void Scene::setBuildIndex(int buildIndex) {
    this->buildIndex = buildIndex;
}

int Scene::getSelectedObjectIndex() const {
    return selectedObjectIndex;
}
void Scene::setSelectedObjectIndex(int index) {
    selectedObjectIndex = index;
}

Scene::~Scene() {}

class EditorWindow;

class Game {
public:
    static Font* font;
    static RenderWindow* window;
    static Scene* currentScene;
    static int collisionCounter;
    static EditorWindow* hierarchy;
};



bool Collider::findMinSeparation(const GameObject& collider1, const GameObject& collider2, Vector2f& sep) {
    float minOverlap = INFINITY;
    Vector2f smallestAxis;
    const Shape* shape1 = collider1.colliderShape;
    const Shape* shape2 = collider2.colliderShape;
    for (int shapeIndex = 0; shapeIndex < 2; shapeIndex++) {
        const Shape* shape = shapeIndex == 0 ? shape1 : shape2;
        for (int i = 0; i < shape->getPointCount(); i++) {
            Vector2f point1 = shape->getTransform().transformPoint(shape->getPoint(i));
            Vector2f point2 = shape->getTransform().transformPoint(shape->getPoint((i + 1) % shape->getPointCount()));
            Vector2f edge = Utility::normalize(point2 - point1);
            Vector2f normal = Utility::calculateNormal(edge);
            float min1 = INFINITY, max1 = -INFINITY;
            float min2 = INFINITY, max2 = -INFINITY;
            for (int j = 0; j < shape1->getPointCount(); j++) {
                float projection = Utility::dotProduct(shape1->getTransform().transformPoint(shape1->getPoint(j)), normal);
                if (projection < min1) min1 = projection;
                if (projection > max1) max1 = projection;
            }
            for (int j = 0; j < shape2->getPointCount(); j++) {
                float projection = Utility::dotProduct(shape2->getTransform().transformPoint(shape2->getPoint(j)), normal);
                if (projection < min2) min2 = projection;
                if (projection > max2) max2 = projection;
            }
            float overlap = max1 - min2; // Calculate overlap
            if (overlap < minOverlap) {
                minOverlap = overlap;
                smallestAxis = normal;
            }
            if (max1 < min2 || max2 < min1) {
                return false; // Separating axis found
            }
        }
    }
    float buffer = 0.01f; // Small buffer to prevent snapping
    sep = (minOverlap + buffer) * smallestAxis; // Move shape2 along the smallest axis by the amount of the minimum overlap plus the buffer
    return true;
}
void Collider::moveCollidersInCollision(GameObject& collider1, GameObject& collider2, const Vector2f& displacement) {
    float totalMass = collider1.mass + collider2.mass;
    Vector2f moveAmount1 = -displacement * (collider2.mass / totalMass);
    Vector2f moveAmount2 = displacement * (collider1.mass / totalMass);

    if (collider1.isMovable) {
        if (collider2.isMovable) {
            collider1.move(moveAmount1);
            collider2.move(moveAmount2);
        }
        else {
            collider1.move(-displacement);
        }
    }
    else {
        if (collider2.isMovable) {
            collider2.move(displacement);
        }
        else {
            cout << "Both objects are immovable!" << endl;
        }
    }
}
bool Collider::polygonCollision(GameObject& collider1, GameObject& collider2) {
    Vector2f displacement;
    bool col1 = findMinSeparation(collider1, collider2, displacement);
    if (col1) {
        if (collider1.colliderIsTrigger || collider2.colliderIsTrigger) {
            //Send message
            return true;
        }
        moveCollidersInCollision(collider1, collider2, displacement);
        return true;
    }
    return false;
}
bool Collider::circleCollision(GameObject& collider1, GameObject& collider2)
{
    const CircleShape* circle1 = static_cast<const CircleShape*>(collider1.colliderShape);
    const CircleShape* circle2 = static_cast<const CircleShape*>(collider2.colliderShape);
    Vector2f direction = Utility::direction(circle1->getPosition(), circle2->getPosition());
    float distance = Utility::magnitude(circle1->getPosition() - circle2->getPosition());
    float overlap = circle1->getRadius() + circle2->getRadius() - distance;

    if (overlap > 0) {

        if (collider1.colliderIsTrigger || collider2.colliderIsTrigger) {
            //Send a message to the objects telling them a collision of type trigger has happened
            return true;
        }

        // The circles are colliding. We need to move them apart.
        Vector2f displacement = direction * overlap;
        moveCollidersInCollision(collider1, collider2, displacement);

        return true;
    }

    return false;
}
bool Collider::collision(GameObject& collider1, GameObject& collider2) {
    if (!collider1.colliderIsActive || !collider2.colliderIsActive)
        return false;
    Game::collisionCounter++;
    bool ret = false;
    if (collider1.colliderIsCircle && collider2.colliderIsCircle)
        ret = circleCollision(collider1, collider2);
    else
        ret = polygonCollision(collider1, collider2);
    return ret;
}
void Collider::handleAllCollisions(const vector<GameObject*>& objects, const vector<Vector2f>& lastPositions) {
    const int iterations = 10; // Number of iterations for collision resolution

    // Resolve collisions
    for (int iteration = 0; iteration < iterations; iteration++) {
        for (int i = 0; i < objects.size(); i++) {
            for (int j = i + 1; j < objects.size(); j++) {
                if (objects[i]->getGlobalBounds().intersects(objects[j]->getGlobalBounds()))
                    collision(*objects[i], *objects[j]);
            }
        }
    }

    // Check if the objects have moved in the opposite direction of their velocity
    for (int i = 0; i < objects.size(); i++) {
        Vector2f displacement = objects[i]->getPosition() - lastPositions[i];

        // If the object has moved in the opposite direction of its velocity, reset its velocity in that direction
        if (displacement.x >= -0.01f && objects[i]->getVelocity().x < 0) {
            objects[i]->setVelocity(Vector2f(0, objects[i]->getVelocity().y));
        }
        if (displacement.x <= 0.01f && objects[i]->getVelocity().x > 0) {
            objects[i]->setVelocity(Vector2f(0, objects[i]->getVelocity().y));
        }
        if (displacement.y >= -0.01f && objects[i]->getVelocity().y < 0) {
            objects[i]->setVelocity(Vector2f(objects[i]->getVelocity().x, 0));
        }
        if (displacement.y <= 0.01f && objects[i]->getVelocity().y > 0) {
            objects[i]->setVelocity(Vector2f(objects[i]->getVelocity().x, 0));
        }
    }
}


class FollowMouseScript : public BehaviourScript {
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
    ~FollowMouseScript();
};
FollowMouseScript::FollowMouseScript(bool applySmoothness, float smoothnessSpeed) {
    this->applySmoothness = applySmoothness;
    this->smoothnessSpeed = smoothnessSpeed;
}
FollowMouseScript* FollowMouseScript::clone() const {
    return new FollowMouseScript(*this);
}
void FollowMouseScript::start(GameObject& gameObject) {

}
void FollowMouseScript::update(GameObject& gameObject) {
    Vector2f mousePosition = Vector2f(Mouse::getPosition(*Game::window).x, Mouse::getPosition(*Game::window).y);
    if (applySmoothness)
        mousePosition = gameObject.getPosition() + (-gameObject.getPosition() + mousePosition) * GameTime::getInstance()->getDeltaTime() * smoothnessSpeed;
    //cout << mousePosition.x<<" "<<mousePosition.y <<" "<< GameTime::getInstance()->getDeltaTime() << endl;
    gameObject.setPosition(mousePosition);
}
void FollowMouseScript::collision(GameObject& gameObject, GameObject& collisionObject) {

}
void FollowMouseScript::trigger(GameObject& gameObject, GameObject& triggerObject) {

}
void FollowMouseScript::destroy(GameObject& gameObject) {

}
FollowMouseScript::~FollowMouseScript() {

}



int Scene::sceneIdCounter = 0;
int GameObject::idCounter = 500;
int Game::collisionCounter = 0;
GameTime* GameTime::instance = NULL;
RenderWindow* Game::window = NULL;
Scene* Game::currentScene = NULL;
EditorWindow* Game::hierarchy = NULL;
Font* Game::font = NULL;

void makeObj(GameObject& ob, const Vector2f& position, float sideLen) {
    ob.setPointCount(4);
    ob.setPoint(0, Vector2f(0, 0));
    ob.setPoint(1, Vector2f(sideLen, 0));
    ob.setPoint(2, Vector2f(sideLen, sideLen));
    ob.setPoint(3, Vector2f(0, sideLen));
    ob.setOrigin(ob.getGlobalBounds().getSize() / 2.f);
    ob.setPosition(position);
    ob.makeSquareCollider(sideLen);
}

string floatToString(float f, int precision = 2) {
    stringstream ss;
    ss << fixed << setprecision(precision) << f;
    return ss.str();
}

class InputField {
private:
    RectangleShape field;
    Text text;
    bool isSelected;
    int cursorIndex;
    bool onlyNumbers;
    string str;
    void (Scene::*onChange)(string str);
    string(Scene::* updateValue)() const;

public:
    InputField(const Font& font, const Vector2f& position, const Vector2f& size, const string& defaultText = "");
    void draw(RenderWindow& window);
    void update();
    void handleEvent(Event& event);
    void select();
    void deselect();
    bool getSelected() const;
    string getText() const;
    void setText(const string& text);
    void clear();
    void setPosition(const Vector2f& position);
    Vector2f getPosition() const;
    void setOnlyNumbers(bool onlyNumbers);
    bool getOnlyNumbers() const;
    void checkMouseClick();
    void changeBackground();
    void setOnChange(void (Scene::*onChange)(string str));
    void setUpdateValue(string(Scene::* updateValue)() const);
    string processText();
};

InputField::InputField(const Font& font, const Vector2f& position, const Vector2f& size, const string& defaultText) {
    field.setSize(size);
    field.setFillColor(Color(100, 100, 100));
    field.setOutlineColor(Color::Black);
    field.setOutlineThickness(1);
    field.setPosition(position);

    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(Color::White);
    text.setString(defaultText);
    text.setPosition(position.x, position.y);

    isSelected = false;
    cursorIndex = 0;
    onlyNumbers = false;
    str = defaultText;
    onChange = NULL;
    updateValue = NULL;
}
void InputField::draw(RenderWindow& window) {
    window.draw(field);
    window.draw(text);
}
void InputField::update() {
    if (isSelected) {
        float t = fmod(GameTime::getInstance()->getTime(), 1.0f);
        if (t < 0.7f) {
            string tmp = str;
            tmp.insert(cursorIndex, "|");
            text.setString(tmp);
        }
        else {
            text.setString(str);
        }
    }
    else {
        if(updateValue) str = (Game::currentScene->*updateValue)();
        text.setString(str);
	}
}
void InputField::handleEvent(Event& event) {
    if (isSelected) {
        if (event.type == Event::TextEntered) {
            if (onlyNumbers) {
                if (event.text.unicode == 8) {
                    if (str.size() > 0 && cursorIndex > 0) {
                        str = str.substr(0, cursorIndex - 1) + str.substr(cursorIndex);
                        cursorIndex--;
                    }
                }
                else if (event.text.unicode == 13) {
                    deselect();
                }
                else if (event.text.unicode == 46) {
                    if (str.find('.') == string::npos) {
                        if (str.size() > 0 && cursorIndex == 0 && str[0] == '-')
                            cursorIndex++;
                        str = str.substr(0, cursorIndex) + '.' + str.substr(cursorIndex);
                        cursorIndex++;
                    }
                }
                else if (event.text.unicode == 45) {
                    if (str[0] != '-') {
                        str = '-' + str;
                        cursorIndex++;
                    }
                    else {
                        str = str.substr(1);
                        cursorIndex--;
                    }
                }
                else if (event.text.unicode >= 48 && event.text.unicode <= 57) {
                    if (str.size() > 0 && cursorIndex == 0 && str[0] == '-')
                        cursorIndex++;
                    str = str.substr(0, cursorIndex) + event.text.unicode + str.substr(cursorIndex);
                    cursorIndex++;
                }
            }
            else {
                if (event.text.unicode == 8) {
                    if (str.size() > 0 && cursorIndex > 0) {
                        str = str.substr(0, cursorIndex - 1) + str.substr(cursorIndex--);
                    }
                }
                else if (event.text.unicode == 13) {
                    deselect();
                }
                else {
                    str = str.substr(0, cursorIndex) + event.text.unicode + str.substr(cursorIndex++);
                }
            }
            if(onChange) (Game::currentScene->*onChange)(processText());
        }
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Left) {
                cursorIndex--;
            }
            if (event.key.code == Keyboard::Right) {
                cursorIndex++;
            }
            if (cursorIndex < 0)
                cursorIndex = 0;
            if (cursorIndex > str.size())
                cursorIndex = str.size();

            if (event.key.control && event.key.code == Keyboard::V) {
                string tmp = Clipboard::getString();
                str = "";
                if (onlyNumbers) {
                    for (int i = 0; i < tmp.size(); i++) {
                        if (tmp[i] == 46 && str.find('.') == string::npos) {
                            str += tmp[i];
                        }
                        else if (tmp[i] == 45 && str.find('-') == string::npos && i == 0) {
                            str += tmp[i];
                        }
                        else if (tmp[i] >= 48 && tmp[i] <= 57) {
                            str += tmp[i];
                        }
                    }
                }
                else {
                    str = tmp;
                }
                cursorIndex = str.size();
                str = processText();
                if (onChange) (Game::currentScene->*onChange)(str);
            }
            if (event.key.control && event.key.code == Keyboard::C) {
                Clipboard::setString(str);
            }
        }
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            int x = Mouse::getPosition(*Game::window).x - field.getPosition().x;
            cout << x << " " << text.findCharacterPos(0).x << endl;
            cursorIndex = x * 2 / text.getCharacterSize();
            if (cursorIndex > str.size())
                cursorIndex = str.size();
            if (cursorIndex < 0)
                cursorIndex = 0;
        }
    }
}
void InputField::select() {
    isSelected = true;
    cursorIndex = str.size();
}
void InputField::deselect() {
    isSelected = false;

    str = processText();

    text.setString(str);
}
bool InputField::getSelected() const {
    return isSelected;
}
string InputField::getText() const {
    return str;
}
void InputField::setText(const string& text) {
    str = text;
    this->text.setString(str);
}
void InputField::clear() {
    str = "";
    cursorIndex = 0;
    if (onlyNumbers) {
        str = "0";
        cursorIndex = 1;
    }
    text.setString(str);
}
void InputField::setPosition(const Vector2f& position) {
	field.setPosition(position);
	text.setPosition(position.x, position.y);
}
Vector2f InputField::getPosition() const {
	return field.getPosition();
}
void InputField::setOnlyNumbers(bool onlyNumbers) {
    this->onlyNumbers = onlyNumbers;
}
bool InputField::getOnlyNumbers() const {
    return onlyNumbers;
}
void InputField::checkMouseClick() {
    Vector2f mousePosition = Vector2f(Mouse::getPosition(*Game::window).x, Mouse::getPosition(*Game::window).y);
    if (field.getGlobalBounds().contains(mousePosition)) {
        if (!isSelected)
            select();
    }
    else {
        deselect();
    }
}
void InputField::changeBackground() {
    if (isSelected) {
        field.setFillColor(Color::Black);
    }
    else {
        field.setFillColor(Color(150, 150, 150));
    }
}
void InputField::setOnChange(void (Scene::* onChange)(string str)) {
	this->onChange = onChange;
}
void InputField::setUpdateValue(string(Scene::* updateValue)() const) {
	this->updateValue = updateValue;
}
string InputField::processText() {
    string ret = str;
    if (onlyNumbers) {
        if (ret.size() > 0 && ret[0] == '-')
            ret = ret.substr(1);
        while (ret.size() > 1 && ret[0] == '0' && ret[1] != '.')
            ret = ret.substr(1);
        if (!ret.empty() && ret[ret.size() - 1] == '.')
            ret.pop_back();
        if (!ret.empty() && ret[0] == '.')
            ret = "0" + ret;
        if (ret.empty())
            ret = "0";
        while (ret.size() > 2 && ret[ret.size() - 1] == '0' && ret.find('.') != string::npos)
            ret.pop_back();
        if (!ret.empty() && ret[ret.size() - 1] == '.')
            ret.pop_back();
        if (ret != "0" && str.size() > 0 && str[0] == '-')
            ret = "-" + ret;
    }
    return ret;
}

class Button {
private:
    RectangleShape button;
    Text text;
    bool isPressed;
    bool isHovered;
    bool isActive;
    bool isToggle;
    bool isToggled;
    Color defaultColor;
    Color pressedColor;
    Color hoverColor;
    Color textColor;
    void (*onClick)();
public:
    Button(const Font& font, const Vector2f& position, const Vector2f& size, const string& buttonText = "");
    void draw(RenderWindow& window);
    void update();
    void handleEvent(Event& event);
    void press();
    void release();
    void hover();
    void unhover();
    void toggle();
    void setToggle(bool isToggle);
    bool getToggle() const;
    bool getToggled() const;
    void setActive(bool isActive);
    bool getActive() const;
    void setText(const string& text);
    string getText() const;
    void setPosition(const Vector2f& position);
    Vector2f getPosition() const;
    void setDefaultColor(const Color& color);
    Color getDefaultColor() const;
    void setPressedColor(const Color& color);
    Color getPressedColor() const;
    void setHoverColor(const Color& color);
    Color getHoverColor() const;
    void setTextColor(const Color& color);
    Color getTextColor() const;
    void setOnClick(void (*onClick)());
};

Button::Button(const Font& font, const Vector2f& position, const Vector2f& size, const string& buttonText) {
    button.setSize(size);
    button.setFillColor(Color(100, 100, 100));
    button.setOutlineColor(Color::Black);
    button.setOutlineThickness(1);
    button.setPosition(position);

    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(Color::White);
    text.setString(buttonText);
    text.setPosition(position.x + size.x / 2 - text.getLocalBounds().getSize().x / 2, position.y + size.y / 2 - text.getLocalBounds().getSize().y / 2);

    isPressed = false;
    isHovered = false;
    isActive = true;
    isToggle = false;
    isToggled = false;
    defaultColor = Color(100, 100, 100);
    pressedColor = Color(50, 50, 50);
    hoverColor = Color(150, 150, 150);
    textColor = Color::White;
    onClick = NULL;
}
void Button::draw(RenderWindow& window) {
    window.draw(button);
    window.draw(text);
}
void Button::update() {
    if (isActive) {
        if (isPressed)
            button.setFillColor(pressedColor);
        else if (isHovered)
            button.setFillColor(hoverColor);
        else
            button.setFillColor(defaultColor);
    }
    else
        button.setFillColor(Color(50, 50, 50));
}
void Button::handleEvent(Event& event) {
    if (isActive) {
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            Vector2f mousePosition = Vector2f(event.mouseButton.x, event.mouseButton.y);
            if (button.getGlobalBounds().contains(mousePosition) && !isPressed) {
                press();
            }
        }
        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            Vector2f mousePosition = Vector2f(event.mouseButton.x, event.mouseButton.y);
            if (button.getGlobalBounds().contains(mousePosition)) {
                if (isToggle)
                    toggle();
                else
                    release();
            }
        }
        if (event.type == Event::MouseMoved) {
            Vector2f mousePosition = Vector2f(event.mouseMove.x, event.mouseMove.y);
            if (button.getGlobalBounds().contains(mousePosition)) {
                hover();
            }
            else {
                unhover();
            }
        }
    }
}
void Button::press() {
    isPressed = true;
    if (onClick)
        onClick();
}
void Button::release() {
    isPressed = false;
}
void Button::hover() {
    isHovered = true;
}
void Button::unhover() {
    isHovered = false;
}
void Button::toggle() {
    isToggled = !isToggled;
}
void Button::setToggle(bool isToggle) {
    this->isToggle = isToggle;
}
bool Button::getToggle() const {
    return isToggle;
}
bool Button::getToggled() const {
    return isToggled;
}
void Button::setActive(bool isActive) {
    this->isActive = isActive;
}
bool Button::getActive() const {
    return isActive;
}
void Button::setText(const string& text) {
    this->text.setString(text);
}
string Button::getText() const {
    return text.getString();
}
void Button::setPosition(const Vector2f& position) {
	button.setPosition(position);
	text.setPosition(position.x + button.getSize().x / 2 - text.getLocalBounds().getSize().x / 2, position.y + button.getSize().y / 2 - text.getLocalBounds().getSize().y / 2);
}
Vector2f Button::getPosition() const {
	return button.getPosition();
}
void Button::setDefaultColor(const Color& color) {
    defaultColor = color;
}
Color Button::getDefaultColor() const {
    return defaultColor;
}
void Button::setPressedColor(const Color& color) {
    pressedColor = color;
}
Color Button::getPressedColor() const {
    return pressedColor;
}
void Button::setHoverColor(const Color& color) {
    hoverColor = color;
}
Color Button::getHoverColor() const {
    return hoverColor;
}
void Button::setTextColor(const Color& color) {
    textColor = color;
    text.setFillColor(textColor);
}
Color Button::getTextColor() const {
    return textColor;
}
void Button::setOnClick(void (*onClick)()) {
    this->onClick = onClick;
}



Text* updateHierarchy(Text* objectTexts, const RectangleShape& hierarchy, const Font& font, const Text& hierarchyTitle) {
    if (objectTexts)
        delete[] objectTexts;
    const vector<GameObject*>& objects = Game::currentScene->getObjects();
    objectTexts = new Text[objects.size()];
    float objectHeight = (hierarchy.getSize().y - hierarchyTitle.getCharacterSize() * 2) / objects.size();
    for (int i = 0; i < objects.size(); i++) {
        objectTexts[i].setFont(font);
        objectTexts[i].setCharacterSize(15);
        objectTexts[i].setFillColor(Color::White);
        objectTexts[i].setString(objects[i]->getName());
        objectTexts[i].setPosition(hierarchy.getPosition().x + 10, hierarchy.getPosition().y + i * objectHeight + hierarchyTitle.getCharacterSize() + 10);
    }
    return objectTexts;
}


class EditorWindow {
protected:
    RectangleShape window;
	Text title;
	vector<Button> buttons;
	vector<InputField> inputFields;
	vector<Text> texts;
	Vector2f position;
	Vector2f size;
public:
    EditorWindow(const Font& font, const Vector2f& position, const Vector2f& size, const string& titleText = "");

	void draw(RenderWindow& window);
	void update();
	void handleEvent(Event& event);

    virtual void mouseOver() = 0;

	void addButton(const Button& button);
	void addInputField(const InputField& inputField);
	virtual void addText(const Text& text);

    void changeText(int index, const string& text);
    virtual void deleteText(int index);
    int getTextCount() const;

	void setTitle(const string& titleText);
	string getTitle() const;

	void setPosition(const Vector2f& position);
	Vector2f getPosition() const;

	void setSize(const Vector2f& size);
	Vector2f getSize() const;

    virtual ~EditorWindow();
};
EditorWindow::EditorWindow(const Font& font, const Vector2f& position, const Vector2f& size, const string& titleText) {
	window.setPosition(position);
	window.setSize(size);
	window.setFillColor(Color(50, 50, 50));
	window.setOutlineColor(Color::Black);
	window.setOutlineThickness(1);

	title.setFont(font);
	title.setCharacterSize(20);
	title.setFillColor(Color::Cyan);
	title.setString(titleText);
	title.setOrigin(title.getLocalBounds().getSize().x / 2.f, 0.f);
	title.setPosition(position.x + size.x / 2.f, position.y);

	this->position = position;
	this->size = size;
}
void EditorWindow::draw(RenderWindow& window) {
	window.draw(this->window);
	window.draw(title);
	for (int i = 0; i < buttons.size(); i++)
		buttons[i].draw(window);
	for (int i = 0; i < inputFields.size(); i++)
		inputFields[i].draw(window);
	for (int i = 0; i < texts.size(); i++)
		window.draw(texts[i]);
}
void EditorWindow::update() {
	for (int i = 0; i < buttons.size(); i++)
		buttons[i].update();
    for (int i = 0; i < inputFields.size(); i++) {
        inputFields[i].update();
        inputFields[i].changeBackground();
    }

}
void EditorWindow::handleEvent(Event& event) {
	for (int i = 0; i < buttons.size(); i++)
		buttons[i].handleEvent(event);
    for (int i = 0; i < inputFields.size(); i++)
        inputFields[i].handleEvent(event);
}
void EditorWindow::addButton(const Button& button) {
	buttons.push_back(button);
}
void EditorWindow::addInputField(const InputField& inputField) {
	inputFields.push_back(inputField);
}
void EditorWindow::addText(const Text& text) {
	texts.push_back(text);
}
void EditorWindow::changeText(int index, const string& text) {
	if (index < texts.size() && index >= 0)
		texts[index].setString(text);
}
void EditorWindow::deleteText(int index) {
    if (index < texts.size() && index >= 0)
        texts.erase(texts.begin() + index);
}
int EditorWindow::getTextCount() const {
	return texts.size();
}
void EditorWindow::setTitle(const string& titleText) {
	title.setString(titleText);
	title.setOrigin(title.getLocalBounds().getSize().x / 2.f, 0.f);
	title.setPosition(position.x + size.x / 2.f, position.y);
}
string EditorWindow::getTitle() const {
	return title.getString();
}
void EditorWindow::setPosition(const Vector2f& position) {
	window.setPosition(position);
	title.setPosition(position.x + size.x / 2.f, position.y);
	this->position = position;
}
Vector2f EditorWindow::getPosition() const {
	return position;
}
void EditorWindow::setSize(const Vector2f& size) {
	window.setSize(size);
	title.setPosition(position.x + size.x / 2.f, position.y);
	this->size = size;
}
Vector2f EditorWindow::getSize() const {
	return size;
}
EditorWindow::~EditorWindow() {
	buttons.clear();
	inputFields.clear();
	texts.clear();
}

void createObj();
void deleteObj();

class HierarchyWindow : public EditorWindow {
private:
    void repositionTexts();
public:
    HierarchyWindow(const Font& font, const Vector2f& position, const Vector2f& size, const string& titleText = "");
	void mouseOver();
    void addText(const Text& text) override;
    void deleteText(int index) override;
};
void HierarchyWindow::repositionTexts() {
	float objectHeight = (window.getSize().y - title.getCharacterSize() * 2) / texts.size();
    for (int i = 0; i < texts.size(); i++) {
		texts[i].setPosition(window.getPosition().x + 10, window.getPosition().y + i * objectHeight + title.getCharacterSize() + 10);
	}
}
HierarchyWindow::HierarchyWindow(const Font& font, const Vector2f& position, const Vector2f& size, const string& titleText) : EditorWindow(font, position, size, titleText) {
    setTitle("Hierarchy");
    Button* createButton = new Button(font, Vector2f(position.x + 10, position.y + size.y - 40), Vector2f(size.x - 20, 30), "Create Object");
    createButton->setOnClick(createObj);
    addButton(*createButton);
    delete createButton;

    //Adding texts for the objects in the hierarchy
    Text* tmp = new Text("Tmp", font, 15);
    for (int i = 0; i < Game::currentScene->getObjects().size(); i++) {
        tmp->setString(Game::currentScene->getObjectByIndex(i)->getName());
        tmp->setPosition(position.x + 10, position.y + i * 30 + tmp->getCharacterSize() + 10);
        addText(*tmp);
    }
    delete tmp;

    Game::hierarchy = this;
}
void HierarchyWindow::mouseOver() {
    Vector2f mousePos = Vector2f(Mouse::getPosition(*Game::window).x, Mouse::getPosition(*Game::window).y);
    if (window.getGlobalBounds().contains(mousePos)) {
        if(Game::currentScene->getSelectedObjectIndex()!=-1)
            texts[Game::currentScene->getSelectedObjectIndex()].setFillColor(Color::White);
        Game::currentScene->setSelectedObjectIndex(-1);
        for (int i = 0; i < Game::currentScene->getObjectsCount(); i++) {
            if (texts[i].getGlobalBounds().contains(mousePos)) {
                Game::currentScene->setSelectedObjectIndex(i);
                break;
            }
        }
        if (Game::currentScene->getSelectedObjectIndex() != -1)
            texts[Game::currentScene->getSelectedObjectIndex()].setFillColor(Color::Cyan);
    }
}
void HierarchyWindow::addText(const Text& text) {
	texts.push_back(text);
    repositionTexts();
}
void HierarchyWindow::deleteText(int index) {
	if (index < texts.size() && index >= 0){
		texts.erase(texts.begin() + index);
        repositionTexts();
	}
}


class InspectorWindow : public EditorWindow {
public:
    InspectorWindow(const Font& font, const Vector2f& position, const Vector2f& size, const string& titleText = "");
	void mouseOver();
};
InspectorWindow::InspectorWindow(const Font& font, const Vector2f& position, const Vector2f& size, const string& titleText) : EditorWindow(font, position, size, titleText) {
    Text* tmp = new Text("Position:", font, 15);
    tmp->setFillColor(Color::White);

    InputField* tmpField = new InputField(font, Vector2f(position.x + 10, position.y + title.getCharacterSize() + 10), Vector2f(100, 20), "0");

    tmp->setPosition(position.x + 10, position.y + title.getCharacterSize() + 10);
    addText(*tmp);

    tmp->setString("X: ");
    tmp->setPosition(position.x + 10, tmp->getPosition().y + tmp->getCharacterSize() + 10);
    tmpField->setPosition(Vector2f(position.x + 10 + tmp->getLocalBounds().getSize().x, tmp->getPosition().y));
    addText(*tmp);
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedPositionX);
    tmpField->setUpdateValue(&Scene::getSelectedPositionX);
    addInputField(*tmpField);

    tmp->setString("Y: ");
    tmp->setPosition(position.x + 10, tmp->getPosition().y + tmp->getCharacterSize() + 10);
    tmpField->setPosition(Vector2f(position.x + 10 + tmp->getLocalBounds().getSize().x, tmp->getPosition().y));
    addText(*tmp);
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedPositionY);
    tmpField->setUpdateValue(&Scene::getSelectedPositionY);
    addInputField(*tmpField);

    tmp->setString("Rotation: ");
    tmp->setPosition(position.x + 10, tmp->getPosition().y + tmp->getCharacterSize() + 10);
    tmpField->setPosition(Vector2f(position.x + 10 + tmp->getLocalBounds().getSize().x, tmp->getPosition().y));
    addText(*tmp);
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedRotation);
    tmpField->setUpdateValue(&Scene::getSelectedRotation);
    addInputField(*tmpField);

    tmp->setString("Scale: ");
    tmp->setPosition(position.x + 10, tmp->getPosition().y + tmp->getCharacterSize() + 10);
    addText(*tmp);

    tmp->setString("X: ");
    tmp->setPosition(position.x + 10, tmp->getPosition().y + tmp->getCharacterSize() + 10);
    tmpField->setPosition(Vector2f(position.x + 10 + tmp->getLocalBounds().getSize().x, tmp->getPosition().y));
    addText(*tmp);
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedScaleX);
    tmpField->setUpdateValue(&Scene::getSelectedScaleX);
    addInputField(*tmpField);

    tmp->setString("Y: ");
    tmp->setPosition(position.x + 10, tmp->getPosition().y + tmp->getCharacterSize() + 10);
    tmpField->setPosition(Vector2f(position.x + 10 + tmp->getLocalBounds().getSize().x, tmp->getPosition().y));
    addText(*tmp);
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedScaleY);
    tmpField->setUpdateValue(&Scene::getSelectedScaleY);
    addInputField(*tmpField);

    tmp->setString("Velocity: ");
    tmp->setPosition(position.x + 10, tmp->getPosition().y + tmp->getCharacterSize() + 10);
    addText(*tmp);

    tmp->setString("X: ");
    tmp->setPosition(position.x + 10, tmp->getPosition().y + tmp->getCharacterSize() + 10);
    tmpField->setPosition(Vector2f(position.x + 10 + tmp->getLocalBounds().getSize().x, tmp->getPosition().y));
    addText(*tmp);
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedVelocityX);
    tmpField->setUpdateValue(&Scene::getSelectedVelocityX);
    addInputField(*tmpField);

    tmp->setString("Y: ");
    tmp->setPosition(position.x + 10, tmp->getPosition().y + tmp->getCharacterSize() + 10);
    tmpField->setPosition(Vector2f(position.x + 10 + tmp->getLocalBounds().getSize().x, tmp->getPosition().y));
    addText(*tmp);
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedVelocityY);
    tmpField->setUpdateValue(&Scene::getSelectedVelocityY);
    addInputField(*tmpField);

    delete tmp;
    delete tmpField;
}
void InspectorWindow::mouseOver() {
	Vector2f mousePos = Vector2f(Mouse::getPosition(*Game::window).x, Mouse::getPosition(*Game::window).y);
    if (window.getGlobalBounds().contains(mousePos)) {
        for (int i = 0; i < inputFields.size(); i++) {
			inputFields[i].checkMouseClick();
		}
	}
}

void createObj() {
    GameObject* ob = new GameObject();
    makeObj(*ob, Vector2f(100, 100), 100.f);
    Game::currentScene->addObject(ob);
    Text tmp(ob->getName(), *Game::font, 15);
    tmp.setPosition(Game::hierarchy->getPosition().x + 10, Game::hierarchy->getPosition().y + Game::currentScene->getObjects().size() * 30 + tmp.getCharacterSize() + 10);
    Game::hierarchy->addText(tmp);
}

void deleteObj() {
    Game::hierarchy->deleteText(Game::currentScene->getSelectedObjectIndex());
    Game::currentScene->removeSelectedObject();
}




int main()
{
    //See views
    RenderWindow window(VideoMode(1280, 720), "PO Game Engine");
    Game::window = &window;
    Font font;
    font.loadFromFile("Resources/Roboto-Black.ttf");
    Game::font = &font;
    //window.setFramerateLimit(60);
    Scene scene;
    Game::currentScene = &scene;


    float nextSpace = 0;

    GameObject ob;
    ob.setName("Object 0");
    makeObj(ob, Vector2f(100, 100), 100.f);

    BehaviourScript* script = new TestScript(Color::Magenta, Color::Cyan);
    ob.addScript(script);
    delete script;

    script = new FollowMouseScript(true);
    ob.addScript(script);
    delete script;

    ob.startScripts();
    scene.addObject(&ob);

    GameTime* time = GameTime::getInstance();

    Text fpsCounter("FPS: ", font, 15);
    fpsCounter.setFillColor(Color::White);
    fpsCounter.setPosition(10, 10);

    HierarchyWindow hierarchyWindow(font, Vector2f(0, 0), Vector2f(window.getSize().x * 0.25f, window.getSize().y), "Hierarchy");
    InspectorWindow inspectorWindow(font, Vector2f(window.getSize().x * 0.75f, 0), Vector2f(window.getSize().x * 0.25f, window.getSize().y), "Inspector");


    while (window.isOpen())
    {
        //Calculate time and delta time
        time->update();

        Game::collisionCounter = 0;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            hierarchyWindow.handleEvent(event);
            inspectorWindow.handleEvent(event);

            if (scene.getSelectedObjectIndex() != -1) {
                if (Keyboard::isKeyPressed(Keyboard::Delete)) {
                    deleteObj();
                }
            }
        }

        //Only update the fps counter 10 times per second
        if (time->getTime() > nextSpace) {
            nextSpace = time->getTime() + 0.1f;
            fpsCounter.setString("FPS: " + floatToString(1.f / time->getDeltaTime()));
        }

        hierarchyWindow.update();
        inspectorWindow.update();

        //Select object
        if (Mouse::isButtonPressed(Mouse::Left)) {
            hierarchyWindow.mouseOver();
            inspectorWindow.mouseOver();
        }

        scene.updateScene();

        //Clear the window
        window.clear();

        //Draw the objects
        for (int i = 0; i < scene.getObjectsCount(); i++)
            window.draw(*scene.getObjectByIndex(i));


        hierarchyWindow.setTitle("Hierarchy (" + to_string(scene.getObjectsCount()) + ")");

        hierarchyWindow.draw(window);
        inspectorWindow.draw(window);
        window.draw(fpsCounter);

        window.display();
    }

    return 0;
}