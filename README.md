# 3D Model Viewer
This is a simple 3D model viewer that can load and display 3D models in the OBJ file format. It is written in C++ and uses OpenGL for rendering.
Model loading is done using the [Assimp](https://github.com/assimp/assimp/releases) library. Using GLFW for window creation and input handling and GLAD for loading OpenGL functions.

## Showcase

![Showcase](https://github.com/goldbarth/3DModelViewer/blob/main/Media/BackpackShowcase.gif "Showcase")

## Features
- Load and display 3D models in the OBJ file format
- Load models with and without textures
- Lighting using a directional light source (for the showcase it is moving slightly for more dynamic)
- Ambient, diffuse, and specular lighting
- Display the model in wireframe mode
- Rotate, pan, and zoom the camera
- Movements are controlled using the mouse and keyboard
- Rotate the model around its own axis

## Controls
- Mouse movement - Rotate the camera
- `W`, `A`, `S`, `D` - Move the camera forward, left, backward, and right
- Arrow keys - Rotate the model around its own axis
- `1` - Toggle wireframe mode on and off
- `R` - Reset the camera position
- Mouse wheel - Zoom in and out
- `ESC` - Close the application

## Future Improvements
- Add UI elements to adjust settings (like wireframe mode, camera speed, lightning, etc.)
- Add support for more advanced lightning models
- Add support for more file formats
- Add support for multiple models

The list of improvements is only a fraction of what could be done.
The main goal is to make a simple game or simulation using this viewer.

## Goals
- Learn more about OpenGL and 3D rendering
- Make a simple (puzzle) game or simulation using this viewer

## Dependencies
- [CMake](https://cmake.org/)
- [GLFW](https://www.glfw.org/)
- [GLAD](https://github.com/Dav1dde/glad)
- [Assimp](https://github.com/assimp/assimp/releases)

## Credits
- Marcus Schaal (SAE Lecture: Graphics and Shader Programming)
- [Joey de Vries](https://joeydevries.com/#home) for his excellent OpenGL tutorials @ [LearnOpenGL](https://learnopengl.com/)