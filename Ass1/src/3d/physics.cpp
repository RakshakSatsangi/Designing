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
bool collBalls(ball *a, ball *b)
{
	GLfloat d = a->tempr->dist(b->tempr);
	vec * L1 = a->tempr->subtract(b->tempr);
	vec * l = L1->scale(1.0f/(L1->length()));
	GLfloat u1 = l->dot(a->v->subtract(b->v));
	vec * u = l->scale(u1);
	if(d<(a->radius+b->radius) && u1<0.0f && a->index!=b->index && d>0.0f)
	{
		a->v = a->v->subtract(u);
		b->v = b->v->add(u);
		a->tempr = a->r->add(a->v);
		b->tempr = b->r->add(b->v);
		
		 // debug
		u1*= l->dot(a->v->subtract(b->v));
		d = a->tempr->dist(b->tempr);
		if(u1>0.0f || d<(a->radius+b->radius))
		{
			//cout<<"jadoo"<<endl;
		}
		return true;
	}
	return false;
}

// Checking collision with walls
bool collWall(ball *a)
{
	
	bool b = false;	
	if(a->tempr->xCoordinate > a->ballXMax) 
	{
		b = true;
		a->v->xCoordinate = -(a->v->xCoordinate);
		a->r->xCoordinate = a->ballXMax;
	}
	else if(a->tempr->xCoordinate < a->ballXMin)
	{
		b = true;
		a->v->xCoordinate = -(a->v->xCoordinate);
		a->r->xCoordinate = a->ballXMin;
	}
	if(a->tempr->yCoordinate > a->ballYMax)
	{
		b = true;
		a->v->yCoordinate = -1.0f*(a->v->yCoordinate);
		a->r->yCoordinate = a->ballYMax;
	}
	else if(a->tempr->yCoordinate < a->ballYMin)
	{
		b = true;
		a->v->yCoordinate = -1.0f*(a->v->yCoordinate);
		a->r->yCoordinate = a->ballYMin;
	}
	if(a->tempr->zCoordinate > a->ballZMax)
	{
		b = true;
		a->v->zCoordinate = -1.0f*(a->v->zCoordinate);
		a->r->zCoordinate = a->ballZMax;
	}
	else if(a->tempr->zCoordinate < a->ballZMin)
	{
		b = true;
		a->v->zCoordinate = -1.0f*(a->v->zCoordinate);
		a->r->zCoordinate = a->ballZMin;
	}
	a->tempr = a->r->add(a->v);
	//do{
		//a->tempr = a->tempr->add(a->v);
	//}while(a->tempr->xCoordinate > a->ballXMax || a->tempr->xCoordinate < a->ballXMin || a->tempr->yCoordinate > a->ballYMax || a->tempr->yCoordinate < a->ballYMin);
	return b;
}
