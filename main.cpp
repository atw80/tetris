/*
Copyright (C) 2013, Dmitry Ivanov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "tetris.h"

Tetris tetris;

void display(void)
{
	/* clear window */
	glClear(GL_COLOR_BUFFER_BIT); 

	/* draw unit square polygon */

	tetris.displayTetris();
	/* flush GL buffers */
	glFlush(); 
}

static void timerCallback (int value) { 
	tetris.MoveDown();

/* call back again after elapsedUSecs have passed */
    glutTimerFunc (tetris.msecs, timerCallback, value);
	display();
}
void keyboard(unsigned char Key, int x, int y){
	switch(Key){
		case 'j':
			tetris.MoveDown();
			break;
		case 'k':
			tetris.MoveRotate();
			break;
		case 'h':
			tetris.MoveLeft();
			break;
		case 'l':
			tetris.MoveRight();
			break;
		default:
		break;
	};
	display();
}

void init()
{
	/* set clear color to black */
	glClearColor (0.0, 0.0, 0.0, 0.0);

	/* set fill color to white */
	glColor3f(1.0, 1.0, 1.0); 

	/* set up standard orthogonal view with clipping */
	/* box as cube of side 2 centered at origin */
	/* This is default view and these statement could be removed */
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho(-20.0, 20.0, -20.0, 20.0, -1.0, 1.0);
}


int main(int argc, char** argv)
{
	/* Initialize mode and open a window in upper left corner of screen */
	/* Window title is name of program (arg[0]) */

	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("simple"); 
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

    	glutTimerFunc (tetris.msecs, timerCallback, 0);

	init();
	glutMainLoop();
}


