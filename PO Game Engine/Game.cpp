#include <fstream>
#include "Game.h"
#include "InspectorWindow.h"
#include "HierarchyWindow.h"
#include "GameTime.h"

using namespace std;
using namespace sf;


void Game::setFont(Font* font) {  //set the font
	Game::font = font;
}
Font* Game::getFont() { //get the font
	return Game::font;
}

void Game::setWindow(RenderWindow* window) { //set the window
	Game::window = window;
}
RenderWindow* Game::getWindow() { //get the window
	return Game::window;
}

void Game::setCurrentScene(Scene* scene) { //set the current scene
	Game::currentScene = scene;
}
Scene* Game::getCurrentScene() { //get the current scene
	return Game::currentScene;
}

void Game::setHierarchy(EditorWindow* hierarchy) { //set the hierarchy
	Game::hierarchy = hierarchy;
}
EditorWindow* Game::getHierarchy() { //get the hierarchy
	return Game::hierarchy;
}

void Game::setInspector(EditorWindow* inspector) { //set the inspector
	Game::inspector = inspector;
}
EditorWindow* Game::getInspector() { //get the inspector
	return Game::inspector;
}

void Game::setColorPicker(EditorWindow* colorPicker) { //set the color picker
	Game::colorPicker = colorPicker;
}
EditorWindow* Game::getColorPicker() { //get the color picker
	return Game::colorPicker;
}

void Game::setGameFilesWindow(EditorWindow* gameFilesWindow) { //set the game files window
	Game::gameFilesWindow = gameFilesWindow;
}
EditorWindow* Game::getGameFilesWindow() { //get the game files window
	return Game::gameFilesWindow;
}

View* Game::getSceneView() { //get the scene view
	return sceneView;
}
void Game::setSceneView(View* view) { //set the scene view
	sceneView = view;
}

View* Game::getGuiView() { //get the gui view
	return guiView;
}
void Game::setGuiView(View* view) { //set the gui view
	guiView = view;
}

View* Game::getGameView() { //get the game view
	return gameView;
}
void Game::setGameView(View* view) { //set the game view
	gameView = view;
}

bool Game::getIsOverGameWindow() { //get if the mouse is over the game window
	return isOverGameWindow;
}
void Game::setIsOverGameWindow(bool isOverGameWindow) { //set if the mouse is over the game window
	Game::isOverGameWindow = isOverGameWindow;
}

bool Game::getIsPlaying() { //get if the game is playing
	return isPlaying;
}
void Game::setIsPlaying(bool isPlaying) { //set if the game is playing
	Game::isPlaying = isPlaying;
	GameTime::getInstance()->reset();
	if (isPlaying && currentScene) {
		isOverGameWindow = true;
		currentScene->startScene();
		/*sceneViewPositionBeforePlaying = sceneView->getCenter();
		sceneViewZoomBeforePlaying = sceneView->getSize();*/
	}
	else if (!isPlaying && currentScene) {
		isOverGameWindow = false;
		currentScene->endScene();
		/*sceneView->setCenter(sceneViewPositionBeforePlaying);
		sceneView->setSize(sceneViewZoomBeforePlaying);*/
	}
}

bool Game::getDrawEditor() { //get if the editor is drawn
	return drawEditor;
}
void Game::setDrawEditor(bool drawEditor) { //set if the editor is drawn
	Game::drawEditor = drawEditor;
}

Gizmo* Game::getGizmo() { //get the gizmo
	return gizmo;
}
void Game::setGizmo(Gizmo* gizmo) { //set the gizmo
	Game::gizmo = gizmo;
}

Texture* Game::getFolderTexture() { //get the folder texture
	return folderTexture;
}
void Game::setFolderTexture(Texture* texture) { //set the folder texture
	folderTexture = texture;
}

void Game::loadScene(const string& scenePath) { //load the scene
	if (isPlaying) {
		return;
	}
	if (currentScene) {
		delete currentScene;
	}
	dynamic_cast<HierarchyWindow*>(hierarchy)->clearTexts();
	currentScene = new Scene();
	ifstream file(scenePath);
	currentScene->read(file);
	currentScene->setSelectedObjectIndex(-1);
	file.close();
	string pathWithoutFile = scenePath.substr(0, scenePath.find_last_of('/') + 1);
	currentScene->setScenePath(pathWithoutFile);
	string sceneName = scenePath.substr(scenePath.find_last_of('/') + 1);
	sceneName = sceneName.substr(0, sceneName.find_last_of('.'));
	currentScene->setName(sceneName);
}

bool Game::getBlockClick() { //get if the click is blocked
	return blockClick;
}
void Game::setBlockClick(bool blockClick) { //set if the click is blocked
	Game::blockClick = blockClick;
}

void Game::clearGame() { //clear the game
	if (currentScene) {
		delete currentScene;
	}
	if (hierarchy) {
		hierarchy = nullptr;
	}
	if (inspector) {
		inspector = nullptr;
	}
	if (colorPicker) {
		colorPicker = nullptr;
	}
	if (gameFilesWindow) {
		gameFilesWindow = nullptr;
	}
	if (gizmo) {
		gizmo = nullptr;
	}
	if (folderTexture) {
		delete folderTexture;
	}
	if (font) {
		font = nullptr;
	}
	if (sceneView) {
		sceneView = nullptr;
	}
	if (guiView) {
		guiView = nullptr;
	}
}