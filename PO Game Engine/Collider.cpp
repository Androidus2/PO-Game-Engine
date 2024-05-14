#include "Collider.h"

using namespace std;
using namespace sf;


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
        if(colliderShape != NULL)
            delete colliderShape;
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
    colliderShape->setFillColor(Color::Transparent);
    colliderShape->setOutlineColor(Color(16, 56, 0, 255));
    colliderShape->setOutlineThickness(2.f);
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

    colliderShape->setFillColor(Color::Transparent);
    colliderShape->setOutlineColor(Color(16, 56, 0, 255));
    colliderShape->setOutlineThickness(2.f);

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

    colliderShape->setFillColor(Color::Transparent);
    colliderShape->setOutlineColor(Color(16, 56, 0, 255));
    colliderShape->setOutlineThickness(2.f);

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

    colliderShape->setFillColor(Color::Transparent);
    colliderShape->setOutlineColor(Color(16, 56, 0, 255));
    colliderShape->setOutlineThickness(2.f);

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
        this->colliderShape = NULL;
    }
}
void Collider::fixShape(Vector2f& position, float& rotation, Vector2f& scale) { //A function used to "fix" the shape after a new one has been assigned
    this->colliderShape->setRotation(rotation);
    this->colliderShape->setScale(scale);
    this->colliderShape->setOrigin(this->colliderShape->getLocalBounds().getSize() / 2.f);
    this->colliderShape->setPosition(position);
    colliderShape->setFillColor(Color::Transparent);
    colliderShape->setOutlineColor(Color(16, 56, 0, 255));
    colliderShape->setOutlineThickness(2.f);
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