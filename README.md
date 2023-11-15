# threeD-renderer
A basic OpenGL 3D graphics renderer in C++, a demo project for me to get into graphics.  
Uses SFML for window management and input, glew/glm for the OpenGL implementation, and assimp to handle model imports (so that it can actually render some useful meshes).  

## Setup
- Clone the repository and ```cd``` into it.
- Make sure you have assimp, sfml, and GLEW installed on your systems. 
- Run ```make compile``` to build the object files.
- Run ```make run``` to link and run the binary.

## Usage
- Load your own model files (.fbx) into the program by replacing the ```modelFile``` constant with your own model file path in ```Renderer.cpp```. (on Line 16)
