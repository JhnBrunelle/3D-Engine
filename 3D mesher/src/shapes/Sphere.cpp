#include <vector>
#include "Sphere.hpp"
#include "Shape.hpp"

#define RES 25	// The Resolution of the Sphere (divisions per circle)

using namespace std;



void Sphere::createSphereCoords(double radius){


	Coord3 initialPoint(0.0, 0.0, radius);
	circle.push_back(initialPoint);

	// First we draw a circle along the X axis
	Coord3 newCoord = initialPoint;
	for(int i = 1; i < RES; i++){
		newCoord = newCoord.xRotate(angle);
		circle.push_back(newCoord);
	}

	// Rotate the circle around the Y axis
	for(int i = 0; i < RES; i++){
		sphere.push_back(circle[i].yRotate(angle));
	}

}

void Sphere::createSphereLines(){

	// For each coordinate along the circle:
	for(int i = 0; i < RES; i++){

		// Create Lines between the sphere point and the circles
		for(int j = 0; j < RES; j++){

			Line newLine(sphere[j], circle[j]);
			addLine(newLine);
		}

		// Create Lines for each coordinate on the sphere circle
		addLine(Line(sphere[RES-1], sphere[0]));
		for(int j = 1; j < RES; j++){

			Line newLine(sphere[j-1],sphere[j]);
			addLine(newLine);
		}

		// Move the current sphere line to the current circle, and rotate
		for(int j = 0; j < RES; j++){

			circle[j] = sphere[j];
			sphere[j] = sphere[j].yRotate(angle);
		}
	}
}



Sphere::Sphere(double radius) {

	angle = 360 / RES;	// Calculate the angle of each division 

	// Construct the coordinates for each line connection
	this->createSphereCoords(radius);
 	
 	// Create the line connections
	this->createSphereLines();
}