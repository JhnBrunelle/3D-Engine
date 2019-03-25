#pragma once
#include <vector>
#include "../shapes/Shape.hpp"
#include "Light.hpp"

using namespace std;

/**
 * A scene represents a collection of Shapes, which will are present in the current
 * world/stage/scene or image. 
 *
 */

class Scene {
private:
	vector<Shape> shapes;	// Vector containing all the shapes
	Light light;			// The light object
public:
	
	/**
	 * Default constructor for creating an empty scene
	 */
	Scene();

	/**
	 * Returns a list of all the shapes
	 * vector (out) - vector of shapes
	 */
	vector<Shape> getShapes();

	/**
	 * Adds a shape to a scene
	 * Shape (input) - Shape to add to the scene
	 * void output
	 */
	void addShape(Shape);

	/**
	 *  Adds a light to the scene
	 * Light (input) - a Light to add to the scene
	 */
	void setLight(Light lightPos);

	/**
	 * Returns the position of the Light coordinate
	 * Returns Light Object
	 */
	Light getLightPos();

};