#include <GL/freeglut.h>
#include <iostream>
using namespace std;

void drawTriangle()
{
	cout<<__FUNCTION__<<endl;
	glBegin(GL_TRIANGLES);
	
	//1st vertex
	glVertex2f(-0.5, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	
	//2nd vertex
	glVertex2f(0.0, 0.5);
	glColor3f(0.0, 1.0, 0.0);
	
	//3rd vertex
	glVertex2f(0.5, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	
	glEnd();
}

void display()
{
	cout<<__FUNCTION__<<endl;	
	glClear(GL_COLOR_BUFFER_BIT);

	drawTriangle();
	
	glutSwapBuffers();
}

void reshape(int, int)
{
}

void Timer(int timer)
{
	display();
	glutTimerFunc(1000, Timer, 0);
}

int main(int argc, char* argv[])
{
	//1. Initialize the glut library
	glutInit(&argc, argv);
	//2. Initialize the Display mode
	glutInitDisplayMode(GLUT_RGBA);
	//3. Set the Window Size
	glutInitWindowSize(500, 500);
	//4. Create Glut Window for OpenGL commands 
	glutCreateWindow("Hello Glut");
	
	//5. clear the color - Initializing the Open GL state
	glClearColor(1.0,1.0,1.0,0.0);
	
	//6. Attach the Display Function
	glutDisplayFunc(display);
	//7. Attach the reshape function
	glutReshapeFunc(reshape);
	//8. Set the Timer function
	glutTimerFunc(1000, Timer, 0);
	
	//9. Start the Glut Main Loop
	glutMainLoop();
	return 0;
}