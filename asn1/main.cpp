/**
 * main.cpp
 * The main file that runs the graphical window
 * 
 * By: Johnathan Brunelle
 * 01/18/2019
 */

#include "GraphicsWindow.hpp"



int main() {	

	GraphicsWindow win (0,0,512,512);	// Create a new graphics window

	// Display the window
	win.openWindow();

	return 0;
}