#include <GL/glew.h>
#include <stdlib.h>
#include <iostream>
#include "GL\freeglut.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "ShaderHelper.h"

using namespace std;

float Vertices [] = { 0.0, 0.5, 0.0, 1.0, 0.0, 0.0, 1.0,
					0.5, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0,
					-0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0};

int programObjectID ;
int positionIndex;
int colorIndex;
int modelMatrixIndex;
int projectionIndex;
int viewMatrixIndex;


float angle = 0.0f;
float zPos = 0.0f;

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

	angle += 1.0f;
	if(angle >=360)
		angle = 0.0f;

	zPos += 0.1f;
	if(zPos > 10)
		zPos = 0.0f;

	float radians = angle * 3.14 /180;
	glm::mat4 modelMatrix;
	
	//modelMatrix = glm::rotate(modelMatrix, radians, glm::vec3(0,1,0));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0,0.0, zPos-1));
	//send the model matrix to shader
	glUniformMatrix4fv(modelMatrixIndex, 1, false, &modelMatrix[0][0]);

	glm::mat4 viewMatrix;
	viewMatrix = glm::lookAt(glm::vec3(0.0, 0.0, zPos),glm::vec3(0.0, 0.0, 0.0),glm::vec3(0.0, 1.0, 0.0));
	glUniformMatrix4fv(viewMatrixIndex, 1, false, &viewMatrix[0][0]);
	drawTriangle();
	glutSwapBuffers();
}

void reshape(int width, int height)
{
	glm::mat4 projectionMatrix;
	projectionMatrix = glm::frustum(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
	glUniformMatrix4fv(projectionIndex, 1, false, &projectionMatrix[0][0]);
}


void init()
{
	cout<<"init"<<endl;
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);

	programObjectID = createProgram();
	glUseProgram(programObjectID);
	
	//query the index/location of attribute named "a_Position"
	positionIndex = glGetAttribLocation(programObjectID, "a_Position");
	colorIndex = glGetAttribLocation(programObjectID, "a_Color");
	modelMatrixIndex = glGetUniformLocation(programObjectID, "u_ModelMatrix");
	projectionIndex = glGetUniformLocation(programObjectID, "u_ProjectionMatrix");
	viewMatrixIndex = glGetUniformLocation(programObjectID, "u_ViewMatrix");
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