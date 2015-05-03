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
bool collBalls(ball *a, ball *b);
bool collWall(ball *a);
void gravitySpeedUpdate(ball * a, char x, GLfloat grav);
