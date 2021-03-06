#define PI 3.14159265f
/* Initialize OpenGL Graphics */
void initGL() {
	glClearColor(0.9, 0.5, 0.0, 1.0); // Set background (clear) color to white
	/*
	for(int i=0;i<numBalls;i++)
	{
		tmp[i]=i;
	}
	*/
		/* Giving Light Effects */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	//glClearColor(1.0,1.0,1.0,1.0);
	glEnable(GL_COLOR_MATERIAL); // extremely important to give color to ball using glColor3f
	
	GLfloat ambientLight[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat lightPos[] = {5.0f,5.0f,5.0f,0.0f};
	
	GLfloat materialAmbient[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat materialDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat materialSpecular[] = {1.0f,1.0f,1.0f,1.0f};
	GLfloat shininess = 100.0f;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLightfv(GL_LIGHT0,GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess); //The shininess parameter
}

void DrawCircle(GLfloat cx, GLfloat cy, GLfloat cz, GLfloat r, GLfloat R, GLfloat G, GLfloat B) { // 3d
	glPushMatrix(); 
	glColor3f(R,G,B); // giving color to ball
    glTranslatef(cx,cy,cz); // 3d
    //gluLookAt (0.0, 0.0, 2.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // 3d
    glutSolidSphere(0.2,30,30);
    
    /* Uncomment this to get 2D ball
    int num_segments = 100; 
	GLfloat theta = 2.0f * PI/ GLfloat(num_segments); 
	GLfloat c = cos(theta);//precalculate the sine and cosine
	GLfloat s = sin(theta);
	GLfloat t;

	GLfloat x = r;//we start at angle = 0 
	GLfloat y = 0.0f; 
	glBegin(GL_POLYGON); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		glVertex2f(x,y);//output vertex 
		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	} 
	glEnd();
	*/ 
	glPopMatrix();                      // Restore the model-view matrix
}
