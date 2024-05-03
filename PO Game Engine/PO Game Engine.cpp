#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <functional>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "GameTime.h"
#include "Utility.h"
#include "Collider.h"
#include "GameObject.h"
#include "BehaviourScript.h"
#include "TestScript.h"
#include "Scene.h"
#include "Game.h"
#include "FollowMouseScript.h"
#include "InputField.h"
#include "Button.h"
#include "EditorWindow.h"
#include "ColorPicker.h"
#include "ImageField.h"
#include "EditableColor.h"
#include "InspectorWindow.h"
#include "HierarchyWindow.h"
#include "Gizmo.h"
#include "FileNode.h"
#include "GameFilesWindow.h"
#include "TopBarWindow.h"


using namespace sf;
using namespace std;

//Initializes the static variables
int Scene::sceneIdCounter = 0;
int GameObject::idCounter = 500;
GameTime* GameTime::instance = NULL;
RenderWindow* Game::window = NULL;
Scene* Game::currentScene = NULL;
EditorWindow* Game::hierarchy = NULL;
EditorWindow* Game::inspector = NULL;
Font* Game::font = NULL;
bool Game::isPlaying = false;
bool Game::drawEditor = true;
EditorWindow* Game::colorPicker = NULL;
EditorWindow* Game::gameFilesWindow = NULL;
Texture* Game::folderTexture = NULL;
Gizmo* Game::gizmo = NULL;
View* Game::sceneView = NULL;
View* Game::guiView = NULL;
bool EditorWindow::clickedUI = false;
Vector2f Game::sceneViewPositionBeforePlaying = Vector2f(0, 0);
Vector2f Game::sceneViewZoomBeforePlaying = Vector2f(1, 1);




