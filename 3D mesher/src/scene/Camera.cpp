#include <cmath>
#include "Camera.hpp"
#include "../utils/Line.hpp"
#include <vector>

#define PI 3.14159
#define offSet 256

// Default Constructor
Camera::Camera(): camPos(0,0,0), cameraMatrix(3,3){}

// Constructor that accepts parameters
Camera::Camera(Coord3 cameraPosition, double degX, double degY, double degZ): camPos(0,0,0), cameraMatrix(3,3){

  // Set the Camera position
  camPos.x = cameraPosition.x;
  camPos.y = cameraPosition.y;
  camPos.z = cameraPosition.z;

  // Generate the camera matrix
  this->generateCameraMatrix((PI * degX) / 180.0,  (PI * degY) / 180.0, (PI * degZ) / 180.0);

}

// Creates the camera matrix from the angeles provides
void Camera::generateCameraMatrix(double radX, double radY, double radZ){

    // Vectors containing required matrices
    std::vector< std::vector<double>> m1;
    std::vector< std::vector<double>> m2;
    std::vector< std::vector<double>> m3;

    m1 = {
      { 1, 0, 0 },
      { 0, cos(radX), sin(radX)},
      { 0, -1.0 * sin(radX), cos(radX)}
    };

    m2 = {
      {cos(radY), 0, -1.0 * sin(radY)},
      {0, 1, 0},
      {sin(radY), 0,cos(radY) }
    };

    m3 = {
      {cos(radZ), sin(radZ), 0},
      {-1.0*sin(radZ), cos(radZ), 0},
      {0, 0, 1}
    };

    // Copy over Vectors into Matrices
    Matrix matrix1(3,3);
    Matrix matrix2(3,3);
    Matrix matrix3(3,3);

    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
        matrix1[i][j] = m1[i][j];
        matrix2[i][j] = m2[i][j];
        matrix3[i][j] = m3[i][j];
      }
    }

    // Multiple together to create camera matrix
    cameraMatrix = matrix1 * matrix2 * matrix3;
}

// Draw the shapes onto the scenes
Shape Camera::drawShapes(Shape inShape){

  vector<Line> allLines = inShape.getLines();

  Shape tempShape;
  for(int i = 0; i < allLines.size(); i++){
    Coord3 a = drawCoord(allLines[i].a);
    Coord3 b= drawCoord(allLines[i].b);
    tempShape.addLine(Line(a,b));
  }
  return tempShape;
}


Coord3 Camera::drawCoord(Coord3 coord){
  Coord3 camPosClone = camPos;
  Coord3 drawnCoord(0,0,0);

  Coord3 diff = camPosClone - coord;
  Matrix diffM = Matrix::Coord3ToMatrix(diff);
  Matrix cM = cameraMatrix * diffM;

  Coord3 a = Matrix::toCoord3(cM);
  Coord3 b(0,0, 300.0);
  drawnCoord.x = (a.x * (b.z/a.z)) + b.x;
  drawnCoord.y = (a.y * (b.z/a.z)) + b.y;

  drawnCoord.x += offSet;
  drawnCoord.y += offSet;

  return drawnCoord;
}


// Create the Scene
Scene Camera::createScene(Scene appliedScene){
  
  vector<Shape> allShapes = appliedScene.getShapes();

  // Draw each shape onto the scene
  for(int i = 0; i < allShapes.size(); i++){
    scene.addShape(drawShapes(allShapes[i]));
  }
  return scene;
}
