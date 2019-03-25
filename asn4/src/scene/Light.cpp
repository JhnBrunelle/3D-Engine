#include "Light.hpp"

// Default constructor
Light::Light(){
    
}

// Create a new coordinate with specific inputs
Light::Light(double xC, double yC, double zC){

		// Coordinates for each
	this->x = xC;
	this->y = yC;
	this->z = zC;

	this->intensity = 1.0;	// Default 100%
}

// Sets the intensity of the light (needs to be set before bound to a scene)
void Light::setIntensity(double in){
	this->intensity = in;
}

// Returns the intensity of the light
double Light::getIntensity(){
	return this->intensity;
}