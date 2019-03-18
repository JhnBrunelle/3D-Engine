#include "Shape.hpp"

using namespace std;

class Torus: public Shape{
private:
	double angle;		// Angle of each division
	double innerR;		// Tube Radius
	double outerR;		// Middle Radius

	// Inner circle
	vector<Coord3> circle;	// Initial Circle (tube)

	/**
	 * Creates the initial Tube circle
	 */
	void createInitialCircle();

	/**
	 * Create all the coordinates for the Torus, by rotating
	 * around the Y axis, copying the initial circle
	 * also Adds all of the edges
	 * returns nothing
	 */
	void createOTube();

public:
	
	/**
	 * Constructor for a Torus
	 * double innerR (in) - radius of the inner circle
	 * double outerR (in) - radius of the middle circle (outer) 
	 */
	Torus(double innerR, double outerR);
};
