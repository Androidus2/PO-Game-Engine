#include "GameTime.h"

using namespace std;
using namespace sf;


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
