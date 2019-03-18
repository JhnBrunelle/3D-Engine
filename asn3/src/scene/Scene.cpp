#include "Scene.hpp"


// Default empty constructor for Shapes
Scene::Scene(){ 
	Light light;	// Create an empty light source
}

// Returns all shapes in the scene
vector<Shape> Scene::getShapes(){
	// Return the Shape vector
	return shapes;
}

// Adds a new Shape to the scene
void Scene::addShape(Shape shape){

	// Add the Shape to the Shape Vector, if it has faces
	if (shape.getFaces().size() != 0){
		shapes.push_back(shape);
	}
}

// Sets the light source
void Scene::setLight(Light lightPos){
	light = lightPos;
}

Light Scene::getLightPos(){
	return light;
}


