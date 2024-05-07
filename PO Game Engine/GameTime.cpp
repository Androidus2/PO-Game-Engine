#include "GameTime.h"
#include <iostream>

using namespace std;
using namespace sf;


GameTime::GameTime() {
    reset();
    cout<<"Created the Singleton GameTime"<<endl;
}
void GameTime::reset() {
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
    static GameTime instance;
    return &instance;
}
GameTime::~GameTime() {
	//empty
    cout<<"Destroyed the Singleton GameTime"<<endl;
}
