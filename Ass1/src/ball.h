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
class vec{
public:
	vec(GLfloat x, GLfloat y);
	GLfloat xCoordinate;
	GLfloat yCoordinate;
	GLfloat dot(vec * v);
	vec * scale(GLfloat c);
	vec * add(vec * v);
	vec * subtract(vec * v);
	GLfloat length();
	GLfloat dist(vec * v);
};

class ball{
public:
	ball(GLfloat centerX, GLfloat centerY, GLfloat speedX, GLfloat speedY); 
	vec* v;
	vec * pv;
	vec* msgv; 
	vec* r;
	
	bool isCollide;
	GLfloat colR;
	GLfloat colG;
	GLfloat colB;
	GLfloat radius;
	GLfloat ballXMax;
	GLfloat ballYMax;
	
	
	GLfloat ballXMin;
	GLfloat ballYMin;
	int index;
};
