#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

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
#include "DebugMacro.h"



using namespace sf;
using namespace std;

//Initializes the static variables
int Scene::sceneIdCounter = 0;
int GameObject::idCounter = 500;
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
bool Game::blockClick = false;
bool Game::isOverGameWindow = false;
View* Game::gameView = NULL;



int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    try {
        //Setup
        RenderWindow window(VideoMode(1920, 1080), "PO Game Engine");
        Game::setWindow(&window);
        Font font;
        font.loadFromFile("Resources/Roboto-Black.ttf");
        Game::setFont(&font);
        //window.setFramerateLimit(60);

        Image folderIconimg;
        if (!folderIconimg.loadFromFile("Resources/Folder.png"))
            cout << "Failed to load image" << endl;
        Texture* folderIcon = new Texture();
        if (!folderIcon->loadFromImage(folderIconimg))
            cout << "Failed to load texture" << endl;
        Game::setFolderTexture(folderIcon);
        if (!Game::getFolderTexture())
            cout << "Failed to set folder texture" << endl;

        Scene* scene = new Scene();
        Game::setCurrentScene(scene);
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

        if (!load) {
            GameObject ob;
            ob.setName("Object0");
            makeObj(ob, Vector2f(100, 100), 100.f);

            BehaviourScript* script = new TestScript(Color::Magenta, Color::Cyan);
            ob.addScript(script);
            delete script;

            script = new FollowMouseScript(true);
            ob.addScript(script);
            delete script;

            Game::getCurrentScene()->addObject(&ob);


            GameObject ob2;
            ob2.setFillColor(Color::Green);
            ob2.setName("Object1");
            ob2.setPosition(Vector2f(300, 300));
            ob2.setRotation(45);
            Game::getCurrentScene()->addObject(&ob2);
        }


        Text fpsCounter("FPS: ", font, 15);
        fpsCounter.setFillColor(Color::White);
        fpsCounter.setPosition(10, 10);

        //if(Game::getIsPlaying())
        //    scene.startScene();

        Gizmo gizmos;
        Game::setGizmo(&gizmos);

        View sceneView(Vector2f(window.getSize().x / 2, window.getSize().y / 2), Vector2f(window.getSize().x, window.getSize().y));
        sceneView.setViewport(FloatRect(0.13177083f, 0.04814f, 0.684375f, 0.672222f));
        View editorView = window.getDefaultView();
        View gameView(Vector2f(window.getSize().x / 2, window.getSize().y / 2), Vector2f(window.getSize().x, window.getSize().y));
        gameView.setViewport(FloatRect(0.13177083f, 0.04814f, 0.684375f, 0.672222f));

        cout<<"Scene view size: "<<sceneView.getSize().x<<" "<<sceneView.getSize().y<<endl;

        Game::setSceneView(&sceneView);
        Game::setGuiView(&editorView);
        Game::setGameView(&gameView);

        Vector2f lastMousePos = Vector2f(0, 0);

        RectangleShape rect(Vector2f(1920, 780)); //Used to cover up the overflowing game files window
        rect.setFillColor(Color::Black);

    
        while (window.isOpen()) //Game loop
        {
            //Calculate time and delta time
            time->update();
            EditorWindow::setClickedUI(false);
            Game::setBlockClick(false);

            //Event handling
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();

                if (Game::getDrawEditor()) {
                    if (Game::getCurrentScene()->getSelectedObjectIndex() != -1 && gameFilesWindow.getSelectedFile() == -1) {
                        if (Keyboard::isKeyPressed(Keyboard::Delete)) {
                            cout<<"We pressed delete and the selected file is: "<<gameFilesWindow.getSelectedFile()<<endl;
                            deleteObj();
                            colorPicker.setActive(false);
                        }
                    }

                    topBarWindow.handleEvent(event);
                    colorPicker.handleEvent(event);
                    inspectorWindow.handleEvent(event);
                    gameFilesWindow.handleEvent(event);
                    hierarchyWindow.handleEvent(event); //Call last
                    gizmos.handleEvent(event);


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
                if (event.type == Event::MouseWheelScrolled && !inspectorWindow.isMouseOver() && !hierarchyWindow.isMouseOver() && !gameFilesWindow.isMouseOver() && !Game::getIsOverGameWindow()) {
					if (event.mouseWheelScroll.delta > 0)
						sceneView.zoom(0.9f);
					else
						sceneView.zoom(1.1f);
				}
            }

            //If we are holding the right mouse button and moving the mouse, pan the scene
            if (Mouse::isButtonPressed(Mouse::Right) && !inspectorWindow.isMouseOver() && !hierarchyWindow.isMouseOver() && !gameFilesWindow.isMouseOver() && !Game::getIsOverGameWindow()) {
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
                Game::getCurrentScene()->updateScene();

            //Clear the window
            window.clear();

            //Draw the game files window
            if (Game::getDrawEditor()) {
                gameFilesWindow.draw(window);
                window.draw(rect);
            }

            //Draw the objects
            if(!Game::getIsOverGameWindow())
                window.setView(sceneView);
            else
                window.setView(gameView);
            Game::getCurrentScene()->drawScene(false, window);

            //Draw the editor
            if (Game::getDrawEditor()) {
                if(!Game::getIsOverGameWindow())
                    gizmos.draw(window);
                window.setView(editorView);
                hierarchyWindow.setTitle("Hierarchy (" + to_string(Game::getCurrentScene()->getObjectsCount()) + ")");
                hierarchyWindow.draw(window);
                inspectorWindow.draw(window);
                //gameFilesWindow.draw(window);
                topBarWindow.draw(window);
                colorPicker.draw(window);
                window.draw(fpsCounter);
            }

            //lastMousePos = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y);

            window.display();
        }

        //Cleaning up
        /*if (folderIcon)
            delete folderIcon;
        if (Game::getCurrentScene())
            delete Game::getCurrentScene();
        if (Game::getHierarchy())
            Game::setHierarchy(NULL);
        if (Game::getInspector())
            Game::setInspector(NULL);
        if (Game::getColorPicker())
            Game::setColorPicker(NULL);
        if (Game::getGameFilesWindow())
            Game::setGameFilesWindow(NULL);
        if (Game::getGizmo())
            Game::setGizmo(NULL);
        if (Game::getSceneView())
            Game::setSceneView(NULL);
        if (Game::getGuiView())
            Game::setGuiView(NULL);
        if (Game::getFont())
            Game::setFont(NULL);*/
        Game::clearGame();
    }
    catch (exception& e) {
		cout<<e.what()<<endl;
        Game::clearGame();
	}
    catch (...) {
        cout<<"An error occurred"<<endl;
        Game::clearGame();
    }

    //A "memory leak" can happen when an exception is thrown and the program exits before the memory is deallocated (fixed i think)
    
    //A memory leak to test if the tool works (it does)
    //int* a = new int[1005];

    return 0;
}