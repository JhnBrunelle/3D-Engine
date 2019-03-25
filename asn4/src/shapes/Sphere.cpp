#include <vector>
#include "Sphere.hpp"
#include "Shape.hpp"

#define RES 45	// The Resolution of the Sphere (divisions per circle)

using namespace std;



void Sphere::createSphereCoords(double radius){


	Coord3 initialPoint(0.0, radius, 0.0);
	circle.push_back(initialPoint);

	// First we draw a circle along the X axis
	Coord3 newCoord = initialPoint;
	for(int i = 0; i <= RES; ++i){
		newCoord = newCoord.xRotate(angle);
		circle.push_back(newCoord);
	}

	// Rotate the circle around the Y axis
	for(int i = 0; i <= RES; ++i){
		sphere.push_back(circle[i].yRotate(angle));
	}

}



void Sphere::createSphereLines(){

  
  for(int i = 0; i < RES*2; ++i){
    for(int j = 1; j <= RES; ++j){
      
      // Add faces
			addFace(PolyFill(circle[j-1],circle[j],sphere[j-1]));
			addFace(PolyFill(sphere[j],sphere[j-1],circle[j]));
    }

    for(int i = 0; i < RES; ++i){

      // Rotate the curr position around the sphere
      circle[i] = sphere[i];
      sphere[i] = sphere[i].yRotate(angle); // Roate sphere coordinate
    }
  }
}


Sphere::Sphere(double radius) {

	angle = 180 / RES;	// Calculate the angle of each division 

	// Construct the coordinates for each line connection
	this->createSphereCoords(radius);
 	
 	// Create the line connections
	this->createSphereLines();
}
