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

  <video src='DemoVideos/GameFilesDemo.mp4' width=540/>

### Hierarchy View
- **Display all objects in the scene**
- **Selection support**
- **Duplicate with Ctrl+D**

### Inspector View
- **Basic object information**: View and edit object properties including name, tag, active status, transform information and more.
- **Collider information**: Configure collision properties for your objects.
- **Texture and color**: Apply visual properties to your game objects.
- **Custom script properties**: Manage and tweak the scripts attached to your objects.

### Scene View
- **Game world visualization**: See and manipulate your game world.
- **Transform objects with gizmos**: Move, rotate, and scale objects with ease.
- **Default movement**: Zoom with the scroll wheel and pan by holding the right mouse button.

### Game View
- **Camera perspective**: See exactly what the camera in your scene sees during gameplay (The camera is an undeleteable object in the scene).

### Playmode Management
- **Entering and exiting playmode**: Test your game.
- **Non-persistent changes**: Changes made in playmode are not saved, allowing for safe experimentation.

### Scene Management
- **Saving and loading scenes with failsafe**: Ensure your scenes load correctly without crashing or causing memory leaks.

### Undo/Redo Support
- **Ctrl+Z / Ctrl+Y support**: Undo and redo actions to quickly correct mistakes (limit of 10, which can easily be changed).

### Available Demos
- **Complete Pong game**: A fully functional Pong game to demonstrate the engine's capabilities.
- **HoleyCastle demo**: Features enemy spawning, hole placement and removal, hole upgrades, and castle damage mechanics.
- **Physics demo**: Showcase the physics capabilities of the engine.

---

My choice of a game engine for the project stems from my passion of making games, primarly in Unity. I wanted a challenge for this project and I decided to try and recreate the basic features of Unity in the best way I could think of. It could be improved a lot, but it served its purpose of teaching me C++ and OOP concepts. In the future I do want to try making a game engine again, but this time I would try it in a more planned out manner rather than simply trying to implement features in the best way I can think of.
