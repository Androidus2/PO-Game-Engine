#pragma once
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"


class FileNode {
private:
	std::string name;
	bool isDir;
	sf::Texture* icon;
	std::vector<FileNode*> children;
	FileNode* parent;
public:
	FileNode(const std::string& name, bool isDir);
	void addChild(FileNode* child);
	int childIndex(std::string name);
	void removeChild(int index);
	FileNode* getChild(int index) const;
	int getChildCount() const;
	void setName(const std::string& name);
	std::string getName() const;
	std::string getPath() const;
	bool getIsDir() const;
	void setIcon(sf::Texture* icon);
	sf::Texture* getIcon() const;
	FileNode* getParent() const;
	void setParent(FileNode* parent);
	~FileNode();
};