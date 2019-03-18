#include "Scene.hpp"


// Default empty constructor for Shapes
Scene::Scene(){ 

}

// Returns all shapes in the scene
vector<Shape> Scene::getShapes(){
	// Return the Shape vector
	return shapes;
}

// Adds a new Shape to the scene
void Scene::addShape(Shape shape){

	// Add the Shape to the Shape Vector, if it has Lines
	if (shape.getLines().size() != 0){
		shapes.push_back(shape);
	}
}


