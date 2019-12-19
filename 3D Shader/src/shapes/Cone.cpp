#include <cstdio>
#include <cmath>
#include <vector>
#include "Cone.hpp"

#define RES 45	// The Resolution of the Cone (divisions per Cone)
using namespace std;


Cone::Cone(double height, double r){
  

  const double angle = 360.0 / RES;

  Coord3 coord(0.0,0.0, r);    // Create the top point of the Cone
  vector<Coord3> rad;          // Radius of the current level 
  rad.push_back(coord);        // Add it to the radius circle
  

  // Rotate around, to get the points
  for(int i = 1; i < RES; i++){
    
    // Rotate around circle
    coord = coord.yRotate(-angle);

    // add to the points
    rad.push_back(coord);
  }

  Coord3 peak(0.0,height,0.0);  // peak of the cone
  addFace(PolyFill(rad[RES-1], rad[0], peak));
  
  for(int i = 1; i < RES; i++){

    // Add side faces
    addFace(PolyFill(rad[i-1], rad[i], peak));

  }
}
