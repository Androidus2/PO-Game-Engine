#include "GameObject.h"
#include "BehaviourScript.h"
#include "Collider.h"
#include "GameTime.h"
#include "Utility.h"
#include "GameFilesWindow.h"
#include "Game.h"

using namespace std;
using namespace sf;

void makeObj(GameObject& obj, const Vector2f& position, float sideLen);


istream& GameObject::pRead(istream& in) { //private read function
    Vector2f position;
    float rotation;
    Vector2f scale;
    int r, g, b, a;
    in.get(); // Ignore the newline character
    getline(in, name); // Read the name
    in >> isActive >> zLayer >> velocity.x >> velocity.y >> position.x >> position.y >> rotation >> scale.x >> scale.y >> r >> g >> b >> a;
    setPosition(position);
    setRotation(rotation);
    setScale(scale);
    setFillColor(Color(r, g, b, a));
    in.get(); // Ignore the newline character
    getline(in, tag);
    getline(in, texturePath);
    if (texturePath != "None")
        changeTexture(texturePath);
    Collider::read(in);
    //Read the scripts
    removeAllScripts();
    int scriptCount;
    in >> scriptCount;
    for (int i = 0; i < scriptCount; i++) {
		string scriptName;
		in >> scriptName;
		BehaviourScript* script = makeScriptFromString(scriptName);
        if (script) {
			script->read(in);
			addScript(script);
            delete script;
		}
	}
    return in;
}
ostream& GameObject::pWrite(ostream& out) const { //private write function
    out << name << "\n" << isActive << " " << zLayer << " " << velocity.x << " " << velocity.y << " ";
    out << getPosition().x << " " << getPosition().y << " " << getRotation() << " " << getScale().x << " " << getScale().y
        << " " << static_cast<int>(getFillColor().r) << " " << static_cast<int>(getFillColor().g) << " " << static_cast<int>(getFillColor().b) << " " << static_cast<int>(getFillColor().a) << '\n';
    out << tag << "\n";
    if(texturePath.size() > 3)
        out << texturePath << '\n';
    else
        out << "None" << '\n';
    Collider::write(out);
    //Write the scripts
    out << attachedScripts.size() << '\n';
    for (int i = 0; i < attachedScripts.size(); i++) {
		out << attachedScripts[i]->getScriptName() << '\n';
		attachedScripts[i]->write(out);
	}
    return out;
}

GameObject::GameObject() : Collider(), ConvexShape(), id(idCounter++) { //default constructor
    this->name = "Object";
    this->tag = "Default";
    this->texturePath = "None";
    this->isActive = true;
    this->zLayer = 0;
    this->velocity = Vector2f();
    makeObj(*this, getPosition(), 100.f);
    updateTransform(*this);
}
GameObject::GameObject(const GameObject& gameObject) : Collider(gameObject), ConvexShape(gameObject), id(gameObject.id) { //copy constructor
    //cout<<"Copy constructor called on "<<gameObject.name<<endl;
    this->name = gameObject.name;
    this->tag = gameObject.tag;
    this->texturePath = gameObject.texturePath;
    this->isActive = gameObject.isActive;
    this->zLayer = gameObject.zLayer;
    this->velocity = gameObject.velocity;
    for (int i = 0; i < gameObject.attachedScripts.size(); i++)
        this->attachedScripts.push_back(gameObject.attachedScripts[i]->clone());
    updateTransform(*this);
}
GameObject& GameObject::operator=(const GameObject& gameObject) { //assignment operator
    if (this == &gameObject)
        return *this;
    Collider::operator=(gameObject);
    ConvexShape::operator=(gameObject);
    this->name = gameObject.name;
    this->tag = gameObject.tag;
    this->texturePath = gameObject.texturePath;
    this->isActive = gameObject.isActive;
    this->zLayer = gameObject.zLayer;
    this->velocity = gameObject.velocity;

    removeAllScripts();
    for (int i = 0; i < gameObject.attachedScripts.size(); i++)
        this->attachedScripts.push_back(gameObject.attachedScripts[i]->clone());

    updateTransform(*this);

    return *this;
}
GameObject* GameObject::clone() const { //clone function (used for adding objects to the scene)
    return new GameObject(*this);
}

void GameObject::drawObject(RenderWindow& window) const { //draw the object
    window.draw(*this);
	for (int i = 0; i < attachedScripts.size(); i++)
		attachedScripts[i]->drawScriptElements(*this);
}

string GameObject::getName() const { //get name
    return this->name;
}
void GameObject::setName(string name) { //set name
    this->name = name;
}

string GameObject::getTag() const { //get tag
	return this->tag;
}
void GameObject::setTag(string tag) { //set tag
	this->tag = tag;
}

