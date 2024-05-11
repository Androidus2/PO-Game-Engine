#include "GameFilesWindow.h"
#include "Game.h"
#include "GameTime.h"
#include "InspectorWindow.h"
#include <filesystem>
#include <fstream>

using namespace std;
using namespace sf;

void GameFilesWindow::updateElementsWithVerticalOffset(float old) { //update the elements with the vertical offset
	float delta = verticalOffset - old;
	for (int i = 0; i < icons.size(); i++)
		icons[i].setPosition(icons[i].getPosition() + Vector2f(0, delta));
	for (int i = 0; i < texts.size() - 1; i++)
		texts[i].setPosition(texts[i].getPosition() + Vector2f(0, delta));
    inputFields[0].setPosition(inputFields[0].getPosition() + Vector2f(0, delta));
    selectedBackground.setPosition(selectedBackground.getPosition() + Vector2f(0, delta));
}
Texture* GameFilesWindow::makeTexture(const string& path) { //make texture function
    Image img;
    img.loadFromFile(path);
    Texture* tex = new Texture();
    tex->loadFromImage(img);
    return tex;
}
void GameFilesWindow::makeTree(FileNode* node) { //make tree function
    //Make a fake directory in the tree which links to the parent directory
    if (node->getName() != "GameFiles" && node->childIndex("\\") == -1) {
		FileNode* tmp = new FileNode("\\", true);
		tmp->setIcon(Game::getFolderTexture());
		node->addChild(tmp);
	}

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
        else if (node->childIndex(name) == -1 && (name.find(".poscene") != string::npos)) {
            FileNode* tmp = new FileNode(name, false);
            tmp->setIcon(makeTexture("Resources/Sans.png"));
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
        if (!exists && name != "\\") {
            cout<<"WE deleted " << name << endl;
            node->removeChild(i);
            i--;
            n--;
        }
        else if (name.find(".") == string::npos && name != "\\") {
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
        addText(Text(node->getChild(i)->getName(), *Game::getFont(), 13));
        texts[i].setPosition(position.x + 10 + (i % 4) * 110 + icons[i].getSize().x / 2 - texts[i].getGlobalBounds().width / 2, position.y + 130 + (i / 4) * 130);
    }
    int elementsPerRow = (size.x - 20) / 110;
    for (int i = 0; i < icons.size(); i++) {
        icons[i].setPosition(position.x + 10 + (i % elementsPerRow) * 110, position.y + 30 + (i / elementsPerRow) * 130);
        texts[i].setPosition(position.x + 10 + (i % elementsPerRow) * 110 + icons[i].getSize().x / 2 - texts[i].getGlobalBounds().width / 2, position.y + 130 + (i / elementsPerRow) * 130);
    }
    text = Text(currentDirectory, *Game::getFont(), 15);
    text.setPosition(position.x + 10, position.y + 5);
    addText(text);
    updateElementsWithVerticalOffset(0);
    selectedFile = -1;
    selectedBackground.setPosition(Vector2f(-1000, -1000));
}
GameFilesWindow::GameFilesWindow(const Font& font, const Vector2f& position, const Vector2f& size, const string& title) : EditorWindow(font, position, size, title), dropdown(font, Vector2f(position.x + size.x - 90, position.y), Vector2f(100, 100)) {
    currentDirectory = "GameFiles/";
    lastClickTime = 0;
    selectedFile = -1;
    isDragging = false;

    dragVisual.setSize(Vector2f(10, 10));
    dragVisual.setFillColor(Color::Red);

    selectedBackground.setSize(Vector2f(110, 130));
    selectedBackground.setFillColor(Color(22, 48, 114, 0)); //194 alpha when visible
    selectedBackground.setOutlineColor(Color::Black);
    selectedBackground.setOutlineThickness(1);

    root = new FileNode("GameFiles", true);
    //makeTree(root);

    dropdown.setActive(false);
    dropdown.addElement("New Folder");
    dropdown.addElement("New Scene");
    dropdown.setCallback([this](int index) {
        if (index == 0) {
            makeDir();
        }
        else if (index == 1) {
            makeScene();
        }
        });

    copyPath = "None";

    InputField* input = new InputField(font, Vector2f(position.x + 10, position.y + 5), Vector2f(100, 20), "Rename");
    /*input->setOnChange([this](const string& text) {
		renameFile(text);
		});*/
    /*input->setUpdateValue([this]() {
        if (selectedFile != -1) {
			return string(texts[selectedFile].getString());
		}
		return string("");
		});*/
    input->setFinishEdit([this](const string& text) {
		renameFile(text);
        inputFields[0].setPosition(Vector2f(-1000, -1000));
		});
    input->setPosition(Vector2f(-1000, -1000));
    addInputField(*input);
    delete input;

    bottomBar.setSize(Vector2f(0, 0));

    loadFiles();
}
void GameFilesWindow::handleEvent(Event& event) { //handle event function
    dropdown.handleEvent(event);
    if (event.type == Event::MouseButtonPressed && isMouseOver()) {
        if (event.mouseButton.button == Mouse::Left && !Game::getBlockClick()) {
            if (selectedFile != -1) {
                if (texts[selectedFile].getString() != "\\") {
                    //Check if the mouse is over the text of the selectedFile and if it is, position the inputfield there and select it
                    if (texts[selectedFile].getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        inputFields[0].setPosition(Vector2f(icons[selectedFile].getPosition().x, texts[selectedFile].getPosition().y - 5));
                        inputFields[0].setText(texts[selectedFile].getString());
                        inputFields[0].select();
                    }
                    else {
                        inputFields[0].deselect();
                    }
                }
            }

            isDragging = true;
            int index = -1;
            for (int i = 0; i < icons.size(); i++) {
                if (icons[i].getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)) || texts[i].getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    if (GameTime::getInstance()->getTime() - lastClickTime < 0.5f && selectedFile == i) {
                        if (texts[i].getString().find(".") == string::npos) {
                            if(texts[i].getString() != "\\")
                                currentDirectory += texts[i].getString() + "/"; 
                            else {//Go up a directory
                                currentDirectory = currentDirectory.substr(0, currentDirectory.size() - 1);
                                currentDirectory = currentDirectory.substr(0, currentDirectory.find_last_of("/") + 1);
                            }
                            verticalOffset = 0;
                            loadFiles();
                            index = -1;
                            inputFields[0].deselect();
                            break;
                        }
                        else if (texts[i].getString().find(".poscene") != string::npos) {
                            Game::loadScene(currentDirectory + texts[i].getString());
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
                string name = texts[selectedFile].getString();
                if (name.find(".png") != string::npos || name.find(".jpg") != string::npos || name.find(".psd") != string::npos) {
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
        if (event.mouseButton.button == Mouse::Right) {
            if (isMouseOver()) {
                //Deselect the selected file
                selectedFile = -1;
                selectedBackground.setPosition(Vector2f(-1000, -1000));
                selectedBackground.setFillColor(Color(22, 48, 114, 0));

                //Show the dropdown
				dropdown.setActive(true);
                dropdown.setPosition(Vector2f(event.mouseButton.x, event.mouseButton.y));
			}
		}
    }
    if (event.type == Event::MouseButtonReleased) {
        if (event.mouseButton.button == Mouse::Left) {
			isDragging = false;
            //Check if the mouse is over the window
            if (isMouseOver()) {
				//Check if the mouse is over an icon
                for (int i = 0; i < icons.size(); i++) {
                    if (icons[i].getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        if (selectedFile != -1 && selectedFile != i) {
							string newPath = currentDirectory + texts[i].getString();
                            if (texts[i].getString() == "\\") {
                                newPath = currentDirectory.substr(0, currentDirectory.size() - 1);
								newPath = newPath.substr(0, newPath.find_last_of("/") + 1);
                            }
                            //Convert path to filesystem::path
                            filesystem::path p = newPath;

                            string oldPath = currentDirectory + texts[selectedFile].getString();
                            filesystem::path oldP = oldPath;
                            //Check if we are moving a file to a directory and if the file already exists
                            if (filesystem::is_directory(p) && !filesystem::exists(p / oldP.filename())) {
                                filesystem::rename(oldP, p / oldP.filename());
							}
							loadFiles();
						}
						break;
					}
				}
			}
		}
	}
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Delete) {
        if (selectedFile != -1) {
            if (texts[selectedFile].getString() != "\\") {
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
    }
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::C) {
        if (Keyboard::isKeyPressed(Keyboard::LControl)) {
			copy();
		}
	}
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::V) {
        if (Keyboard::isKeyPressed(Keyboard::LControl)) {
            paste();
        }
    }
    EditorWindow::handleEvent(event);
}
void GameFilesWindow::update() { //update function
    if (isDragging) {
		dragVisual.setPosition(Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y));
	}
	EditorWindow::update();
    dropdown.update();
}
string GameFilesWindow::getCurrentDirectory() const { //get current directory function
    return currentDirectory;
}
void GameFilesWindow::setCurrentDirectory(const string& directory) { //set current directory function
    verticalOffset = 0;
    currentDirectory = directory;
    loadFiles();
}
void GameFilesWindow::draw(RenderWindow& window) const { //draw function
    if(!isActive)
		return;
    //EditorWindow::draw(window);
    window.draw(this->window);
    if (isDragglable)
        window.draw(draggingArea);
    for (int i = 0; i < icons.size(); i++) {
        window.draw(icons[i]);
    }
    window.draw(selectedBackground);
    for (int i = 0; i < texts.size() - 1; i++) {
		window.draw(texts[i]);
	}
    window.draw(topBar);
    window.draw(texts[texts.size() - 1]);
    window.draw(title);
    inputFields[0].draw(window);
    dropdown.draw(window);
    if(isDragging && selectedFile != -1)
		window.draw(dragVisual);
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
void GameFilesWindow::makeScene() { //make scene function
	string path = currentDirectory;
	string name = "New Scene";
	//Check if the scene already exists
    int i = 1;
    while (filesystem::exists(path + name + ".poscene")) {
     	name = "New Scene (" + to_string(i) + ")";
     	i++;
    }
    ofstream file(path + name + ".poscene");
    file << "Scene" << endl;
    file << -1 << endl;
    file << 0 << endl;
    file.close();
    loadFiles();
}
int GameFilesWindow::getSelectedFile() const { //get selected file function
	return selectedFile;
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
void GameFilesWindow::copy() { //copy function
    if (selectedFile != -1) {
		copyPath = currentDirectory + texts[selectedFile].getString();
	}
}
void GameFilesWindow::paste() { //paste function
    //Check if the copied path is valid
    if (copyPath != "None" && filesystem::exists(copyPath)) {
        string fileName = copyPath.substr(copyPath.find_last_of("/") + 1);
        if(fileName == "\\")
            return;
        string newPath = currentDirectory + fileName;
        //Check if the file already exists
        int i = 1;
        while (filesystem::exists(newPath)) {
            if (filesystem::is_directory(newPath)) {
				newPath = currentDirectory + fileName + " (" + to_string(i) + ")";
			}
            else {
				newPath = currentDirectory + fileName.substr(0, fileName.find_last_of(".")) + " (" + to_string(i) + ")" + fileName.substr(fileName.find_last_of("."));
			}
			i++;
		}
        filesystem::copy(copyPath, newPath);
        loadFiles();
	}
    else
        copyPath = "None";
}
void GameFilesWindow::renameFile(const string& newName) { //rename function
    if (selectedFile != -1) {
		string path = currentDirectory + texts[selectedFile].getString();
        string ext = "";
        if (path.find(".") != string::npos)
			ext = path.substr(path.find_last_of("."));
        string newNameWithExt = newName;
        if (newName == "" || newName == "\\")
            newNameWithExt = "New Folder";
        //If the new name has an extension, remove it
        if (newNameWithExt.find(".") != string::npos)
            newNameWithExt = newNameWithExt.substr(0, newNameWithExt.find_last_of("."));

        cout<<"The new name is " << newNameWithExt << endl;
        cout<<"The extension is " << ext << endl;

        //Check if the file already exists
        string tmp = newNameWithExt;
        int i = 1;
        while (filesystem::exists(currentDirectory + tmp + ext)) {
			tmp = newNameWithExt + " (" + to_string(i) + ")";
			i++;
		}
        newNameWithExt = tmp;

        cout << "After the while loop\n";
        cout<<"The new name is " << newNameWithExt << endl;
        cout<<"The extension is " << ext << endl;

        //Add the extension to the new name
        newNameWithExt += ext;
		string newPath = currentDirectory + newNameWithExt;
		filesystem::rename(path, newPath);
		loadFiles();
	}
}
GameFilesWindow::~GameFilesWindow() { //destructor
	delete root;
}