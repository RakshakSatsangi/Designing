#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <GL/glut.h>  	// GLUT, includes glu.h and gl.h
#include <math.h>     	// Needed for sin, cos
#include <pthread.h>
#include <vector>
#include <string>

using namespace std;	

class window{
public:
	window(){
		title = "Screen Saver";
		windowWidth  = 640;
		windowHeight = 480;
		windowPosX   = 50; 
		windowPosY   = 50; 
		initWindow();
	}
	const char * title;  		// Windowed mode's title
	int windowWidth;	// Windowed mode's width
	int windowHeight;	// Windowed mode's height
	int windowPosX;		// Windowed mode's top-left corner x
	int windowPosY;		// Windowed mode's top-left corner y
	//GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;	// Projection clipping area
	void initWindow()
	{
		glutInitWindowSize(windowWidth, windowHeight);		// Initial window width and height
		glutInitWindowPosition(windowPosX, windowPosY);		// Initial window top-left corner (x, y)
		glutCreateWindow(title);							// Create window with given title
		/*
		glutReshapeFunc(reshape);
		glViewport(0, 0, windowWidth, windowHeight);
		clipAreaXLeft   = -1.0;
		clipAreaXRight  = 1.0;
		clipAreaYBottom = -1.0;
		clipAreaYTop    = 1.0;
		*/
	}
	/*
	void reshape(GLsizei width, GLsizei height) {
		// Compute aspect ratio of the new window
		if (height == 0) height = 1;                // To prevent divide by 0
		GLfloat aspect = (GLfloat)width / (GLfloat)height;

		// Set the viewport to cover the new window
		glViewport(0, 0, width, height);

		// Set the aspect ratio of the clipping area to match the viewport
		glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
		glLoadIdentity();             // Reset the projection matrix
		if (width >= height) {
		clipAreaXLeft   = -1.0 * aspect;
		clipAreaXRight  = 1.0 * aspect;
		clipAreaYBottom = -1.0;
		clipAreaYTop    = 1.0;
		} else {
		clipAreaXLeft   = -1.0;
		clipAreaXRight  = 1.0;
		clipAreaYBottom = -1.0 / aspect;
		clipAreaYTop    = 1.0 / aspect;
		}
		gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
	}
	*/
};