bool GameObject::getActive() const { //get if the object is active
    return this->isActive;
}
void GameObject::setActive(bool isActive) { //set if the object is active
    this->isActive = isActive;
}

int GameObject::getId() const { //get id
    return id;
}

int GameObject::getZLayer() const { //get zLayer
    return zLayer;
}
void GameObject::setZLayer(int zLayer) { //set zLayer
    this->zLayer = zLayer;
}

Vector2f GameObject::getVelocity() const { //get velocity
    return this->velocity;
}
void GameObject::setVelocity(const Vector2f& velocity) { //set velocity
    this->velocity = velocity;
}
void GameObject::setVelocity(float x, float y) { //set velocity
    this->velocity.x = x;
    this->velocity.y = y;
}

void GameObject::addScript(BehaviourScript* script) { //add a script to the object
    if (scriptIndex(script) == -1 || true)
        this->attachedScripts.push_back(script->clone());
}
int GameObject::scriptIndex(BehaviourScript* script) const { //get the index of a script
    //Loop and check if there is a script with the same name
    for (int i = 0; i < attachedScripts.size(); i++) {
		if (attachedScripts[i]->getScriptName() == script->getScriptName())
			return i;
	}
	return -1;
}
int GameObject::scriptIndex(const string& scriptName) const { //get the index of a script
    //Loop and check if there is a script with the same name
    for (int i = 0; i < attachedScripts.size(); i++) {
     	if (attachedScripts[i]->getScriptName() == scriptName)
     		return i;
    }
    return -1;
}
void GameObject::removeScript(BehaviourScript* script) { //remove a script from the object
    removeScript(scriptIndex(script));
}
void GameObject::removeScript(int index) { //remove a script from the object
    if (index < attachedScripts.size() && index >= 0) {
        delete attachedScripts[index];
        attachedScripts.erase(attachedScripts.begin() + index);
    }
}
void GameObject::removeAllScripts() { //remove all scripts from the object
    int i = attachedScripts.size();
    while (i > 0) {
        if (attachedScripts[i - 1])
            delete attachedScripts[i - 1];
        --i;
        attachedScripts.pop_back();
    }
}
int GameObject::getScriptsCount() const { //get the number of scripts attached to the object
    return attachedScripts.size();
}

void GameObject::startScripts() { //start all scripts
    for (int i = 0; i < attachedScripts.size(); i++)
        attachedScripts[i]->start(*this);
}
void GameObject::updateScripts() { //update all scripts (called every frame), also moves the object
    //Reset the collisions ids
    collisionIds.clear();
    float dt = Singleton<GameTime>::getInstance().getDeltaTime();
    move(velocity * dt);
    if (useGravity) {
        move(dt * dt * Vector2f(0, 9.81f * 100) / 2.f);
        velocity += dt * Vector2f(0, 9.81f * 10 * mass);
        if(velocity.y > 1000 * mass)
			velocity.y = 1000 * mass;
    }
    for (int i = 0; i < attachedScripts.size(); i++)
        attachedScripts[i]->update(*this);
}
void GameObject::triggerScripts(GameObject& trigger) { //trigger all scripts
    if(collisionIds.find(trigger.getId()) != collisionIds.end())
        return;
    collisionIds.insert(trigger.getId());
    for (int i = 0; i < attachedScripts.size(); i++)
        attachedScripts[i]->trigger(*this, trigger);
}
void GameObject::collisionScripts(GameObject& collision) { //collision all scripts
    if(collisionIds.find(collision.getId()) != collisionIds.end())
		return;
    collisionIds.insert(collision.getId());
    for (int i = 0; i < attachedScripts.size(); i++)
        attachedScripts[i]->collision(*this, collision);
}
void GameObject::destroyScripts() { //destroy all scripts
    for (int i = 0; i < attachedScripts.size(); i++)
        attachedScripts[i]->destroy(*this);
}

void GameObject::setAttributeOnScripts(int scriptIndex, int attributeIndex, string value) { //set attribute on all scripts
    if (scriptIndex < attachedScripts.size() && scriptIndex >= 0)
        attachedScripts[scriptIndex]->setAttribute(attributeIndex, value);
}
string GameObject::getAttributeFromScripts(int scriptIndex, int attributeIndex) const { //get attribute from all scripts
    if (scriptIndex < attachedScripts.size() && scriptIndex >= 0)
        return attachedScripts[scriptIndex]->getAttribute(attributeIndex);
    return "";
}
string GameObject::getAttributeNamesFromScripts(int scriptIndex, int attributeIndex) const { //get attribute names from all scripts
    if (scriptIndex < attachedScripts.size() && scriptIndex >= 0)
        return attachedScripts[scriptIndex]->getAttributeName(attributeIndex);
    return "";
}
int GameObject::getAttributeTypeFromScripts(int scriptIndex, int attributeIndex) const { //get attribute type from all scripts
    if (scriptIndex < attachedScripts.size() && scriptIndex >= 0)
        return attachedScripts[scriptIndex]->getAttributeType(attributeIndex);
    return 0;
}
int GameObject::getAttributeCountFromScripts(int scriptIndex) const { //get attribute count from all scripts
    if (scriptIndex < attachedScripts.size() && scriptIndex >= 0)
        return attachedScripts[scriptIndex]->getAttributeCount();
    return 0;
}

