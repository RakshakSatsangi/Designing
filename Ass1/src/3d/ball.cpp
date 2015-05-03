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

// 3d
class vec{
public:
	vec(GLfloat x, GLfloat y, GLfloat z)
	{
		xCoordinate = x;
		yCoordinate = y;
		zCoordinate = z;
	}
	GLfloat xCoordinate;
	GLfloat yCoordinate;
	GLfloat zCoordinate;
	GLfloat dot(vec * v)
	{
		return ((this->xCoordinate)*(v->xCoordinate) + (this->yCoordinate)*(v->yCoordinate) + (this->zCoordinate)*(v->zCoordinate));
	}
	vec * scale(GLfloat c)
	{
		vec * temp = new vec((this->xCoordinate)*c, (this->yCoordinate)*c, (this->zCoordinate)*c);
		return temp;
	}
	vec * add(vec * v)
	{
		vec * temp = new vec(((this->xCoordinate) + (v->xCoordinate)), ((this->yCoordinate) + (v->yCoordinate)), ((this->zCoordinate) + (v->zCoordinate)));
		return temp;
	}
	vec * subtract(vec * v)
	{
		vec * temp = new vec(((this->xCoordinate) - (v->xCoordinate)), ((this->yCoordinate) - (v->yCoordinate)), ((this->zCoordinate) - (v->zCoordinate)));
		return temp;
	}
	GLfloat length()
	{
		return (sqrtf((this->xCoordinate*this->xCoordinate) + (this->yCoordinate*this->yCoordinate) + (this->zCoordinate*this->zCoordinate)));
	}
	GLfloat dist(vec * v)
	{
		vec * temp = this->subtract(v);
		return temp->length();
	}
};


class ball{
public:
	ball(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat speedX, GLfloat speedY, GLfloat speedZ){ // 3d
		v=new vec(speedX, speedY, speedZ); // 3d
		r=new vec(centerX, centerY, centerZ); // 3d
		tempr = r->add(v);
	}
	vec* v;
	vec* r;
	vec* tempr;
	bool isCollide;
	GLfloat colR;
	GLfloat colG;
	GLfloat colB;
	GLfloat radius;
	GLfloat ballXMax;
	GLfloat ballYMax;
	GLfloat ballZMax; // 3d
	
	GLfloat ballXMin;
	GLfloat ballYMin;
	GLfloat ballZMin; // 3d
	int index;
};
