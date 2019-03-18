#pragma once

/**
 * The Coord3 defines a class for defining 3 coordinates
 * in a 3D space. 
 */
class Coord3 {
public:
	double x;	// X coordinate
	double y;   // Y coordinate
	double z;   // Z coordinate

	/**
	 * The Default constructor
	 * Returns an empty coordinate (0,0,0)
	 */
	Coord3();
	
	/**
	 * Roates a coordinate around the  axis
	 * double offset(in) - The distance to move
	 * Returns the translated
	 */
	Coord3 translate(Coord3 offest);

	/**
	 * A Parametric contructor
	 * double xC (in) - X coordinate
	 * double yC (in) - Y coordinate
	 * double zC (in) - Z coordinate
	 * Returns a coordinate
	 */
	Coord3(double x, double y , double z);

	/**
	 * Roates a coordinate around the X axis
	 * double angle(in) - Angle to rotate
	 * Returns the rotated coordinate
	 */
	Coord3 xRotate(double angle);

	/**
	 * Roates a coordinate around the Y axis
	 * double angle(in) - Angle to rotate
	 * Returns the rotated coordinate
	 */
	Coord3 yRotate(double angle);

	/**
	 * Roates a coordinate around the Z axis
	 * double angle(in) - Angle to rotate
	 * Returns the rotated coordinate
	 */
	Coord3 zRotate(double angle);

	//Operators
	Coord3 operator-(Coord3& operand);
	Coord3 operator*(Coord3& operand);

};