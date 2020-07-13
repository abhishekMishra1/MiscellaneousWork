#include <GL/glew.h>
#include <stdlib.h>
#include <iostream>
#include "GL\freeglut.h"
#include <FreeImage.h>

using namespace std;

float Vertices [] = { 0.0, 0.5, 0.0, 1.0, 0.0, 0.0, 1.0, 0.5, 1.0,
					0.5, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0,
					-0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0};

float squareVertices[] = {0.5, 0.5, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0,
					-0.5, 0.5, 0.0, 0.0, 1.0, 1.0, 1.0,  0.0, 1.0,
					-0.5, -0.5, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0,
					0.5, -0.5, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0
};

GLuint triangeVBOIds;
GLuint squareVBOId;
GLuint textureID;

unsigned int width, height;


void initTexture(GLuint texID, int level, BYTE* image)
{
	//bind to the texture object
	glBindTexture(GL_TEXTURE_2D, texID);

	//upload pixel data to the texture object
	glTexImage2D(GL_TEXTURE_2D,
		0, //mipmap level
		GL_RGBA, width, height, 
		0, 
		GL_RGBA, 
		GL_UNSIGNED_BYTE, 
		image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR /*GL_NEAREST*/);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
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
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture(GL_TEXTURE_2D, textureID);
	
	//bind to the VBO that contains poistioned data
	glBindBuffer(GL_ARRAY_BUFFER, triangeVBOIds);
	//specify where and how vertex data is stored
	glVertexPointer(3, GL_FLOAT, 36, 0);

	//bind to the VBO that contains poistioned data
	glColorPointer(4, GL_FLOAT, 36, (void*)12);

	glTexCoordPointer(2, GL_FLOAT, 36, (void*)28);

	//send data to graphics pipeline
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void drawSquare()
{
	//enable sending vertex position data
	glEnableClientState(GL_VERTEX_ARRAY);	
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture(GL_TEXTURE_2D, textureID);
	//bind to the VBO that contains poistioned data
	glBindBuffer(GL_ARRAY_BUFFER, squareVBOId);
	//specify where and how vertex data is stored
	glVertexPointer(3, GL_FLOAT, 36, 0);

	//bind to the VBO that contains poistioned data
	glColorPointer(4, GL_FLOAT, 36, (void*)12);

	glTexCoordPointer(2, GL_FLOAT, 36, (void*)28);
	//send data to graphics pipeline
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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
	if(zPos > 100.0)
		zPos = -1.0;

	//set the model view matrix as current matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -2.0);
//	glRotatef(angle, 0.0, 1.0, 0.0);
	glColor3f(1.0,1.0,0.0);

	glPushMatrix();
	glTranslatef(-0.5, 0.0, 0.0);

	drawTriangle();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -.1);
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

	triangeVBOIds = initalizeVBO(104, Vertices);
	squareVBOId = initalizeVBO(144, squareVertices);
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &textureID);

	BYTE* image = initializeImage("C:\\Users\\ab1\\Desktop\\PAUL\\mipmap\\mipmap\\mipmap128.png");
	initTexture(textureID, 0, image);

	image = initializeImage("C:\\Users\\ab1\\Desktop\\PAUL\\mipmap\\mipmap\\mipmap64.png");
	initTexture(textureID, 0, image);

	image = initializeImage("C:\\Users\\ab1\\Desktop\\PAUL\\mipmap\\mipmap\\mipmap32.png");
	initTexture(textureID, 0, image);

	image = initializeImage("C:\\Users\\ab1\\Desktop\\PAUL\\mipmap\\mipmap\\mipmap16.png");
	initTexture(textureID, 0, image);

	image = initializeImage("C:\\Users\\ab1\\Desktop\\PAUL\\mipmap\\mipmap\\mipmap8.png");
	initTexture(textureID, 0, image);

	image = initializeImage("C:\\Users\\ab1\\Desktop\\PAUL\\mipmap\\mipmap\\mipmap4.png");
	initTexture(textureID, 0, image);

	image = initializeImage("C:\\Users\\ab1\\Desktop\\PAUL\\mipmap\\mipmap\\mipmap2.png");
	initTexture(textureID, 0, image);

	image = initializeImage("C:\\Users\\ab1\\Desktop\\PAUL\\mipmap\\mipmap\\mipmap1.png");
	initTexture(textureID, 0, image);
	glAlphaFunc(GL_LESS, 0.1);
	glEnable(GL_ALPHA_TEST);
}


void timer(int val)
{
	display();
	glutTimerFunc(10, timer, 0);
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