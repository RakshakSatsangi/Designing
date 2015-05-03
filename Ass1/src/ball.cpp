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

using namespace std;

	vec::vec(GLfloat x, GLfloat y)
	{
		xCoordinate = x;
		yCoordinate = y;
	}

	GLfloat vec::dot(vec * v)
	{
		return ((this->xCoordinate)*(v->xCoordinate) + (this->yCoordinate)*(v->yCoordinate));
	}
	vec * vec::scale(GLfloat c)
	{
		vec * temp = new vec((this->xCoordinate)*c, (this->yCoordinate)*c);
		return temp;
	}
	vec * vec::add(vec * v)
	{
		vec * temp = new vec(((this->xCoordinate) + (v->xCoordinate)), ((this->yCoordinate) + (v->yCoordinate)));
		return temp;
	}
	vec * vec::subtract(vec * v)
	{
		vec * temp = new vec(((this->xCoordinate) - (v->xCoordinate)), ((this->yCoordinate) - (v->yCoordinate)));
		return temp;
	}
	GLfloat vec::length()
	{
		return (sqrtf((this->xCoordinate*this->xCoordinate) + (this->yCoordinate*this->yCoordinate)));
	}
	GLfloat vec::dist(vec * v)
	{
		vec * temp = this->subtract(v);
		return temp->length();
	}




	ball::ball(GLfloat centerX, GLfloat centerY, GLfloat speedX, GLfloat speedY){
		v=new vec(speedX, speedY);
		r=new vec(centerX, centerY);
		pv = new vec(0.0,0.0);
	}
	
