#pragma once
#include "../utils/Coord3.hpp"


/**
 * A light source in the scene, which adds an intensity factor
 * Subclass of Coord3 
 */
 class Light: public Coord3{
 private:
    
 public:
   /*
   * Creates an empty light source at 0, 0, 0
   */

   double intensity;  // The intensity of the light
   Light();


   /**
	 * A Parametric contructor
	 * double xC (in) - X coordinate
	 * double yC (in) - Y coordinate
	 * double zC (in) - Z coordinate
	 * Returns a coordinate
	 */
   Light(double,double,double);
   
   /**
    * Returns the position of the light
    */
   Light getPosition();

   /**
    * Sets the intensity % of the light
    * double (in) - 0 to 1 value indicating percent brightness
    */
   void setIntensity(double);

  /**
    * returns intensity % of the light
    * double (out) - 0 to 1 value indicating percent brightness
    */
   double getIntensity();
 };