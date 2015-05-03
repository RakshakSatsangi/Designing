#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <GL/glut.h>  	// GLUT, includes glu.h and gl.h
#include <math.h>     	// Needed for sin, cos
#include <pthread.h>
#include <vector>
#include <string>
#include "ball.h"
#include "gui.h"
#include "window.h"
#include "physics.h"

	window::window(){
		title = "Bouncing Ball (2D)"; 
		windowWidth  = 640;
		windowHeight = 480;
		windowPosX   = 50; 
		windowPosY   = 50; 
		initWindow();
	}
	// initialising window
	void window::initWindow()
	{
		glutInitWindowSize(windowWidth, windowHeight);		// Initial window width and height
		glutInitWindowPosition(windowPosX, windowPosY);		// Initial window top-left corner (x, y)
		glutCreateWindow(title);							// Create window with given title
	}
	// reshape window on Exit FULL screen mode
	void window::reshapeWindow()
	{
		glutPositionWindow(windowPosX,windowPosY);
		glutReshapeWindow(windowWidth,windowHeight);
	}
	

