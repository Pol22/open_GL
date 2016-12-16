#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	<iostream>
#include	"glut.h"

#define M_PI           3.14159265358979323846  /* pi */

GLdouble eye_x = 3.0, eye_y = 5.0, eye_z = 5.0;
GLdouble rot_x = 0.0, rot_y = 0.0, rot_z = 0.0;

GLdouble light_x = 5.0, light_y = 0.0, light_z = 4.0;

int			mouseOldX = 0;
int			mouseOldY = 0;

/////////////////////////////////////////////////////////////////////////////////

GLfloat light_position[] = { 3.0, 3.0, 3.0, 0.0 };

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

void Scene(void)
{
	glPushMatrix();
	glColor3f(0, 1, 1);
	//glutSolidSphere(0.2, 30, 30);
	glutSolidTeapot(1);
	glPopMatrix();
}

void Mirror()
{
	glColor3f(1, 1, 1);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glNormal3f(0, 1, 0);
	for (double phi = 0; phi <= 2 * M_PI; phi += M_PI / 20)
		glVertex3f(4.5 * cos(phi), 0, 3 * sin(phi));
	glEnd();
	glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glRotatef(rot_y, 0, 1, 0);
	glRotatef(rot_z, 0, 0, 1);

	glTranslatef(0.0, 0.0, 0.0);
	Scene();

	glPopMatrix();
	glPushMatrix();
	
	glEnable(GL_STENCIL_TEST); // enable test stencil
	glStencilMask(0xFF); // stencil mask 0xff
	glStencilFunc(GL_ALWAYS, 1, 1); // always test and write in buffer 1
	glStencilOp(GL_TRUE, GL_TRUE, GL_REPLACE); // in z buf replace 1 if pass
	//glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glDepthMask(GL_FALSE);
	glDisable(GL_LIGHTING);
	glTranslatef(0, -2, 0);
	Mirror();
	glEnable(GL_LIGHTING);
	glDepthMask(GL_TRUE);

	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glTranslatef(0, -2, 0);
	glScalef(1, -1, 1);

	glRotatef(rot_y, 0, 1, 0);
	glRotatef(rot_z, 0, 0, 1);

	Scene();
	glDisable(GL_STENCIL_TEST);

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