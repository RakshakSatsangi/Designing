#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <GL/glut.h>  	// GLUT, includes glu.h and gl.h
#include <math.h>     	// Needed for sin, cos
#include <pthread.h>
#include <vector>
#include <string>
#include "ball.cpp"
#include "gui.cpp"
#include "window.cpp"
#include "physics.cpp"
#include "cube.cpp"

using namespace std;
// Global variables
	
const int numBalls = 5;
const GLfloat ballRadius = 0.4f;   	// Radius of the bouncing ball
int refreshMillis = 10;      		// Refresh period in milliseconds
bool pause;
window * myWindow;

GLdouble xMin=-1.0f, xMax=1.0f, yMin=-1.0f, yMax=1.0f;	// Projection clipping area
//GLfloat ballXMax, ballXMin, ballYMax, ballYMin; 						// Ball's center (x, y) bounds

pthread_t threads[numBalls]; 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


vector<ball*> balls;
cube * box = new cube(3.0);
void display()
{
	//cout<<"display"<<endl;
	// Checking Collision among balls
	vector<int> collided;
	vector<int> temp;
	for(int i=0;i<numBalls; i++)
	{
		collided.push_back(i);
		balls[i]->tempr = balls[i]->r->add(balls[i]->v);
		balls[i]->isCollide = false;
	}
	
	//cout<< "do while begin"<<endl;
	do{
		for(int i=0; i<collided.size(); i++)
		{
			//collision with wall
			if(collWall(balls[collided[i]]))
			{
				//cout<<"wall"<<endl;
				bool a=false;
				for(int k=0; k<temp.size(); k++)
				{
					if(temp[k]==collided[i])
						a=true;
				}
				if(!a)
					temp.push_back(collided[i]);	
				balls[collided[i]]->isCollide=true;
			}
			
			 // collision among balls
			for(int j=0; j<numBalls; j++)
			{
				if(collBalls(balls[collided[i]],balls[j]))
				{
					bool a=false;
					for(int k=0; k<temp.size(); k++)
					{
						if(temp[k]==collided[i])
							a=true;
					}
					if(!a)
						temp.push_back(collided[i]);
					balls[collided[i]]->isCollide=true;
					a=false;
					for(int k=0; k<temp.size(); k++)
					{
						if(temp[k]==j)
							a=true;
					}
					if(!a)
						temp.push_back(j);
					balls[j]->isCollide=true;
				}
			}
			 
		}
		while(!collided.empty())
			collided.pop_back();
		//delete temp;
		while(!temp.empty())
		{
			collided.push_back(temp[temp.size()-1]);
			temp.pop_back();
		}

	}while(!collided.empty());
	 
	 // if no collision takes place 
	for(int i=0; i<numBalls; i++)
	{
		if(!balls[i]->isCollide)
		{
			balls[i]->r = balls[i]->tempr;
		}
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear the color buffer
	glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
	glLoadIdentity();              // Reset model-view matrix
	
	// 3d cube
	
	box->drawCube();
	
	for(int i=0;i<numBalls;i++)
	{
		balls[i]->colR=(GLfloat)(rand()%10)/10.0f;
		balls[i]->colG=(GLfloat)(rand()%10)/10.0f;
		balls[i]->colB=(GLfloat)(rand()%10)/10.0f;
		DrawCircle(balls[i]->r->xCoordinate, balls[i]->r->yCoordinate, balls[i]->r->zCoordinate, balls[i]->radius, balls[i]->colR, balls[i]->colG, balls[i]->colB);	
	}	
	
	glutSwapBuffers();  // Swap front and back buffers (of double buffered mode)
}
 /* Called back when the timer expired */
void Timer(int value) {
	glutPostRedisplay();    					// Post a paint request to activate display()
	glutTimerFunc(refreshMillis, Timer, 0); 	// subsequent timer call at milliseconds
}

 /* SpaceBar to reduce frame rate */
void keypress(unsigned char key, int x, int y)
{
	if(key==' ')
	{
		pause=!pause;
		if(pause) refreshMillis=10;
		else refreshMillis=1000;
	}
	if(key=='x')
	{
		box->rotateX();
	}
	if(key=='y')
	{
		box->rotateY();
	}
	if(key=='z')
	{
		box->rotateZ();
	}
}



void reshape(GLsizei width, GLsizei height) {
	cout<<"reshape"<<endl;
	// Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping area to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset the projection matrix
	
	
	
	if (width >= height) {
		//cout<<"aspect>1"<<endl;
		xMin   = -1.0f * aspect;
		xMax  = 1.0f * aspect;
		yMin = -1.0f;
		yMax    = 1.0f;
	} else {
		//cout<<"aspect<1"<<endl;
		xMin   = -1.0;
		xMax  = 1.0;
		yMin = -1.0f/aspect;
		yMax    = 1.0f/aspect;
	}
	
	gluPerspective(45, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes  
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly  
}

int main(int argc, char** argv) 
{
	glutInit(&argc, argv);            	// Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH); 	// Enable double buffered mode
	myWindow = new window;
	glutReshapeFunc(reshape);     // Register callback handler for window re-shape
	
	//Initial co-ordinates assignment
	//reshape(myWindow.windowWidth,myWindow.windowHeight);
	srand(time(NULL));
	GLfloat grid=2.4f*ballRadius;
	int no_gridx=(int)(2.0f/grid);
	int no_gridy=(int)(2.0f/grid);
	int no_gridz=(int)(2.0f/grid);
	int randvals1[numBalls];
	int randvals2[numBalls];
	int randvals3[numBalls];
	for(int mi=0;mi<numBalls;mi++)
	{
		bool checkrand=0;
		if(mi==0)
		{
			checkrand=1;
			randvals1[mi]=rand()%no_gridx;
	    	randvals2[mi]=rand()%no_gridy;
	    	randvals3[mi]=rand()%no_gridz;
		}
	    while(!checkrand)
	    {
	    	randvals1[mi]=rand()%no_gridx;
	    	randvals2[mi]=rand()%no_gridy;
	    	randvals3[mi]=rand()%no_gridz;
	    	for(int mj=0;mj<mi;mj++)
	    	{
	    		if(randvals1[mi]==randvals1[mj]&&randvals2[mi]==randvals2[mj]&&randvals3[mi]==randvals3[mj])
	    		{
	    			checkrand=0;
	    			break;
	    		}
	    		else
	    		{
	    			checkrand=1;
	    		}
	    	}

	    }
	    
	    GLfloat centerX=(GLfloat)(randvals1[mi])*grid+grid/2.0f-1.0f;
	    GLfloat centerY=(GLfloat)(randvals2[mi])*grid+grid/2.0f-1.0f;
	    GLfloat centerZ=(GLfloat)(randvals2[mi])*grid+grid/2.0f-1.0f;
		GLfloat speedX=(GLfloat)(rand()%10)/1000.0f+0.01f;
		GLfloat speedY=(GLfloat)(rand()%10)/1000.0f+0.01f; 
		GLfloat speedZ=(GLfloat)(rand()%10)/1000.0f+0.01f; 
		
		ball *xyz = new ball(centerX, centerY, centerZ, speedX, speedY, speedZ);
		xyz->colR=(GLfloat)(rand()%10)/10.0f;
		xyz->colG=(GLfloat)(rand()%10)/10.0f;
		xyz->colB=(GLfloat)(rand()%10)/10.0f;
		xyz->radius = ballRadius;
		xyz->ballXMax = box->edge/2.0f - ballRadius;
		xyz->ballXMin = -1.0f*box->edge/2.0f + ballRadius;
		xyz->ballYMax = box->edge/2.0f - ballRadius;
		xyz->ballYMin = -1.0f*box->edge/2.0f + ballRadius;
		xyz->ballZMax = box->edge/2.0f - ballRadius;
		xyz->ballZMin = -1.0f*box->edge/2.0f + ballRadius;
		xyz->index = mi;
		balls.push_back(xyz);
	}
	
	glutKeyboardFunc(&keypress);
	glutDisplayFunc(display);     // Register callback handler for window re-paint
	glutTimerFunc(0, Timer, 0);   // First timer call immediately
	initGL();                     // Our own OpenGL initialization
	glutMainLoop();               // Enter event-processing loop
	return 0;
}
