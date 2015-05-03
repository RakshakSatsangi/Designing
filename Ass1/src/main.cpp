#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <GL/glut.h>  	// GLUT, includes glu.h and gl.h
#include <math.h>     	// Needed for sin, cos
#include <pthread.h>
#include <vector>
#include <string>
#include <cstring>
#include "ball.h"
#include "gui.h"
#include "window.h"
#include "physics.h"

using namespace std;
// Global variables
	
int numBalls;

GLfloat maxRadius = 0.18f;			// max radius for a ball
int refreshMillis = 10;      		// Refresh period in milliseconds
bool paused=0;
bool done=0;						// signal to CONDITION VARIABLE in ONE-TO-ONE SYNCHRONISATION of P_THREADS
bool fullscr;
bool menu=0;
bool inst=0;
bool gravU, gravL, gravR, gravD;

window * myWindow;

GLdouble xMin=-1.33f, xMax=1.33f, yMin=-1.0f, yMax=1.0f;	// Projection clipping area

pthread_t * threads; 										// pthreads array
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;			// Mutex Variable
pthread_cond_t c = PTHREAD_COND_INITIALIZER;				// Condition Variable
vector<ball*> qMessage;
vec* *qSpeed;

vector<ball*> balls;

/* to display text on openGL window */
void displayText( float x, float y, float r, float g, float b, const char *string ) 
{
	int j = strlen( string );
 	glColor3f( r, g, b );
	glRasterPos2f( x, y );
	for( int i = 0; i < j; i++ ) 
	{
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
		
	}
}

/* function called by pthread */
void * fun(void * arg)
{
	pthread_mutex_lock( &mutex);	
	int argu = *(static_cast<int*>(arg));
	// checking collision with all balls in queueMessage
	for(int i=0; i<qMessage.size(); i++)
	{
		if(collBalls(balls[argu], qMessage[i]))
		{
			qSpeed[qMessage[i]->index] = balls[argu]->msgv;
			balls[argu]->isCollide = true;
		}
	}
	// checking collision with walls
	if(collWall(balls[argu]))
	{
		balls[argu]->isCollide=true;
	}
	qMessage.push_back(balls[argu]);
	done = 1;
	pthread_cond_signal( &c);
	pthread_mutex_unlock( &mutex);	
}

