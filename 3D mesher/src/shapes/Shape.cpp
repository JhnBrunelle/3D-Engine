#include <vector>
#include <iostream>

#include "../utils/Line.hpp"
#include "Shape.hpp"


// Default constructor for Shape
Shape::Shape():lines(){

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
			for(int i = 0; i < lines.size(); i++){
				lines[i] = lines[i].xRotate(angle);
			}
			break;
		case 'y':
			for(int i = 0; i < lines.size(); i++){
				lines[i] = lines[i].yRotate(angle);
			}
			break;
		case 'z':
			for(int i = 0; i < lines.size(); i++){
				lines[i] = lines[i].zRotate(angle);
			}
			break;
		default:
			std::cout << "Needs an Axis\n";

	}
}

// Translate the lines
void Shape::translate(Coord3 offset){

	// Translate each line
	for(int i = 0; i < lines.size(); i++){
		lines[i] = lines[i].translate(offset);
	}

}


