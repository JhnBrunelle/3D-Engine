#pragma once
#include "Coord3.hpp"

/**
 * A line of the shape, made up of two points
 */
class Line {
public:
	Coord3 a;	// First coord of line segment
	Coord3 b;	// Second coord of line segment

	/**
	 * Constructor of a line
	 * a,b Coord - End points of the line
	 * returns a new lines
	 */
	Line(Coord3 a, Coord3 b);

	/**
	 * Rotates a line over the x axis
	 * angle - Angle to rotate by
	 * returns a new rotated line
	 */
	Line xRotate(double angle);

	/**
	 * Rotates a line over the y axis
	 * angle - Angle to rotate by
	 * returns a new rotated line
	 */
	Line yRotate(double angle);

	/**
	 * Rotates a line over the z axis
	 * angle - Angle to rotate by
	 * returns a new rotated line
	 */
	Line zRotate(double angle);

	/**
	 * Translates a line over an offset
	 * angle - offset move by
	 * returns a new translated line
	 */
	Line translate(Coord3 offset);

	


};