/* update speed of each ball at the end of jth thread */
void updateSpeed()
{
	pthread_mutex_lock( &mutex);	
	while(done==0)
		pthread_cond_wait(&c, &mutex);
	done = 0;
	for(int i=0; i<numBalls; i++)
	{
		if(qSpeed[i]!=NULL)
		{
			balls[i]->v=qSpeed[i];
			balls[i]->isCollide = true;
			qSpeed[i]=NULL;
		}
	}
	pthread_mutex_unlock( &mutex);	
}
void display()
{
    if(!menu&&!inst)
    {
		// Emptying queuing signals
		while(!qMessage.empty())
		{
			qMessage.pop_back();
		}
		for(int j=0;j<numBalls;j++)
		{
			qSpeed[j]=NULL;
		}
		for(int j=0; j<numBalls; j++)
		{
			pthread_create(&threads[j],NULL,fun,static_cast<void*> (&j)); // creating jth thread 
			updateSpeed(); 
			pthread_join(threads[j],NULL); // holding 'main' thread until jth thread gets complete
		}

		 // if no collision takes place 
		for(int i=0; i<numBalls; i++)
		{
			if(!balls[i]->isCollide)
			{
				balls[i]->r = balls[i]->r->add(balls[i]->v); // 1-1
			}
			balls[i]->isCollide=false;
		}

		// Gravity effects
		for(int i=0; i<numBalls; i++)
		{
			if(gravL)
				gravitySpeedUpdate(balls[i], 'l', 0.0005);
			if(gravR)
				gravitySpeedUpdate(balls[i], 'r', 0.0005);
			if(gravD)
				gravitySpeedUpdate(balls[i], 'd', 0.0005);
			if(gravU)
				gravitySpeedUpdate(balls[i], 'u', 0.0005);
		}
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear the color buffer
		glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
		glLoadIdentity();              // Reset model-view matrix
		
		for(int i=0;i<numBalls;i++)
		{
			 // random colors to a ball at every step
			balls[i]->colR=(GLfloat)(rand()%10)/10.0f;
			balls[i]->colG=(GLfloat)(rand()%10)/10.0f;
			balls[i]->colB=(GLfloat)(rand()%10)/10.0f;
			DrawCircle(balls[i]->r->xCoordinate, balls[i]->r->yCoordinate, balls[i]->radius, balls[i]->colR, balls[i]->colG, balls[i]->colB);	
		}	
		
		glutSwapBuffers();  // Swap front and back buffers (of double buffered mode)
    }
    // Menu Window
    else if(menu)
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);  // Clear the color buffer
        glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
        glLoadIdentity();
        glPushMatrix();
        displayText(-0.15f,0.4f,0.5,0.5,0.5,"MENU");
        displayText(-0.35f,-0.1f,0.0,0.0,0.0,"Show Paused Screen");
        displayText(-0.25f,-0.2f,0.0,0.0,0.0,"Instructions");
        displayText(-0.15f,-0.3f,0.0,0.0,0.0,"Resume");
        glPopMatrix();

        glutSwapBuffers();

    }
    // Instruction Window
    else
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);  // Clear the color buffer
        glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
        glLoadIdentity();
        glPushMatrix();
        displayText(-0.35f,0.4f,0.5,0.5,0.5,"INSTRUCTIONS");
        displayText(-0.5f,0.1f,0.0,0.0,0.0,"Press ESC for MENU");
        displayText(-1.1f,0.0f,0.0,0.0,0.0,"To pause screen press SPACE during Screen Saver or");
        displayText(-1.05f,-0.1f,0.0,0.0,0.0,"go to menu and click on SHOW PAUSED SCREEN");
        displayText(-1.1f,-0.2f,0.0,0.0,0.0,"To increase/decrease a ball speed click LMB/RMB");
        displayText(-0.6f,-0.3f,0.0,0.0,0.0,"on paused or running screen");
        displayText(-1.0f,-0.4f,0.0,0.0,0.0,"To stop a ball click on Middle mouse button");
        glPopMatrix();
        glutSwapBuffers();

    }
}
 /* Called back when the timer expired */
void Timer(int value) {
	glutPostRedisplay();    					// Post a paint request to activate display()
	glutTimerFunc(refreshMillis, Timer, 0); 	// subsequent timer call at milliseconds
}

void keypress(unsigned char key, int x, int y)
{
	if(key==' ')
	{
		paused=!paused;
		if(paused) 
		{
			for(int ba=0;ba<numBalls;ba++)
			{
				balls[ba]->pv->xCoordinate=balls[ba]->v->xCoordinate;
				balls[ba]->pv->yCoordinate=balls[ba]->v->yCoordinate;
				balls[ba]->v=balls[ba]->v->scale(0.0f);
			}
		}
		else
		{
			for(int ba=0;ba<numBalls;ba++)
			{
				balls[ba]->v->xCoordinate=balls[ba]->pv->xCoordinate;
				balls[ba]->v->yCoordinate=balls[ba]->pv->yCoordinate;
			}
		}
	}
	if(key==27)
	{
		menu=!menu;
		inst=0;
	}
	if(key=='f')
	{
		fullscr = !fullscr;
		if(fullscr) glutFullScreen();
		else myWindow->reshapeWindow();
	}
	if(key=='q')
	{
		exit(0);
	}
	if(key=='w')
		gravU = 1;
	if(key=='a')
		gravL = 1;
	if(key=='d')
		gravR = 1;
	if(key=='x')
		gravD = 1;
}

void keyUp(unsigned char key, int x, int y)
{
	if(key=='w')
		gravU = 0;
	if(key=='a')
		gravL = 0;
	if(key=='d')
		gravR = 0;
	if(key=='x')
		gravD = 0;
}

