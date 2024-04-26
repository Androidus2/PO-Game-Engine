#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"


using namespace sf;
using namespace std;

string floatToString(float f, int precision = 2) { //for input fields
    stringstream ss;
    ss << fixed << setprecision(precision) << f;
    return ss.str();
}

string keyToString(Keyboard::Key key) { //for saving key bindings
    switch (key) {
	    case Keyboard::A: return "A";
	    case Keyboard::B: return "B";
	    case Keyboard::C: return "C";
	    case Keyboard::D: return "D";
	    case Keyboard::E: return "E";
	    case Keyboard::F: return "F";
	    case Keyboard::G: return "G";
	    case Keyboard::H: return "H";
	    case Keyboard::I: return "I";
	    case Keyboard::J: return "J";
	    case Keyboard::K: return "K";
	    case Keyboard::L: return "L";
	    case Keyboard::M: return "M";
	    case Keyboard::N: return "N";
	    case Keyboard::O: return "O";
	    case Keyboard::P: return "P";
	    case Keyboard::Q: return "Q";
	    case Keyboard::R: return "R";
	    case Keyboard::S: return "S";
	    case Keyboard::T: return "T";
	    case Keyboard::U: return "U";
	    case Keyboard::V: return "V";
	    case Keyboard::W: return "W";
	    case Keyboard::X: return "X";
	    case Keyboard::Y: return "Y";
	    case Keyboard::Z: return "Z";
	    case Keyboard::Num0: return "0";
	    case Keyboard::Num1: return "1";
	    case Keyboard::Num2: return "2";
	    case Keyboard::Num3: return "3";
	    case Keyboard::Num4: return "4";
	    case Keyboard::Num5: return "5";
	    case Keyboard::Num6: return "6";
	    case Keyboard::Num7: return "7";
	    case Keyboard::Num8: return "8";
	    case Keyboard::Num9: return "9";
	    case Keyboard::Escape: return "Escape";
	    case Keyboard::LControl: return "Left-Control";
	    case Keyboard::LShift: return "Left-Shift";
	    case Keyboard::LAlt: return "Left-Alt";
	    case Keyboard::RControl: return "Right-Control";
	    case Keyboard::RShift: return "Right-Shift";
	    case Keyboard::RAlt: return "Right-Alt";
        case Keyboard::Space: return "Space";
        case Keyboard::Left: return "Left";
        case Keyboard::Right: return "Right";
        case Keyboard::Up: return "Up";
        case Keyboard::Down: return "Down";
        default: return "Unknown";
    }
}

Keyboard::Key stringToKey(string s) { //for loading key bindings
    if(s == "A") return Keyboard::A;
    if(s == "B") return Keyboard::B;
    if(s == "C") return Keyboard::C;
    if(s == "D") return Keyboard::D;
    if(s == "E") return Keyboard::E;
    if(s == "F") return Keyboard::F;
    if(s == "G") return Keyboard::G;
    if(s == "H") return Keyboard::H;
    if(s == "I") return Keyboard::I;
    if(s == "J") return Keyboard::J;
    if(s == "K") return Keyboard::K;
    if(s == "L") return Keyboard::L;
    if(s == "M") return Keyboard::M;
    if(s == "N") return Keyboard::N;
    if(s == "O") return Keyboard::O;
    if(s == "P") return Keyboard::P;
    if(s == "Q") return Keyboard::Q;
    if(s == "R") return Keyboard::R;
    if(s == "S") return Keyboard::S;
    if(s == "T") return Keyboard::T;
    if(s == "U") return Keyboard::U;
    if(s == "V") return Keyboard::V;
    if(s == "W") return Keyboard::W;
    if(s == "X") return Keyboard::X;
    if(s == "Y") return Keyboard::Y;
    if(s == "Z") return Keyboard::Z;
    if(s == "0") return Keyboard::Num0;
    if(s == "1") return Keyboard::Num1;
    if(s == "2") return Keyboard::Num2;
    if(s == "3") return Keyboard::Num3;
    if(s == "4") return Keyboard::Num4;
    if(s == "5") return Keyboard::Num5;
    if(s == "6") return Keyboard::Num6;
    if(s == "7") return Keyboard::Num7;
    if(s == "8") return Keyboard::Num8;
    if(s == "9") return Keyboard::Num9;
    if(s == "Escape") return Keyboard::Escape;
    if(s == "Left-Control") return Keyboard::LControl;
    if(s == "Left-Shift") return Keyboard::LShift;
    if(s == "Left-Alt") return Keyboard::LAlt;
    if(s == "Right-Control") return Keyboard::RControl;
    if(s == "Right-Shift") return Keyboard::RShift;
    if(s == "Right-Alt") return Keyboard::RAlt;
    if(s == "Space") return Keyboard::Space;
    if(s == "Left") return Keyboard::Left;
    if(s == "Right") return Keyboard::Right;
    if(s == "Up") return Keyboard::Up;
    if(s == "Down") return Keyboard::Down;
    return Keyboard::Unknown;
}

string ColorToString(Color color) {
    char hex[16];
    sprintf_s(hex, "%02X%02X%02X%02X", color.r, color.g, color.b, color.a);
    string ret(hex);
    return ret;
}

Color stringToColor(string inp) {
    //return Color::Black;
    //Clean up the string
    string s = "";
    for (int i = 0; i < inp.size(); i++)
        if ((inp[i] >= '0' && inp[i] <= '9') || (inp[i] >= 'a' && inp[i] <= 'f') || (inp[i] >= 'A' && inp[i] <= 'F'))
            s += inp[i];
    for(int i=s.size(); i<8; i++)
        s+="F";
    Color color;
	color.r = stoi(s.substr(0, 2), nullptr, 16);
	color.g = stoi(s.substr(2, 2), nullptr, 16);
	color.b = stoi(s.substr(4, 2), nullptr, 16);
	color.a = stoi(s.substr(6, 2), nullptr, 16);
	return color;
}

