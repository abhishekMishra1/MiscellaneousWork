#include <GL/freeglut.h>
#include <iostream>
using namespace std;

void display()
{
	cout<<__FUNCTION__<<endl;	
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

void reshape(int, int)
{
}

void Timer(int timer)
{
	glutTimerFunc(100, Timer, 0);
}

int main(int argc, char* argv[])
{
	//1. Initialize glut library
	glutInit(&argc, argv);
	
	//2. Init display mode
	glutInitDisplayMode(GLUT_RGBA);
	
	//3. init window
	glutInitWindowSize(500, 500);
	
	//4. create glut window
	glutCreateWindow("Hello Glut");
	
	//5. set bg color
	glClearColor(1.0,0.0,0.0,0.0);
	
	//6. clear depth
	glClearDepth(1.0);
	
	//7. attach display func
	glutDisplayFunc(display);
	
	//8. attach reshape func
	glutReshapeFunc(reshape);
	
	//9. set timer
	glutTimerFunc(100, Timer, 0);
	
	//10. start glut loop
	glutMainLoop();
	return 0;
}