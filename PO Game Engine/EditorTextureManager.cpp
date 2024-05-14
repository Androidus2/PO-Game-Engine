#include "EditorTextureManager.h"

using namespace std;
using namespace sf;

EditorTextureManager::EditorTextureManager() { //Constructor
	textures = map<string, Texture*>();
	cout<<"EditorTextureManager created"<<endl;
}

void EditorTextureManager::addTexture(const string& name, Texture* texture) { //Add texture
	textures[name] = texture;
}
void EditorTextureManager::loadTexture(const string& name, const string& path) { //Load texture
	Texture* texture = new Texture();
	if (!texture->loadFromFile(path)) {
		cout<<"Error loading texture: "<<name<<" from path "<<path << endl;
		delete texture;
		return;
	}
	addTexture(name, texture);
}
Texture* EditorTextureManager::getTexture(const string& name) { //Get texture
	if (textures.find(name) == textures.end())
		return NULL;
	return textures[name];
}
void EditorTextureManager::removeTexture(const string& name) { //Remove texture
	if (textures.find(name) == textures.end()) {
		return;
	}
	delete textures[name];
	textures.erase(name);
}
void EditorTextureManager::clearTextures() { //Clear textures
	for (auto& texture : textures) {
		delete texture.second;
	}
	textures.clear();
}

EditorTextureManager::~EditorTextureManager() { //Destructor
	clearTextures();
	cout<<"EditorTextureManager destroyed"<<endl;
}