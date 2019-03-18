#include <vector>
#include <iostream>
#include <cstdio>

#include "../utils/Line.hpp"
#include "Shape.hpp"



// Default constructor for Shape
// Shape::Shape():lines(){

// }

// Default constructor for Shape, using polygons 
Shape::Shape(): polygons(){

	// Toggle color RGB flags of the XColor
	color.flags = DoRed | DoGreen | DoBlue;
}

// Add a face to the shape
void Shape::addFace(PolyFill face){

	// Add to the front, no need to sort
	if(polygons.size() == 0){
		polygons.push_back(face);
	}
	double cur= polygons[0].getCenterCoord().z;
	double faceDepth = face.getCenterCoord().z;

	// Inorder to ensure correct shading, we need to sort the faces
	// Iterate through triangles to sort
	for(std::vector<PolyFill>::iterator i = polygons.begin(); i != polygons.end(); ++i){
		
		// if at the correct position, then insert 
		if (cur > faceDepth){
			polygons.insert(i, face);
			return;
		} else {
			// next depth
			cur = i->getCenterCoord().z;
		}

	}

	// Add face to the polygons collection
	polygons.push_back(face);
	
}

std::vector<PolyFill> Shape::getFaces(){	
	return polygons;
}



// Add an edge to the shape
void Shape::addLine(Line l){
	lines.push_back(l);
}

// Return the lines
std::vector<Line> Shape::getLines(){
	return lines;
}


// Rotates the Shape
void Shape::rotate(char axis, double angle){

	// Rotate on the specific Axis
	switch(axis){
		case 'x':
			for(int i = 0; i < polygons.size(); i++){
				polygons[i] = polygons[i].xRotate(angle);
			}
			break;
		case 'y':
			for(int i = 0; i < polygons.size(); i++){
				polygons[i] = polygons[i].yRotate(angle);
			}
			break;
		case 'z':
			for(int i = 0; i < polygons.size(); i++){
				polygons[i] = polygons[i].zRotate(angle);
			}
			break;
		default:
			std::cout << "Needs an Axis\n";

	}
}

// Translate the lines
void Shape::translate(Coord3 offset){

	// Translate each line
	for(int i = 0; i < polygons.size(); i++){
		polygons[i] = polygons[i].translate(offset);
	}

}

void Shape::setColor(unsigned short r, unsigned short g, unsigned short b){
	this->setRed(r);
	this->setBlue(b);
	this->setGreen(g);
}

XColor Shape::getColor(){
	return color;
}

unsigned short Shape::getRed(){
	return color.red;
}

unsigned short Shape::getBlue(){
	return color.blue;
}

unsigned short Shape::getGreen(){
	return color.green;
}

void Shape::setRed(unsigned short redNum){
	this->color.red = redNum;
}

void Shape::setBlue(unsigned short blueNum){
	this->color.blue = blueNum;
}

void Shape::setGreen(unsigned short greenNum){
	this->color.green = greenNum;
}

