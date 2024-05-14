#pragma once
#include <iostream>
#include <map>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Singleton.h"

class EditorTextureManager { //Editor texture manager class (Singleton)
private:
	std::map<std::string, sf::Texture*> textures; //Textures map
public:
	EditorTextureManager(); //Constructor
	~EditorTextureManager(); //Destructor

	void addTexture(const std::string& name, sf::Texture* texture); //Add texture
	void loadTexture(const std::string& name, const std::string& path); //Load texture
	sf::Texture* getTexture(const std::string& name); //Get texture
	void removeTexture(const std::string& name); //Remove texture
	void clearTextures(); //Clear textures
};