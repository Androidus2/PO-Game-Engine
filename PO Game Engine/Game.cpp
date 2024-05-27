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
	Singleton<GameTime>::getInstance().getData().reset();
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

void Game::loadScene(const string& scenePath) { //load the scene
	if (isPlaying) {
		return;
	}

	Scene* newScene = new Scene();
	try{
		ifstream file(scenePath);
		newScene->read(file);
		file.close();
		delete newScene;
	}
	catch (exception e) {
		cout<<"Error loading scene: "<<e.what()<<endl;
		delete newScene;
		return;
	}
	catch (...) {
		cout<<"Error loading scene"<<endl;
		delete newScene;
		return;
	}

	if (currentScene) {
		delete currentScene;
	}
	clearControlZScenes();
	dynamic_cast<HierarchyWindow*>(hierarchy)->clearTexts();
	currentScene = new Scene();

	ifstream file(scenePath); //We have a valid scene, so we can load it
	currentScene->read(file);
	file.close();

	currentScene->setSelectedObjectIndex(-1);
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

void Game::addControlZScene() { //add a scene to the control z scenes
	if (isPlaying) {
		return;
	}
	Scene* scene = new Scene(*currentScene, -500);
	scene->setSelectedObjectIndex(currentScene->getSelectedObjectIndex());
	scene->setId(currentScene->getId());
	controlZScenes.push_back(scene);
	if (controlZScenes.size() > 10) {
		controlZScenes.front()->setId(-510);
		delete controlZScenes.front();
		controlZScenes.pop_front();
	}

	//Clear control Y scenes
	clearControlYScenes();
}
void Game::addControlYScene() { //add a scene to the control y scenes
	Scene* scene = new Scene(*currentScene, -505);
	scene->setSelectedObjectIndex(currentScene->getSelectedObjectIndex());
	scene->setId(currentScene->getId());
	controlYScenes.push_back(scene);
	if (controlYScenes.size() > 10) {
		delete controlYScenes.front();
		controlYScenes.pop_front();
	}
}
void Game::clearControlZScenes() { //clear the control z scenes
	for (Scene* scene : controlZScenes) {
		if (scene != NULL && scene != currentScene) {
			scene->setId(-511);
			delete scene;
		}
	}
	controlZScenes.clear();
	clearControlYScenes();
}
void Game::clearControlYScenes() { //clear the control y scenes
	for (Scene* scene : controlYScenes) {
		if (scene != NULL && scene != currentScene) {
			scene->setId(-510);
			delete scene;
		}
	}
	controlYScenes.clear();
}
Scene* Game::getControlZScene() { //get the control z scene
	if (controlZScenes.empty()) {
		return NULL;
	}
	Scene* scene = controlZScenes.back();
	controlZScenes.pop_back();
	return scene;
}
void Game::undo() {
	if (isPlaying) {
		return;
	}
	if (controlZScenes.empty()) {
		return;
	}
	Scene* scene = getControlZScene();
	if (scene) {
		addControlYScene();
		dynamic_cast<HierarchyWindow*>(hierarchy)->clearTexts();
		*currentScene = *scene;
		int slctd = scene->getSelectedObjectIndex();
		scene->setId(-501);
		delete scene;
		scene = NULL;
		dynamic_cast<HierarchyWindow*>(hierarchy)->changeSelectedObject(slctd);
	}
}

void Game::redo() {
	if (isPlaying) {
		return;
	}
	if (controlYScenes.empty()) {
		return;
	}
	Scene* scene = controlYScenes.back();
	controlYScenes.pop_back();
	if (scene) {
		Scene* scene2 = new Scene(*currentScene, -500);
		scene2->setSelectedObjectIndex(currentScene->getSelectedObjectIndex());
		scene2->setId(currentScene->getId());
		controlZScenes.push_back(scene2);
		if (controlZScenes.size() > 10) {
			delete controlZScenes.front();
			controlZScenes.pop_front();
		}
		//addControlZScene();
		dynamic_cast<HierarchyWindow*>(hierarchy)->clearTexts();
		*currentScene = *scene;
		int slctd = scene->getSelectedObjectIndex();
		scene->setId(-502);
		delete scene;
		scene = NULL;
		dynamic_cast<HierarchyWindow*>(hierarchy)->changeSelectedObject(slctd);
	}
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
	if (font) {
		font = nullptr;
	}
	if (sceneView) {
		sceneView = nullptr;
	}
	if (guiView) {
		guiView = nullptr;
	}
	if (controlZScenes.size() > 0) {
		clearControlZScenes();
	}
	if (controlYScenes.size() > 0) {
		clearControlYScenes();
	}
}