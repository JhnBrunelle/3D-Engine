# 3D Renderer

This repo encompases multiple aspects of a 3D renderer, including 2D line drawing, 3D transformation

Each project contains a make file to build and run the project. X11 is required.

Scroll to see the different iterations of the project

### 1. Brenseham's Algorthm - Line Drawing
* First step in the renderer, which implements an [brenseham's algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm) for drawing lines 

![First Step](https://raw.githubusercontent.com/JhnBrunelle/3D-Renderer/master/Bresenham's%20Algorithm/Screenshot.png?token=AE2VNU4G4I6WKEYI6OA4ZTC6ARIDI)

### 2. 3D Mesher - Wireframes
* Uses line algorithm from part 1 and applies 3D transforms
* Features models for Sphere and Torus'
* Features 3D camera and light objects (camera shown below)
* Creates Wiremeshes

![First Step](https://raw.githubusercontent.com/JhnBrunelle/3D-Renderer/master/3D%20mesher/view1.png)
![First Step](https://raw.githubusercontent.com/JhnBrunelle/3D-Renderer/master/3D%20mesher/view4.png)
![First Step](https://raw.githubusercontent.com/JhnBrunelle/3D-Renderer/master/3D%20mesher/view5.png)


### 3. 3D Shader - Polygon Face filling
* Uses part 2, and shades implements a 2D vertex polygon filling algorithm
* Adds model for Torus
* Creates shapes with shaded textures, creating a full model

![3D shape](https://raw.githubusercontent.com/JhnBrunelle/3D-Renderer/master/3D%20Shader/shot1.png?token=AE2VNU5ELYETC3JSB4HHU3K6ARIUA)

### 4. Ray Tracer - Shadows
* Adds a Ray Tracing framework, to allow for shadowing on the the Objects

![3D shape](https://raw.githubusercontent.com/JhnBrunelle/3D-Renderer/master/RayTracer/src/screenshot.png?token=AE2VNU454GYOUSAF7U73Y226ARIYM)
