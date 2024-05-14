#pragma once
#include "SFML\System.hpp"
#include "Singleton.h"
class GameTime { //for delta time and time (singleton)
private:
    sf::Clock clock;
    float deltaTime;
    float time;
public:
    GameTime();
    void reset();
    void update();
    float getDeltaTime() const;
    float getTime() const;
    ~GameTime();
};