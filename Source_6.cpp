#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	<iostream>
#include	"glut.h"


GLdouble eye_x = 7.0, eye_y = 5.0, eye_z = 7.0;
GLdouble rot_x = 0.0, rot_y = 0.0, rot_z = 0.0;

GLdouble light_x = 5.0, light_y = 0.0, light_z = 4.0;

int			mouseOldX = 0;
int			mouseOldY = 0;

/////////////////////////////////////////////////////////////////////////////////

GLfloat light_position[] = { 3.0, 3.0, 3.0, 0.0 };

void init() 
{
	glClearColor(0.0, 0.0, 0.0, -1.0);
	glEnable(GL_DEPTH_TEST);

	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF,	20) ;

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

GLfloat points[] = { 2,-2,0,
					  3,-1,0,
					  3,1,0,
					  2,2,0,
					  1,-3,0,
					  2,-3,5,
					  2,3,5,
					  1,3,0,
					  -1,-3,0,
					  -2,-3,5,
					  -2,3,5,
					  -1,3,0,
					  -2,-2,0,
					  -3,-1,0,
					  -3,1,0,
					  -2,2,0 };

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glRotatef(rot_x, 1, 0, 0);
	glRotatef(rot_y, 0, 1, 0);
	glRotatef(rot_z, 0, 0, 1);

	glEnable(GL_MAP2_VERTEX_3);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, points);

	double step = 0.05;

	glColor3f(1, 0, 0);
	glBegin(GL_QUAD_STRIP);
	for (float u = 0; u < 1; u += step)
	{
		for (float v = 0; v <= 1 + step; v += step)
		{
			glEvalCoord2f(u, v);
			glEvalCoord2f(u + step, v);
		}
	}
	glEnd();
	glRotatef(180, 0, 1, 0);
	glColor3f(0, 1, 0);
	glBegin(GL_QUAD_STRIP);
	for (float u = 0; u < 1; u += step)
	{
		for (float v = 0; v <= 1 + step; v += step)
		{
			glEvalCoord2f(u, v);
			glEvalCoord2f(u + step, v);
		}
	}
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex3f(3, 3, 0);
	glVertex3f(3, -3, 0);
	glVertex3f(-3, -3, 0);
	glVertex3f(-3, 3, 0);
	glEnd();

	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 60.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye_x, eye_y, eye_z,	// eye
		0, 0, 0,				// center
		0.0, 0.0, 1.0);		// up
}

void motion(int x, int y)
{
	//std::cout << x << " " << y << std::endl;
	rot_y -= ((mouseOldY - y) * 180.0f) / 200.0f;
	rot_z -= ((mouseOldX - x) * 180.0f) / 200.0f;
	rot_x = 0;

	if (rot_z > 360)
		rot_z -= 360;

	if (rot_z < -360)
		rot_z += 360;

	if (rot_y > 360)
		rot_y -= 360;

	if (rot_y < -360)
		rot_y += 360;

	mouseOldX = x;
	mouseOldY = y;

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		mouseOldX = x;
		mouseOldY = y;
	}
}

void key(unsigned char key, int x, int y)
{
	if (key == 27 || key == 'q' || key == 'Q')		//quit requested
		exit(0);
}



int main(int argc, char * argv[]) {
	glutInit(&argc, argv); //initialise glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("OpenGL lab");  // create window
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	init();
	glutMainLoop();
	return 0;
}