string GameObject::getScriptName(int scriptIndex) const { //get script name
	if (scriptIndex < attachedScripts.size() && scriptIndex >= 0)
		return attachedScripts[scriptIndex]->getScriptName();
	return "";
}

void GameObject::setPosition(const Vector2f& position) { //set position
    ConvexShape::setPosition(position);
    Collider::updateTransform(*this);
}
void GameObject::setPosition(float x, float y) { //set position
    ConvexShape::setPosition(x, y);
    Collider::updateTransform(*this);
}
void GameObject::move(const Vector2f& position) { //move the object
    ConvexShape::move(position);
    Collider::updateTransform(*this);
}
void GameObject::move(float x, float y) { //move the object
    ConvexShape::move(x, y);
    Collider::updateTransform(*this);
}

void GameObject::setRotation(float angle) { //set rotation
	ConvexShape::setRotation(angle);
	Collider::updateTransform(*this);
}
void GameObject::rotate(float angle) { //rotate the object
	ConvexShape::rotate(angle);
	Collider::updateTransform(*this);
}

void GameObject::setScale(const Vector2f& factors) { //set scale
	ConvexShape::setScale(factors);
	Collider::updateTransform(*this);
}
void GameObject::setScale(float x, float y) { //set scale
	ConvexShape::setScale(x, y);
	Collider::updateTransform(*this);
}
void GameObject::scale(const Vector2f& factors) { //scale the object
	ConvexShape::scale(factors);
	Collider::updateTransform(*this);
}
void GameObject::scale(float x, float y) { //scale the object
	ConvexShape::scale(x, y);
	Collider::updateTransform(*this);
}

void GameObject::changeId() { //change the id of the object
    id = idCounter++;
}

istream& GameObject::read(istream& in) { //read function
    GameObject::pRead(in);
    return in;
}
ostream& GameObject::write(ostream& out) const { //write function
    out << "GameObject" << endl;
    GameObject::pWrite(out);
    return out;

}

GameObject::~GameObject() { //destructor (deletes all scripts to free memory)
    removeAllScripts();
    cout<<"Destroying "<<name<<endl;
}

void GameObject::changeTexture(const string& path) { //change the texture of the object
	GameFilesWindow* gameFilesWindow = dynamic_cast<GameFilesWindow*>(Game::getGameFilesWindow());
    if (gameFilesWindow) {
		Texture* texture = gameFilesWindow->getTextureFromPath(path);
	    setTexture(texture, true);
        if(!texture)
            texturePath = "";
        else
            texturePath = path;
	}
}
string GameObject::getTexturePath() const { //get the texture path of the object
	return texturePath;
}




