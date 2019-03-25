#pragma once

#include <X11/Xlib.h>
#include "Line.hpp"
#include "Matrix.hpp"
#include "Coord3.hpp"
#include "../scene/Light.hpp"
/**
 * The PolyFill class describes a collection of points, forming a triangle
 * that can be drawn and shaded in.
 */
class PolyFill {
public:

  // The 3 verticies of the triangle
  Coord3 v1;
  Coord3 v2;
  Coord3 v3;

  // Bounding max and mins
  int xMin;
  int yMin;
  int xMax;
  int yMax;

  /*
   * Default constructor
   * v1, v2, v3 = Vertices of the polyfill
   * returns a new PolyFill object
   */
  PolyFill(const Coord3 &v1, const Coord3 &v2, const Coord3 &v3);
  
  /**
   * Returns the centre coordinate of the PolyFill
   * Returns Coord3 - Centre coordinate
   */
  Coord3 getCenterCoord();

  /**
   * Translate a PolyFill
   * Coord3 (in) - coord to move by
   * returns a translate polyfill
   */
  PolyFill translate(Coord3);

   /**
   * rotate a PolyFill
   * double (in) - anlge to rotate by
   * returns a rotated polyfill
   */
  PolyFill xRotate(double);

   /**
   * rotate a PolyFill
   * double (in) - anlge to rotate by
   * returns a rotated polyfill
   */
  PolyFill yRotate(double);

  /**
   * rotate a PolyFill
   * double (in) - anlge to rotate by
   * returns a rotated polyfill
   */
  PolyFill zRotate(double);

  /**
   * Shades the face of the polyfill, dependent on the light provided
   * Light (in) - A light object, referencing the light to shade with
   * XColor (in) - A color to shade with
   * Returns an unsigned long, representing a color
   */
  unsigned long shade(Light lightSource, XColor color);


};
