#include "Line.hpp"
#include "Coord3.hpp"

// Constructor for a line
Line::Line(Coord3 aPt, Coord3 bPt){
	a = aPt;
	b = bPt;
}

// Rotate line along x axis
Line Line::xRotate(double angle){
	Coord3 aNew = a.xRotate(angle);
	Coord3 bNew = b.xRotate(angle);
	return Line(aNew, bNew);
}

// Rotate line along y axis
Line Line::yRotate(double angle){
	Coord3 aNew = a.xRotate(angle);
	Coord3 bNew = b.xRotate(angle);
	return Line(aNew, bNew);
}

// Rotate line along z axis
Line Line::zRotate(double angle){
	Coord3 aNew = a.xRotate(angle);
	Coord3 bNew = b.xRotate(angle);
	return Line(aNew, bNew);
}

// translate a line
Line Line::translate(Coord3 offset){
	Coord3 aNew = a.translate(offset);
	Coord3 bNew = b.translate(offset);
	return Line(aNew, bNew);
}