/* Computing aspect ratio and extreme co-ordinate of viewport */
void aspectRatio(GLfloat width, GLfloat height)
{
// Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	
	if (width >= height) {
		
		#ifdef DEBUG
		cout<<"aspect>=1"<<endl;
		#endif

	xMin   = -1.0f * aspect;
	xMax  = 1.0f * aspect;
	yMin = -1.0f;
	yMax    = 1.0f;
	} else {

		#ifdef DEBUG
		cout<<"aspect<1"<<endl;
		#endif

	xMin   = -1.0;
	xMax  = 1.0;
	yMin = -1.0f/aspect;
	yMax    = 1.0f/aspect;
	}
}
/* Function supporting callback of reshapeWindow */
void reshape(GLsizei width, GLsizei height) {
	myWindow->windowWidth=width;
	myWindow->windowHeight=height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping area to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset the projection matrix
	
	aspectRatio(width, height);
	gluOrtho2D(xMin, xMax, yMin, yMax);//-10.0f,10.0f for glOrtho
	for(int i=0; i<numBalls; i++)
	{
		balls[i]->ballXMin = xMin + balls[i]->radius;
		balls[i]->ballXMax = xMax - balls[i]->radius;
		balls[i]->ballYMin = yMin + balls[i]->radius;
		balls[i]->ballYMax = yMax - balls[i]->radius;
	}
	//gluPerspective(0, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes  
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly  
}
 /* Handling mouse events */
