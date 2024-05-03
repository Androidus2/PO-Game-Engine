#pragma once
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "EditorWindow.h"
#include "FileNode.h"



class GameFilesWindow : public EditorWindow { //Game files window class (derived from EditorWindow)
private:
    FileNode* root;
    std::string currentDirectory;
    std::vector<sf::RectangleShape> icons;

    float lastClickTime;
    int selectedFile;

    sf::RectangleShape selectedBackground;
    void loadFiles();
    void makeTree(FileNode* node);
    sf::Texture* makeTexture(const std::string& path);
public:
    GameFilesWindow(const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size, const std::string& title);
    void handleEvent(sf::Event& event) override;
    void draw(sf::RenderWindow& window) const override;
    std::string getCurrentDirectory() const;
    void setCurrentDirectory(const std::string& directory);
    void mouseOver() override {};
    void makeDir();
    sf::Texture* getTextureFromPath(const std::string& path);
};