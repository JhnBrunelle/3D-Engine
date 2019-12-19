#pragma once
#include "Shape.hpp"
#include "../utils/Coord3.hpp"

using namespace std;
/*
 * Represents a sphere object in 3D space
 * */
class Sphere: public Shape {
private:
	double angle; // Angle of the circle
	double radius;	// The Radius of the circle

	vector<Coord3> circle;
	vector<Coord3> sphere;
	/**
	 * Creates the coordinates for the sphere
	 */
	void createSphereCoords(double radius);

	/**
	 * Creates and adds the edges of the spheres to the underlying shape
	 */
	void createSphereLines();

public:
	/*
	 * Creates a new sphere with given radius. The sphere is has its centre at the origin.
	 * */
	Sphere(double radius);


};

