#include <stdlib.h>

#include "GraphicsWindow.hpp"
#include "scene/Scene.hpp"
#include "scene/Camera.hpp"
#include "shapes/Torus.hpp"
#include "shapes/Sphere.hpp"


int main(int argc, char *argv[]){

	// Make a New Window
	GraphicsWindow window (0,0,512,512);

	// Create a new Scene
	Scene scene;

	// Add Torus
	Torus ring(75.0, 250.0);
  	ring.translate(Coord3(0.0, 100.0, 800.0));
  	scene.addShape(ring);

	// Add Sphere
	Sphere ball(100.0);
	ball.rotate('y', 45.0);
	ball.translate(Coord3(0.0, -100.0, 800.0));
	scene.addShape(ball);

	// Assign a scene to the window
	window.scene = scene; 

	// Set the Camera
	window.camera = Camera(Coord3(0.0,0.0,0.0), 0.0, 0.0, 0.0);			// Base origin camera
	//window.camera = Camera(Coord3(-100.0,-500.0,0.0), 0.0, 0.0, 0.0);
	//window.camera = Camera(Coord3(0.0, 150.0, -800.0), 0.0, 180.0, 0.0);

	// Show the window
	window.openWindow(); 

	return 0;
}
