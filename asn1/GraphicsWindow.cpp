/**
 * GraphicsWindow.cpp
 * Creates a graphics window class, with the ability to draw, lines, shapes,
 * and pixels
 *
 * See header file GraphicsWindow.hpp for documentation
 * 
 * By: Johnathan Brunelle
 * 01/18/2019
 */

#include "GraphicsWindow.hpp"


// Default constructor
GraphicsWindow::GraphicsWindow () {
	// Set display
	setDisplayAsDefault();


	// Create a new display with default parameters
	createNewWindow(DEFAULT_X,DEFAULT_Y,DEFAULT_WIDTH,DEFAULT_HEIGHT,1);

}

// Paramaterized Constructor
GraphicsWindow::GraphicsWindow (int x, int y, int width, int height) {
	// Set display
	setDisplayAsDefault();


	// Create a new display with user parameters
	createNewWindow(x,y,width,height,1);

}

void GraphicsWindow::setDisplayAsDefault(){

	disp = XOpenDisplay(getenv("DISPLAY"));		// Open a new display

	// Error opening display
	if (disp == NULL) {
		printf("An error occured opening the display\n");
		exit(1);
	}
}


void GraphicsWindow::createNewWindow(int x, int y, int width, int height, int border){

	// Set the screen as the current Display
	screen = DefaultScreen(disp);

	// Set the root window
	rootWindow = DefaultRootWindow(disp);

	// Set default black pixel
	black = BlackPixel(disp, screen);

	// Create a new x11 simple window
	mainWindow = XCreateSimpleWindow(disp, rootWindow, x, y, width, height, border, 
                            BlackPixel(disp, screen), WhitePixel(disp, screen));

	XStoreName(disp, mainWindow, "Graphics Window"); // Set window title

	// Create Graphics Container
	graphicsContainer = XCreateGC(disp, rootWindow, 0, NULL);

}


void GraphicsWindow::openWindow(){

	

	// Map window to display (show window on)
	XMapRaised(disp, mainWindow);


	//Select events for the window to listen to
	XSelectInput(disp, mainWindow, ExposureMask | ButtonPressMask | KeyPressMask);
	XEvent ev;	// Event to listen for


	// Run loop
	while (true) {

		XNextEvent(disp, &ev);	// Scan next event

		// Upon key press
		if (ev.type == KeyPress){
			char key[255];
			KeySym keyS;

			// Check for the q key
			if(XLookupString(&ev.xkey, key, 255, &keyS, 0) == 1){
				if (key[0] == 'q'){

					// Upon q close the window
					closeWindow();
					return;
				}
			}
		}

		// Upon exposing
		if (ev.type == Expose && ev.xexpose.count == 0) {

			// Draw the sample provided. This can be replaced later
			// for other applications
			drawSample();
			XFlush(disp);
		
		}
	}
  
}

void GraphicsWindow::closeWindow(){	
	XFreeGC(disp, graphicsContainer);	// Clear the graphics container
	XDestroyWindow(disp, mainWindow);   // Destory window
	XCloseDisplay(disp);                // Close the display
}


void GraphicsWindow::drawPixel(int x, int y, int color){

	// Set the color
	XSetForeground(disp, graphicsContainer, color);

	// Draw the point
	XDrawPoint(disp, mainWindow, graphicsContainer, x, y);
}


void GraphicsWindow::drawLine(int x1, int y1, int x2, int y2, int type){
	// Diference between x and ys
	int dx = x2 - x1;
	int dy = y2 - y1;

	// Staring point of the lines
	int m = 1;		// difference to apply to prev point (increasing or decreasing)
	int diff;		// The difference between two points

	// For a Low quarant line
	if(type == 0){

		// Check if y is increasing or decreasing
		if(dy < 0){
			dy *= -1;
    		m = -1;
  		}

  		diff = (2 * dy) - dx;
  		int y = y1;

  		// Draw pixels along the x line
  		for (int x = x1; x <=x2; x++){
  			drawPixel(x,y,black);
  			if(diff > 0) {
  				y += m;
  				diff -= 2* dx;
  			}

  			diff+= 2 *dy;
  		}

  	// For a High quadrant line	
	} else if( type == 1){

	  // Check if x is increasing or decreasing
	  if(dx < 0){
	    dx *= -1;	// Give negative difference
	    m = -1;
	  }

	  diff = (2 * dx) - dy;
	  int x = x1;

	  for(int y = y1; y <= y2; y++){
	    drawPixel(x, y, black);
	    if(diff > 0){
	      x += m;
	      diff -= 2 * dy;
	    }
	    diff += 2 * dx;
	  }

	}
}


void GraphicsWindow::Bresenham(int x1, int  x2, int y1, int y2){
  if(abs(y2 - y1) < abs(x2 - x1)){

  	// Low octant lines
    if(x1 > x2){
      drawLine(x2, y2, x1, y1, 0);
    }
    else {
      drawLine(x1, y1, x2, y2,0);
    }
  }

  // High octant lines
  else {
    if(y1 > y2){
      drawLine(x2, y2, x1, y1, 1);
    }
    else {
      drawLine(x1, y1, x2, y2, 1);
    }
  }
}

// Draw the sample code provided for Assignment 1
void GraphicsWindow::drawSample(){
	for( int a = 10; a < 300; a = a + 1 ) {
			double dt = 2.0 * M_PI / 200.0;
				for(double t = 0.0; t < 2.0 * M_PI; ){

				int x1 = 256 + (int)100.0*(1.5*cos(t) - cos(13.0*t));
				int y1 = 256 + (int)100.0*(1.5*sin(t) - sin(13.0*t));
 				t += dt;
				int x2 = 256 + (int)100.0*(1.5*cos(t) - cos(13.0*t));
				int y2 = 256 + (int)100.0*(1.5*sin(t) - sin(13.0*t));

				// Call Bresenham algorithm to draw the window
				Bresenham(x1, x2, y1, y2);
				}
			}

}
