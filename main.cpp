#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include "Maze.h"

#include <unistd.h>

#define TIME 1

using std::cout;
using std::endl;

Maze maze(100, 100);

float px = 1.25f;
float nx = -px;
float py = 1.25f;
float ny = -py;

void initOpenGL()
{
	glClearColor(0, 0, 0, 0);
	glEnable(GL_LINE_SMOOTH);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(int w, int h)
{
	glClearColor(0.5, 0.5, 1.0, 1.0);
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluPerspective(90, (GLfloat)w/(GLfloat)h, 1, 1000);
	glOrtho(nx, px, ny, py, -1, 1);
	//gluLookAt(90, 90, 90, 0, 0, 0, 0, 1, 0);
}

void idle(void)
{
}

void timer(int val)
{
	if (!maze.Generate())
	{
		glutPostRedisplay();
		glutTimerFunc(TIME, timer, 0);
	} else {
		glutSetWindowTitle("My Window! - Finished!");
	}
}

void drawMiniSquare(float x, float y, float dx, float dy, const Node& node)
{
	if (!node.visited)
	{
		if (node.active)
		{
			glColor3f(1.0f, 1.0f, 0.5f);
		} else {
			glColor3f(0.4f, 0.4f, 0.4f);
		}
	} else {
		if (node.active)
		{
			glColor3f(1.0f, 0.8f, 0.8f);
		} else {
			glColor3f(1.0f, 1.0f, 1.0f);
		}
	}


	glBegin(GL_QUADS);
	glVertex2f(x, 	 y);
	glVertex2f(x+dx, y);
	glVertex2f(x+dx, y-dy);
	glVertex2f(x,	 y-dy);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	if (!node.top_edge)
	{
		glVertex2f(x,    y);
		glVertex2f(x+dx, y);
	}
	if (!node.right_edge) 
	{
		glVertex2f(x+dx, y);
		glVertex2f(x+dx, y-dy);
	}
	if (!node.bottom_edge)
	{
		glVertex2f(x+dx, y-dy);
		glVertex2f(x,	 y-dy);
	}
	if (!node.left_edge)
	{
		glVertex2f(x,	 y-dy);
		glVertex2f(x,	 y);
	}
	glEnd();
}

void repaint(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(nx-0.1f, px+0.1f, ny-0.1f, py+0.1f, -1, 1);

	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex2f(nx, ny);
	glVertex2f(nx, py);
	glVertex2f(px, py);
	glVertex2f(py, ny);
	glEnd();

	float _px = nx;
	float _py = py;

	glLineWidth(1.0);
	glPointSize(2.0);
	float step_x = (px - nx)/maze.Width();
	float step_y = (py - ny)/maze.Height();

	for (int y = 0; y < maze.Height(); ++y)
	{
		for (int x = 0; x < maze.Width(); ++x)
		{
			Node n = maze.GetNode(x, y);
			if (n.invalid)
			{
				n.print();
				glBegin(GL_POINTS);
				glColor3f(1, 0, 0);
				glVertex2f(_px + (step_x/2), _py - (step_y/2));
				glEnd();
			} else {
				drawMiniSquare(_px, _py, step_x, step_y, n);				
			}

			_px += step_x;
		}

		_px = nx;
		_py -= step_y;
	}

	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("My Window!");

	glutIdleFunc(idle);
	glutDisplayFunc(repaint);
	glutReshapeFunc(reshape);

	initOpenGL();
	glutTimerFunc(16, timer, 0);
	glutMainLoop();

	return 0;
}