void mouse(int button, int state, int x, int y)
{
	if(!menu&&!inst)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{

			GLfloat clipx;
			GLfloat clipy;
			
			if (myWindow->windowWidth>myWindow->windowHeight)
			{
				GLfloat asp=(GLfloat)(myWindow->windowWidth)/(GLfloat)(myWindow->windowHeight);
				
				clipx=asp*2.0f*(GLfloat)x/(GLfloat)(myWindow->windowWidth)-asp;
				clipy=-2.0f*(GLfloat)y/(GLfloat)(myWindow->windowHeight)+1.0f;
			}
			else
			{
				GLfloat asp=(GLfloat)(myWindow->windowHeight)/(GLfloat)(myWindow->windowWidth);
				clipx=2.0f*(GLfloat)x/(GLfloat)(myWindow->windowWidth)-1.0f;
				clipy=-asp*2.0f*(GLfloat)y/(GLfloat)(myWindow->windowHeight)+asp;
			}
			vec * clip = new vec(clipx, clipy);
			//mouse click coordinate
			#ifdef DEBUG
			cout<<"mouse click coordinate"<<endl;
			cout<<x<<endl<<y<<endl;
			#endif
			for(int at=0;at<numBalls;at++)
			{
				if(balls[at]->r->dist(clip) < balls[at]->radius)
				{
					GLfloat abspeed;

					if(paused)
					{
						abspeed=balls[at]->pv->length();
						GLfloat addsp=abspeed+0.001f;	
						if(abspeed>0.0f)
						{
							balls[at]->pv=balls[at]->pv->scale(addsp/abspeed);
						}
						else
						{
							balls[at]->pv->xCoordinate=(GLfloat)(rand()%10)/1000.0f+0.0001f;
							balls[at]->pv->yCoordinate=(GLfloat)(rand()%10)/1000.0f+0.0001f; 
						}
					}
					else
					{
						abspeed=balls[at]->v->length();
						GLfloat addsp=abspeed+0.001f;
						if(abspeed>0.0f)
						{
							balls[at]->v=balls[at]->v->scale(addsp/abspeed);
						}
						else
						{
							balls[at]->v->xCoordinate=(GLfloat)(rand()%10)/1000.0f+0.0001f;
							balls[at]->v->yCoordinate=(GLfloat)(rand()%10)/1000.0f+0.0001f; 
						}
					}
				}
			}
		}
		else if (button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
		{

			GLfloat clipx;
			GLfloat clipy;
			
			if (myWindow->windowWidth>myWindow->windowHeight)
			{
				GLfloat asp=(GLfloat)(myWindow->windowWidth)/(GLfloat)(myWindow->windowHeight);
				
				clipx=asp*2.0f*(GLfloat)x/(GLfloat)(myWindow->windowWidth)-asp;
				clipy=-2.0f*(GLfloat)y/(GLfloat)(myWindow->windowHeight)+1.0f;
			}
			else
			{
				GLfloat asp=(GLfloat)(myWindow->windowHeight)/(GLfloat)(myWindow->windowWidth);
				clipx=2.0f*(GLfloat)x/(GLfloat)(myWindow->windowWidth)-1.0f;
				clipy=-asp*2.0f*(GLfloat)y/(GLfloat)(myWindow->windowHeight)+asp;
			}
			vec * clip = new vec(clipx, clipy);
			#ifdef DEBUG
			cout<<"right click coordinate"<<endl;
			cout<<x<<endl<<y<<endl;
			#endif
			for(int at=0;at<numBalls;at++)
			{
				if(balls[at]->r->dist(clip) < balls[at]->radius)
				{
					if(paused)
					{	
						balls[at]->pv=balls[at]->pv->scale(1.0f/1.4f);
					}
					else
					{
						balls[at]->v=balls[at]->v->scale(1.0f/1.4f);
					}
				}
			}
		}
		else if (button==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)
		{
			

			GLfloat clipx;
			GLfloat clipy;
			
			if (myWindow->windowWidth>myWindow->windowHeight)
			{
				GLfloat asp=(GLfloat)(myWindow->windowWidth)/(GLfloat)(myWindow->windowHeight);
				
				clipx=asp*2.0f*(GLfloat)x/(GLfloat)(myWindow->windowWidth)-asp;
				clipy=-2.0f*(GLfloat)y/(GLfloat)(myWindow->windowHeight)+1.0f;
			}
			else
			{
				GLfloat asp=(GLfloat)(myWindow->windowHeight)/(GLfloat)(myWindow->windowWidth);
				clipx=2.0f*(GLfloat)x/(GLfloat)(myWindow->windowWidth)-1.0f;
				clipy=-asp*2.0f*(GLfloat)y/(GLfloat)(myWindow->windowHeight)+asp;
			}
			vec * clip = new vec(clipx, clipy);
			for(int at=0;at<numBalls;at++)
			{
				if(balls[at]->r->dist(clip) < balls[at]->radius)
				{
					if(paused)
					{	
						balls[at]->pv=balls[at]->pv->scale(0.0f);
					}
					else
					{
						balls[at]->v=balls[at]->v->scale(0.0f);
					}
				}
			}
		}
	}
	else if(menu)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			for(int io=0;io<=2;io++)
			{
				GLfloat co_x;
				GLfloat co_y;
				if(io==0)
				{
					co_x=-0.35f;
					co_y=-0.1f;
				}
				else if(io==1)
				{
					co_x=-0.25f;
					co_y=-0.2f;
				}
				else
				{
					co_x=-0.15f;
					co_y=-0.3f;
				}
				GLfloat bldx;
				GLfloat bldy;
				GLfloat blux;
				GLfloat bluy;
				GLfloat brux;
				GLfloat bruy;
				GLfloat brdx;
				GLfloat brdy;
				if (myWindow->windowWidth>myWindow->windowHeight)
				{
					GLfloat asp=(GLfloat)(myWindow->windowWidth)/(GLfloat)(myWindow->windowHeight);
					bldx=(co_x+asp)*(GLfloat)(myWindow->windowWidth)/(2.0f*asp);
					bldy=(1.0f-co_y)*(GLfloat)(myWindow->windowHeight)/2.0f;
					blux=bldx;
					bluy=bldy-18.0f;
					brux=blux+206.0f;
					bruy=bluy;
					brdx=brux;
					brdy=bldy;
				}
				else
				{
					GLfloat asp=(GLfloat)(myWindow->windowHeight)/(GLfloat)(myWindow->windowWidth);
					bldx=(co_x+1.0f)*(GLfloat)(myWindow->windowWidth)/(2.0f);
					bldy=(asp-co_y)*(GLfloat)(myWindow->windowHeight)/(2.0f*asp);
					blux=bldx;
					bluy=bldy-18.0f;
					brux=blux+206.0f;
					bruy=bluy;
					brdx=brux;
					brdy=bldy;
				}
				if ((GLfloat)x>bldx&&(GLfloat)x<brdx&&(GLfloat)y<bldy&&(GLfloat)y>bluy)
				{
					if(io==0)
					{
						if(!paused)
						{
							paused=1;
							for(int ba=0;ba<numBalls;ba++)
							{
								balls[ba]->pv->xCoordinate=balls[ba]->v->xCoordinate;
								balls[ba]->pv->yCoordinate=balls[ba]->v->yCoordinate;
								balls[ba]->v=balls[ba]->v->scale(0.0f);
							}

						}
						menu=!menu;
					}
					else if(io==1)
					{
						inst=1;
						menu=0;
					}
					else
					{
						if(paused)
						{
							paused=0;
							for(int ba=0;ba<numBalls;ba++)
							{
								balls[ba]->v->xCoordinate=balls[ba]->pv->xCoordinate;
								balls[ba]->v->yCoordinate=balls[ba]->pv->yCoordinate;
							}
							menu=0;
							inst=0;
						}
						else
						{
							menu=0;
							inst=0;
						}
					}
				}
			}

		}
	}
	else
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			inst=0;
			menu=1;
		}
	}
}
 /* Initialising Balls */
