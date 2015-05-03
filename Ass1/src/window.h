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
	window();
	const char * title;  		// Windowed mode's title
	int windowWidth;	// Windowed mode's width
	int windowHeight;	// Windowed mode's height
	int windowPosX;		// Windowed mode's top-left corner x
	int windowPosY;		// Windowed mode's top-left corner y
	
	void initWindow();
	void reshapeWindow();
};
