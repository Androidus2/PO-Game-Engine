#include "FileNode.h"

using namespace std;
using namespace sf;


FileNode::FileNode(const string& name, bool isDir) { //constructor
	this->name = name;
	this->isDir = isDir;
	parent = nullptr;
	icon = nullptr;
}
void FileNode::addChild(FileNode* child) { //add child function
	children.push_back(child);
	child->setParent(this);
}
int FileNode::childIndex(string name) { //child index function
	for (int i = 0; i < children.size(); i++) {
		if (children[i]->getName() == name)
			return i;
	}
	return -1;
}
void FileNode::removeChild(int index) { //remove child function
	if (index < children.size() && index >= 0) {
		delete children[index];
		children.erase(children.begin() + index);
	}
}
FileNode* FileNode::getChild(int index) const { //get child function
	if (index < children.size() && index >= 0)
		return children[index];
	return nullptr;
}
int FileNode::getChildCount() const { //get child count function
	return children.size();
}
void FileNode::setName(const string& name) { //set name function
	this->name = name;
}
string FileNode::getPath() const { //get path function
	if (name == "\\") {
		//Return the path of the grandparent
		if (parent != nullptr && parent->getParent() != nullptr)
			return parent->getParent()->getPath();
		else
			throw exception("We have a \\ folder in the root!");
	}

	string path = "";
	const FileNode* tmp = this;
	while (tmp != nullptr) {
		path = tmp->getName() + "/" + path;
		tmp = tmp->getParent();
	}
	return path;
}
string FileNode::getName() const { //get name function
	return name;
}
bool FileNode::getIsDir() const { //get is directory function
	return isDir;
}
void FileNode::setIcon(Texture* icon) { //set icon function
	this->icon = icon;
}
Texture* FileNode::getIcon() const { //get icon function
	return icon;
}
FileNode* FileNode::getParent() const { //get parent function
	return parent;
}
void FileNode::setParent(FileNode* parent) { //set parent function
	this->parent = parent;
}
FileNode::~FileNode() { //destructor
	for (int i = 0; i < children.size(); i++) {
		delete children[i];
	}
	string extension = name.substr(name.find_last_of('.') + 1);
	if (icon != nullptr && !isDir && extension != "poscene")
		delete icon;
}
