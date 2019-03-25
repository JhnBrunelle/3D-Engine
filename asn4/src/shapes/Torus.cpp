#include <vector>
#include "Torus.hpp"

#define RES 45

using namespace std;

void Torus::createInitialCircle(){
	Coord3 initialPoint(0.0, 0.0, innerR);	// First point
	circle.push_back(initialPoint);

	// Rotate the initial point around the X axis
	for(int i = 1; i < RES; ++i){
		initialPoint = initialPoint.xRotate(angle);
		circle.push_back(initialPoint);
	}

	// Translate to the outer radius, into position 
	for(int j = 0; j < RES; ++j){
		circle[j] = circle[j].translate(Coord3(0,0, outerR));
	}
}

void Torus::createOTube(){
	vector<Coord3> tempCircle;

	// Rotate Around the Y-Axis
	for(int i = 0; i < circle.size(); ++i){
		tempCircle.push_back(circle[i].yRotate(angle));
	}

	// Finish Connecting the circles
	for(int i = 0; i < RES; i++){

		for(int j = 1; j < RES; ++j){
			addFace(PolyFill(tempCircle[j-1],circle[j],circle[j-1]));
      		addFace(PolyFill(circle[j],tempCircle[j-1],tempCircle[j]));
		}

		addFace(PolyFill(tempCircle[RES-1],circle[0],circle[RES-1]));
    	addFace(PolyFill(circle[0],tempCircle[RES-1], tempCircle[0]));

		// Move the current sphere line to the current circle, and rotate
		for(int k = 0; k < RES; ++k){
			circle[k] = tempCircle[k];
			tempCircle[k] = tempCircle[k].yRotate(angle);
		}

	
	}

}

Torus::Torus(double inner, double outer){


	// Calculate the number of divisions
	angle = 360 / RES;

	// Assign private variables
	innerR = inner;
	outerR = outer;

	this->createInitialCircle();

	this->createOTube();



}