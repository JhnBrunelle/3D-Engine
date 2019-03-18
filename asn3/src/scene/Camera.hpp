#pragma once


#include "../utils/Coord3.hpp"
#include "../utils/Matrix.hpp"
#include "Scene.hpp"
#include "../shapes/Shape.hpp"
#include "../utils/PolyFill.hpp"


#define PI 3.14159

/**
 * A custom camera class, since I wasn't able to get the provided camera.h working
 */
class Camera {
private:
			
  Coord3 camPos;			// Camera Position in 3D space
  Matrix cameraMatrix;		// The Camera matrix

  Scene scene;				// Scene associated with Camera
 
  /**
   * Generates a camera matrix from the given angles
   * double x3 (in) - the x, y and z tilt of camera in rads
   * returns nothing
   */
  void generateCameraMatrix(double radX, double radY, double radZ);


  /**
   * Draws the shapes of the scene from the projection of the camera
   * Shape (in) - Shape to project
   * returns projected shapes
   */
  Shape drawShapes(Shape);

  /**
   * Draws the faces of the scene from the projection of the camera
   * face(in) - face to project
   * returns projected faces
   */
  PolyFill drawFace(PolyFill face);

  /**
   * Draws the coords of the scene from the projection of the camera
   * coord3 (in) - coord to project
   * returns projected coordinate
   */
  Coord3 drawCoord(Coord3);


public:
  
  /**
   * Camera constructors
   */
  Camera();

  /**
   * Creates a new camera
   * Coord3 - the poistion of the camera
   * 3x doubles - the X, Y and Z tilt of the camera in Degrees
   * returns a new camera
   */
  Camera(Coord3, double, double, double);

  /**
   * Creates a scene within the camera
   * Scene (in) - Scene to add
   * Returns the scene after being projected by the camera
   */
  Scene createScene(Scene);
  
};