bool Collider::findMinSeparation(const GameObject& collider1, const GameObject& collider2, Vector2f& sep) { //Find the minimum separation between two colliders
    //Separating axis theorem
    //This states that if you can draw a line between two objects, then they are not colliding
    //We do this by checking if the projections of the points of the objects onto the line between them overlap
    //Since there are an infinite number of possible lines, we cannot check all of them
    //Instead, we check the normals of the edges of the objects, which is enough
    //This only works for convex shapes
    float minOverlap = INFINITY;
    Vector2f smallestAxis;
    const Shape* shape1 = collider1.colliderShape;
    const Shape* shape2 = collider2.colliderShape;
    for (int shapeIndex = 0; shapeIndex < 2; shapeIndex++) { //Check the lines in both objects
        const Shape* shape = shapeIndex == 0 ? shape1 : shape2;
        for (int i = 0; i < shape->getPointCount(); i++) {
            //Check the normals of the edges
            Vector2f point1 = shape->getTransform().transformPoint(shape->getPoint(i));
            Vector2f point2 = shape->getTransform().transformPoint(shape->getPoint((i + 1) % shape->getPointCount()));
            Vector2f edge = Utility::normalize(point2 - point1);
            Vector2f normal = Utility::calculateNormal(edge);
            float min1 = INFINITY, max1 = -INFINITY;
            float min2 = INFINITY, max2 = -INFINITY;
            for (int j = 0; j < shape1->getPointCount(); j++) { //Project the points of the objects onto the normal and check for the min and max
                float projection = Utility::dotProduct(shape1->getTransform().transformPoint(shape1->getPoint(j)), normal);
                if (projection < min1) min1 = projection;
                if (projection > max1) max1 = projection;
            }
            for (int j = 0; j < shape2->getPointCount(); j++) { //Project the points of the objects onto the normal and check for the min and max
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
void Collider::moveCollidersInCollision(GameObject& collider1, GameObject& collider2, const Vector2f& displacement) { //Move the colliders in a collision
    //This function is responsible for moving the objects which collided so they no longer overlap
    //It takes into account the mass of the objects and wether they are movable and moves them accordingly
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
            //cout << "Both objects are immovable!" << endl;
        }
    }
}
bool Collider::polygonCollision(GameObject& collider1, GameObject& collider2) { //Check for a collision between two polygons
    Vector2f displacement;
    bool col1 = findMinSeparation(collider1, collider2, displacement);
    if (col1) {
        if (collider1.colliderIsTrigger || collider2.colliderIsTrigger) { //If the colliders are triggers, send a message to the objects
            collider1.triggerScripts(collider2); //Send message
            collider2.triggerScripts(collider1);
            return true;
        }
        collider1.collisionScripts(collider2); //Send message
        collider2.collisionScripts(collider1);
        moveCollidersInCollision(collider1, collider2, displacement); //Move the colliders
        return true;
    }
    return false;
}
bool Collider::circleCollision(GameObject& collider1, GameObject& collider2) //Check for a collision between two circles
{
    //When checking the collision between 2 circles, we only need to check if the distance between their centers is less than the sum of their radius
    const CircleShape* circle1 = static_cast<const CircleShape*>(collider1.colliderShape);
    const CircleShape* circle2 = static_cast<const CircleShape*>(collider2.colliderShape);
    Vector2f direction = Utility::direction(circle1->getPosition(), circle2->getPosition());
    float distance = Utility::magnitude(circle1->getPosition() - circle2->getPosition());
    float overlap = circle1->getRadius() + circle2->getRadius() - distance;

    if (overlap > 0) {

        if (collider1.colliderIsTrigger || collider2.colliderIsTrigger) {
            //Send a message to the objects telling them a collision of type trigger has happened
            collider1.triggerScripts(collider2);
            collider2.triggerScripts(collider1);
            return true;
        }

        // The circles are colliding. We need to move them apart.
        Vector2f displacement = direction * overlap;
        moveCollidersInCollision(collider1, collider2, displacement);

        return true;
    }

    return false;
}
bool Collider::collision(GameObject& collider1, GameObject& collider2) { //Check for a collision between two colliders
    if (!collider1.colliderIsActive || !collider2.colliderIsActive)
        return false;
    bool ret = false;
    if (collider1.colliderIsCircle && collider2.colliderIsCircle)
        ret = circleCollision(collider1, collider2);
    else
        ret = polygonCollision(collider1, collider2);
    return ret;
}
void Collider::handleAllCollisions(const vector<GameObject*>& objects, const vector<Vector2f>& lastPositions) { //Handle all collisions
    const int iterations = 10; // Number of iterations for collision resolution 
    //We do this multiple times to make sure that all collisions are resolved (if we only do it once, some objects might still be colliding)

    // Resolve collisions
    for (int iteration = 0; iteration < iterations; iteration++) {
        for (int i = 0; i < objects.size(); i++) {
            for (int j = i + 1; j < objects.size(); j++) {
                if (objects[i]->getColliderShape()->getGlobalBounds().intersects(objects[j]->getColliderShape()->getGlobalBounds()))
                    collision(*objects[i], *objects[j]);
            }
        }
    }

    // Check if the objects have moved in the opposite direction of their velocity
    for (int i = 0; i < objects.size(); i++) {
        if (!objects[i]->getIsMovable() || !objects[i]->getColliderIsActive() || objects[i]->getColliderIsTrigger())
            continue;
        Vector2f displacement = objects[i]->getPosition() - lastPositions[i];

        // If the object has moved in the opposite direction of its velocity, reset its velocity in that direction
        float minMov = 0.01f * Singleton<GameTime>::getInstance().getDeltaTime();
        if (displacement.x >= -minMov && objects[i]->getVelocity().x < 0) {
            objects[i]->setVelocity(Vector2f(0, objects[i]->getVelocity().y));
        }
        if (displacement.x <= minMov && objects[i]->getVelocity().x > 0) {
            objects[i]->setVelocity(Vector2f(0, objects[i]->getVelocity().y));
        }
        if (displacement.y >= -minMov && objects[i]->getVelocity().y < 0) {
            objects[i]->setVelocity(Vector2f(objects[i]->getVelocity().x, 0));
        }
        if (displacement.y <= minMov && objects[i]->getVelocity().y > 0) {
            objects[i]->setVelocity(Vector2f(objects[i]->getVelocity().x, 0));
        }
    }
}
