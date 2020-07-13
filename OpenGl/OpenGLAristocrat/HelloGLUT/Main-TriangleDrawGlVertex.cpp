#include <stdlib.h>
#include <iostream>
#include "GL\freeglut.h"
using namespace std;
static float r = 0.0f;
static float g = 0.0f;
static float b = 0.0f;

void drawTriangle()
{
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0, 0.5);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(0.5, 0.0);
	glColor3f(0.0,1.0, 0.0);
	glVertex2f(-0.5, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glEnd();
}

void display(void)
{
	std::cout<<"display"<<std::endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glColor3f(1.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	drawTriangle();
	glutSwapBuffers();
}

void reshape(int width, int height)
{
	glViewport(50,50,width,height);
}

void init()
{
	cout<<"init"<<endl;
	glClearColor(1.0, 1.0, 0.0, 1.0);
	glClearDepth(1.0);
}

void myInit(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClearDepth(1.0);
}

void timer(int val)
{
	display();
	glutTimerFunc(100, timer, 0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA| GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Hello GLUT");
	
	//initialize the openGL state
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutIdleFunc(display);
	glutTimerFunc(100, timer, 0);
	glutMainLoop();
	
	return 0;
}