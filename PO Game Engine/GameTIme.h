#pragma once
#include "SFML\System.hpp"
class GameTime { //for delta time and time (singleton)
private:
    sf::Clock clock;
    float deltaTime;
    float time;
    GameTime();
public:
    GameTime(const GameTime& gameTime) = delete;
    GameTime& operator=(const GameTime& gameTime) = delete;
    void reset();
    void update();
    float getDeltaTime() const;
    float getTime() const;
    static GameTime* getInstance();
    ~GameTime();
};