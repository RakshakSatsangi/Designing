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

class cube{
public:
	cube(GLfloat a)
	{
		edge = a;
		angleX = 0.0f;
		angleY = 0.0f;
		angleZ = 0.0f;
	}
	GLfloat edge;
	GLfloat angleX;
	GLfloat angleY;
	GLfloat angleZ;
	void drawCube()
	{
		glColor3f (1.0, 1.0, 1.0);
		glLoadIdentity ();             /* clear the matrix */
	
		
		
	
			   /* viewing transformation  */
		//gluLookAt (0.0, 0.0, 2.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		//glScalef (1.0, 2.0, 1.0);      /* modeling transformation */ 
		glTranslatef(0.0,0.0,-6.0f);
		glRotatef(angleX,1.0,0.0,0.0);
		glRotatef(angleY,0.0,1.0,0.0);
		glRotatef(angleZ,0.0,0.0,1.0);
		//glRotatef(180.0, 1.0, 0.0, 0.0);
		//glRotatef(180.0, 0.0, 1.0, 0.0);
		glutWireCube (edge);
	}
	void rotateX()
	{
		angleX+=5.0f;
		if(angleX>360.0f)
			angleX-=360.0f;
		//glRotatef(angleX,1.0f,0.0f,0.0f);
	}
	void rotateY()
	{
		angleY+=5.0f;
		if(angleY>360.0f)
			angleY-=360.0f;
		//glRotatef(angleY,0.0f,1.0f,0.0f);
	}
	void rotateZ()
	{
		angleZ+=5.0f;
		if(angleZ>360.0f)
			angleZ-=360.0f;
		//glRotatef(angleZ,0.0f,0.0f,1.0f);
	}
};