void initBalls()
{
	//Initial co-ordinates assignment
	aspectRatio(myWindow->windowWidth,myWindow->windowHeight);
	srand(time(NULL));
	while(numBalls>=(int(xMax/maxRadius)*int(yMax/maxRadius))/1.5)
	{
		#ifdef DEBUG
		cout<<"limit of ball exceeded"<<endl;
		#endif
		maxRadius/=2;
	}
	GLfloat grid=2.0f*maxRadius;
	int no_gridx=(int)(2.0*xMax/grid);
	int no_gridy=(int)(2.0*yMax/grid);
	int randvals1[numBalls];
	int randvals2[numBalls];
	bool checkrand;
	for(int mi=0;mi<numBalls;mi++)
	{
	    do
	    {
			checkrand=1;
	    	randvals1[mi]=rand()%no_gridx;
	    	randvals2[mi]=rand()%no_gridy;
	    	for(int mj=0;mj<mi;mj++)
	    	{
	    		if(randvals1[mi]==randvals1[mj]&&randvals2[mi]==randvals2[mj])
	    		{
	    			checkrand=0;
	    			break;
	    		}
	    	}
	    }while(!checkrand);	    
	    GLfloat centerX=(GLfloat)(randvals1[mi])*grid+grid/2.0f-xMax;
	    GLfloat centerY=(GLfloat)(randvals2[mi])*grid+grid/2.0f-yMax;
		GLfloat speedX=(GLfloat)(rand()%10)/1000.0f+0.0001f;
		GLfloat speedY=(GLfloat)(rand()%10)/1000.0f+0.0001f; 
		
		ball *xyz = new ball(centerX, centerY, speedX, speedY);
		xyz->colR=(GLfloat)(rand()%10)/10.0f;
		xyz->colG=(GLfloat)(rand()%10)/10.0f;
		xyz->colB=(GLfloat)(rand()%10)/10.0f;
		xyz->radius = (GLfloat)(3+rand()%((int)(100*(maxRadius-0.03))))/100.0f; // radius must be atleast 0.06
		xyz->ballXMax = xMax-xyz->radius;
		xyz->ballXMin = xMin+xyz->radius;
		xyz->ballYMax = yMax-xyz->radius;
		xyz->ballYMin = yMin+xyz->radius;
		xyz->index = mi;
		balls.push_back(xyz);
	}
}

int main(int argc, char** argv) 
{
	numBalls=atoi(argv[1]);					// taking input of no. of balls from command line
	threads = new pthread_t[numBalls];
	qSpeed = new vec*[numBalls];
	
	glutInit(&argc, argv);            							// Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH); 	// Enable double buffered mode
	myWindow = new window;										// Initialising window object
	glutReshapeFunc(reshape);     								// Register callback handler for window re-shape
	glutFullScreen(); fullscr = 1; 								// FullScreen Mode
	#ifdef DEBUG
	cout<<"DEBUGGING IS BEING DONE"<<endl;
	#endif
	
	initBalls();					// initialising balls 
	
	glutKeyboardFunc(&keypress);	// Tell GLUT to use the method "keyPressed" for key pressed events  
	glutKeyboardUpFunc(&keyUp); 	// Tell GLUT to use the method "keyUp" for key up events  
	glutMouseFunc(mouse);			// Handle mouse click events
	glutDisplayFunc(display);     	// Register callback handler for window re-paint
	glutTimerFunc(0, Timer, 0);   	// First timer call immediately
	initGL();                     	// Our own OpenGL initialization
	glutMainLoop();               	// Enter event-processing loop
	return 0;
}
