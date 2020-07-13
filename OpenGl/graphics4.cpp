#include <GL/freeglut.h>
#include <iostream>

using namespace std;

float vertices[] = {0.0, 0.5, 0.0, 1.0, 0.0, 0.0, 1.0,
				    0.5, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0,
				   -0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0
				   };


void drawTriangle()
{
	cout<<__FUNCTION__<<endl;
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	//7 values* size of float
	glVertexPointer(3, GL_FLOAT, 28, vertices);
	
	glColorPointer(4, GL_FLOAT, 28, vertices+3);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void display()
{
	cout<<__FUNCTION__<<endl;	
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

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
	glutInitDisplayMode(GLUT_RGBA| GLUT_DEPTH);
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