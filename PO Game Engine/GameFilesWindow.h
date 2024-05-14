#pragma once
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "EditorWindow.h"
#include "FileNode.h"
#include "Dropdown.h"



class GameFilesWindow : public EditorWindow { //Game files window class (derived from EditorWindow)
private:
    FileNode* root;
    std::string currentDirectory;
    std::vector<sf::RectangleShape> icons;

    Dropdown dropdown;

    std::string copyPath;

    std::string rename;

    float lastClickTime;
    int selectedFile;

    bool isDragging;
    sf::RectangleShape dragVisual;

    sf::RectangleShape selectedBackground;
    void makeTree(FileNode* node);
    sf::Texture* makeTexture(const std::string& path);
    void updateElementsWithVerticalOffset(float old) override;
public:
    GameFilesWindow(const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size, const std::string& title);
    void handleEvent(sf::Event& event) override;
    void update() override;
    void draw(sf::RenderWindow& window) const override;
    std::string getCurrentDirectory() const;
    void setCurrentDirectory(const std::string& directory);
    void mouseOver() override {};
    void makeDir();
    void makeScene();
    int getSelectedFile() const;
    sf::Texture* getTextureFromPath(const std::string& path);
    void copy();
    void paste();
    void renameFile(const std::string& newName);
    void loadFiles();
    ~GameFilesWindow();
};