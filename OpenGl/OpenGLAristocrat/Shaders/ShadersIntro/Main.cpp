#include <GL/glew.h>
#include <stdlib.h>
#include <iostream>
#include "GL\freeglut.h"
#include "ShaderHelper.h"

using namespace std;

float Vertices [] = { 0.0, 0.5, 0.0, 1.0, 0.0, 0.0, 1.0,
					0.5, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0,
					-0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0};

int programObjectID ;
int positionIndex;
int colorIndex;
	
void drawTriangle()
{
	//enable sending vertex position data
	glEnableVertexAttribArray(positionIndex);
	glEnableVertexAttribArray(colorIndex);

	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, false, 28, Vertices);
	glVertexAttribPointer(colorIndex, 4, GL_FLOAT, false, 28, Vertices+3);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(positionIndex);	
	glDisableVertexAttribArray(colorIndex);	
}

void display(void)
{
	std::cout<<"display"<<std::endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawTriangle();
	glutSwapBuffers();
}

void reshape(int width, int height)
{
	glViewport(0,0,width,height);
}


void init()
{
	cout<<"init"<<endl;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClearDepth(1.0);

	programObjectID = createProgram();
	glUseProgram(programObjectID);

	//query the index/location of attribute named "a_Position"
	positionIndex = glGetAttribLocation(programObjectID, "a_Position");
	colorIndex = glGetAttribLocation(programObjectID, "a_Color");
}


void timer(int val)
{
	display();
	glutTimerFunc(10000, timer, 0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA| GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Hello GLUT");
	
	glewInit();
	//initialize the openGL state
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutIdleFunc(display);
	glutTimerFunc(100, timer, 0);
	glutMainLoop();
	
	return 0;
}