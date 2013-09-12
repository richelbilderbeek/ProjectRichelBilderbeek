/**********************************************************************
	
  Simple Tokamak Sample
  Used the introduce my CTokSim-Class

  December 2005

  This tutorial was written by Philipp Crocoll
  Contact: 
	philipp.crocoll@web.de
	www.codecolony.de

  Every comment would be appreciated.

  If you want to use parts of any code of mine:
	let me know and
	use it!

**********************************************************************
ESC: exit

CAMERA movement:
w : forwards
s : backwards
a : turn left
d : turn right
x : turn up
y : turn down
v : strafe right
c : strafe left
r : move up
f : move down

***********************************************************************/
#include "stdafx.h"


#include "gl/glut.h"

#include "camera.h"
#include "SimpleTokSim.h"

CCamera Camera;

SimpleTokSim TokSim;

static GLfloat LightPos[] = {-2.0,1.0,3.0,0.0};
static GLfloat LightAmb[] = {0.5f,0.5f,0.5f,1.0f};
static GLfloat LightPos0[] = {-2.0,10.0,3.0,0.0};


///**************************
//* GLUT Callback Functions:

void reshape(int x, int y)
{
	//---
	//This function is not important for the Tokamak simulation
	//---
	if (y == 0 || x == 0) return;  //Nothing is visible then, so return
	
	//Set a new projection matrix
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();
	//Angle of view:40 degrees
	gluPerspective(40.0,(GLdouble)x/(GLdouble)y,1.0f,500.0f);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,x,y);  //Use the whole window for rendering
}


void Display(void)
{
	//---
	//This function displays the scene
	//---

	//init the drawing for OpenGL
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
	glLoadIdentity();	//Load a new modelview matrix -> we can apply new transformations

	//set the camera position
	Camera.Render();

	//set the light
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);

	//update the tokamak simulation:
	TokSim.CalculateNextFrame(0.02f);  //I use a fix time step (1/50 sec) for the examples

	//Call the display function of the tokamak-simulation class:
	TokSim.Display();

	//Finish rendering:
	glFlush();			
	glutSwapBuffers();	//Swap the buffers ->make the result of rendering visible



}
void KeyDown(unsigned char key, int x, int y)
{
	//handle the camera movement:
	float CamSpeed = 1.0f;
	switch (key) 
	{
	case 27:		//ESC
		PostQuitMessage(0);
		break;
	case 'a':		
		Camera.RotateY(5.0);
		Display();
		break;
	case 'd':		
		Camera.RotateY(-5.0);
		Display();
		break;
	case 'w':		
		Camera.MoveForward( -CamSpeed ) ;
		Display();
		break;
	case 's':		
		Camera.MoveForward( CamSpeed ) ;
		Display();
		break;
	case 'x':		
		Camera.RotateX(5.0);
		Display();
		break;
	case 'y':		
		Camera.RotateX(-5.0);
		Display();
		break;
	case 'c':		
		Camera.StrafeRight(-CamSpeed);
		Display();
		break;
	case 'v':		
		Camera.StrafeRight(CamSpeed);
		Display();
		break;
	case 'f':
		Camera.MoveUpward(-CamSpeed);
		Display();
		break;
	case 'r':
		Camera.MoveUpward(CamSpeed);
		Display();
		break;

	case 'm':
		Camera.RotateZ(-5.0);
		Display();
		break;
	case 'n':
		Camera.RotateZ(5.0);
		Display();
		break;

	}
}

void InitGL(int argc, _TCHAR* argv[],char * WindowTitle, int WindowX, int WindowY)
{
	//---
	//This function is not important for the Tokamak simulation
	//---
	
	//Initialize GLUT
	glutInit(&argc, argv);
	//Lets use doublebuffering, RGB-mode and a depth buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WindowX,WindowY);
	//Create a window with rendering context and everything else we need
	glutCreateWindow(WindowTitle);
	//Assign the event-handling routines
	glutDisplayFunc(Display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(KeyDown);
	glutIdleFunc(Display);
	
	//Lighting stuff:
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


}



int _tmain(int argc, _TCHAR* argv[])
{

	InitGL(argc, argv,"Tokamak testing environment - Simple Sample- W,A,S,D to move",700,700);

	Camera.Move(F3dVector(0,10,60));
	
	//Inititalize the physics simulation
	TokSim.Init();
	//init the random number generator:
	srand(timeGetTime());

	//Let GLUT get the msgs and tell us the ones we need
	glutMainLoop();
	return 0;
}


