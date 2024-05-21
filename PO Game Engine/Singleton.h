#pragma once
#include <iostream>
#include "DebugMacro.h"
template <class T>
class Singleton { //Singleton class
private:
	T data;
	Singleton() : data() { std::cout << "Created a singleton" << std::endl; }
	~Singleton() {
		std::cout<<"Singleton destroyed"<<std::endl;
	}
public:
	static T& getInstance() {
		static Singleton<T> instance;
		return instance.data;
	}
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
};