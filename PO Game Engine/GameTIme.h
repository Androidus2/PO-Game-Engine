#pragma once
#include "SFML\System.hpp"
class GameTime { //for delta time and time (singleton)
private:
    sf::Clock clock;
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