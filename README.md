# Terrain Block Generator

## Overview
- The Terrain Block Generator project is designed to be a versatile visualization tool for rendering and manipulating 3D terrain blocks. Leveraging the capabilities of Qt and OpenGL, this application provides an interactive environment for users to explore and modify terrain structures in real-time.

### 1. User Interface
- Buttons and Sliders
1. `Read STL`: Opens a file dialog for selecting an STL file and renders it.
2. `Generate Block`: Initiates the terrain block generation.
3. `Clear Screen`: Clears openGL window.

### 2. Classes and Data Structures
**Geometry Classes**
1. `Point3D`: Represents a point in 3D space.
2. `Triangle`: Represents a triangle in 3D space with vertices and a normal.
3. `Triangulation`: Represents a collection of triangles forming a 3D structure.

**STLReader Classes**
- `Reader`: Reads and processes STL files to extract vertex and normal information.

**Rendering Classes**
- `OpenGLWindow`: Handles OpenGL rendering, user interactions, and shader programs.

**Shader Program**
`Shaders`: Includes vertex shader and fragment shader program for openGL rendering. 

**Algorithm classes**
- `Algorithm`: The algorithm which take vertex data from binary stl and generate terrain block.

**Visualizer Classes**
- `Visualizer`: The main application window that includes the user interface and interactions.

**main function**
- `main`: The main function serves as the entry point of the application.


### 3. Software Tools

1. `C++`: The primary programming language for the application.

2. `QT`: The Qt framework is utilized for the development of the graphical user interface (GUI) components.

3. `OpenGL`: OpenGL is employed for rendering 3D graphics, enhancing the visualization capabilities of the application.

4. `Visual Studio`: The project is developed and built using the Visual Studio integrated development environment.

5. `Git`: Git is used for version control and collaborative development, allowing for easy tracking of changes and contributions.


### 4. File Structure

- The project adopts a well-organized file structure, promoting modularity and code clarity. Here's an overview of the key components:

**Geometry DLL**

1. `Geometry.h/.cpp`

2. `Point3D.h/.cpp`

3. `Triangle.h/.cpp`

4. `Triangulation.h/.cpp`

**STL_Reader DLL**
1. `STL_Reader.h/.cpp`

2. `Reader.h/.cpp`

**OpenGL Rendering**

- `OpenGLWindow.h/cpp`

**Shaders File**

1. `vertexShader.glsl`

2. `fragmentShader.glsl`

**Algorithm code**

- `Algorithm.h/cpp`

**Visualizer Project**

- `Visualizer.h/cpp`

**main function**

- `main.cpp`
