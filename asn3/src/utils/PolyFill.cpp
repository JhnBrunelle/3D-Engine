#include <cmath>
#include "PolyFill.hpp"

/**
 * The Default constructor for a PolyFill
 */
PolyFill::PolyFill(const Coord3 &v1, const Coord3 &v2, const Coord3 &v3){

  // Set the vertices 
  this->v1 = v1;
  this->v2 = v2;
  this->v3 = v3;

  // Set the bounds of the PolyFill
  this->xMin = std::min(v1.x, std::min(v2.x, v3.x));
  this->yMin = std::min(v1.y, std::min(v2.y, v3.y));

  this->xMax = std::max(v1.x, std::max(v2.x, v3.x));
  this->yMax = std::max(v1.y, std::max(v2.y, v3.y));
}


// Gets the centre coordinate
Coord3 PolyFill::getCenterCoord(){

  double x = (v1.x + v2.x + v3.x)/3.0;
  double y = (v1.x + v2.x + v3.x)/3.0;
  double z = 0;

  if(v1.z > v2.z){
    z = v1.z;
  } else if(v2.z > v3.z){
    z = v2.z;
  } else {
    z = v3.z;
  }

  return Coord3(x, y, z);
}

// Translate the polyfill
PolyFill PolyFill::translate(Coord3 coord){
  return PolyFill(v1.translate(coord), v2.translate(coord), v3.translate(coord));
}

// rotate the polyfill
PolyFill PolyFill::xRotate(double angle){
  return PolyFill(v1.xRotate(angle), v2.xRotate(angle), v3.xRotate(angle));
}

// rotate the polyfill
PolyFill PolyFill::yRotate(double angle){
  return PolyFill( v1.yRotate(angle), v2.yRotate(angle), v3.yRotate(angle));
}

// rotate the polyfill
PolyFill PolyFill::zRotate(double angle){
  return PolyFill(v1.zRotate(angle), v2.zRotate(angle), v3.zRotate(angle));
}

unsigned long PolyFill::shade(Light ls, XColor color){

  // Calculate the centre point of the 
  Coord3 center = getCenterCoord();

  // Get two vectors on the plane
  Coord3 u(v1.x - v2.x, v1.y - v2.y, v1.z- v2.z);
  Coord3 v(v3.x- v2.x, v3.y - v2.y, v3.z-v2.z);

  // Cross product to get the normal of the plane
  Coord3 norm = u.crossProduct(v);

  // Get the dot product
  double dp = (norm - center).dotProduct(ls - center);
  if(dp <= 0.0) dp = 0.0;      // Ensure it stays positive

  // Get the magnitude with the light source
  double mag = (norm - center).mag() * (ls - center).mag();

  // Calculate the coefficient to shade with
  double c = (acos(dp/mag)*2/ PI);

  XColor shadedColor;
  shadedColor.flags = DoRed | DoGreen | DoBlue; // Set RGB flag of the color

  // Apply colors
  shadedColor.red = color.red * c * ls.getIntensity();
  shadedColor.blue = color.blue * c * ls.getIntensity();
  shadedColor.green = color.green * c * ls.getIntensity();

  // // Convert XColor to an unsigned int. Need to shift RGB into binary positions
  unsigned long colorLong = shadedColor.blue;
  colorLong += shadedColor.green << 8;
  colorLong += shadedColor.red << 16;

  return colorLong;
}
