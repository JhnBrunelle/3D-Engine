/**
 * GraphicsWindow.hpp
 * Header file for the GraphicsWindow class
 * 
 * By: Johnathan Brunelle
 * 01/18/2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <math.h>

// Defaults for a new Window
const int DEFAULT_X = 0;
const int DEFAULT_Y = 0;
const int DEFAULT_WIDTH = 512;
const int DEFAULT_HEIGHT = 512;

class GraphicsWindow {

public:

	/*
	 * Default constructor for Graphics Window
	 * returns GraphicsWindow Object
	 */
	GraphicsWindow();

	/*
	 * User constructor for Graphics Window
	 * int x - initial x position
	 * int y - initial y position
	 * int width - width of window
	 * int height - height of window
	 * returns GraphicsWindow Object
	 */
	GraphicsWindow (int x, int y, int width, int height);


	/**
	 * Shows the window on screen, and draws the content to the graphics container
	 * also attaches the key listener
	 * returns void
	 */
	void openWindow();



	/**
	 * Closes the window
	 * returns void
	 */
	void closeWindow();



private:

	Display *disp;			// The Main Display
	int screen;				// Screen Number
	Window rootWindow;		// Root Window object
	Window mainWindow;		// Main Window object
	GC graphicsContainer;	// Holds the graphics of the image
	int black;				// The color black, from the screen


	/**
	 * Draws a single pixel to the graphics container
	 * int x - x coord of pixel
	 * int y - y coord of pixel
	 * int color - color of pixel
	 * returns void
	 */
	void drawPixel(int x, int y, int color);

	/**
	 * Creates a new x11 window, with user's parameters
	 * int x - initial x position 
	 * int y - intial y position 
	 * int width - width of window 
	 * int height - height of window 
	 * int border - border width of window 
	 * string title - title of window
	 * returns void 
	 */
	void createNewWindow(int x, int y, int width, int height, int border);

	/**
	 * Creates a new display that serves as a connection to the Xserver,
	 * and assigns it to the GraphicWindow's display
	 * void
	 */
	void setDisplayAsDefault();

	/**
	 * An implementation of Bresenham's line drawing algorithm that covers all
	 * possible quadrants
	 * int x1 - first x point
	 * int x2 - second x point
	 * int y1 - first y point
	 * int y2 - second y point
	 * returns void
	 */
	void Bresenham(int x1, int y1, int x2, int y2);

	/**
	 * Draws a line, further extending Bresenham's algorithm
	 * int x1 - first x point
	 * int x2 - second x point
	 * int y1 - first y point
	 * int y2 - second y point
	 * int type - whehter it's a high quatrant line 1, or a low quatrant line 0
	 * returns void
	 */
	void drawLine(int x1, int y1, int x2, int y2, int type);


	/**
	 * Draws the sample code provided by the prof. Can be overriden later with
	 * a different draw method
	 * returns void
	 */
	void drawSample();
};