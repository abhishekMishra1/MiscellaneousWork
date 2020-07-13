#include <GL/glew.h>
#include <stdlib.h>
#include <iostream>
#include "GL\freeglut.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "ShaderHelper.h"
#include <FreeImage.h>

using namespace std;

float Vertices [] = { 0.0, 0.5, 0.0, 1.0, 0.0, 0.0, 1.0, 0.5, 1.0,
					0.5, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0,
					-0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0};

int programObjectID ;
int positionIndex;
int colorIndex;
int modelMatrixIndex;
int projectionIndex;
int viewMatrixIndex;
int textureCoordinateIndex;
int activeTextureIndex;
GLuint textureID;
unsigned int width, height;
float angle = 0.0f;
float zPos = 0.0f;


int initTexture(BYTE* image)
{
	//create id for texture object
	GLuint ids[1];
	glGenTextures(1, ids);

	//bind to the texture object
	glBindTexture(GL_TEXTURE_2D, ids[0]);

	//upload pixel data to the texture object
	glTexImage2D(GL_TEXTURE_2D,
		0, //mipmap level
		GL_RGB, width, height, 
		0, 
		GL_RGB, 
		GL_UNSIGNED_BYTE, 
		image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR /*GL_NEAREST*/);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR/*GL_LINEAR*/);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP/*GL_LINEAR*/);
	glBindTexture(GL_TEXTURE_2D, 0);
	return ids[0];
}

void drawTriangle()
{
	//enable sending vertex position data
	glEnableVertexAttribArray(positionIndex);
	glEnableVertexAttribArray(colorIndex);
	glEnableVertexAttribArray(textureCoordinateIndex);

	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, false, 36, Vertices);
	glVertexAttribPointer(colorIndex, 4, GL_FLOAT, false, 36, Vertices+3);
	glVertexAttribPointer(textureCoordinateIndex, 2, GL_FLOAT, false, 36, Vertices+7);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	glDisableVertexAttribArray(positionIndex);	
	glDisableVertexAttribArray(colorIndex);	
	glDisableVertexAttribArray(textureCoordinateIndex);	
}


BYTE* initializeImage(const char* filepath) {
	BYTE* image;
	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib = 0;
	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filepath, 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filepath);

	dib = FreeImage_Load(fif, filepath, 0);
	if (dib == NULL) {
		printf("Unable to load image");
		return NULL;
	}
	image = FreeImage_GetBits(dib);
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	return image;
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
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0,0.0, -zPos));
	//send the model matrix to shader
	glUniformMatrix4fv(modelMatrixIndex, 1, false, &modelMatrix[0][0]);

	glm::mat4 viewMatrix;
	viewMatrix = glm::lookAt(glm::vec3(0.0, 0.0, zPos),glm::vec3(0.0, 0.0, 0.0),glm::vec3(0.0, 1.0, 0.0));
	glUniformMatrix4fv(viewMatrixIndex, 1, false, &viewMatrix[0][0]);
	
	//set texture unit 0 to be the active texture unit
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//tell the fragment shader which texture unit is active
	glUniform1i(activeTextureIndex, 0);
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

	textureCoordinateIndex = glGetAttribLocation(programObjectID, "a_TextureCoordinate");
	modelMatrixIndex = glGetUniformLocation(programObjectID, "u_ModelMatrix");
	projectionIndex = glGetUniformLocation(programObjectID, "u_ProjectionMatrix");
	viewMatrixIndex = glGetUniformLocation(programObjectID, "u_ViewMatrix");
	activeTextureIndex= glGetUniformLocation(programObjectID, "activeTexture");

	BYTE* image = initializeImage("C:\\Users\\ab1\\Desktop\\Lighthouse.jpg");
	if(image == NULL)
	{
		cout<<"Unable to load image\n";
	}
	else
	{
		cout<<"Image loaded successfully\n";
	}

	//create the texture object and load texture data
	textureID = initTexture(image);

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