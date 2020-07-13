#include <GL/glew.h>
#include <stdlib.h>
#include <iostream>
#include "GL\freeglut.h"

using namespace std;

float Vertices [] = { 0.0, 0.5, 0.0, 1.0, 0.0, 0.0, 1.0,
					0.5, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0,
					-0.5, 0.0, 0.0,	0.0, 0.0, 1.0, 1.0};

float squareVertices[] = {0.5, 0.5, 0.0, 1.0, 0.0, 1.0, 1.0,
					-0.5, 0.5, 0.0, 0.0, 1.0, 0.0, 1.0,
					-0.5, -0.5, 0.0, 0.0, 1.0, 1.0, 1.0,
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
}

float angle = 0.0f;
float xPos = 0.0f;
float zPos = 0.0f;
void display(void)
{
	std::cout<<"display"<<std::endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glColor3f(1.0, 0.0, 1.0);

	angle +=1.0f;
	if(angle>=360.0)
		angle = 0.0;

	xPos += 0.1;
	if(xPos > 1.0)
		xPos = -1.0;

	zPos += 0.1;
	if(zPos > 100.0)
		zPos = -1.0;

	//set the model view matrix as current matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -2.0);

	//Setup the stencil buffer

	//disable writing to the color buffere
	glColorMask(false, false, false, false);

	//setup stencil test
	glStencilFunc(GL_ALWAYS/*GL_EQUAL*/, 1, 1);

	//what to do if stencil test passes
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);

	drawTriangle();

	//disable writing to the color buffere
	glColorMask(true, true, true, true);

	//setup stencil test
	glStencilFunc(GL_EQUAL, 1, 1);

	//what to do if stencil test passes
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	drawSquare();

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
	//glEnable(GL_DEPTH_TEST);
//	glEnable(GL_STENCIL_TEST);
	glScissor(150,150,200,200);
	glEnable(GL_SCISSOR_TEST);
	//glEnable(GL_FOG);
	//float fog[] = {0.5f, 0.5f, 0.5f, 0.5f};
	//glFogfv(GL_FOG_COLOR, fog);


}


void timer(int val)
{
	display();
	glutTimerFunc(100, timer, 0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
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