#include "GameFilesWindow.h"
#include "Game.h"
#include "GameTime.h"
#include "InspectorWindow.h"
#include <filesystem>

using namespace std;
using namespace sf;


Texture* GameFilesWindow::makeTexture(const string& path) { //make texture function
    Image img;
    img.loadFromFile(path);
    Texture* tex = new Texture();
    tex->loadFromImage(img);
    return tex;
}
void GameFilesWindow::makeTree(FileNode* node) { //make tree function
    string path = node->getPath();
    for (const auto& entry : filesystem::directory_iterator(path)) {
        string name = entry.path().filename().string();
        //If a file exists and is not in the tree, add it
        if (name.find(".") == string::npos && node->childIndex(name) == -1) {
            FileNode* tmp = new FileNode(name, true);
            tmp->setIcon(Game::getFolderTexture());
            if (!Game::getFolderTexture())
                cout << "Folder texture not loaded" << endl;
            node->addChild(tmp);
            makeTree(tmp);
        }
        else if (node->childIndex(name) == -1 && (name.find(".png") != string::npos || name.find(".psd") != string::npos || name.find(".jpg") != string::npos)) {
            FileNode* tmp = new FileNode(name, false);
            tmp->setIcon(makeTexture(path + "/" + name));
            node->addChild(tmp);
        }
    }
    //If a file is in the tree but doesn't exist, remove it
    int n = node->getChildCount();
    for (int i = 0; i < n; i++) {
        string name = node->getChild(i)->getName();
        bool exists = false;
        for (const auto& entry : filesystem::directory_iterator(path)) {
            if (entry.path().filename().string() == name) {
                exists = true;
            }
        }
        if (!exists) {
            node->removeChild(i);
            i--;
            n--;
        }
        else if (name.find(".") == string::npos) {
            makeTree(node->getChild(i));
        }
    }
}
void GameFilesWindow::loadFiles() { //load files function
    icons.clear();
    texts.clear();
    makeTree(root);
    string path = currentDirectory;
    Image img;
    Text text;
    FileNode* node = root;
    //Get the node that represents the current directory
    if (currentDirectory != "GameFiles/") {
        //Split the path into the respective directories
        vector<string> dirs;
        string dir = "";
        for (int i = 0; i < path.size(); i++) {
            if (path[i] == '/') {
                dirs.push_back(dir);
                dir = "";
            }
            else {
                dir += path[i];
            }
        }
        while (dirs.size() > 0) {
            for (int i = 0; i < node->getChildCount(); i++) {
                if (node->getChild(i)->getName() == dirs[0]) {
                    node = node->getChild(i);
                    break;
                }
            }
            dirs.erase(dirs.begin());
        }
    }
    //Load the files in the current directory
    for (int i = 0; i < node->getChildCount(); i++) {
        icons.push_back(RectangleShape(Vector2f(100, 100)));
        icons[i].setTexture(node->getChild(i)->getIcon());
        icons[i].setOutlineColor(Color::Black);
        icons[i].setOutlineThickness(1);
        icons[i].setPosition(position.x + 10 + (i % 4) * 110, position.y + 30 + (i / 4) * 130);
        texts.push_back(Text(node->getChild(i)->getName(), *Game::getFont(), 13));
        texts[i].setPosition(position.x + 10 + (i % 4) * 110 + icons[i].getSize().x / 2 - texts[i].getGlobalBounds().width / 2, position.y + 130 + (i / 4) * 130);
    }
    int elementsPerRow = (size.x - 20) / 110;
    for (int i = 0; i < icons.size(); i++) {
        icons[i].setPosition(position.x + 10 + (i % elementsPerRow) * 110, position.y + 30 + (i / elementsPerRow) * 130);
        texts[i].setPosition(position.x + 10 + (i % elementsPerRow) * 110 + icons[i].getSize().x / 2 - texts[i].getGlobalBounds().width / 2, position.y + 130 + (i / elementsPerRow) * 130);
    }
    text = Text(currentDirectory, *Game::getFont(), 15);
    text.setPosition(position.x + 10, position.y + 5);
    texts.push_back(text);
    selectedFile = -1;
    selectedBackground.setPosition(Vector2f(-1000, -1000));
}
GameFilesWindow::GameFilesWindow(const Font& font, const Vector2f& position, const Vector2f& size, const string& title) : EditorWindow(font, position, size, title) {
    Button outButton(font, Vector2f(position.x + size.x - 30, position.y), Vector2f(30, 30), "<-");
    outButton.setOnClick([]() {
        GameFilesWindow* window = dynamic_cast<GameFilesWindow*>(Game::getGameFilesWindow());
        if (window == nullptr)
            return;
        string path = window->getCurrentDirectory();
        if (path != "GameFiles/") {
            path = path.substr(0, path.size() - 1);
            path = path.substr(0, path.find_last_of("/") + 1);
            window->setCurrentDirectory(path);
        }
        });
    buttons.push_back(outButton);

    Button newFolderButton(font, Vector2f(position.x + size.x - 60, position.y), Vector2f(30, 30), "+");
    newFolderButton.setOnClick([]() {
        GameFilesWindow* window = dynamic_cast<GameFilesWindow*>(Game::getGameFilesWindow());
        if (window == nullptr)
            return;
        window->makeDir();
        }
    );
    buttons.push_back(newFolderButton);

    currentDirectory = "GameFiles/";
    lastClickTime = 0;
    selectedFile = -1;

    selectedBackground.setSize(Vector2f(110, 130));
    selectedBackground.setFillColor(Color(22, 48, 114, 0)); //194 alpha when visible
    selectedBackground.setOutlineColor(Color::Black);
    selectedBackground.setOutlineThickness(1);

    root = new FileNode("GameFiles", true);
    //makeTree(root);

    loadFiles();
}
void GameFilesWindow::handleEvent(Event& event) { //handle event function
    if (event.type == Event::MouseButtonPressed) {
        if (event.mouseButton.button == Mouse::Left) {
            int index = -1;
            for (int i = 0; i < icons.size(); i++) {
                if (icons[i].getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    if (texts[i].getString().find(".") == string::npos) {
                        if (GameTime::getInstance()->getTime() - lastClickTime < 0.5f && selectedFile == i) {
                            currentDirectory += texts[i].getString() + "/";
                            loadFiles();
                            index = -1;
                            break;
                        }
                    }
                    index = i;
                    break;
                }
            }
            selectedFile = index;
            if (selectedFile != -1) {
                selectedBackground.setPosition(icons[selectedFile].getPosition() - Vector2f(5, 5));
                selectedBackground.setFillColor(Color(22, 48, 114, 194));
                if (texts[selectedFile].getString().find(".") != string::npos) {
                    InspectorWindow* inspector = dynamic_cast<InspectorWindow*>(Game::getInspector());
                    if(inspector)
						inspector->changeImage(currentDirectory + texts[selectedFile].getString());
                }
            }
            else {
                selectedBackground.setPosition(Vector2f(-1000, -1000));
                selectedBackground.setFillColor(Color(22, 48, 114, 0));
                if (Game::getGameFilesWindow()->isMouseOver()) {
					InspectorWindow* inspector = dynamic_cast<InspectorWindow*>(Game::getInspector());
					if(inspector)
                        inspector->changeImage("");
                }
            }
            lastClickTime = GameTime::getInstance()->getTime();
        }
    }
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Delete) {
        if (selectedFile != -1) {
            string path = currentDirectory + texts[selectedFile].getString();
            if (filesystem::is_directory(path)) {
                filesystem::remove_all(path);
            }
            else {
                filesystem::remove(path);
            }
            loadFiles();
        }
    }
    EditorWindow::handleEvent(event);
}
string GameFilesWindow::getCurrentDirectory() const { //get current directory function
    return currentDirectory;
}
void GameFilesWindow::setCurrentDirectory(const string& directory) { //set current directory function
    currentDirectory = directory;
    loadFiles();
}
void GameFilesWindow::draw(RenderWindow& window) const { //draw function
    EditorWindow::draw(window);
    for (int i = 0; i < icons.size(); i++) {
        window.draw(icons[i]);
    }
    window.draw(selectedBackground);
}
void GameFilesWindow::makeDir() { //make directory function
    string path = currentDirectory;
    string name = "New Folder";
    //Check if the folder already exists
    int i = 1;
    while (filesystem::exists(path + name)) {
        name = "New Folder (" + to_string(i) + ")";
        i++;
    }
    filesystem::create_directory(path + name);
    loadFiles();
}
Texture* GameFilesWindow::getTextureFromPath(const string& path) {
    //Go through the tree and find the node that represents the path
    FileNode* node = root;
    vector<string> dirs;
    string dir = "";
    for (int i = 0; i < path.size(); i++) {
        if (path[i] == '/') {
			dirs.push_back(dir);
			dir = "";
		}
        else {
			dir += path[i];
		}
	}
    while (dirs.size() > 0) {
        for (int i = 0; i < node->getChildCount(); i++) {
            if (node->getChild(i)->getName() == dirs[0]) {
				node = node->getChild(i);
				break;
			}
		}
		dirs.erase(dirs.begin());
	}
    for (int i = 0; i < node->getChildCount(); i++) {
        if (node->getChild(i)->getName() == dir) {
			return node->getChild(i)->getIcon();
		}
	}
	return nullptr;
}