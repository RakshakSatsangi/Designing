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

/* check collision among balls */
bool collBalls(ball *a, ball *b)
{
	vec * atempr=a->r->add(a->v);
	vec * btempr=b->r->add(b->v);
	GLfloat d = atempr->dist(btempr);
	vec * L1 = atempr->subtract(btempr);
	vec * l = L1->scale(1.0f/(L1->length()));
	GLfloat u1 = l->dot(a->v->subtract(b->v));
	vec * u = l->scale(u1);
	if(d<(a->radius+b->radius) && u1<0.0f && a->index!=b->index && d>0.0f)
	{
		a->v = a->v->subtract(u);
		a->msgv = b->v->add(u); // 1-1 synchronisation signal velocity to ball 'b'
		
		d = a->r->dist(b->r);
		L1 = a->r->subtract(b->r);
		l = L1->scale(1.0f/(L1->length()));
		a->r = a->r->subtract(l->scale(d-a->radius-b->radius));
		return true;
	}
	return false;
}

// Checking collision with walls
bool collWall(ball *a)
{
	vec * atempr=a->r->add(a->v);
	bool b = false;	
	if(atempr->xCoordinate > a->ballXMax) 
	{
		b = true;
		a->v->xCoordinate = -(a->v->xCoordinate);
		a->r->xCoordinate = a->ballXMax;
	}
	else if(atempr->xCoordinate < a->ballXMin)
	{
		b = true;
		a->v->xCoordinate = -(a->v->xCoordinate);
		a->r->xCoordinate = a->ballXMin;
	}
	if(atempr->yCoordinate > a->ballYMax)
	{
		b = true;
		a->v->yCoordinate = -(a->v->yCoordinate);
		a->r->yCoordinate = a->ballYMax;
	}
	else if(atempr->yCoordinate < a->ballYMin)
	{
		b = true;
		a->v->yCoordinate = -(a->v->yCoordinate);
		a->r->yCoordinate = a->ballYMin;
	}
	return b;
}

/* Updates speed of ball due to gravity */
void gravitySpeedUpdate(ball * a, char x, GLfloat grav)
{
	switch(x)
	{
		case 'l':
			a->v->xCoordinate -= grav;
			break;
		case 'r':
			a->v->xCoordinate += grav;
			break;
		case 'd':
			a->v->yCoordinate -= grav;
			break;
		case 'u':
			a->v->yCoordinate += grav;
			break;
	}
	
}

