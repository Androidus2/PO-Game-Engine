#include "GameTime.h"
#include <iostream>

using namespace std;
using namespace sf;


GameTime::GameTime() {
    reset();
    cout<<"Created the GameTime"<<endl;
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
GameTime::~GameTime() {
	//empty
    cout<<"Destroyed the GameTime"<<endl;
}
