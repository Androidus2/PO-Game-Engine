#pragma once
#include "SFML\Graphics.hpp"
#include "Scene.h"
#include "DebugMacro.h"



class EditorWindow;
class Gizmo;

class Game { //Game class (has static variables for the game)
private:
    static sf::Font* font;
    static sf::RenderWindow* window;
    static Scene* currentScene;
    static EditorWindow* hierarchy;
    static EditorWindow* inspector;
    static EditorWindow* colorPicker;
    static EditorWindow* gameFilesWindow;
    static sf::View* sceneView;
    static sf::View* guiView;
    static sf::View* gameView;
    static Gizmo* gizmo;
    static sf::Texture* folderTexture;
    static bool isPlaying;
    static bool drawEditor;
    static bool blockClick;

    static bool isOverGameWindow;
public:
    static void setFont(sf::Font* font);
    static sf::Font* getFont();

    static void setWindow(sf::RenderWindow* window);
    static sf::RenderWindow* getWindow();

    static void setCurrentScene(Scene* scene);
    static Scene* getCurrentScene();

    static void setHierarchy(EditorWindow* hierarchy);
    static EditorWindow* getHierarchy();

    static void setInspector(EditorWindow* inspector);
    static EditorWindow* getInspector();

    static void setColorPicker(EditorWindow* colorPicker);
    static EditorWindow* getColorPicker();

    static void setGameFilesWindow(EditorWindow* gameFilesWindow);
    static EditorWindow* getGameFilesWindow();

    static bool getIsPlaying();
    static void setIsPlaying(bool isPlaying);

    static bool getDrawEditor();
    static void setDrawEditor(bool drawEditor);

    static sf::View* getSceneView();
    static void setSceneView(sf::View* view);

    static sf::View* getGuiView();
    static void setGuiView(sf::View* view);

    static sf::View* getGameView();
    static void setGameView(sf::View* view);

    static bool getIsOverGameWindow();
    static void setIsOverGameWindow(bool isOverGameWindow);

    static Gizmo* getGizmo();
    static void setGizmo(Gizmo* gizmo);

    static sf::Texture* getFolderTexture();
    static void setFolderTexture(sf::Texture* texture);

    static void loadScene(const std::string& scenePath);

    static bool getBlockClick();
    static void setBlockClick(bool blockClick);

    static void clearGame();
};