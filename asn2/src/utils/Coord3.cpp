#include "Matrix.hpp"
#include "Coord3.hpp"


// default constructor for a Coord
Coord3::Coord3(){

	// Creates an empty coordinate
	x = 0.0;
	y = 0.0;
	z = 0.0;
	
}

// Create a new coordinate with specific inputs
Coord3::Coord3(double xC, double yC, double zC){

	// Coordinates for each
	x = xC;
	y = yC;
	z = zC;
}

// Translate a point
Coord3 Coord3::translate(Coord3 offset){
	return Coord3(x + offset.x, y + offset.y, z + offset.z);
}

// Rotate X
Coord3 Coord3::xRotate(double angle){

	// Convert to a matrix, and rotate along Y
	Matrix coord = Matrix::Coord3ToMatrix((*this));
	Matrix newX = Matrix::getRotation('x',angle) * coord;

	return Coord3(newX[0][0], newX[1][0], newX[2][0]);
}

// Rotate Y
Coord3 Coord3::yRotate(double angle){

	// Convert to a matrix, and rotate along Y
	Matrix coord = Matrix::Coord3ToMatrix((*this));
	Matrix newY = Matrix::getRotation('y',angle) * coord;

	return Coord3(newY[0][0], newY[1][0], newY[2][0]);
}

// Rotate Z
Coord3 Coord3::zRotate(double angle){

	// Convert to a matrix, and rotate along Z
	Matrix coord = Matrix::Coord3ToMatrix((*this));
	Matrix newZ = Matrix::getRotation('z',angle) * coord;

	return Coord3(newZ[0][0], newZ[1][0], newZ[2][0]);
}


// Create a Subtraction operator
Coord3 Coord3::operator-(Coord3& operand){
	
	double newX = x - operand.x;
	double newY = y - operand.y;
	double newZ = z - operand.z;

	return Coord3(newX, newY, newZ);
	
}

// Create a Subtraction operator
Coord3 Coord3::operator*(Coord3& operand){
	
	double newX = x * operand.x;
	double newY = y * operand.y;
	double newZ = z * operand.z;

	return Coord3(newX, newY, newZ);
	
}