int main()
{
    try {
        //Setup
        RenderWindow window(VideoMode(1920, 1080), "PO Game Engine");
        Game::setWindow(&window);
        Font font;
        font.loadFromFile("Resources/Roboto-Black.ttf");
        Game::setFont(&font);
        //window.setFramerateLimit(60);

        Image folderIconimg;
        if(!folderIconimg.loadFromFile("Resources/Folder.png"))
            cout<<"Failed to load image"<<endl;
        Texture* folderIcon = new Texture();
        if(!folderIcon->loadFromImage(folderIconimg))
            cout<<"Failed to load texture"<<endl;
        Game::setFolderTexture(folderIcon);
        if(!Game::getFolderTexture())
		    cout<<"Failed to set folder texture"<<endl;

        Scene scene;
        Game::setCurrentScene(&scene);
        HierarchyWindow hierarchyWindow(font, Vector2f(0, 0), Vector2f(250, window.getSize().y), "Hierarchy");
        InspectorWindow inspectorWindow(font, Vector2f(window.getSize().x - 350, 0), Vector2f(350, window.getSize().y), "Inspector");
        ColorPicker colorPicker(font, Vector2f(window.getSize().x * 0.25f, 0), Vector2f(320, 320), "Color Picker");
        GameFilesWindow gameFilesWindow(font, Vector2f(250, window.getSize().y - 300), Vector2f(window.getSize().x - 600, 300), "Game Files");
        TopBarWindow topBarWindow(font, Vector2f(253, 0), Vector2f(window.getSize().x - 606, 50), "");
        Game::setHierarchy(&hierarchyWindow);
        Game::setInspector(&inspectorWindow);
        Game::setColorPicker(&colorPicker);
        Game::setGameFilesWindow(&gameFilesWindow);
        GameTime* time = GameTime::getInstance();


        bool save = false;
        bool load = false;


        float nextSpace = 0;

        GameObject ob;
        ob.setName("Object0");
        makeObj(ob, Vector2f(100, 100), 100.f);

        BehaviourScript* script = new TestScript(Color::Magenta, Color::Cyan);
        ob.addScript(script);
        delete script;

        script = new FollowMouseScript(true);
        ob.addScript(script);
        delete script;

        scene.addObject(&ob);


        GameObject ob2;
        ob2.setFillColor(Color::Green);
        ob2.setName("Object1");
        ob2.setPosition(Vector2f(300, 300));
        ob2.setRotation(45);
        scene.addObject(&ob2);

        /*Player ob3;
        ob3.setName("Player1");
        ob3.setPosition(Vector2f(500, 500));
        ob3.setFillColor(Color::Blue);
        scene.addObject(&ob3);


        Player ob4;
        ob4.setFillColor(Color::Yellow);
        ob4.setName("Player2");
        ob4.setPosition(Vector2f(700, 700));
        ob4.setDownKey(Keyboard::Down);
        ob4.setLeftKey(Keyboard::Left);
        ob4.setRightKey(Keyboard::Right);
        ob4.setUpKey(Keyboard::Up);
        ob4.setShootKey(Keyboard::RControl);
        scene.addObject(&ob4);*/
        if (load) {
            ifstream in("Resources/Test.txt"); //Read scene
            in >> scene;
            in.close();
        }


        Text fpsCounter("FPS: ", font, 15);
        fpsCounter.setFillColor(Color::White);
        fpsCounter.setPosition(10, 10);

        if(Game::getIsPlaying())
            scene.startScene();

        Gizmo gizmos;
        Game::setGizmo(&gizmos);

        View sceneView(Vector2f(window.getSize().x / 2, window.getSize().y / 2), Vector2f(window.getSize().x, window.getSize().y));
        View editorView = window.getDefaultView();

        Game::setSceneView(&sceneView);
        Game::setGuiView(&editorView);

        Vector2f lastMousePos = Vector2f(0, 0);

    
        while (window.isOpen()) //Game loop
        {
            //Calculate time and delta time
            time->update();
            EditorWindow::setClickedUI(false);

            //Event handling
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();

                if (Game::getDrawEditor()) {
                    topBarWindow.handleEvent(event);
                    colorPicker.handleEvent(event);
                    inspectorWindow.handleEvent(event);
                    gameFilesWindow.handleEvent(event);
                    hierarchyWindow.handleEvent(event); //Call last


                    if (scene.getSelectedObjectIndex() != -1) {
                        if (Keyboard::isKeyPressed(Keyboard::Delete)) {
                            deleteObj();
                            colorPicker.setActive(false);
                        }
                    }
                }
                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::F1)
                        Game::setDrawEditor(!Game::getDrawEditor());
                    else if (event.key.code == Keyboard::W)
                        gizmos.setGizmoType(0);
                    else if (event.key.code == Keyboard::E)
                        gizmos.setGizmoType(1);
                    else if (event.key.code == Keyboard::R)
                        gizmos.setGizmoType(2);
                }

                //If we are scrolling, zoom the scene
                if (event.type == Event::MouseWheelScrolled) {
					if (event.mouseWheelScroll.delta > 0)
						sceneView.zoom(0.9f);
					else
						sceneView.zoom(1.1f);
				}
            }

            //If we are holding the right mouse button and moving the mouse, pan the scene
            if (Mouse::isButtonPressed(Mouse::Right)) {
                Vector2f mousePos = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
                mousePos = window.mapPixelToCoords(Vector2i(mousePos.x, mousePos.y), sceneView);
                Vector2f lastMousePosCpy = lastMousePos;
                lastMousePosCpy = window.mapPixelToCoords(Vector2i(lastMousePosCpy.x, lastMousePosCpy.y), sceneView);
                sceneView.move(lastMousePosCpy - mousePos);
            }
            lastMousePos = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y);

            //Only update the fps counter 10 times per second
            if (time->getTime() > nextSpace) {
                nextSpace = time->getTime() + 0.1f;
                fpsCounter.setString("FPS: " + floatToString(1.f / time->getDeltaTime()));
            }

            //Update the editor
            if (Game::getDrawEditor()) {
                topBarWindow.update();
                hierarchyWindow.update();
                inspectorWindow.update();
                colorPicker.update();
                gameFilesWindow.update();
                gizmos.update();
            }


            //Select object
            if (Mouse::isButtonPressed(Mouse::Left)) {
                topBarWindow.mouseOver();
                hierarchyWindow.mouseOver();
                inspectorWindow.mouseOver();
                colorPicker.mouseOver();
                gameFilesWindow.mouseOver();
            }

            //Update the scene
            if (Game::getIsPlaying())
                scene.updateScene();

            //Clear the window
            window.clear();

            //Draw the objects
            window.setView(sceneView);
            Game::getCurrentScene()->drawScene(false, window);

            //Draw the editor
            if (Game::getDrawEditor()) {
                gizmos.draw(window);
                window.setView(editorView);
                hierarchyWindow.setTitle("Hierarchy (" + to_string(scene.getObjectsCount()) + ")");
                hierarchyWindow.draw(window);
                inspectorWindow.draw(window);
                gameFilesWindow.draw(window);
                topBarWindow.draw(window);
                colorPicker.draw(window);
                window.draw(fpsCounter);
            }

            //lastMousePos = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y);

            window.display();
        }

        //Save scene
        if (save) {
            Game::setIsPlaying(false);
            ofstream out("Resources/Test.txt");
            out << scene;
            out.close();
        }

        if (folderIcon)
            delete folderIcon;
    }
    catch (exception& e) {
		cout<<e.what()<<endl;
	}
    catch (...) {
        cout<<"An error occurred"<<endl;
    }

    return 0;
}