bool isColorFormat(string s) {
    if(s.size() != 8)
		return false;
	for(int i=0; i<s.size(); i++)
		if(!((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f') || (s[i] >= 'A' && s[i] <= 'F')))
			return false;
	return true;

}

class Utility { //for vector calculations
public:
    static float magnitude(const Vector2f& source);
    static float dotProduct(const Vector2f& source1, const Vector2f& source2);
    static Vector2f normalize(const Vector2f& source);
    static Vector2f calculateNormal(const Vector2f& source);
    static Vector2f direction(const Vector2f& source, const Vector2f& target);
};

float Utility::magnitude(const Vector2f& source) //magnitude of a vector
{
    return sqrt((source.x * source.x) + (source.y * source.y));
}
float Utility::dotProduct(const Vector2f& source1, const Vector2f& source2) //dot product of 2 vectors
{
    return source1.x * source2.x + source1.y * source2.y;
}
Vector2f Utility::normalize(const Vector2f& source) //normalize a vector
{
    float length = magnitude(source);
    if (length != 0)
    {
        return Vector2f(source.x / length, source.y / length);
    }
    return source;
}
Vector2f Utility::calculateNormal(const Vector2f& source) //calculate normal of a vector
{
    return normalize(Vector2f(source.y, -source.x));
}
Vector2f Utility::direction(const Vector2f& source, const Vector2f& target) //direction from source to target
{
    return normalize(Vector2f(target.x - source.x, target.y - source.y));
}

class GameTime { //for delta time and time (singleton)
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

void makeObj(GameObject& obj, const Vector2f& position, float sideLen);

class Collider { //Collider class for collision detection
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

    virtual istream& pRead(istream& in); //for polymorphic reading
    virtual ostream& pWrite(ostream& out) const; //for polymorphic writing

private:
    static bool findMinSeparation(const GameObject& collider1, const GameObject& collider2, Vector2f& sep); //SAT collision detection
    static void moveCollidersInCollision(GameObject& collider1, GameObject& collider2, const Vector2f& displacement); //move the colliders
    static bool polygonCollision(GameObject& collider1, GameObject& collider2); //check if 2 polygons are colliding
    static bool circleCollision(GameObject& collider1, GameObject& collider2); //check if 2 circles are colliding

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

    virtual istream& read(istream& in);
    virtual ostream& write(ostream& out) const;

    virtual ~Collider();
};

istream& operator>>(istream& in, Collider& collider) {
	return collider.read(in);
}
ostream& operator<<(ostream& out, const Collider& collider) {
	return collider.write(out);
}

istream& Collider::pRead(istream& in) { //"private" read function, means it only reads the Collider class
    in >> colliderOffset.x >> colliderOffset.y >> colliderRotation >> colliderScale.x >> colliderScale.y;
    in >> colliderIsCircle >> colliderIsActive >> colliderIsTrigger >> mass >> isMovable >> useGravity;
    if (colliderIsCircle) {
        float radius;
        in >> radius;
        makeCircleCollider(radius);
    }
    else {
        int pointCount;
        in >> pointCount;
        ConvexShape* tmp = new ConvexShape();
        tmp->setPointCount(pointCount);
        for (int i = 0; i < pointCount; i++) {
            float x, y;
            in >> x >> y;
            tmp->setPoint(i, Vector2f(x, y));
        }
        this->colliderShape = tmp;
    }
    return in;
}
ostream& Collider::pWrite(ostream& out) const { //"private" write function, means it only writes the Collider class
    out << colliderOffset.x << " " << colliderOffset.y << " " << colliderRotation << " " << colliderScale.x << " " << colliderScale.y << endl;
    out << colliderIsCircle << " " << colliderIsActive << " " << colliderIsTrigger << " " << mass << " " << isMovable << " " << useGravity << endl;
    if (colliderIsCircle) {
        out << static_cast<CircleShape&>(*colliderShape).getRadius() << endl;
    }
    else {
        out << static_cast<ConvexShape&>(*colliderShape).getPointCount() << endl;
        for (int i = 0; i < static_cast<ConvexShape&>(*colliderShape).getPointCount(); i++) {
            out << static_cast<ConvexShape&>(*colliderShape).getPoint(i).x << " " << static_cast<ConvexShape&>(*colliderShape).getPoint(i).y << endl;
        }
    }
    return out;
}

Collider::Collider() { //default constructor
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
//constructor with parameters
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
Collider::Collider(const Collider& collider) { //copy constructor
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
Collider& Collider::operator=(const Collider& collider) { //assignment operator
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

void Collider::cleanShape(Vector2f& position, float& rotation, Vector2f& scale) { //A function used to "clean" the shape so a new one can be assigned
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
void Collider::fixShape(Vector2f& position, float& rotation, Vector2f& scale) { //A function used to "fix" the shape after a new one has been assigned
    this->colliderShape->setRotation(rotation);
    this->colliderShape->setScale(scale);
    this->colliderShape->setOrigin(this->colliderShape->getLocalBounds().getSize() / 2.f);
    this->colliderShape->setPosition(position);
}

Vector2f Collider::getColliderOffset() const { //get offset
    return colliderOffset;
}
void Collider::setColliderOffset(const Vector2f& colliderOffset) { //set offset
    this->colliderOffset = colliderOffset;
}

float Collider::getColliderRotation() const { //get rotation
    return colliderRotation;
}
void Collider::setColliderRotation(float colliderRotation) { //set rotation
    this->colliderRotation = colliderRotation;
}

Vector2f Collider::getColliderScale() const { //get scale
    return colliderScale;
}
void Collider::setColliderScale(const Vector2f& colliderScale) { //set scale
    this->colliderScale = colliderScale;
}

const Shape* Collider::getColliderShape() const { //get shape
    return colliderShape;
}
void Collider::setColliderShape(Shape* colliderShape, bool isCircle) { //set shape (can either be a circle or a polygon)
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

bool Collider::getColliderIsCircle() const { //get if the collider is a circle
    return colliderIsCircle;
}

bool Collider::getColliderIsActive() const { //get if the collider is active
    return colliderIsActive;
}
void Collider::setColliderIsActive(bool colliderIsActive) { //set if the collider is active
    this->colliderIsActive = colliderIsActive;
}

bool Collider::getColliderIsTrigger() const { //get if the collider is a trigger
    return colliderIsTrigger;
}
void Collider::setColliderIsTrigger(bool colliderIsTrigger) { //set if the collider is a trigger
    this->colliderIsTrigger = colliderIsTrigger;
}

float Collider::getMass() const { //get mass
    return mass;
}
void Collider::setMass(float mass) { //set mass (minimum mass is 0.01)
    this->mass = mass;
    if (this->mass < 0.01f)
        this->mass = 0.01f;
}

bool Collider::getIsMovable() const { //get if the collider is movable
    return isMovable;
}
void Collider::setIsMovable(bool isMovable) { //set if the collider is movable
    this->isMovable = isMovable;
}

bool Collider::getUseGravity() const { //get if the collider uses gravity
    return useGravity;
}
void Collider::setUseGravity(bool useGravity) { //set if the collider uses gravity
    this->useGravity = useGravity;
}

void Collider::makeCircleCollider(float radius) { //make the collider into a circle
    this->colliderIsCircle = true;
    Vector2f position, scale;
    float rotation;
    cleanShape(position, rotation, scale);
    this->colliderShape = new CircleShape(radius);
    fixShape(position, rotation, scale);
}

void Collider::makeSquareCollider(float sideLength) { //make the collider into a square
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

void Collider::makeTriangleCollider(float sideLength) { //make the collider into a triangle
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

void Collider::makeHexagonCollider(float sideLength) { //make the collider into a hexagon
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

void Collider::updateTransform(const Vector2f& position, float colliderRotation, const Vector2f& colliderScale) { //update the transform of the collider (used for GameObjects)
    colliderShape->setPosition(position + colliderOffset);
    colliderShape->setRotation(colliderRotation + this->colliderRotation);
    colliderShape->setScale(colliderScale.x * this->colliderScale.x, colliderScale.y * this->colliderScale.y);
}
void Collider::updateTransform(const Transformable& transform) { //update the transform of the collider (used for GameObjects)
    colliderShape->setPosition(transform.getPosition() + colliderOffset);
    colliderShape->setRotation(transform.getRotation() + this->colliderRotation);
    colliderShape->setScale(transform.getScale().x * this->colliderScale.x, transform.getScale().y * this->colliderScale.y);
}

istream& Collider::read(istream& in) { //"public" read function
	return Collider::pRead(in);
}
ostream& Collider::write(ostream& out) const { //"public" write function
    return Collider::pWrite(out);
}

Collider::~Collider() { //destructor
    if (colliderShape != NULL)
        delete colliderShape;
}


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
    virtual string getAttributeName(int index) const = 0;

    virtual string getAttribute(int index) const = 0;
    virtual void setAttribute(int index, string value) = 0;

    virtual ~BehaviourScript() {}
};


class GameObject : public Collider, public ConvexShape { //GameObject class
protected:
    string name;
    bool isActive;
    int zLayer;
    Vector2f velocity;
    int id;
    static int idCounter;
    vector<BehaviourScript*> attachedScripts; //Scripts attached to the GameObject

    GameObject* objectBeforePlaying;

    istream& pRead(istream& in) override;
    ostream& pWrite(ostream& out) const override;
public:
    GameObject();
    GameObject(const GameObject& gameObject);
    GameObject& operator=(const GameObject& gameObject);
    virtual GameObject* clone() const;

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

    virtual void startScripts();
    virtual void updateScripts();
    virtual void triggerScripts(GameObject& trigger);
    virtual void collisionScripts(GameObject& collision);
    virtual void destroyScripts();

    void setAttributeOnScripts(int scriptIndex, int attributeIndex, string value);
    string getAttributeFromScripts(int scriptIndex, int attributeIndex) const;

    string getAttributeNamesFromScripts(int scriptIndex, int attributeIndex) const;

    int getAttributeCountFromScripts(int scriptIndex) const;

    void setPosition(const Vector2f& position);
    void setPosition(float x, float y);
    void move(const Vector2f& position);
    void move(float x, float y);

    istream& read(istream& in) override;
    ostream& write(ostream& out) const override;

    virtual ~GameObject();
};

istream& GameObject::pRead(istream& in) { //private read function
    Vector2f position;
    float rotation;
    Vector2f scale;
    Color color;
    in >> name >> isActive >> zLayer >> velocity.x >> velocity.y >> position.x >> position.y >> rotation >> scale.x >> scale.y >> color.r
        >> color.g >> color.b >> color.a;
    setPosition(position);
    setRotation(rotation);
    setScale(scale);
    setFillColor(color);
    Collider::read(in);
    return in;
}
ostream& GameObject::pWrite(ostream& out) const { //private write function
    out << name << " " << isActive << " " << zLayer << " " << velocity.x << " " << velocity.y << " ";
    out << getPosition().x << " " << getPosition().y << " " << getRotation() << " " << getScale().x << " " << getScale().y
        << " " << getFillColor().r << " " << getFillColor().g << " " << getFillColor().b << " " << getFillColor().a << endl;
    Collider::write(out);
	return out;
}

GameObject::GameObject() : Collider(), ConvexShape(), id(idCounter++) { //default constructor
    this->name = "Object";
    this->isActive = true;
    this->zLayer = 0;
    this->velocity = Vector2f();
    makeObj(*this, getPosition(), 100.f);
}
GameObject::GameObject(const GameObject& gameObject) : Collider(gameObject), ConvexShape(gameObject), id(gameObject.id) { //copy constructor
    //cout<<"Copy constructor called on "<<gameObject.name<<endl;
    this->name = gameObject.name;
    this->isActive = gameObject.isActive;
    this->zLayer = gameObject.zLayer;
    this->velocity = gameObject.velocity;
    for (int i = 0; i < gameObject.attachedScripts.size(); i++)
        this->attachedScripts.push_back(gameObject.attachedScripts[i]->clone());
}
GameObject& GameObject::operator=(const GameObject& gameObject) { //assignment operator
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
GameObject* GameObject::clone() const { //clone function (used for adding objects to the scene)
	return new GameObject(*this);
}

string GameObject::getName() const { //get name
    return this->name;
}
void GameObject::setName(string name) { //set name
    this->name = name;
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
    if (scriptIndex(script) == -1)
        this->attachedScripts.push_back(script->clone());
}
int GameObject::scriptIndex(BehaviourScript* script) const { //get the index of a script
    return -1; //Has to be implemented
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
    if(objectBeforePlaying)
        delete objectBeforePlaying;
    objectBeforePlaying = clone();
    for (int i = 0; i < attachedScripts.size(); i++)
        attachedScripts[i]->start(*this);
}
void GameObject::updateScripts() { //update all scripts (called every frame), also moves the object
    float dt = GameTime::getInstance()->getDeltaTime();
    move(velocity * dt);
    if (useGravity) {
        move(dt * dt * Vector2f(0, 9.81f * 10) / 2.f);
        velocity += dt * Vector2f(0, 9.81f * 10);
    }
    for (int i = 0; i < attachedScripts.size(); i++)
        attachedScripts[i]->update(*this);
}
void GameObject::triggerScripts(GameObject& trigger) { //trigger all scripts
    for (int i = 0; i < attachedScripts.size(); i++)
        attachedScripts[i]->trigger(*this, trigger);
}
void GameObject::collisionScripts(GameObject& collision) { //collision all scripts
    for (int i = 0; i < attachedScripts.size(); i++)
        attachedScripts[i]->collision(*this, collision);
}
void GameObject::destroyScripts() { //destroy all scripts
    for (int i = 0; i < attachedScripts.size(); i++)
        attachedScripts[i]->destroy(*this);
    if (objectBeforePlaying) {
		*this = *objectBeforePlaying;
		delete objectBeforePlaying;
		objectBeforePlaying = NULL;
    }
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
int GameObject::getAttributeCountFromScripts(int scriptIndex) const { //get attribute count from all scripts
	if (scriptIndex < attachedScripts.size() && scriptIndex >= 0)
		return attachedScripts[scriptIndex]->getAttributeCount();
	return 0;
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

istream& GameObject::read(istream& in) { //read function
    GameObject::pRead(in);
	return in;
}
ostream& GameObject::write(ostream& out) const { //write function
    out<<"GameObject"<<endl;
    GameObject::pWrite(out);
	return out;

}

GameObject::~GameObject() { //destructor (deletes all scripts to free memory)
    removeAllScripts();
}


void addTextToHierarchy(const string& obName);
void removeTextFromHierarchy(int index);


class TestScript : public BehaviourScript { //Test script for GameObjects (changes color when clicked)
private:
    Color defaultColor;
    Color pressedColor;
public:
    TestScript();
    TestScript(Color a, Color b);
    void setColors(Color a, Color b);
    TestScript* clone() const;
    void start(GameObject& gameObject);
    void update(GameObject& gameObject);
    void collision(GameObject& gameObject, GameObject& collisionObject);
    void trigger(GameObject& gameObject, GameObject& triggerObject);
    void destroy(GameObject& gameObject);

    string getAttribute(int index) const;
    void setAttribute(int index, string value);

    string getAttributeName(int index) const;

    ~TestScript();
};
TestScript::TestScript() { //default constructor
	defaultColor = Color::White;
	pressedColor = Color::Red;
	attributeCount = 2;
}
TestScript::TestScript(Color a, Color b) { //constructor
	defaultColor = a;
	pressedColor = b;
    attributeCount = 2;
}
void TestScript::setColors(Color a, Color b) { //set colors
	defaultColor = a;
	pressedColor = b;
}
TestScript* TestScript::clone() const { //clone function
    return new TestScript(*this);
}
void TestScript::start(GameObject& gameObject) { //start function
    cout << "Start function called on object with id " << gameObject.getId() << endl;
}
void TestScript::update(GameObject& gameObject) { //update function
    if (Mouse::isButtonPressed(Mouse::Left))
        gameObject.setFillColor(pressedColor);
    else
        gameObject.setFillColor(defaultColor);
    //cout << "Update function called on object with id " << gameObject.getId() << endl;
}
void TestScript::collision(GameObject& gameObject, GameObject& collisionObject) { //collision function
    cout << "Collision function called on object with id " << gameObject.getId() << endl;
}
void TestScript::trigger(GameObject& gameObject, GameObject& triggerObject) { //trigger function
    //cout << "Trigger function called on object with id " << gameObject.getId() << endl;
}
void TestScript::destroy(GameObject& gameObject) { //destroy function
    cout << "Destroy function called on object with id " << gameObject.getId() << endl;
}
string TestScript::getAttribute(int index) const { //get attribute
	if (index == 0)
		return ColorToString(defaultColor);
	if (index == 1)
		return ColorToString(pressedColor);
	return "";
}
void TestScript::setAttribute(int index, string value) { //set attribute
    if (index == 0) {
		defaultColor = stringToColor(value);
	}
    if (index == 1) {
		pressedColor = stringToColor(value);
	}
}
string TestScript::getAttributeName(int index) const { //get attribute name
	if (index == 0)
		return "Default Color";
	if (index == 1)
		return "Pressed Color";
	return "";
}
TestScript::~TestScript() { //destructor
    cout << "Destructor called" << endl;
}

GameObject* makeObjFromString(const string& obj);



class Scene { //Scene class
private:
    string sceneName;
    vector<GameObject*> sceneObjects; //Objects in the scene
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
    int getIndexOfObject(int id) const;
    void removeSelectedObject();

    void moveSelectedObject(Vector2f moveBy);

    void modifySelectedCustom(string value, int index);
    string getSelectedCustom(int index) const;

    string getSelectedCustomName(int index) const;

    void changeSelectedIsMovable();

    void setLastPositions(const vector<Vector2f>& lastPositions);
    const vector<Vector2f>& getLastPositions() const;
    void modifyLastPosition(int index, const Vector2f& position);

    void startScene();
    void drawScene(bool drawColliders, RenderWindow& window) const;
    void updateScene();
    void endScene();

    int getId() const;

    int getBuildIndex() const;
    void setBuildIndex(int buildIndex);

    int getSelectedObjectIndex() const;
    void setSelectedObjectIndex(int index);

    istream& read(istream& in);
    ostream& write(ostream& out) const;

    ~Scene();
};

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
}
Scene::Scene(const Scene& scene) : sceneId(scene.sceneId) { //copy constructor
    sceneName = scene.sceneName;
    setObjects(scene.sceneObjects);
    buildIndex = scene.buildIndex;
}
Scene& Scene::operator=(const Scene& scene) { //assignment operator
    if (this == &scene)
        return *this;
    sceneName = scene.sceneName;
    setObjects(scene.sceneObjects);
    buildIndex = scene.buildIndex;
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
    for (int i = 0; i < sceneObjects.size(); i++)
        delete sceneObjects[i];
    sceneObjects.clear();
    clearLastPositions();
    selectedObjectIndex = -1;
}
void Scene::addObject(const GameObject* object) { //add an object to the scene
    sceneObjects.push_back(object->clone());
    addTextToHierarchy(object->getName());
    addLastPosition(object->getPosition());
}
void Scene::removeObjectByIndex(int index) { //remove an object by index
    if (selectedObjectIndex == index)
        selectedObjectIndex = -1;
    if (index < sceneObjects.size() && index >= 0) {
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
    if(index < 0)
        return;
    if (index == 0) {
        //Change name
		sceneObjects[selectedObjectIndex]->setName(value);
		return;
    }
    if (index == 1) { //Change position.x
        sceneObjects[selectedObjectIndex]->setPosition(stof(value), sceneObjects[selectedObjectIndex]->getPosition().y);
        return;
    }
    if (index == 2) { //Change position.y
    	sceneObjects[selectedObjectIndex]->setPosition(sceneObjects[selectedObjectIndex]->getPosition().x, stof(value));
    	return;
    }
    if (index == 3) { //Change rotation
        sceneObjects[selectedObjectIndex]->setRotation(stof(value));
        return;
    }
    if (index == 4) { //Change scale.x
    	sceneObjects[selectedObjectIndex]->setScale(stof(value), sceneObjects[selectedObjectIndex]->getScale().y);
    	return;
    }
    if (index == 5) { //Change scale.y
    	sceneObjects[selectedObjectIndex]->setScale(sceneObjects[selectedObjectIndex]->getScale().x, stof(value));
    	return;
    }
    if (index == 6) { //Change velocity.x
    	sceneObjects[selectedObjectIndex]->setVelocity(stof(value), sceneObjects[selectedObjectIndex]->getVelocity().y);
		return;
    }
    if (index == 7) { //Change velocity.y
    	sceneObjects[selectedObjectIndex]->setVelocity(sceneObjects[selectedObjectIndex]->getVelocity().x, stof(value));
    	return;
    }
    if (index == 8) { //Change mass
        sceneObjects[selectedObjectIndex]->setMass(stof(value));
		return;
    }
    if(index == 9){ //Change color
        sceneObjects[selectedObjectIndex]->setFillColor(stringToColor(value));
        return;
    }
    int poz = 10;
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
        if (index == 1)
            return floatToString(sceneObjects[selectedObjectIndex]->getPosition().x);
        if (index == 2)
            return floatToString(sceneObjects[selectedObjectIndex]->getPosition().y);
        if (index == 3)
            return floatToString(sceneObjects[selectedObjectIndex]->getRotation());
        if (index == 4)
            return floatToString(sceneObjects[selectedObjectIndex]->getScale().x);
        if (index == 5)
            return floatToString(sceneObjects[selectedObjectIndex]->getScale().y);
        if (index == 6)
            return floatToString(sceneObjects[selectedObjectIndex]->getVelocity().x);
        if (index == 7)
            return floatToString(sceneObjects[selectedObjectIndex]->getVelocity().y);
        if (index == 8)
            return floatToString(sceneObjects[selectedObjectIndex]->getMass());
        if(index == 9)
            return ColorToString(sceneObjects[selectedObjectIndex]->getFillColor());
		int poz = 10;
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
		int poz = 9;
        for (int i = 0; i < sceneObjects[selectedObjectIndex]->getScriptsCount(); i++) {
			if (index >= poz && index < poz + sceneObjects[selectedObjectIndex]->getAttributeCountFromScripts(i))
				return sceneObjects[selectedObjectIndex]->getAttributeNamesFromScripts(i, index-poz);
			poz += sceneObjects[selectedObjectIndex]->getAttributeCountFromScripts(i);
		}
	}
	return "";
}

void Scene::changeSelectedIsMovable() { //change if the selected object is movable
	if (selectedObjectIndex < sceneObjects.size() && selectedObjectIndex >= 0)
		sceneObjects[selectedObjectIndex]->setIsMovable(!sceneObjects[selectedObjectIndex]->getIsMovable());
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
    for (int i = 0; i < sceneObjects.size(); i++) {
		if (sceneObjects[i]->getActive())
			sceneObjects[i]->startScripts();
	}
}
void Scene::drawScene(bool drawColliders, RenderWindow& window) const { //draw the scene
    for (int i = 0; i < sceneObjects.size(); i++) {
        if (sceneObjects[i]->getActive()) {
            if (drawColliders) {
                if (sceneObjects[i]->getColliderIsActive()) {
                    window.draw(*sceneObjects[i]->getColliderShape());
				}
			}
			window.draw(*sceneObjects[i]);
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
}

int Scene::getId() const { //get the id of the scene
    return sceneId;
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
	}
	return in;
}
ostream& Scene::write(ostream& out) const { //write function
	out << sceneName << " " << buildIndex << " " << getObjectsCount() << endl;
	for (int i = 0; i < getObjectsCount(); i++)
		out << *sceneObjects[i];
	return out;
}

Scene::~Scene() {} //destructor

class EditorWindow;

class Game { //Game class (has static variables for the game)
private:
    static Font* font;
    static RenderWindow* window;
    static Scene* currentScene;
    static EditorWindow* hierarchy;
    static EditorWindow* inspector;
    static EditorWindow* colorPicker;
    static bool isPlaying;
    static bool drawEditor;
public:
    static void setFont(Font* font);
	static Font* getFont();

	static void setWindow(RenderWindow* window);
	static RenderWindow* getWindow();

	static void setCurrentScene(Scene* scene);
	static Scene* getCurrentScene();

	static void setHierarchy(EditorWindow* hierarchy);
	static EditorWindow* getHierarchy();

    static void setInspector(EditorWindow* inspector);
    static EditorWindow* getInspector();

    static void setColorPicker(EditorWindow* colorPicker);
    static EditorWindow* getColorPicker();

    static bool getIsPlaying();
    static void setIsPlaying(bool isPlaying);

    static bool getDrawEditor();
    static void setDrawEditor(bool drawEditor);
};

void Game::setFont(Font* font) {  //set the font
	Game::font = font;
}
Font* Game::getFont() { //get the font
	return Game::font;
}

void Game::setWindow(RenderWindow* window) { //set the window
	Game::window = window;
}
RenderWindow* Game::getWindow() { //get the window
	return Game::window;
}

void Game::setCurrentScene(Scene* scene) { //set the current scene
	Game::currentScene = scene;
}
Scene* Game::getCurrentScene() { //get the current scene
	return Game::currentScene;
}

void Game::setHierarchy(EditorWindow* hierarchy) { //set the hierarchy
	Game::hierarchy = hierarchy;
}
EditorWindow* Game::getHierarchy() { //get the hierarchy
	return Game::hierarchy;
}

void Game::setInspector(EditorWindow* inspector) { //set the inspector
	Game::inspector = inspector;
}
EditorWindow* Game::getInspector() { //get the inspector
	return Game::inspector;
}

void Game::setColorPicker(EditorWindow* colorPicker) { //set the color picker
	Game::colorPicker = colorPicker;
}
EditorWindow* Game::getColorPicker() { //get the color picker
	return Game::colorPicker;
}

bool Game::getIsPlaying() { //get if the game is playing
	return isPlaying;
}
void Game::setIsPlaying(bool isPlaying) { //set if the game is playing
	Game::isPlaying = isPlaying;
    if (isPlaying && currentScene) {
        currentScene->startScene();
    }
    else if (!isPlaying && currentScene) {
		currentScene->endScene();
    }
}

bool Game::getDrawEditor() { //get if the editor is drawn
	return drawEditor;
}
void Game::setDrawEditor(bool drawEditor) { //set if the editor is drawn
	Game::drawEditor = drawEditor;
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
            cout << "Both objects are immovable!" << endl;
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
                if (objects[i]->getGlobalBounds().intersects(objects[j]->getGlobalBounds()))
                    collision(*objects[i], *objects[j]);
            }
        }
    }

    // Check if the objects have moved in the opposite direction of their velocity
    for (int i = 0; i < objects.size(); i++) {
        if(!objects[i]->getIsMovable() || !objects[i]->getColliderIsActive() || objects[i]->getColliderIsTrigger())
			continue;
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


class FollowMouseScript : public BehaviourScript { //Script that makes an object follow the mouse
private:
    bool applySmoothness;
    float smoothnessSpeed;
public:
    FollowMouseScript();
    FollowMouseScript(bool applySmoothness = false, float smoothnessSpeed = 5.f);
    FollowMouseScript* clone() const;
    void start(GameObject& gameObject);
    void update(GameObject& gameObject);
    void collision(GameObject& gameObject, GameObject& collisionObject);
    void trigger(GameObject& gameObject, GameObject& triggerObject);
    void destroy(GameObject& gameObject);

    string getAttribute(int index) const;
    void setAttribute(int index, string value);

    string getAttributeName(int index) const;

    ~FollowMouseScript();
};
FollowMouseScript::FollowMouseScript() { //default constructor
	applySmoothness = false;
	smoothnessSpeed = 5.f;
	attributeCount = 2;
}
FollowMouseScript::FollowMouseScript(bool applySmoothness, float smoothnessSpeed) { //constructor
    this->applySmoothness = applySmoothness;
    this->smoothnessSpeed = smoothnessSpeed;
    attributeCount = 2;
}
FollowMouseScript* FollowMouseScript::clone() const { //clone function
    return new FollowMouseScript(*this);
}
void FollowMouseScript::start(GameObject& gameObject) { //start function (does nothing)

}
void FollowMouseScript::update(GameObject& gameObject) { //update function
    //Get the mouse position and make the object follow it
    Vector2f mousePosition = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
    if (applySmoothness)
        mousePosition = gameObject.getPosition() + (-gameObject.getPosition() + mousePosition) * GameTime::getInstance()->getDeltaTime() * smoothnessSpeed;
    //cout << mousePosition.x<<" "<<mousePosition.y <<" "<< GameTime::getInstance()->getDeltaTime() << endl;
    gameObject.setPosition(mousePosition);
}
void FollowMouseScript::collision(GameObject& gameObject, GameObject& collisionObject) { //collision function (does nothing)

}
void FollowMouseScript::trigger(GameObject& gameObject, GameObject& triggerObject) { //trigger function (does nothing)

}
void FollowMouseScript::destroy(GameObject& gameObject) { //destroy function (does nothing)

}
string FollowMouseScript::getAttribute(int index) const { //get attribute
	if (index == 0)
		return applySmoothness ? "true" : "false";
	if (index == 1)
		return floatToString(smoothnessSpeed);
	return "";
}
void FollowMouseScript::setAttribute(int index, string value) { //set attribute
    if (index == 0) {
		applySmoothness = value == "true";
	}
    if (index == 1) {
		smoothnessSpeed = stof(value);
	}
}

string FollowMouseScript::getAttributeName(int index) const { //get attribute name
	if (index == 0)
		return "Apply Smoothness";
	if (index == 1)
		return "Smoothness Speed";
	return "";
}
FollowMouseScript::~FollowMouseScript() { //destructor (does nothing)

}


//Initializes the static variables
int Scene::sceneIdCounter = 0;
int GameObject::idCounter = 500;
GameTime* GameTime::instance = NULL;
RenderWindow* Game::window = NULL;
Scene* Game::currentScene = NULL;
EditorWindow* Game::hierarchy = NULL;
EditorWindow* Game::inspector = NULL;
Font* Game::font = NULL;
bool Game::isPlaying = false;
bool Game::drawEditor = true;
EditorWindow* Game::colorPicker = NULL;

void makeObj(GameObject& ob, const Vector2f& position, float sideLen) { //make a square object
    ob.setPointCount(4);
    ob.setPoint(0, Vector2f(0, 0));
    ob.setPoint(1, Vector2f(sideLen, 0));
    ob.setPoint(2, Vector2f(sideLen, sideLen));
    ob.setPoint(3, Vector2f(0, sideLen));
    ob.setOrigin(ob.getGlobalBounds().getSize() / 2.f);
    ob.setPosition(position);
    ob.makeSquareCollider(sideLen);
}

void changeSelectedIsMovable() { //change if the selected object is movable
    cout << "FUnction called\n";
	Game::getCurrentScene()->changeSelectedIsMovable();
}

class InputField { //Input field class
private:
    RectangleShape field;
    Text text;
    bool isSelected;
    int cursorIndex;
    bool onlyNumbers;
    string str;
    int callIndex;
    void (Scene::*onChange)(string str, int index); //Function pointer to a member function of Scene that takes a string as an argument and returns void (used to call a function when the text changes)
    string(Scene::* updateValue)(int index) const; //Function pointer to a member function of Scene that takes no arguments and returns a string (used to get the value of a variable from the scene)

public:
    InputField(const Font& font, const Vector2f& position, const Vector2f& size, const string& defaultText = "");
    void draw(RenderWindow& window) const;
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
    void setOnChange(void (Scene::*onChange)(string str, int index));
    void setUpdateValue(string(Scene::* updateValue)(int index) const);
    void setCallIndex(int index);
    string processText();
};

InputField::InputField(const Font& font, const Vector2f& position, const Vector2f& size, const string& defaultText) { //constructor
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
    callIndex = 0;
}
void InputField::draw(RenderWindow& window) const { //draw function
    window.draw(field);
    window.draw(text);
}
void InputField::update() { //update function
    if (isSelected) { //If the input field is selected, show the cursor
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
        if(updateValue) str = (Game::getCurrentScene()->*updateValue)(callIndex);
        text.setString(str);
	}
}
void InputField::handleEvent(Event& event) { //handle event function
    if (isSelected) {
        if (event.type == Event::TextEntered) {
            if (onlyNumbers) { //If only numbers are allowed, only allow numbers, a single decimal point and a single minus sign
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
            else { //If all characters are allowed
                if (event.text.unicode == 8) {
                    if (str.size() > 0 && cursorIndex > 0) {
                        str = str.substr(0, cursorIndex - 1) + str.substr(cursorIndex);
                        cursorIndex--;
                    }
                }
                else if (event.text.unicode == 13) {
                    deselect();
                }
                else {
                    str = str.substr(0, cursorIndex) + event.text.unicode + str.substr(cursorIndex);
                    cursorIndex++;
                }
            }
            if(onChange) (Game::getCurrentScene()->*onChange)(processText(), callIndex); //Call the onChange function
        }
        if (event.type == Event::KeyPressed) { //Handle arrow keys and copy-paste
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
                if (onChange) (Game::getCurrentScene()->*onChange)(str, callIndex); //Call the onChange function
            }
            if (event.key.control && event.key.code == Keyboard::C) {
                Clipboard::setString(str);
            }
        }
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) { //Handle mouse clicks
            int x = Mouse::getPosition(*Game::getWindow()).x - field.getPosition().x;
            cout << x << " " << text.findCharacterPos(0).x << endl;
            cursorIndex = x * 2 / text.getCharacterSize();
            if (cursorIndex > str.size())
                cursorIndex = str.size();
            if (cursorIndex < 0)
                cursorIndex = 0;
        }
    }
}
void InputField::select() { //select function
    isSelected = true;
    cursorIndex = str.size();
}
void InputField::deselect() { //deselect function
    isSelected = false;

    str = processText();

    text.setString(str);
}
bool InputField::getSelected() const { //get if the input field is selected
    return isSelected;
}
string InputField::getText() const { //get the text of the input field
    return str;
}
void InputField::setText(const string& text) { //set the text of the input field
    str = text;
    str = processText();
    cursorIndex = str.size();
    this->text.setString(str);
}
void InputField::clear() { //clear the input field
    str = "";
    cursorIndex = 0;
    if (onlyNumbers) {
        str = "0";
        cursorIndex = 1;
    }
    text.setString(str);
}
void InputField::setPosition(const Vector2f& position) { //set the position of the input field
	field.setPosition(position);
	text.setPosition(position.x, position.y);
}
Vector2f InputField::getPosition() const { //get the position of the input field
	return field.getPosition();
}
void InputField::setOnlyNumbers(bool onlyNumbers) { //set if only numbers are allowed
    this->onlyNumbers = onlyNumbers;
}
bool InputField::getOnlyNumbers() const { //get if only numbers are allowed
    return onlyNumbers;
}
void InputField::checkMouseClick() { //check if the input field is clicked, and select it if it is
    Vector2f mousePosition = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
    if (field.getGlobalBounds().contains(mousePosition)) {
        if (!isSelected)
            select();
    }
    else {
        deselect();
    }
}
void InputField::changeBackground() { //change the background of the input field based on if it is selected
    if (isSelected) {
        field.setFillColor(Color::Black);
    }
    else {
        field.setFillColor(Color(150, 150, 150));
    }
}
void InputField::setOnChange(void (Scene::* onChange)(string str, int index)) { //set the onChange function
	this->onChange = onChange;
}
void InputField::setUpdateValue(string(Scene::* updateValue)(int index) const) { //set the updateValue function
	this->updateValue = updateValue;
}
void InputField::setCallIndex(int index) { //set the call index
	callIndex = index;
}
string InputField::processText() { //process the text of the input field
    string ret = str;
    if (onlyNumbers) { //If only numbers are allowed, make sure the text is a valid number (no multiple decimal points, no multiple minus signs, etc.)
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

class Button { //Button class
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
    void (*onClick)(); //Function pointer to a function that takes no arguments and returns void (used to call a function when the button is clicked)
public:
    Button(const Font& font, const Vector2f& position, const Vector2f& size, const string& buttonText = "");
    void draw(RenderWindow& window) const;
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

Button::Button(const Font& font, const Vector2f& position, const Vector2f& size, const string& buttonText) { //constructor
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
void Button::draw(RenderWindow& window) const { //draw function
    window.draw(button);
    window.draw(text);
}
void Button::update() { //update function(Changes the color of the button based on if it is pressed, hovered, etc.)
    if (isActive) {
        if (isPressed || isToggled)
            button.setFillColor(pressedColor);
        else if (isHovered)
            button.setFillColor(hoverColor);
        else
            button.setFillColor(defaultColor);
    }
    else
        button.setFillColor(Color(50, 50, 50));
}
void Button::handleEvent(Event& event) { //handle event function
    if (isActive) { //If the button is active, handle events
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) { //If the left mouse button is pressed, check if the mouse is over the button and press it or toggle it
            Vector2f mousePosition = Vector2f(event.mouseButton.x, event.mouseButton.y);
            if (button.getGlobalBounds().contains(mousePosition) && !isPressed && !isToggle) {
                press();
            }
        }
        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) { //If the left mouse button is released, check if the mouse is over the button and release it or toggle it
            Vector2f mousePosition = Vector2f(event.mouseButton.x, event.mouseButton.y);
            if (button.getGlobalBounds().contains(mousePosition)) {
                if (isToggle)
                    toggle();
                else
                    release();
            }
        }
        if (event.type == Event::MouseMoved) { //If the mouse is moved, check if the mouse is over the button and hover it or unhover it
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
void Button::press() { //press function
    isPressed = true;
    if (onClick)
        onClick();
}
void Button::release() { //release function
    isPressed = false;
}
void Button::hover() { //hover function
    isHovered = true;
}
void Button::unhover() { //unhover function
    isHovered = false;
}
void Button::toggle() { //toggle function
    cout<<"Toggled\n"<<isToggled<<endl;
    if(isToggled)
        button.setFillColor(defaultColor);
    else
        button.setFillColor(pressedColor);
    if (onClick)
        onClick();
    isToggled = !isToggled;
}
void Button::setToggle(bool isToggle) { //set if the button is toggle
    this->isToggle = isToggle;
}
bool Button::getToggle() const { //get if the button is toggle
    return isToggle;
}
bool Button::getToggled() const { //get if the button is toggled
    return isToggled;
}
void Button::setActive(bool isActive) { //set if the button is active
    this->isActive = isActive;
}
bool Button::getActive() const { //get if the button is active
    return isActive;
}
void Button::setText(const string& text) { //set the text of the button
    this->text.setString(text);
}
string Button::getText() const { //get the text of the button
    return text.getString();
}
void Button::setPosition(const Vector2f& position) { //set the position of the button
	button.setPosition(position);
	text.setPosition(position.x + button.getSize().x / 2 - text.getLocalBounds().getSize().x / 2, position.y + button.getSize().y / 2 - text.getLocalBounds().getSize().y / 2);
}
Vector2f Button::getPosition() const { //get the position of the button
	return button.getPosition();
}
void Button::setDefaultColor(const Color& color) { //set the default color of the button
    defaultColor = color;
}
Color Button::getDefaultColor() const { //get the default color of the button
    return defaultColor;
}
void Button::setPressedColor(const Color& color) { //set the pressed color of the button
    pressedColor = color;
}
Color Button::getPressedColor() const { //get the pressed color of the button
    return pressedColor;
}
void Button::setHoverColor(const Color& color) { //set the hover color of the button
    hoverColor = color;
}
Color Button::getHoverColor() const { //get the hover color of the button
    return hoverColor;
}
void Button::setTextColor(const Color& color) { //set the text color of the button
    textColor = color;
    text.setFillColor(textColor);
}
Color Button::getTextColor() const { //get the text color of the button
    return textColor;
}
void Button::setOnClick(void (*onClick)()) { //set the onClick function
    this->onClick = onClick;
}


Text* updateHierarchy(Text* objectTexts, const RectangleShape& hierarchy, const Font& font, const Text& hierarchyTitle) { //update the hierarchy window
    if (objectTexts)
        delete[] objectTexts;
    const vector<GameObject*>& objects = Game::getCurrentScene()->getObjects();
    objectTexts = new Text[objects.size()];
    float objectHeight = (hierarchy.getSize().y - hierarchyTitle.getCharacterSize() * 2) / objects.size();
    for (int i = 0; i < objects.size(); i++) {
        objectTexts[i].setFont(font); //Fake warning
        objectTexts[i].setCharacterSize(15);
        objectTexts[i].setFillColor(Color::White);
        objectTexts[i].setString(objects[i]->getName());
        objectTexts[i].setPosition(hierarchy.getPosition().x + 10, hierarchy.getPosition().y + i * objectHeight + hierarchyTitle.getCharacterSize() + 10);
    }
    return objectTexts;
}


class EditorWindow { //Editor window class(used for the hierarchy and inspector windows and can be expanded upon), abstract class
protected:
    RectangleShape window;
    RectangleShape draggingArea;
	Text title;
	vector<Button> buttons;
	vector<InputField> inputFields;
	vector<Text> texts;
	Vector2f position;
	Vector2f size;
    bool isActive;
    bool isDragglable;
    bool isDragging;
    Vector2f dragOffset;

    static bool clickedUI;
public:
    EditorWindow(const Font& font, const Vector2f& position, const Vector2f& size, const string& titleText = "");

	virtual void draw(RenderWindow& window) const;
	virtual void update();
	virtual void handleEvent(Event& event);

    virtual void mouseOver() = 0; //pure virtual function because it is completely different for the hierarchy and inspector windows
    virtual void drag(Event& event);

	void addButton(const Button& button);
	void addInputField(const InputField& inputField);
	virtual void addText(const Text& text);

    void changeText(int index, const string& text);
    virtual void deleteText(int index);
    void deleteFields();
    int getTextCount() const;

	void setTitle(const string& titleText);
	string getTitle() const;

	void setPosition(const Vector2f& position);
	Vector2f getPosition() const;

	void setSize(const Vector2f& size);
	Vector2f getSize() const;

    virtual void setActive(bool isActive);
    bool getActive() const;

    static void setClickedUI(bool clickedUI);
    static bool getClickedUI();

    virtual ~EditorWindow();
};
EditorWindow::EditorWindow(const Font& font, const Vector2f& position, const Vector2f& size, const string& titleText) { //constructor
	window.setPosition(position);
	window.setSize(size);
	window.setFillColor(Color(50, 50, 50));
	window.setOutlineColor(Color::Black);
	window.setOutlineThickness(1);

    draggingArea.setPosition(position);
    draggingArea.setSize(Vector2f(size.x, 25));
    draggingArea.setFillColor(Color(100, 100, 100));
    draggingArea.setOutlineColor(Color::Black);
    draggingArea.setOutlineThickness(1);

	title.setFont(font);
	title.setCharacterSize(20);
	title.setFillColor(Color::Cyan);
	title.setString(titleText);
	title.setOrigin(title.getLocalBounds().getSize().x / 2.f, 0.f);
	title.setPosition(position.x + size.x / 2.f, position.y);

	this->position = position;
	this->size = size;
	isActive = true;
    isDragglable = false;
    isDragging = false;
    dragOffset = Vector2f(0, 0);
}
void EditorWindow::draw(RenderWindow& window) const { //draw function
    if(!isActive)
		return;
	window.draw(this->window);
    if(isDragglable)
		window.draw(draggingArea);
	window.draw(title);
	for (int i = 0; i < buttons.size(); i++)
		buttons[i].draw(window);
	for (int i = 0; i < inputFields.size(); i++)
		inputFields[i].draw(window);
	for (int i = 0; i < texts.size(); i++)
		window.draw(texts[i]);
}
void EditorWindow::update() { //update function
    if (!isActive)
        return;
	for (int i = 0; i < buttons.size(); i++)
		buttons[i].update();
    for (int i = 0; i < inputFields.size(); i++) {
        inputFields[i].update();
        inputFields[i].changeBackground();
    }

}
void EditorWindow::handleEvent(Event& event) { //handle event function
    if (!isActive)
        return;

    //Check if we clicked on the window and update the clickedUI variable
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
		Vector2f mousePosition = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
        if (window.getGlobalBounds().contains(mousePosition))
			clickedUI = true;
	}

    drag(event);
	for (int i = 0; i < buttons.size(); i++)
		buttons[i].handleEvent(event);
    for (int i = 0; i < inputFields.size(); i++)
        inputFields[i].handleEvent(event);
}
void EditorWindow::drag(Event& event) { //drag function
    if (isDragglable) {
		Vector2f mousePosition = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
        if (isDragging) {
            Vector2f deltaMovedAmount = mousePosition - dragOffset - position;
            setPosition(mousePosition - dragOffset);
			draggingArea.setPosition(position);

            title.setPosition(position.x + size.x / 2.f, position.y);

            for (int i = 0; i < buttons.size(); i++)
				buttons[i].setPosition(buttons[i].getPosition() + deltaMovedAmount);
            for (int i = 0; i < inputFields.size(); i++)
				inputFields[i].setPosition(inputFields[i].getPosition() + deltaMovedAmount);
			for (int i = 0; i < texts.size(); i++)
				texts[i].setPosition(texts[i].getPosition() + deltaMovedAmount);
		}
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && draggingArea.getGlobalBounds().contains(mousePosition)) {
            isDragging = true;
			dragOffset = mousePosition - position;
		}
        if (!Mouse::isButtonPressed(Mouse::Left)) {
			isDragging = false;
		}
	}
}
void EditorWindow::addButton(const Button& button) { //add a button to the window
	buttons.push_back(button);
}
void EditorWindow::addInputField(const InputField& inputField) { //add an input field to the window
	inputFields.push_back(inputField);
}
void EditorWindow::addText(const Text& text) { //add a text to the window
	texts.push_back(text);
}
void EditorWindow::changeText(int index, const string& text) { //change the text of a text in the window
	if (index < texts.size() && index >= 0)
		texts[index].setString(text);
}
void EditorWindow::deleteText(int index) { //delete a text from the window
    if (index < texts.size() && index >= 0)
        texts.erase(texts.begin() + index);
}
void EditorWindow::deleteFields() { //delete all the input fields from the window
	inputFields.clear();
}
int EditorWindow::getTextCount() const { //get the number of texts in the window
	return texts.size();
}
void EditorWindow::setTitle(const string& titleText) { //set the title of the window
	title.setString(titleText);
	title.setOrigin(title.getLocalBounds().getSize().x / 2.f, 0.f);
	title.setPosition(position.x + size.x / 2.f, position.y);
}
string EditorWindow::getTitle() const { //get the title of the window
	return title.getString();
}
void EditorWindow::setPosition(const Vector2f& position) { //set the position of the window
	window.setPosition(position);
	title.setPosition(position.x + size.x / 2.f, position.y);
	this->position = position;
}
Vector2f EditorWindow::getPosition() const { //get the position of the window
	return position;
}
void EditorWindow::setSize(const Vector2f& size) { //set the size of the window
	window.setSize(size);
	title.setPosition(position.x + size.x / 2.f, position.y);
	this->size = size;
}
Vector2f EditorWindow::getSize() const { //get the size of the window
	return size;
}
void EditorWindow::setActive(bool isActive) { //set if the window is active
	this->isActive = isActive;
}
bool EditorWindow::getActive() const { //get if the window is active
	return isActive;
}
void EditorWindow::setClickedUI(bool clickedUI) { //set if the UI is clicked
	EditorWindow::clickedUI = clickedUI;
}
bool EditorWindow::getClickedUI() { //get if the UI is clicked
	return clickedUI;
}
EditorWindow::~EditorWindow() { //destructor
	buttons.clear();
	inputFields.clear();
	texts.clear();
}


bool EditorWindow::clickedUI = false;

void createObj();
void deleteObj();


class ColorPicker : public EditorWindow {
private:
    VertexArray colorsDisplay;
    VertexArray hueBarDisplay;
    VertexArray alphaBarDisplay;
    RectangleShape alphaBarBackground;
    CircleShape colorsCursor;
    CircleShape hueBarCursor;
    CircleShape alphaBarCursor;
    Color selectedColor;
    int selected;

    Vector2f colorsOffset;
    Vector2f hueBarOffset;
    Vector2f alphaBarOffset;

    void drawHSV(Vertex& point, double h, double s, double v, double alpha);
    void modulate(VertexArray& points, double hue);
    void accuratePosition(int& x, int& y, int xLimit, int yLimit);
    void setCursorsBasedOnColor();
    void reposition();
public:
    ColorPicker(Font& font, const Vector2f& position, const Vector2f& size, const string& title);
    void handleEvent(Event& event) override;
    void draw(RenderWindow& window) const override;
    void update() override;
    void mouseOver() override;
    void drag(Event& event) override;
    Color getSelectedColor() const;
    void setSelectedColor(const Color& color);
    void setActive(bool active) override;
    ~ColorPicker() override;
};
void ColorPicker::drawHSV(Vertex& point, double h, double s, double v, double alpha) {
    // Pick the correct case based on our position on the color wheel.
    const int cs = h * 6;

    // Calculate some helper values used in our cases below.
    const double f = h * 6 - cs;
    const double p = v * (1 - s);
    const double q = v * (1 - s * f);
    const double t = v * (1 - s * (1 - f));

    switch (cs) {
    case 0:
    case 6:
        point.color = Color(v * 255, t * 255, p * 255, 255 * alpha);
        break;
    case 1:
        point.color = Color(q * 255, v * 255, p * 255, 255 * alpha);
        break;
    case 2:
        point.color = Color(p * 255, v * 255, t * 255, 255 * alpha);
        break;
    case 3:
        point.color = Color(p * 255, q * 255, v * 255, 255 * alpha);
        break;
    case 4:
        point.color = Color(t * 255, p * 255, v * 255, 255 * alpha);
        break;
    case 5:
        point.color = Color(v * 255, p * 255, q * 255, 255 * alpha);
        break;
    }
}
void ColorPicker::modulate(VertexArray& points, double hue) {
    // First, Let's "sanitize" inputs a bit.
    // Don't accept negative numbers.
    if (hue < 0)
        hue = 0;
    // Lazy overflow by subtracting the integer portion of the number.
    else if (hue > 1)
        hue -= static_cast<int>(hue);

    // Now iterate over all "pixels" and upate their colors.
    for (unsigned int y = 0; y <= 255; ++y) {
        for (unsigned int x = 0; x <= 255; ++x) {
            // "Calculate" our missing HSV components with ranges from 0 to 1.
            const double s = x / 255.; // x is our saturation
            const double v = y / 255.; // y is our value

            // Draw the pixel.
            drawHSV(points[y * 256 + x], hue, s, v, 1);
        }
    }
}
void ColorPicker::accuratePosition(int& x, int& y, int xLimit, int yLimit) {
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    if (x > xLimit)
        x = xLimit;
    if (y > yLimit)
        y = yLimit;
}
void ColorPicker::setCursorsBasedOnColor() {
    double r = selectedColor.r / 255.;
    double g = selectedColor.g / 255.;
    double b = selectedColor.b / 255.;
    double maxx = max(r, max(g, b));
    double minn = min(r, min(g, b));
    double delta = maxx - minn;
    double h = 0;
    if (delta == 0)
		h = 0;
	else if (maxx == r)
		h = 60 * fmod((g - b) / delta, 6);
	else if (maxx == g)
		h = 60 * ((b - r) / delta + 2);
	else
		h = 60 * ((r - g) / delta + 4);
    if (h < 0)
		h += 360;
	double s = maxx == 0 ? 0 : delta / maxx;
	double v = maxx;
	double a = selectedColor.a / 255.;

    colorsOffset = Vector2f(255 * s, 255 * v);
	hueBarOffset = Vector2f(hueBarOffset.x, h * 255 / 360);
	alphaBarOffset = Vector2f(alphaBarOffset.x, a * 255);

    modulate(colorsDisplay, h / 360);

	reposition();
}
void ColorPicker::reposition() {
    for (unsigned int y = 0; y <= 255; ++y) {
        for (unsigned int x = 0; x <= 255; ++x) {
            Vertex& vertex(colorsDisplay[y * 256 + x]);
            vertex.position.x = 255 - x + position.x + 5;
            vertex.position.y = 255 - y + position.y + 30;
        }
    }

    for (unsigned int y = 0; y <= 255; ++y) {
        for (unsigned int x = 0; x < 20; ++x) {
            Vertex& vertex(hueBarDisplay[y * 20 + x]);
            vertex.position.x = x + position.x + size.x - 55;
            vertex.position.y = y + position.y + 30;

            // Calculate the hue value based on the y position.
            const double hue = y / 255.;
            drawHSV(vertex, hue, 1, 1, 1);
        }
    }

    for (unsigned int y = 0; y <= 255; ++y) {
        for (unsigned int x = 0; x < 20; ++x) {
            Vertex& vertex(alphaBarDisplay[y * 20 + x]);
            vertex.position.x = x + position.x + size.x - 25;
            vertex.position.y = y + position.y + 30;

            // Calculate the hue value based on the y position.
            drawHSV(vertex, 1, 0, y / 255., y / 255.);
        }
    }

    alphaBarBackground.setPosition(position.x + size.x - 25, position.y + 29);

    colorsCursor.setPosition(colorsDisplay[colorsOffset.y * 256 + colorsOffset.x].position);
    hueBarCursor.setPosition(hueBarDisplay[hueBarOffset.y * 20 + hueBarOffset.x].position);
    alphaBarCursor.setPosition(alphaBarDisplay[alphaBarOffset.y * 20 + alphaBarOffset.x].position);
}
ColorPicker::ColorPicker(Font& font, const Vector2f& position, const Vector2f& size, const string& title) : EditorWindow(font, position, size, title) {
    colorsDisplay = VertexArray(Points, 256 * 256);
    hueBarDisplay = VertexArray(Points, 256 * 20);
    alphaBarDisplay = VertexArray(Points, 256 * 20);

    colorsOffset = Vector2f(0, 255);
    hueBarOffset = Vector2f(0, 0);
    alphaBarOffset = Vector2f(19, 255);

    colorsCursor = CircleShape(5);
    colorsCursor.setOrigin(5, 5);
    colorsCursor.setFillColor(Color::Transparent);
    colorsCursor.setOutlineColor(Color::Black);
    colorsCursor.setOutlineThickness(2);

    hueBarCursor = CircleShape(5);
    hueBarCursor.setOrigin(5, 5);
    hueBarCursor.setFillColor(Color::Transparent);
    hueBarCursor.setOutlineColor(Color::Black);
    hueBarCursor.setOutlineThickness(2);

    alphaBarCursor = CircleShape(5);
    alphaBarCursor.setOrigin(5, 5);
    alphaBarCursor.setFillColor(Color::Transparent);
    alphaBarCursor.setOutlineColor(Color::Red);
    alphaBarCursor.setOutlineThickness(2);

    alphaBarBackground = RectangleShape(Vector2f(20, 256));
    alphaBarBackground.setFillColor(Color::Black);
    alphaBarBackground.setOutlineColor(Color::White);
    alphaBarBackground.setOutlineThickness(1);
    alphaBarBackground.setPosition(position.x + size.x - 25, position.y + 29);

    reposition();

    modulate(colorsDisplay, 0);

    Text* tmp = new Text("Color: ", font, 15);
    tmp->setPosition(position.x + 15, position.y + 295);
    texts.push_back(*tmp);
    delete tmp;

    InputField* tmp2 = new InputField(font, Vector2f(position.x + 70, position.y + 295), Vector2f(100, 20), "#00000000");
    tmp2->setOnlyNumbers(false);
    inputFields.push_back(*tmp2);
    delete tmp2;


    selectedColor = Color::White;
    selected = -1;
    isActive = false;
    isDragglable = true;

    
}
void ColorPicker::handleEvent(Event& event) { //handle event function
    if (!isActive)
        return;
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        Vector2f mousePos = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
        if (colorsDisplay.getBounds().contains(mousePos))
            selected = 0;
        else if (hueBarDisplay.getBounds().contains(mousePos))
            selected = 1;
        else if (alphaBarDisplay.getBounds().contains(mousePos))
            selected = 2;
        else if (!window.getGlobalBounds().contains(mousePos))
            setActive(false);
    }
    else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
        selected = -1;
    EditorWindow::handleEvent(event);
}
void ColorPicker::draw(RenderWindow& window) const { //draw function
    if (!isActive)
        return;
    EditorWindow::draw(window);
    window.draw(colorsDisplay);
    window.draw(hueBarDisplay);
    window.draw(alphaBarBackground);
    window.draw(alphaBarDisplay);
    window.draw(colorsCursor);
    window.draw(hueBarCursor);
    window.draw(alphaBarCursor);
}
void ColorPicker::update() { //update function
	if (!isActive)
		return;
	EditorWindow::update();
    if (selected == -1) {
        if (!inputFields[0].getSelected())
            inputFields[0].setText("#" + ColorToString(selectedColor));
        else {
            selectedColor = stringToColor(inputFields[0].getText());
            setCursorsBasedOnColor();
        }
    }
}
void ColorPicker::mouseOver() { //mouse over function (used to check if the mouse is over the color picker window and to check the color picker's elements)
    if (!isActive)
        return;
    Vector2f mousePos = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
    if (selected == 0) {
        int relativeX = 255 - (mousePos.x - colorsDisplay[255].position.x);
        int relativeY = 255 - (mousePos.y - colorsDisplay[255 * 256 - 1].position.y);
        accuratePosition(relativeX, relativeY, 255, 255);
        colorsCursor.setPosition(255 - relativeX + colorsDisplay[255].position.x, 255 - relativeY + colorsDisplay[255 * 256 - 1].position.y);
        selectedColor = colorsDisplay[relativeY * 256 + relativeX].color;
        colorsOffset = Vector2f(relativeX, relativeY);
    }
    else if (selected == 1) {
        int relativeY = mousePos.y - hueBarDisplay[0].position.y;
        int relativeX = mousePos.x - hueBarDisplay[0].position.x;
        accuratePosition(relativeX, relativeY, 19, 255);
        hueBarCursor.setPosition(relativeX + hueBarDisplay[0].position.x, relativeY + hueBarDisplay[0].position.y);
        modulate(colorsDisplay, relativeY / 255.);
        hueBarOffset = Vector2f(relativeX, relativeY);
        relativeX = 255 - (colorsCursor.getPosition().x - colorsDisplay[255].position.x);
        int relativeY2 = 255 - (colorsCursor.getPosition().y - colorsDisplay[255 * 256 - 1].position.y);
        accuratePosition(relativeX, relativeY2, 255, 255);
        selectedColor = colorsDisplay[relativeY2 * 256 + relativeX].color;
    }
    else if (selected == 2) {
        int relativeX = mousePos.x - alphaBarDisplay[0].position.x;
        int relativeY = mousePos.y - alphaBarDisplay[0].position.y;
        accuratePosition(relativeX, relativeY, 19, 255);
        alphaBarCursor.setPosition(relativeX + alphaBarDisplay[0].position.x, relativeY + alphaBarDisplay[0].position.y);
        selectedColor.a = alphaBarDisplay[relativeY * 20 + relativeX].color.a;
        alphaBarOffset = Vector2f(relativeX, relativeY);
    }
    if (!inputFields[0].getSelected())
        inputFields[0].setText("#" + ColorToString(selectedColor));
    for (int i = 0; i < inputFields.size(); i++) {
        inputFields[i].checkMouseClick();
    }
}
void ColorPicker::drag(Event& event) {
	EditorWindow::drag(event);
    if (isDragging) {
        reposition();
	}

}
Color ColorPicker::getSelectedColor() const { //get the selected color of the color picker
    return selectedColor;
}
void ColorPicker::setSelectedColor(const Color& color) { //set the selected color of the color picker
	selectedColor = color;
	setCursorsBasedOnColor();
}
void ColorPicker::setActive(bool active) { //set the active state of the color picker
    isActive = active;
    selected = -1;
    if (!active) {
        inputFields[0].deselect();
		inputFields[0].setText("#" + ColorToString(selectedColor));
	}
}
ColorPicker::~ColorPicker() {} //destructor



class EditableColor {
private:
    RectangleShape colorBox;
    void (Scene::* onChange) (string str, int index);
    string(Scene::* updateValue)(int index) const;
    int callIndex;
    bool isSelected;
public:
    EditableColor(const Vector2f& position, const Vector2f& size, const Color& color, void (Scene::* onChange) (string str, int index), string(Scene::* updateValue)(int index) const, int callIndex);
	void draw(RenderWindow& window) const;
	void update();
	void handleEvent(Event& event);
	void mouseOver();
	void setSelected(bool isSelected);
	bool getSelected() const;
	void setColor(const Color& color);
	Color getColor() const;
	void setPosition(const Vector2f& position);
	Vector2f getPosition() const;
	void setSize(const Vector2f& size);
	Vector2f getSize() const;
	void setOnChange(void (Scene::* onChange) (string str, int index));
	void setUpdateValue(string(Scene::* updateValue)(int index) const);
	void setCallIndex(int callIndex);
	int getCallIndex() const;
};
EditableColor::EditableColor(const Vector2f& position, const Vector2f& size, const Color& color, void (Scene::* onChange) (string str, int index), string(Scene::* updateValue)(int index) const, int callIndex) {
	colorBox.setPosition(position);
	colorBox.setSize(size);
	colorBox.setFillColor(color);
	colorBox.setOutlineColor(Color::Black);
	colorBox.setOutlineThickness(1);

	this->onChange = onChange;
	this->updateValue = updateValue;
	this->callIndex = callIndex;
	isSelected = false;
}
void EditableColor::draw(RenderWindow& window) const { //draw function
	window.draw(colorBox);
}
void EditableColor::update() { //update function
    if (isSelected) {
		ColorPicker* colorPicker = dynamic_cast<ColorPicker*>(Game::getColorPicker());
        if (colorPicker) {
			colorBox.setFillColor(colorPicker->getSelectedColor());
			(Game::getCurrentScene()->*onChange)(ColorToString(colorBox.getFillColor()), callIndex);
            if(!colorPicker->getActive())
                isSelected = false;
		}
	}
    else {
        if (updateValue) {
            colorBox.setFillColor(stringToColor((Game::getCurrentScene()->*updateValue)(callIndex)));
            (Game::getCurrentScene()->*onChange)(ColorToString(colorBox.getFillColor()), callIndex);
		}
    }
}
void EditableColor::handleEvent(Event& event) { //handle event function
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
		Vector2f mousePos = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
        if (colorBox.getGlobalBounds().contains(mousePos)) {
            isSelected = true;
            ColorPicker* colorPicker = dynamic_cast<ColorPicker*>(Game::getColorPicker());
            if (colorPicker) {
				colorPicker->setActive(true);
                //colorBox.setFillColor(Game::getCurrentScene()->getObjectByIndex(Game::getCurrentScene()->getSelectedObjectIndex())->getFillColor());
                cout<<"Tanta " << ColorToString(colorBox.getFillColor()) << endl;
                colorPicker->setSelectedColor(colorBox.getFillColor());
			}
		}
	}
}
void EditableColor::mouseOver() { //mouse over function
}
void EditableColor::setSelected(bool isSelected) { //set if the color is selected
	this->isSelected = isSelected;
}
bool EditableColor::getSelected() const { //get if the color is selected
	return isSelected;
}
void EditableColor::setColor(const Color& color) { //set the color of the color box
	colorBox.setFillColor(color);
}
Color EditableColor::getColor() const { //get the color of the color box
	return colorBox.getFillColor();
}
void EditableColor::setPosition(const Vector2f& position) { //set the position of the color box
	colorBox.setPosition(position);
}
Vector2f EditableColor::getPosition() const { //get the position of the color box
	return colorBox.getPosition();
}
void EditableColor::setSize(const Vector2f& size) { //set the size of the color box
	colorBox.setSize(size);
}
Vector2f EditableColor::getSize() const { //get the size of the color box
	return colorBox.getSize();
}
void EditableColor::setOnChange(void (Scene::* onChange) (string str, int index)) { //set the onChange function
	this->onChange = onChange;
}
void EditableColor::setUpdateValue(string(Scene::* updateValue)(int index) const) { //set the updateValue function
	this->updateValue = updateValue;
}
void EditableColor::setCallIndex(int callIndex) { //set the call index
	this->callIndex = callIndex;
}
int EditableColor::getCallIndex() const { //get the call index
	return callIndex;
}



class InspectorWindow : public EditorWindow { //Inspector window class
private:
    vector<EditableColor> colors;
    void makeDefaultFields();
public:
    InspectorWindow(const Font& font, const Vector2f& position, const Vector2f& size, const string& titleText = "");
    void makeCustomFields();
    void update() override;
    void handleEvent(Event& event) override;
    void draw(RenderWindow& window) const;
    void mouseOver();
};


class HierarchyWindow : public EditorWindow { //Hierarchy window class
private:
    void repositionTexts();
public:
    HierarchyWindow(const Font& font, const Vector2f& position, const Vector2f& size, const string& titleText = "");
    void update() override;
    void handleEvent(Event& event) override;
	void mouseOver();
    void changeSelectedObject(int index);
    void addText(const Text& text) override;
    void deleteText(int index) override;
};
void HierarchyWindow::repositionTexts() { //reposition the texts in the hierarchy window
	float objectHeight = (window.getSize().y - title.getCharacterSize() * 2) / texts.size();
    for (int i = 0; i < texts.size(); i++) {
		texts[i].setPosition(window.getPosition().x + 10, window.getPosition().y + i * objectHeight + title.getCharacterSize() + 10);
	}
}
//Hierarchy window constructor (makes a button to create objects and adds texts for the objects in the hierarchy)
HierarchyWindow::HierarchyWindow(const Font& font, const Vector2f& position, const Vector2f& size, const string& titleText) : EditorWindow(font, position, size, titleText) {
    setTitle("Hierarchy");
    Button* createButton = new Button(font, Vector2f(position.x + 10, position.y + size.y - 40), Vector2f(size.x - 20, 30), "Create Object");
    createButton->setOnClick(createObj);
    addButton(*createButton);
    delete createButton;

    //Adding texts for the objects in the hierarchy
    Text* tmp = new Text("Tmp", font, 15);
    for (int i = 0; i < Game::getCurrentScene()->getObjects().size(); i++) {
        tmp->setString(Game::getCurrentScene()->getObjectByIndex(i)->getName());
        tmp->setPosition(position.x + 10, position.y + i * 30 + tmp->getCharacterSize() + 10);
        addText(*tmp);
    }
    delete tmp;

    Game::setHierarchy(this);
}
void HierarchyWindow::update() { //update the texts in the hierarchy window
    EditorWindow::update();
    for (int i = 0; i < Game::getCurrentScene()->getObjects().size(); i++) {
		texts[i].setString(Game::getCurrentScene()->getObjectByIndex(i)->getName());
	}
}
void HierarchyWindow::handleEvent(Event& event) { //handle event function
    if (isActive) {
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && !clickedUI) {
			Vector2f mousePos = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
            if (window.getGlobalBounds().contains(mousePos)) {
				int newSelectedIndex = -1;
                for (int i = 0; i < Game::getCurrentScene()->getObjectsCount(); i++) {
                    if (texts[i].getGlobalBounds().contains(mousePos)) {
						newSelectedIndex = i;
						break;
					}
				}
				changeSelectedObject(newSelectedIndex);
			}
            else{
                int newSelectedIndex = -1;
                //Loop through the objects in the scene and check if the mouse is over them
                for (int i = 0; i < Game::getCurrentScene()->getObjectsCount(); i++) {
                    if (Game::getCurrentScene()->getObjectByIndex(i)->getGlobalBounds().contains(mousePos)) {
						newSelectedIndex = i;
						break;
					}
				}
                if(newSelectedIndex != Game::getCurrentScene()->getSelectedObjectIndex())
					changeSelectedObject(newSelectedIndex);
            }
		}
	}
	EditorWindow::handleEvent(event);
}
void HierarchyWindow::mouseOver() { //mouse over function (responsible for selecting objects in the hierarchy window)
    
}
void HierarchyWindow::changeSelectedObject(int newSelectedIndex) {
    if (newSelectedIndex != Game::getCurrentScene()->getSelectedObjectIndex()) {
        if (Game::getCurrentScene()->getSelectedObjectIndex() != -1)
            texts[Game::getCurrentScene()->getSelectedObjectIndex()].setFillColor(Color::White);
        Game::getCurrentScene()->setSelectedObjectIndex(newSelectedIndex);
        InspectorWindow* tmp = dynamic_cast<InspectorWindow*>(Game::getInspector());
        if (tmp)
            tmp->makeCustomFields();
        if (Game::getCurrentScene()->getSelectedObjectIndex() != -1)
            texts[Game::getCurrentScene()->getSelectedObjectIndex()].setFillColor(Color::Cyan);
    }
}
void HierarchyWindow::addText(const Text& text) { //add a text to the hierarchy window
	texts.push_back(text);
    repositionTexts();
}
void HierarchyWindow::deleteText(int index) { //delete a text from the hierarchy window
	if (index < texts.size() && index >= 0){
		texts.erase(texts.begin() + index);
        repositionTexts();
	}
}



void InspectorWindow::makeDefaultFields() {
    //Make the field for the object's name
    InputField* tmpField = new InputField(*Game::getFont(), Vector2f(position.x + 10, position.y + title.getCharacterSize() + 10), Vector2f(100, 20), "Name");
    tmpField->setOnChange(&Scene::modifySelectedCustom);
    tmpField->setUpdateValue(&Scene::getSelectedCustom);
    tmpField->setCallIndex(0);
    addInputField(*tmpField);
    delete tmpField;

    //Make the position fields
    Text* tmp = new Text("Position:", *Game::getFont(), 15);
    tmp->setFillColor(Color::White);
    tmp->setPosition(position.x + 10, position.y + title.getCharacterSize() + 40);
    addText(*tmp);
    delete tmp;

    tmpField = new InputField(*Game::getFont(), Vector2f(position.x + 10, position.y + title.getCharacterSize() + 70), Vector2f(100, 20), "0");
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedCustom);
    tmpField->setUpdateValue(&Scene::getSelectedCustom);
    tmpField->setCallIndex(1);
    addInputField(*tmpField);
    delete tmpField;

    tmpField = new InputField(*Game::getFont(), Vector2f(position.x + 10, position.y + title.getCharacterSize() + 100), Vector2f(100, 20), "0");
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedCustom);
    tmpField->setUpdateValue(&Scene::getSelectedCustom);
    tmpField->setCallIndex(2);
    addInputField(*tmpField);
    delete tmpField;

    //Make the rotation field
    tmp = new Text("Rotation:", *Game::getFont(), 15);
    tmp->setFillColor(Color::White);
    tmp->setPosition(position.x + 10, position.y + title.getCharacterSize() + 130);
    addText(*tmp);
    delete tmp;

    tmpField = new InputField(*Game::getFont(), Vector2f(position.x + 10, position.y + title.getCharacterSize() + 160), Vector2f(100, 20), "0");
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedCustom);
    tmpField->setUpdateValue(&Scene::getSelectedCustom);
    tmpField->setCallIndex(3);
    addInputField(*tmpField);
    delete tmpField;

    //Make the scale fields
    tmp = new Text("Scale:", *Game::getFont(), 15);
    tmp->setFillColor(Color::White);
    tmp->setPosition(position.x + 10, position.y + title.getCharacterSize() + 190);
    addText(*tmp);
    delete tmp;

    tmpField = new InputField(*Game::getFont(), Vector2f(position.x + 10, position.y + title.getCharacterSize() + 220), Vector2f(100, 20), "0");
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedCustom);
    tmpField->setUpdateValue(&Scene::getSelectedCustom);
    tmpField->setCallIndex(4);
    addInputField(*tmpField);
    delete tmpField;

    tmpField = new InputField(*Game::getFont(), Vector2f(position.x + 10, position.y + title.getCharacterSize() + 250), Vector2f(100, 20), "0");
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedCustom);
    tmpField->setUpdateValue(&Scene::getSelectedCustom);
    tmpField->setCallIndex(5);
    addInputField(*tmpField);
    delete tmpField;

    //Make the velocity fields
    tmp = new Text("Velocity:", *Game::getFont(), 15);
    tmp->setFillColor(Color::White);
    tmp->setPosition(position.x + 10, position.y + title.getCharacterSize() + 280);
    addText(*tmp);
    delete tmp;

    tmpField = new InputField(*Game::getFont(), Vector2f(position.x + 10, position.y + title.getCharacterSize() + 310), Vector2f(100, 20), "0");
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedCustom);
    tmpField->setUpdateValue(&Scene::getSelectedCustom);
    tmpField->setCallIndex(6);
    addInputField(*tmpField);
    delete tmpField;

    tmpField = new InputField(*Game::getFont(), Vector2f(position.x + 10, position.y + title.getCharacterSize() + 340), Vector2f(100, 20), "0");
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedCustom);
    tmpField->setUpdateValue(&Scene::getSelectedCustom);
    tmpField->setCallIndex(7);
    addInputField(*tmpField);
    delete tmpField;

    //Make the mass field
    tmp = new Text("Mass:", *Game::getFont(), 15);
    tmp->setFillColor(Color::White);
    tmp->setPosition(position.x + 10, position.y + title.getCharacterSize() + 370);
    addText(*tmp);
    delete tmp;

    tmpField = new InputField(*Game::getFont(), Vector2f(position.x + 10, position.y + title.getCharacterSize() + 400), Vector2f(100, 20), "0");
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedCustom);
    tmpField->setUpdateValue(&Scene::getSelectedCustom);
    tmpField->setCallIndex(8);
    addInputField(*tmpField);
    delete tmpField;

    //Make the color field
    EditableColor* tmpColor = new EditableColor(Vector2f(position.x + 10, position.y + title.getCharacterSize() + 430), Vector2f(100, 20), Color::White, &Scene::modifySelectedCustom, &Scene::getSelectedCustom, 9);
    tmpColor->setCallIndex(9);
    tmpColor->setOnChange(&Scene::modifySelectedCustom);
    tmpColor->setUpdateValue(&Scene::getSelectedCustom);
    colors.push_back(*tmpColor);
    delete tmpColor;
}
//Inspector window constructor (makes input fields for the position, rotation, scale, and velocity of the selected object, a button to delete the selected object, and a button to change if the selected object is movable) will need to be expanded upon
InspectorWindow::InspectorWindow(const Font& font, const Vector2f& position, const Vector2f& size, const string& titleText) : EditorWindow(font, position, size, titleText) {
    /*Text* tmp = new Text("Position:", font, 15);
    tmp->setFillColor(Color::White);

    InputField* tmpField = new InputField(font, Vector2f(position.x + 10, position.y + title.getCharacterSize() + 10), Vector2f(100, 20), "0");

    //Position label
    tmp->setPosition(position.x + 10, position.y + title.getCharacterSize() + 10);
    addText(*tmp);

    //Position X input field
    tmp->setString("X: ");
    tmp->setPosition(position.x + 10, tmp->getPosition().y + tmp->getCharacterSize() + 10);
    tmpField->setPosition(Vector2f(position.x + 10 + tmp->getLocalBounds().getSize().x, tmp->getPosition().y));
    addText(*tmp);
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedPositionX); //Select the modifySelectedPositionX function to be called when the text changes
    tmpField->setUpdateValue(&Scene::getSelectedPositionX); //Select the getSelectedPositionX function to get the value of the selected object's position X
    addInputField(*tmpField);

    //Position Y input field
    tmp->setString("Y: ");
    tmp->setPosition(position.x + 10, tmp->getPosition().y + tmp->getCharacterSize() + 10);
    tmpField->setPosition(Vector2f(position.x + 10 + tmp->getLocalBounds().getSize().x, tmp->getPosition().y));
    addText(*tmp);
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedPositionY); //Select the modifySelectedPositionY function to be called when the text changes
    tmpField->setUpdateValue(&Scene::getSelectedPositionY); //Select the getSelectedPositionY function to get the value of the selected object's position Y
    addInputField(*tmpField);

    //Rotation label and input field
    tmp->setString("Rotation: ");
    tmp->setPosition(position.x + 10, tmp->getPosition().y + tmp->getCharacterSize() + 10);
    tmpField->setPosition(Vector2f(position.x + 10 + tmp->getLocalBounds().getSize().x, tmp->getPosition().y));
    addText(*tmp);
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedRotation); //Select the modifySelectedRotation function to be called when the text changes
    tmpField->setUpdateValue(&Scene::getSelectedRotation); //Select the getSelectedRotation function to get the value of the selected object's rotation
    addInputField(*tmpField);

    //Scale label
    tmp->setString("Scale: ");
    tmp->setPosition(position.x + 10, tmp->getPosition().y + tmp->getCharacterSize() + 10);
    addText(*tmp);

    //Scale X input field
    tmp->setString("X: ");
    tmp->setPosition(position.x + 10, tmp->getPosition().y + tmp->getCharacterSize() + 10);
    tmpField->setPosition(Vector2f(position.x + 10 + tmp->getLocalBounds().getSize().x, tmp->getPosition().y));
    addText(*tmp);
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedScaleX); //Select the modifySelectedScaleX function to be called when the text changes
    tmpField->setUpdateValue(&Scene::getSelectedScaleX); //Select the getSelectedScaleX function to get the value of the selected object's scale X
    addInputField(*tmpField);

    //Scale Y input field
    tmp->setString("Y: ");
    tmp->setPosition(position.x + 10, tmp->getPosition().y + tmp->getCharacterSize() + 10);
    tmpField->setPosition(Vector2f(position.x + 10 + tmp->getLocalBounds().getSize().x, tmp->getPosition().y));
    addText(*tmp);
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedScaleY); //Select the modifySelectedScaleY function to be called when the text changes
    tmpField->setUpdateValue(&Scene::getSelectedScaleY); //Select the getSelectedScaleY function to get the value of the selected object's scale Y
    addInputField(*tmpField);

    //Velocity label
    tmp->setString("Velocity: ");
    tmp->setPosition(position.x + 10, tmp->getPosition().y + tmp->getCharacterSize() + 10);
    addText(*tmp);

    //Velocity X input field
    tmp->setString("X: ");
    tmp->setPosition(position.x + 10, tmp->getPosition().y + tmp->getCharacterSize() + 10);
    tmpField->setPosition(Vector2f(position.x + 10 + tmp->getLocalBounds().getSize().x, tmp->getPosition().y));
    addText(*tmp);
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedVelocityX); //Select the modifySelectedVelocityX function to be called when the text changes
    tmpField->setUpdateValue(&Scene::getSelectedVelocityX); //Select the getSelectedVelocityX function to get the value of the selected object's velocity X
    addInputField(*tmpField);

    //Velocity Y input field
    tmp->setString("Y: ");
    tmp->setPosition(position.x + 10, tmp->getPosition().y + tmp->getCharacterSize() + 10);
    tmpField->setPosition(Vector2f(position.x + 10 + tmp->getLocalBounds().getSize().x, tmp->getPosition().y));
    addText(*tmp);
    tmpField->setOnlyNumbers(true);
    tmpField->setOnChange(&Scene::modifySelectedVelocityY); //Select the modifySelectedVelocityY function to be called when the text changes
    tmpField->setUpdateValue(&Scene::getSelectedVelocityY); //Select the getSelectedVelocityY function to get the value of the selected object's velocity Y
    addInputField(*tmpField);*/

    //Delete button
    Button* deleteButton = new Button(font, Vector2f(position.x + 10, position.y + size.y - 40), Vector2f(size.x - 20, 30), "Delete Object");
    deleteButton->setOnClick(deleteObj); //Select the deleteObj function to be called when the button is clicked
    addButton(*deleteButton); 
    delete deleteButton;

    //Change isMoveable button
    Button* changeIsMoveableButton = new Button(font, Vector2f(position.x + 10, position.y + size.y - 80), Vector2f(size.x - 20, 30), "Change Moveable");
    changeIsMoveableButton->setOnClick(changeSelectedIsMovable); //Select the changeSelectedIsMovable function to be called when the button is clicked
    changeIsMoveableButton->setToggle(true); //Set the button to be a toggle button
    addButton(*changeIsMoveableButton);
    delete changeIsMoveableButton;

    //delete tmp;
    //delete tmpField;
}
void InspectorWindow::makeCustomFields() { //make custom fields function (used to add custom fields to the inspector window)
    deleteFields();
    colors.clear();
    texts.clear();
    makeDefaultFields();
    if (Game::getCurrentScene()->getSelectedObjectIndex() != -1) {
		const GameObject* selectedObject = Game::getCurrentScene()->getObjectByIndex(Game::getCurrentScene()->getSelectedObjectIndex());
        InputField* tmp = NULL;
        int cnt = 10;
        for (int i = 0; i < selectedObject->getScriptsCount(); i++) {
            for (int j = 0; j < selectedObject->getAttributeCountFromScripts(i); j++) {
				tmp = new InputField(*Game::getFont(), Vector2f(position.x + 10, position.y + title.getCharacterSize() + 10), Vector2f(100, 20), "0");
                tmp->setPosition(Vector2f(position.x + 10, position.y + title.getCharacterSize() + 170 + 30 * cnt));
                tmp->setOnChange(&Scene::modifySelectedCustom);
                tmp->setUpdateValue(&Scene::getSelectedCustom);
                tmp->setCallIndex(cnt);
                addInputField(*tmp);
                cnt++;
			}
		}
        if(tmp)
            delete tmp;
	}
}
void InspectorWindow::update() { //update function
	EditorWindow::update();
    if (Game::getCurrentScene()->getSelectedObjectIndex() != -1) {
        for (int i = 0; i < colors.size(); i++) {
            colors[i].update();
        }
    }
}
void InspectorWindow::handleEvent(Event& event) { //handle event function
	EditorWindow::handleEvent(event);
    if (isActive) {
        for(int i=0; i<colors.size(); i++)
			colors[i].handleEvent(event);
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
			Vector2f mousePos = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
            if (window.getGlobalBounds().contains(mousePos)) {
                for (int i = 0; i < inputFields.size(); i++) {
                    inputFields[i].checkMouseClick();
                }
			}
		}
	}
}
void InspectorWindow::draw(RenderWindow& window) const { //draw function
    if (!isActive)
        return;
    if (Game::getCurrentScene()->getSelectedObjectIndex() != -1) { //If an object is selected, draw the inspector window
        EditorWindow::draw(window);
        for (int i = 0; i < colors.size(); i++) {
			colors[i].draw(window);
		}
    }
    else {
        window.draw(this->window);
        window.draw(title);
    }
}
void InspectorWindow::mouseOver() { //mouse over function (used to check if the mouse is over the inspector window and to check the input fields)
    
}

void createObj() { //Create object function (it is called when the create object button is clicked)
    GameObject* ob = new GameObject();
    makeObj(*ob, Vector2f(100, 100), 100.f);
    Game::getCurrentScene()->addObject(ob);
    delete ob;
}

void deleteObj() { //Delete object function (it is called when the delete object button is clicked)
    Game::getHierarchy()->deleteText(Game::getCurrentScene()->getSelectedObjectIndex());
    Game::getCurrentScene()->removeSelectedObject();
}


class Bullet : public GameObject { //Bullet class (derived from GameObject)
private:
    int parentId;
    float damage;
	float speed;
	float size;
    float lifeTime;

    istream& pRead(istream& in) override;
    ostream& pWrite(ostream& out) const override;
public:
    Bullet(const Vector2f& position, const Vector2f& velocity, int parentId, float damage, float speed, float size, float lifeTime);
    Bullet(const Bullet& bullet);
    GameObject* clone() const override;
	void updateScripts() override;
    void triggerScripts(GameObject& trigger) override;

    istream& read(istream& in) override;
    ostream& write(ostream& out) const override;
};


class Shootable : virtual public GameObject { //Shootable class (derived from GameObject and virtual because it is used for diamond inheritance)
protected:
    float damage;
    float fireRate;
    float nextFire;
    float bulletSpeed;
    float bulletSize;

    void shoot();

    istream& pRead(istream& in) override;
    ostream& pWrite(ostream& out) const override;
public:
    Shootable();
    Shootable(const Shootable& shootable);
    Shootable& operator=(const Shootable& shootable);
    GameObject* clone() const override;

    void updateScripts() override;

    void setDamage(float damage);
    float getDamage() const;

    void setFireRate(float fireRate);
    float getFireRate() const;

    void setNextFire(float nextFire);
    float getNextFire() const;

    void setBulletSpeed(float bulletSpeed);
    float getBulletSpeed() const;

    void setBulletSize(float bulletSize);
    float getBulletSize() const;

    istream& read(istream& in) override;
    ostream& write(ostream& out) const override;

    ~Shootable() override;
};

void Shootable::shoot() { //Shoot function (used to shoot bullets)
    if (GameTime::getInstance()->getTime() > nextFire) {
        Vector2f direction = Vector2f(cos(getRotation() * 3.14159265f / 180.f), sin(getRotation() * 3.14159265f / 180.f));
		Vector2f position = getPosition() + direction * getGlobalBounds().getSize().x / 2.f;
		Vector2f velocity = direction * bulletSpeed;
		Bullet* bullet = new Bullet(position, velocity, id, damage, bulletSpeed, bulletSize, .5f);
        bullet->setName(("Bullet" + to_string(id)));
		Game::getCurrentScene()->addObject(bullet);
		nextFire = GameTime::getInstance()->getTime() + fireRate;
        delete bullet;
	}
}
istream& Shootable::pRead(istream& in) { //private read function (used to read the shootable class's variables)
	in >> damage >> fireRate >> bulletSpeed >> bulletSize;
	return in;
}
ostream& Shootable::pWrite(ostream& out) const { //private write function (used to write the shootable class's variables)
	out << damage << " " << fireRate << " " << bulletSpeed << " " << bulletSize << endl;
	return out;
}

Shootable::Shootable() { //constructor
	damage = 10.f;
	fireRate = 0.5f;
	nextFire = 0.f;
	bulletSpeed = 500.f;
	bulletSize = 10.f;
}
Shootable::Shootable(const Shootable& shootable) : GameObject(shootable) { //copy constructor
	damage = shootable.damage;
	fireRate = shootable.fireRate;
	nextFire = shootable.nextFire;
	bulletSpeed = shootable.bulletSpeed;
	bulletSize = shootable.bulletSize;
}
Shootable& Shootable::operator=(const Shootable& shootable) { //assignment operator
    if(this == &shootable)
        return *this;
    GameObject::operator=(shootable);
	damage = shootable.damage;
	fireRate = shootable.fireRate;
	nextFire = shootable.nextFire;
	bulletSpeed = shootable.bulletSpeed;
	bulletSize = shootable.bulletSize;
	return *this;
}
GameObject* Shootable::clone() const { //clone function
	return new Shootable(*this);
}
void Shootable::updateScripts() { //update scripts function (used to shoot bullets)
	shoot();
    GameObject::updateScripts();
}
void Shootable::setDamage(float damage) { //set the damage of the shootable object
	this->damage = damage;
}
float Shootable::getDamage() const { //get the damage of the shootable object
	return damage;
}
void Shootable::setFireRate(float fireRate) { //set the fire rate of the shootable object
	this->fireRate = fireRate;
}
float Shootable::getFireRate() const { //get the fire rate of the shootable object
	return fireRate;
}
void Shootable::setNextFire(float nextFire) { //set the next fire time of the shootable object
	this->nextFire = nextFire;
}
float Shootable::getNextFire() const { //get the next fire time of the shootable object
	return nextFire;
}
void Shootable::setBulletSpeed(float bulletSpeed) { //set the bullet speed of the shootable object
	this->bulletSpeed = bulletSpeed;
}
float Shootable::getBulletSpeed() const { //get the bullet speed of the shootable object
	return bulletSpeed;
}
void Shootable::setBulletSize(float bulletSize) { //set the bullet size of the shootable object
	this->bulletSize = bulletSize;
}
float Shootable::getBulletSize() const { //get the bullet size of the shootable object
	return bulletSize;
}
istream& Shootable::read(istream& in) { //read function (also reads the GameObject class's variables)
	GameObject::pRead(in);
    Shootable::pRead(in);
	return in;
}
ostream& Shootable::write(ostream& out) const { //write function (also writes the GameObject class's variables)
    out<<"Shootable"<<endl;
	GameObject::pWrite(out);
    Shootable::pWrite(out);
	return out;
}
Shootable::~Shootable() {} //destructor



class Hitable : virtual public GameObject { //Hitable class (derived from GameObject and virtual because it is used for diamond inheritance)
protected:
    float health;
	float maxHealth;
	float invincibilityTime;
	float nextHit;
	bool isInvincible;
	void hit(float damage);

	istream& pRead(istream& in) override;
	ostream& pWrite(ostream& out) const override;
public:
    Hitable();
	Hitable(const Hitable& hitable);
	Hitable& operator=(const Hitable& hitable);
    GameObject* clone() const override;

	void updateScripts() override;

    void damage(float damage);

    istream& read(istream& in) override;
    ostream& write(ostream& out) const override;

	~Hitable() override;
};
istream& Hitable::pRead(istream& in) { //private read function (used to read the hitable class's variables)
	in >> health >> maxHealth >> invincibilityTime >> nextHit >> isInvincible;
	return in;
}
ostream& Hitable::pWrite(ostream& out) const { //private write function (used to write the hitable class's variables)
	out << health << " " << maxHealth << " " << invincibilityTime << " " << nextHit << " " << isInvincible << endl;
	return out;
}

void Hitable::hit(float damage) { //hit function (used to damage the hitable object)
	health -= damage;
    Color color = getFillColor();
    color.a = (health / maxHealth) * 255;
    setFillColor(color);
    if (health <= 0) {
		Game::getCurrentScene()->removeObjectById(id);
	}
}
Hitable::Hitable() { //constructor
	health = 100.f;
	maxHealth = 100.f;
	invincibilityTime = 1.f;
	nextHit = 0.f;
	isInvincible = false;
}
Hitable::Hitable(const Hitable& hitable) : GameObject(hitable) { //copy constructor
	health = hitable.health;
	maxHealth = hitable.maxHealth;
	invincibilityTime = hitable.invincibilityTime;
	nextHit = hitable.nextHit;
	isInvincible = hitable.isInvincible;
}
Hitable& Hitable::operator=(const Hitable& hitable) { //assignment operator
    if(this == &hitable)
		return *this;
	GameObject::operator=(hitable);
	health = hitable.health;
	maxHealth = hitable.maxHealth;
	invincibilityTime = hitable.invincibilityTime;
	nextHit = hitable.nextHit;
	isInvincible = hitable.isInvincible;
	return *this;
}
GameObject* Hitable::clone() const { //clone function
	return new Hitable(*this);
}
void Hitable::updateScripts() { //update scripts function (used to make the hitable object invincible for a certain amount of time after being hit)
    if (isInvincible) {
        if (GameTime::getInstance()->getTime() > nextHit) {
			isInvincible = false;
		}
	}
	GameObject::updateScripts();
}
void Hitable::damage(float damage) { //damage function (used to damage the hitable object)
    if (!isInvincible) {
		hit(damage);
		isInvincible = true;
		nextHit = GameTime::getInstance()->getTime() + invincibilityTime;
	}
}
istream& Hitable::read(istream& in) { //read function (also reads the GameObject class's variables)
	GameObject::pRead(in);
    Hitable::pRead(in);
	return in;
}
ostream& Hitable::write(ostream& out) const { //write function (also writes the GameObject class's variables)
    out<<"Hitable"<<endl;
	GameObject::pWrite(out);
    Hitable::pWrite(out);
	return out;
}
Hitable::~Hitable() {} //destructor


istream& Bullet::pRead(istream& in) { //private read function (used to read the bullet class's variables)
	in >> parentId >> damage >> speed >> size >> lifeTime;
	return in;
}
ostream& Bullet::pWrite(ostream& out) const { //private write function (used to write the bullet class's variables)
	out << parentId << " " << damage << " " << speed << " " << size << " " << lifeTime << endl;
	return out;
}
//Bullet constructor (used to create a bullet object)
Bullet::Bullet(const Vector2f& position, const Vector2f& velocity, int parentId, float damage, float speed, float size, float lifeTime) {
    this->damage = damage;
    this->speed = speed;
    this->size = size;
    this->lifeTime = lifeTime;
    this->parentId = parentId;

    colliderIsTrigger = true;

    CircleShape tmp(size / 2.f);
    setColliderShape(&tmp, true);

    setPointCount(tmp.getPointCount());
    for (int i = 0; i < tmp.getPointCount(); i++) {
        setPoint(i, tmp.getPoint(i));
    }

    setOrigin(getGlobalBounds().getSize() / 2.f);
    setPosition(position);

    setFillColor(Color::Red);
    setVelocity(velocity);
}
Bullet::Bullet(const Bullet& bullet) : GameObject(bullet) { //copy constructor
    damage = bullet.damage;
    speed = bullet.speed;
    size = bullet.size;
    lifeTime = bullet.lifeTime;
    parentId = bullet.parentId;
}
GameObject* Bullet::clone() const { //clone function
    return new Bullet(*this);
}
void Bullet::updateScripts() { //update scripts function (used to move the bullet and remove it after a certain amount of time)
    move(getVelocity() * GameTime::getInstance()->getDeltaTime());
    lifeTime -= GameTime::getInstance()->getDeltaTime();
    if (lifeTime <= 0) {
        Game::getCurrentScene()->removeObjectById(id);
    }
}
void Bullet::triggerScripts(GameObject& trigger) { //trigger scripts function (used to damage the object the bullet hits and remove the bullet)
    if (trigger.getId() != parentId) {
        if (Game::getCurrentScene()->sceneHasObject(trigger.getId())) {
            Hitable* hitable = dynamic_cast<Hitable*>(&trigger);
            if (hitable)
                hitable->damage(damage);
        }
        Game::getCurrentScene()->removeObjectById(id);
    }
}
istream& Bullet::read(istream& in) { //read function (also reads the GameObject class's variables)
	GameObject::pRead(in);
    Bullet::pRead(in);
	return in;
}
ostream& Bullet::write(ostream& out) const { //write function (also writes the GameObject class's variables)
    out<<"Bullet"<<endl;
	GameObject::pWrite(out);
    Bullet::pWrite(out);
	return out;
}


class Controlable : virtual public GameObject { //Controlable class (derived from GameObject and virtual because it is used for diamond inheritance)
protected:
    float speed;
    float rotationSpeed;
    Keyboard::Key upKey;
    Keyboard::Key downKey;
    Keyboard::Key leftKey;
    Keyboard::Key rightKey;

    istream& pRead(istream& in) override;
    ostream& pWrite(ostream& out) const override;
public:
    Controlable();
	Controlable(const Controlable& controlable);
	Controlable& operator=(const Controlable& controlable);
    GameObject* clone() const override;

	void updateScripts() override;

	void setSpeed(float speed);
	float getSpeed() const;

	void setRotationSpeed(float rotationSpeed);
	float getRotationSpeed() const;

	void setUpKey(Keyboard::Key upKey);
	Keyboard::Key getUpKey() const;

	void setDownKey(Keyboard::Key downKey);
	Keyboard::Key getDownKey() const;

	void setLeftKey(Keyboard::Key leftKey);
	Keyboard::Key getLeftKey() const;

	void setRightKey(Keyboard::Key rightKey);
	Keyboard::Key getRightKey() const;

    istream& read(istream& in) override;
    ostream& write(ostream& out) const override;

	~Controlable() override;
};
istream& Controlable::pRead(istream& in) { //private read function (used to read the controlable class's variables)
    string up, down, left, right;
    in >> speed >> rotationSpeed >> up >> down >> left >> right;
    upKey = stringToKey(up);
    downKey = stringToKey(down);
    leftKey = stringToKey(left);
    rightKey = stringToKey(right);
	return in;
}
ostream& Controlable::pWrite(ostream& out) const { //private write function (used to write the controlable class's variables)
    out << speed << " " << rotationSpeed << " " << keyToString(upKey) << " " << keyToString(downKey) << " " << keyToString(leftKey) << " " << keyToString(rightKey) << endl;
	return out;
}

Controlable::Controlable() { //constructor
	speed = 300.f;
	rotationSpeed = 200.f;
	upKey = Keyboard::W;
	downKey = Keyboard::S;
	leftKey = Keyboard::A;
	rightKey = Keyboard::D;
}
Controlable::Controlable(const Controlable& controlable) : GameObject(controlable) { //copy constructor
	speed = controlable.speed;
	rotationSpeed = controlable.rotationSpeed;
	upKey = controlable.upKey;
	downKey = controlable.downKey;
	leftKey = controlable.leftKey;
	rightKey = controlable.rightKey;
}
Controlable& Controlable::operator=(const Controlable& controlable) { //assignment operator
    if(this == &controlable)
        return *this;
	GameObject::operator=(controlable);
	speed = controlable.speed;
	rotationSpeed = controlable.rotationSpeed;
	upKey = controlable.upKey;
	downKey = controlable.downKey;
	leftKey = controlable.leftKey;
	rightKey = controlable.rightKey;
	return *this;
}
GameObject* Controlable::clone() const { //clone function
	return new Controlable(*this);
}
void Controlable::updateScripts() { //update scripts function (used to move and rotate the controlable object)
    if (Keyboard::isKeyPressed(upKey)) {
		move(Vector2f(cos(getRotation() * 3.14159265f / 180.f), sin(getRotation() * 3.14159265f / 180.f)) * speed * GameTime::getInstance()->getDeltaTime());
	}
    if (Keyboard::isKeyPressed(downKey)) {
		move(Vector2f(-cos(getRotation() * 3.14159265f / 180.f), -sin(getRotation() * 3.14159265f / 180.f)) * speed * GameTime::getInstance()->getDeltaTime());
	}
    if (Keyboard::isKeyPressed(leftKey)) {
		rotate(-rotationSpeed * GameTime::getInstance()->getDeltaTime());
	}
    if (Keyboard::isKeyPressed(rightKey)) {
		rotate(rotationSpeed * GameTime::getInstance()->getDeltaTime());
	}
	GameObject::updateScripts();
}
void Controlable::setSpeed(float speed) { //set the speed of the controlable object
	this->speed = speed;
}
float Controlable::getSpeed() const { //get the speed of the controlable object
	return speed;
}
void Controlable::setRotationSpeed(float rotationSpeed) { //set the rotation speed of the controlable object
	this->rotationSpeed = rotationSpeed;
}
float Controlable::getRotationSpeed() const { //get the rotation speed of the controlable object
	return rotationSpeed;
}
void Controlable::setUpKey(Keyboard::Key upKey) { //set the up key of the controlable object
	this->upKey = upKey;
}
Keyboard::Key Controlable::getUpKey() const { //get the up key of the controlable object
	return upKey;
}
void Controlable::setDownKey(Keyboard::Key downKey) { //set the down key of the controlable object
	this->downKey = downKey;
}
Keyboard::Key Controlable::getDownKey() const { //get the down key of the controlable object
	return downKey;
}
void Controlable::setLeftKey(Keyboard::Key leftKey) { //set the left key of the controlable object
	this->leftKey = leftKey;
}
Keyboard::Key Controlable::getLeftKey() const { //get the left key of the controlable object
	return leftKey;
}
void Controlable::setRightKey(Keyboard::Key rightKey) { //set the right key of the controlable object
	this->rightKey = rightKey;
}
Keyboard::Key Controlable::getRightKey() const { //get the right key of the controlable object
	return rightKey;
}
istream& Controlable::read(istream& in) { //read function (also reads the GameObject class's variables)
	GameObject::pRead(in);
    Controlable::pRead(in);
	return in;
}
ostream& Controlable::write(ostream& out) const { //write function (also writes the GameObject class's variables)
    out<<"Controlable"<<endl;
	GameObject::pWrite(out);
    Controlable::pWrite(out);
    return out;
}
Controlable::~Controlable() {} //destructor


class Player : public Shootable, public Controlable, public Hitable { //Player class (derived from Shootable, Controlable, and Hitable), the "tip" of the diamond inheritance
private:
    Keyboard::Key shootKey;

    istream& pRead(istream& in) override;
    ostream& pWrite(ostream& out) const override;
public:
    Player();
	Player(const Player& player);
	Player& operator=(const Player& player);
    GameObject* clone() const override;

	void updateScripts() override;

	void setShootKey(Keyboard::Key shoot);
	Keyboard::Key getShootKey() const;

    istream& read(istream& in) override;
    ostream& write(ostream& out) const override;

	~Player() override;
};
istream& Player::pRead(istream& in) { //private read function (used to read the player class's variables)
	string shoot;
	in >> shoot;
	shootKey = stringToKey(shoot);
	return in;
}
ostream& Player::pWrite(ostream& out) const { //private write function (used to write the player class's variables)
	out << keyToString(shootKey) << endl;
	return out;
}

Player::Player() { //constructor
	shootKey = Keyboard::Space;
}
Player::Player(const Player& player) : GameObject(player), Shootable(player), Controlable(player), Hitable(player) { //copy constructor
	shootKey = player.shootKey;
}
Player& Player::operator=(const Player& player) { //assignment operator
    if(this == &player)
		return *this;
	GameObject::operator=(player);
	Shootable::operator=(player);
	Controlable::operator=(player);
	Hitable::operator=(player);
	shootKey = player.shootKey;
	return *this;
}
GameObject* Player::clone() const { //clone function
	return new Player(*this);
}
void Player::updateScripts() { //update scripts function (used to shoot bullets and make the player invincible for a certain amount of time after being hit)
    if (Keyboard::isKeyPressed(shootKey)) {
		shoot();
	}
    if (isInvincible) {
        if (GameTime::getInstance()->getTime() > nextHit) {
            isInvincible = false;
        }
    }
	Controlable::updateScripts();
}
void Player::setShootKey(Keyboard::Key shootKey) { //set the shoot key of the player object
    this->shootKey = shootKey;
}
Keyboard::Key Player::getShootKey() const { //get the shoot key of the player object
	return shootKey;
}
istream& Player::read(istream& in) { //read function (also reads the GameObject, Shootable, Controlable, and Hitable class's variables)
	GameObject::pRead(in);
	Shootable::pRead(in);
	Controlable::pRead(in);
	Hitable::pRead(in);
    pRead(in);
	return in;
}
ostream& Player::write(ostream& out) const { //write function (also writes the GameObject, Shootable, Controlable, and Hitable class's variables)
    out<<"Player"<<endl;
	GameObject::pWrite(out);
	Shootable::pWrite(out);
	Controlable::pWrite(out);
	Hitable::pWrite(out);
    pWrite(out);
	return out;
}
Player::~Player() {} //destructor


void addTextToHierarchy(const string& text) { //Add text to hierarchy function
	Text* tmp = new Text(text, *Game::getFont(), 15);
	Game::getHierarchy()->addText(*tmp);
	delete tmp;
}

void removeTextFromHierarchy(int index) { //Remove text from hierarchy function
    if (index < Game::getHierarchy()->getTextCount() && index >= 0)
        Game::getHierarchy()->deleteText(index);
}


GameObject* makeObjFromString(const string& obj) { //Make object from string function (used to know which variant of GameObject to create when reading a scene from a file)
    if (obj == "Hitable") {
		Hitable* tmp = new Hitable();
		return tmp;
	}
    else if (obj == "Shootable") {
		Shootable* tmp = new Shootable();
		return tmp;
	}
    else if (obj == "Controlable") {
		Controlable* tmp = new Controlable();
		return tmp;
	}
    else if (obj == "Player") {
		Player* tmp = new Player();
		return tmp;
	}
    else if (obj == "Bullet") {
		Bullet* tmp = new Bullet(Vector2f(0, 0), Vector2f(0, 0), 0, 0, 0, 0, 0);
		return tmp;
	}
	return new GameObject();
}


class Gizmo {
private:
    RectangleShape selectionBox;
    bool dragging;
    Vector2f dragStart;
    void reposition();
public:
    Gizmo();
    void draw(RenderWindow& window) const;
    void update();
};
void Gizmo::reposition() { //reposition function
    if (Game::getCurrentScene()->getSelectedObjectIndex() != -1) {
		int index = Game::getCurrentScene()->getSelectedObjectIndex();
		const GameObject* selectedObject = Game::getCurrentScene()->getObjectByIndex(index);
		selectionBox.setSize(selectedObject->getGlobalBounds().getSize());
		selectionBox.setPosition(selectedObject->getPosition());
		selectionBox.setOrigin(selectedObject->getGlobalBounds().getSize() / 2.f);
	}
}
Gizmo::Gizmo() {
	selectionBox.setSize(Vector2f(0, 0));
	selectionBox.setFillColor(Color(0, 0, 0, 0));
	selectionBox.setOutlineColor(Color::White);
	selectionBox.setOutlineThickness(2);

    dragging = false;
    dragStart = Vector2f(0, 0);
}
void Gizmo::draw(RenderWindow& window) const { //draw function
    if (Game::getCurrentScene()->getSelectedObjectIndex() != -1) 
        window.draw(selectionBox);
}
void Gizmo::update() { //update function
    if (Mouse::isButtonPressed(Mouse::Left) && Game::getCurrentScene()->getSelectedObjectIndex() != -1) {
        Vector2f mousePos = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
        if (dragging) {
            //Move the selected object
            Vector2f dragEnd = mousePos;
            Vector2f drag = dragEnd - dragStart;
            Game::getCurrentScene()->moveSelectedObject(drag);
            dragStart = dragEnd;

            //Move the selection box
            selectionBox.move(drag);
        }
        //If we are not dragging, check if the cursor is over the selected object and if it is start dragging
        else if (Game::getCurrentScene()->getObjectByIndex(Game::getCurrentScene()->getSelectedObjectIndex())->getGlobalBounds().contains(mousePos)) {
            dragging = true;
            dragStart = mousePos;
		}
    }
    else
        dragging = false;
    if(Game::getCurrentScene()->getSelectedObjectIndex() != -1)
		reposition();
}





int main()
{
    //Setup
    RenderWindow window(VideoMode(1280, 720), "PO Game Engine");
    Game::setWindow(&window);
    Font font;
    font.loadFromFile("Resources/Roboto-Black.ttf");
    Game::setFont(&font);
    //window.setFramerateLimit(60);
    Scene scene;
    Game::setCurrentScene(&scene);
    HierarchyWindow hierarchyWindow(font, Vector2f(0, 0), Vector2f(window.getSize().x * 0.25f, window.getSize().y), "Hierarchy");
    InspectorWindow inspectorWindow(font, Vector2f(window.getSize().x * 0.75f, 0), Vector2f(window.getSize().x * 0.25f, window.getSize().y), "Inspector");
    ColorPicker colorPicker(font, Vector2f(window.getSize().x * 0.25f, 0), Vector2f(window.getSize().x * 0.25f, window.getSize().y * 0.5f), "Color Picker");
    Game::setHierarchy(&hierarchyWindow);
    Game::setInspector(&inspectorWindow);
    Game::setColorPicker(&colorPicker);
    GameTime* time = GameTime::getInstance();

    bool save = false;
    bool load = false;


    float nextSpace = 0;

    GameObject ob;
    ob.setName("Object0");
    makeObj(ob, Vector2f(100, 100), 100.f);

    BehaviourScript* script = new TestScript(Color::Magenta, Color::Cyan);
    ob.addScript(script);
    delete script;

    script = new FollowMouseScript(true);
    ob.addScript(script);
    delete script;

    scene.addObject(&ob);


    GameObject ob2;
    ob2.setFillColor(Color::Green);
    ob2.setName("Object1");
    ob2.setPosition(Vector2f(300, 300));
    ob2.setRotation(45);
    scene.addObject(&ob2);

    /*Player ob3;
    ob3.setName("Player1");
    ob3.setPosition(Vector2f(500, 500));
    ob3.setFillColor(Color::Blue);
    scene.addObject(&ob3);


    Player ob4;
    ob4.setFillColor(Color::Yellow);
    ob4.setName("Player2");
    ob4.setPosition(Vector2f(700, 700));
    ob4.setDownKey(Keyboard::Down);
    ob4.setLeftKey(Keyboard::Left);
    ob4.setRightKey(Keyboard::Right);
    ob4.setUpKey(Keyboard::Up);
    ob4.setShootKey(Keyboard::RControl);
    scene.addObject(&ob4);*/
    if (load) {
        ifstream in("Resources/Scene.txt"); //Read scene
        in >> scene;
        in.close();
    }


    Text fpsCounter("FPS: ", font, 15);
    fpsCounter.setFillColor(Color::White);
    fpsCounter.setPosition(10, 10);

    if(Game::getIsPlaying())
        scene.startScene();

    Gizmo moveGizmo;



    while (window.isOpen()) //Game loop
    {
        //Calculate time and delta time
        time->update();
        EditorWindow::setClickedUI(false);
        //cout<<ob2.getPosition().x<<" "<<ob2.getPosition().y<<endl;

        //Event handling
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (Game::getDrawEditor()) {
                colorPicker.handleEvent(event);
                inspectorWindow.handleEvent(event);
                hierarchyWindow.handleEvent(event); //Call last


                if (scene.getSelectedObjectIndex() != -1) {
                    if (Keyboard::isKeyPressed(Keyboard::Delete)) {
                        deleteObj();
                    }
                }
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::F1) {
                    Game::setDrawEditor(!Game::getDrawEditor());
                }
                else if (event.key.code == Keyboard::F2)
                    colorPicker.setActive(!colorPicker.getActive());
                else if(event.key.code == Keyboard::F3)
                    Game::setIsPlaying(!Game::getIsPlaying());
			}
        }

        //Only update the fps counter 10 times per second
        if (time->getTime() > nextSpace) {
            nextSpace = time->getTime() + 0.1f;
            fpsCounter.setString("FPS: " + floatToString(1.f / time->getDeltaTime()));
        }

        //Update the editor
        if (Game::getDrawEditor()) {
            hierarchyWindow.update();
            inspectorWindow.update();
            colorPicker.update();
            moveGizmo.update();
        }


        //Select object
        if (Mouse::isButtonPressed(Mouse::Left)) {
            hierarchyWindow.mouseOver();
            inspectorWindow.mouseOver();
            colorPicker.mouseOver();
        }

        //Update the scene
        if(Game::getIsPlaying())
            scene.updateScene();

        //Clear the window
        window.clear();

        //Draw the objects
        Game::getCurrentScene()->drawScene(false, window);

        //Draw the editor
        if (Game::getDrawEditor()) {
            moveGizmo.draw(window);
            hierarchyWindow.setTitle("Hierarchy (" + to_string(scene.getObjectsCount()) + ")");
            hierarchyWindow.draw(window);
            inspectorWindow.draw(window);
            colorPicker.draw(window);
            window.draw(fpsCounter);
        }

        /*GameObject* tmp = new GameObject(*scene.getObjectByIndex(1));
        Color color = colorPicker.getSelectedColor();
        tmp->setFillColor(color);
        scene.addObject(tmp);
        scene.removeObjectByIndex(1);
        delete tmp;*/

        window.display();
    }

    //Save scene
    if (save) {
        ofstream out("Resources/Scene.txt");
        out << scene;
        out.close();
    }

    return 0;
}