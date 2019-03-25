#include <cmath>
#include "Matrix.hpp"


// Empty Array Constructor
Matrix::Matrix(int x, int y){

	// Assign size
	length = x;
	width= y;

	// Fill the Array with zeroes
	for(int i = 0; i < length; i++){
		for(int j = 0; j < width; j++){
			matrix[i][j] = 0.0;
		}
	}
}


// Converts a coordinate to a Matrix
Matrix Matrix::Coord3ToMatrix(Coord3 coord){
		Matrix newMat(3,1);	//Create a 3x1 matrix
		newMat[0][0] = coord.x;
		newMat[1][0] = coord.y;
		newMat[2][0] = coord.z;
		return newMat;
}

Coord3 Matrix::toCoord3(Matrix mat){
		// Ensure that it's the correct length
		if(mat.length == 3 && mat.width == 1){
			return Coord3(mat[0][0], mat[1][0], mat[2][0]);
		} else {
			return Coord3(0.0,0.0,0.0);
		}
}


// Returns the rotation matrix for a specific axis
Matrix Matrix::getRotation(char axis, double angle){
	angle = (angle * PI) / 180.0;	// Normalize angle

	// Define transformation matrix depending on which axis
	std::vector< std::vector<double>> T;
	switch(axis){
		case 'x':
			T = {
			{ 1, 0, 0 },
			{ 0, cos(angle), -1.0*sin(angle)},
			{ 0, sin(angle), cos(angle) }
			};
			break;
		case 'y':
			T = {
			{ cos(angle), 0, sin(angle)},
			{ 0, 1, 0 },
			{ -1.0*sin(angle), 0, cos(angle)}
			};
			break;

		case 'z':
			T = {
			{ cos(angle), -1.0*sin(angle), 0},
			{ sin(angle), cos(angle), 0},
			{ 0, 0, 1 }
			};
			break;

	}

	// Apply transformation to the matrix and return it
	Matrix newMat(3,3);
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			newMat[i][j] = T[i][j];
		}
	}

	return newMat;

}


bool Matrix::areEqualSize(Matrix& newMat){
	if(length == newMat.length && width == newMat.width){
		return true;
	} else {
		return false;
	}
}


// Create a Subtraction operator
Matrix Matrix::operator-(Matrix& operand){
	
	// Check that length = widht
	if(!this->areEqualSize(operand)){
		return Matrix(0,0);	
	}

	// Create a new empty matrix
	Matrix diffMatrix(length, width);

	// Subtract every value from it's matching value
	for(int i = 0; i < length; i++){
		for(int j = 0; j < width; j++){
			diffMatrix[i][j] = matrix[i][j] - operand[i][j];
		}
	}

	// Return the difference
	return diffMatrix;
	

}

// Multiply 2 matricies together
Matrix Matrix::operator*(Matrix& operand){
	
	// The width of the first array must equal the length of the second
	if(width != operand.length){
		return Matrix(0,0);
	}

	Matrix prodMatrix(length, operand.width);

	// Multiple in order
	for(int i = 0; i < prodMatrix.length; i++){
		for(int j = 0; j < prodMatrix.width; j++){
			for(int k = 0; k < operand.length; k++){
				prodMatrix[i][j] = prodMatrix[i][j] + matrix[i][k] * operand[k][j];
			}
		}
	}

	return prodMatrix;

}

// Returns the vector located at index i
double* Matrix::operator[](int i){
	return matrix[i];
}


