#include <GL/glew.h>
#include <stdlib.h>
#include <iostream>
#include "GL\freeglut.h"

using namespace std;

float Vertices [] = { 0.0, 0.5, 0.0, 1.0, 0.0, 0.0, 1.0,
					0.5, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0,
					-0.5, 0.0, 0.0,	0.0, 0.0, 1.0, 1.0};

float squareVertices[] = {0.5, 0.5, 0.0, 1.0, 0.0, 0.0, 1.0,
					-0.5, 0.5, 0.0, 0.0, 1.0, 0.0, 1.0,
					-0.5, -0.5, 0.0, 1.0, 1.0, 1.0, 1.0,
					0.5, -0.5, 0.0, 0.0, 0.0, 1.0, 1.0
};

GLuint triangeVBOIds;
GLuint squareVBOId;

int initalizeVBO(int size, float arr[])
{
	GLuint ids[1];

	//generate id for VBO
	glGenBuffers(1, ids);

	if(ids[0] < 0)
	{
		cout<<"Unable to generate ID for VBO\n";
		return -1;
	}

	//bind to that VBO
	glBindBuffer(GL_ARRAY_BUFFER, ids[0]);

	// allocate  memory for the VBO
	glBufferData(GL_ARRAY_BUFFER, size, arr, GL_STATIC_DRAW);

	//unbind from VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return ids[0];
}
	
void drawTriangle()
{
	//enable sending vertex position data
	glEnableClientState(GL_VERTEX_ARRAY);	
	glEnableClientState(GL_COLOR_ARRAY);
	
	//bind to the VBO that contains poistioned data
	glBindBuffer(GL_ARRAY_BUFFER, triangeVBOIds);
	//specify where and how vertex data is stored
	glVertexPointer(3, GL_FLOAT, 28, 0);

	//bind to the VBO that contains poistioned data
	//glBindBuffer(GL_ARRAY_BUFFER, triangleColorVBOId);
	glColorPointer(4, GL_FLOAT, 28, (void*)12);

	//send data to graphics pipeline
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void drawSquare()
{
	//enable sending vertex position data
	glEnableClientState(GL_VERTEX_ARRAY);	
	glEnableClientState(GL_COLOR_ARRAY);
	
	//bind to the VBO that contains poistioned data
	glBindBuffer(GL_ARRAY_BUFFER, squareVBOId);
	//specify where and how vertex data is stored
	glVertexPointer(3, GL_FLOAT, 28, 0);

	//bind to the VBO that contains poistioned data
	glColorPointer(4, GL_FLOAT, 28, (void*)12);

	//send data to graphics pipeline
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

float angle = 0.0f;
float xPos = 0.0f;
float zPos = 0.0f;
void display(void)
{
	std::cout<<"display"<<std::endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glColor3f(1.0, 0.0, 1.0);

	angle +=1.0f;
	if(angle>=360.0)
		angle = 0.0;

	xPos += 0.1;
	if(xPos > 1.0)
		xPos = -1.0;

	zPos += 0.1;
	if(zPos > 110.0)
		zPos = -1.0;

	//set the model view matrix as current matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -2.0);
	glPushMatrix();
	glTranslatef(-0.5, 0.0, 0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);
//	gluLookAt( 0.0, 0.0, zPos, //eye pos
	//	0.0, 0.0, 0.0, //where eye is looking at
		//0.0, -1.0, 0.0);//UP vector
	drawTriangle();
	glPopMatrix();

	//glLoadIdentity();
	//glTranslatef(1.0, 0.0, -2.0);
	glPushMatrix();
	glTranslatef(0.5, 0.0, 0.0);
	glRotatef(angle, 1.0, 0.0, 0.0);
	drawSquare();
	glPopMatrix();

	glutSwapBuffers();

}

void reshape(int width, int height)
{
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 100.0);
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
}

void init()
{
	cout<<"init"<<endl;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClearDepth(1.0);

	triangeVBOIds = initalizeVBO(84, Vertices);
	squareVBOId = initalizeVBO(112, squareVertices);
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