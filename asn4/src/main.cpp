#include <stdlib.h>

#include "GraphicsWindow.hpp"
#include "scene/Scene.hpp"
#include "scene/Camera.hpp"
#include "shapes/Torus.hpp"
#include "shapes/Sphere.hpp"
#include "shapes/Cone.hpp"
#include "scene/Light.hpp"

int main(int argc, char *argv[]){

	// Make a New Window
	GraphicsWindow window (0,0,512,512);

	// Create a new Scene
	Scene scene;

	// Create a sphere to add to the scene
	Sphere ball(175.0);
	ball.setColor(0, 0, 255);
  	ball.translate(Coord3(250.0, 100.0, -500.0));
  	scene.addShape(ball);

	// Add a torue to the scene
	Torus tor(75.0, 200.0);
	tor.setColor(150, 0, 0);
	tor.translate(Coord3(-25, -300.0, -600.0));
	scene.addShape(tor);

	// Add a cone to the scene
	Cone co(175.0, 150.0);
	co.setColor(100, 0, 150);
	co.rotate('x', 25);
	co.translate(Coord3(-200.0, 100.0, -500.0));
	scene.addShape(co);




	// Create a light source and set it's intensity
	Light ls(0.0, 100, -500.0);
	ls.setIntensity(1.0);
	scene.setLight(ls);

	// Assign a scene to the window
	window.scene = scene; 

	// Set the Camera
	window.camera = Camera(Coord3(0.0, 100.0, 100.0), 355.0, 0.0, 0.0);

	// Show the window
	window.openWindow(); 

	return 0;
}
