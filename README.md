# PO Game Engine

PO Game Engine is a C++ and SFML based engine made in around 2 months which has around 9000 lines of code. It was my project for my Object Oriented Programming class in my first year of college.

## Features

### File Manager
- **Reflection of a folder from the user's computer**
- **Create new scenes and folders**
- **Move files between folders**
- **Rename files**
- **Copy-pasting**
- **Navigate folders**
- **Delete files and folders**

![GameFilesDemo](https://github.com/Androidus2/PO-Game-Engine/assets/36742066/e7853c7a-630f-4578-8f38-5335cd08646a)

### Hierarchy View
- **Display all objects in the scene**
- **Selection support**
- **Duplicate with Ctrl+D**

![HierarchyWindowDemo](https://github.com/Androidus2/PO-Game-Engine/assets/36742066/e38928f9-7f78-42c8-9dca-fdc89ed03b06)


### Inspector View
- **Basic object information**: View and edit object properties including name, tag, active status, transform information and more.
- **Collider information**: Configure collision properties for your objects.
- **Texture and color**: Apply visual properties to your game objects.
- **Custom script properties**: Manage and tweak the scripts attached to your objects.

![InspectorDemo](https://github.com/Androidus2/PO-Game-Engine/assets/36742066/6d55a174-0bba-42f2-949b-96d10d5f9f7c)


### Scene View
- **Game world visualization**: See and manipulate your game world.
- **Transform objects with gizmos**: Move, rotate, and scale objects with ease.
- **Default movement**: Zoom with the scroll wheel and pan by holding the right mouse button.

![SceneViewDemo](https://github.com/Androidus2/PO-Game-Engine/assets/36742066/6dd80abe-44aa-4030-9cc5-89bfdf567ee9)


### Game View
- **Camera perspective**: See exactly what the camera in your scene sees during gameplay (The camera is an undeleteable object in the scene).

![GameViewDemo](https://github.com/Androidus2/PO-Game-Engine/assets/36742066/55e49ad9-b12f-4a97-911f-72a3233ec9a6)


### Playmode Management
- **Entering and exiting playmode**: Test your game.
- **Non-persistent changes**: Changes made in playmode are not saved, allowing for safe experimentation.

![PlayModeDemo](https://github.com/Androidus2/PO-Game-Engine/assets/36742066/155d12e9-c1dc-4201-be1a-07667f42ef78)


### Scene Management
- **Saving and loading scenes with failsafe**: Ensure your scenes load correctly without crashing or causing memory leaks.

![SceneSavingLoadingDemo](https://github.com/Androidus2/PO-Game-Engine/assets/36742066/61a2c7b6-4a0e-48e6-b1b6-709c63f4b5a7)


### Undo/Redo Support
- **Ctrl+Z / Ctrl+Y support**: Undo and redo actions to quickly correct mistakes (limit of 10, which can easily be changed).

![CtrlZCtrlYDemo](https://github.com/Androidus2/PO-Game-Engine/assets/36742066/fd510c20-e986-4837-acd0-387947072bb5)


### Available Demos
- **Complete Pong game**: A fully functional Pong game to demonstrate the engine's capabilities.
![PongDemo](https://github.com/Androidus2/PO-Game-Engine/assets/36742066/620a6ca7-555a-46fc-8e94-166e8f8433ab)
- **HoleyCastle demo**: Features enemy spawning, hole placement and removal, hole upgrades, and castle damage mechanics.
![HoleyCastkeDemo](https://github.com/Androidus2/PO-Game-Engine/assets/36742066/7a9a226a-29db-46aa-9eb0-8130357077e0)
- **Physics demo**: Showcase the physics capabilities of the engine.
![PhysicsDemo](https://github.com/Androidus2/PO-Game-Engine/assets/36742066/b6941cbe-4577-41b8-ac52-25f866695ce0)


---

My choice of a game engine for the project stems from my passion of making games, primarly in Unity. I wanted a challenge for this project and I decided to try and recreate the basic features of Unity in the best way I could think of. It could be improved a lot, but it served its purpose of teaching me C++ and OOP concepts. In the future I do want to try making a game engine again, but this time I would try it in a more planned out manner rather than simply trying to implement features in the best way I can think of.

---

### Installation
- This repository contains all the files necessary to run the project, but it does require Visual Studio Community with the C++ add-ons to work. After cloning, it is as simple as opening the solution file and pressing run.
