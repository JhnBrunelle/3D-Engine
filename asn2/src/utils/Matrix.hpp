#pragma once
#include <vector>
#include "Coord3.hpp"

#define PI 3.14159	// PI constant

/**
 * Custom matrix class, since I wasn't able to get the provided one working
 */
class Matrix {
private:

	/**
	 * Underlying data structure for the matrix, assuming it's always under 4x4, since it's a 3D space
	 */
	double matrix[4][4];

public:
	int length;
	int width;

	/**
	 * Default constructor for Matrix
	 */
	Matrix(int n, int m);

	/**
	 * Converts a Coordinate3 to Matrix
	 * coord (in) Coordinate to convert
	 * returns a matrix with coordinate
	 */
	static Matrix Coord3ToMatrix(Coord3 coord);

	/**
	 * Converts a Matrix to Coordinate
	 * 
	 */
	static Coord3 toCoord3(Matrix mat);

	/**
	 * Gets the rotation matrix based off an angle,
	 * along a specific axis
	 * char axis (in) - Axis to rotate on
	 * double angle (in) - Angle to rotate
	 * returns a rotation matrix 
	 */
	static Matrix getRotation(char, double angle);

	/**
	 * Checks if two matrices are equal size
	 * newMat (in) - matrix to compare
	 * returns boolean
	 */
	bool areEqualSize(Matrix& newMat);

	// Defines the operations that can be performed on the matrix
	Matrix operator-(Matrix& operand);
	Matrix operator*(Matrix& operand);
	double* operator[](int);


		
};
