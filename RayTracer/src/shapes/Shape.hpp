#pragma once
#include <vector>
#include "../utils/Line.hpp"
#include "../utils/PolyFill.hpp"
#include "../utils/Coord3.hpp"

/**
 * The Shape class defines the base class for a shape.
 * A shape itself cannot be used, it needs to defined by a subclass
 */
class Shape {

protected:
	std::vector<Line> lines;	// Stores the lines of a shape
	std::vector<PolyFill> polygons;		// Stores the Faces of PolyFills of the shape
	XColor color;						// Color of the shape
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
	 * Add a face to the shape, and sort it by it's z position
	 * to ensure correct shading
	 * PolyFill (in) - a PolyFill face
	 */
	void addFace(PolyFill pf);

	/**
	 * Returns a vector containing the edges
	 */
	std::vector<Line> getLines();

	/**
	 * Returns a vector containing the faces
	 */
	std::vector<PolyFill> getFaces();

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

	/**
	 * Functions to set the specific RGB values, each take in a value from 0 - 255
	 */
	void setRed(unsigned short);
	void setBlue(unsigned short);
	void setGreen(unsigned short);

	/**
	 * Returns a specific RGB value
	 */
	unsigned short getRed();
	unsigned short getBlue();
	unsigned short getGreen();

	/**
	 * Set the color
	 * red, green, blue - between 0-255
	 */
	void setColor(unsigned short red, unsigned short green, unsigned short blue);

	/*
	 * Getter for the object colour
	 * Returns an X11 Color
	 * */
	XColor getColor();
	

};