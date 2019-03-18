#pragma once
#include <vector>
#include "../utils/Line.hpp"

/**
 * The Shape class defines the base class for a shape.
 * A shape itself cannot be used, it needs to defined by a subclass
 */
class Shape {

protected:
	std::vector<Line> lines;	// Stores the lines of a shape

public:

	/**
	 * Default shape constructor
	 */
	Shape();

	/**
	 *	Add an line of the shape
	 * 	Line l (in) - Line to add
	 */
	void addLine(Line l);

	/**
	 * Returns a vector containing the edges
	 */
	std::vector<Line> getLines();
	

	/**
	 * Rotate the shape
	 * char axis (in) - x, y, z axis to rotate in
	 * double axis (in) - angle to rotate by
	 */
	void rotate(char axis, double angle);

	
	/**
	 * Translate a shape, based on an offset
	 */
	void translate(Coord3 offset);

};