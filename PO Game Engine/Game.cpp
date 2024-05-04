#include "Game.h"
#include "InspectorWindow.h"

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

bool Game::getIsPlaying() { //get if the game is playing
	return isPlaying;
}
void Game::setIsPlaying(bool isPlaying) { //set if the game is playing
	Game::isPlaying = isPlaying;
	if (isPlaying && currentScene) {
		currentScene->startScene();
		sceneViewPositionBeforePlaying = sceneView->getCenter();
		sceneViewZoomBeforePlaying = sceneView->getSize();
	}
	else if (!isPlaying && currentScene) {
		currentScene->endScene();
		sceneView->setCenter(sceneViewPositionBeforePlaying);
		sceneView->setSize(sceneViewZoomBeforePlaying);
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
