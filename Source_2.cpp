#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	<iostream>
#include	"glut.h"


GLdouble eye_x = 7.0, eye_y = 5.0, eye_z = 7.0;
GLdouble rot_x = 0.0, rot_y = 0.0, rot_z = 0.0;

//GLdouble light_x = 5.0, light_y = 0.0, light_z = 4.0;

int			mouseOldX = 0;
int			mouseOldY = 0;

/////////////////////////////////////////////////////////////////////////////////

GLfloat light_position[] = { 3.0, 3.0, 3.0, 0.0 };

void init() {
	glClearColor(0.0, 0.0, 0.0, -1.0);

	// фонова€ освещенность
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	//фоновый свет
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	//рассе€ный свет
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//зеркальный свет
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	//положение света
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0); // включить источник 0
	glEnable(GL_LIGHTING); // включить освещение

	//интерпол€ци€ цветов
	glShadeModel(GL_SMOOTH);

	//прорисовка с глубиной
	glEnable(GL_DEPTH_TEST);
	//более реалистичное освещение
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	//освещенность всей сценый
	float ambient[4] = { 0.0, 0.0, 0.0, 1 };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

}

void cube_perpendicular_peaks(void)
{
	glColor3f(0.5, 0.5, 0.5);
	//1 
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glEnd();
	//2 
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glEnd();
	//3 
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glEnd();
	//4 
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 1.0, 1.0);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, -1.0, 1.0);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, -1.0, -1.0);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 1.0, -1.0);
	glEnd();
	//5 
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(1.0, 1.0, 1.0);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(1.0, 1.0, -1.0);
	glEnd();
	//6 
	glBegin(GL_QUADS);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(1.0, -1.0, -1.0);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(1.0, -1.0, 1.0);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glEnd();
}

void cube_normals_peaks(void)
{
	//1 
	glBegin(GL_QUADS);
	glNormal3f(1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 1.0, 1.0);
	glNormal3f(-1.0, 1.0, 1.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glNormal3f(-1.0, -1.0, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glNormal3f(1.0, -1.0, 1.0);
	glColor3f(1, 1, 1);
	glVertex3f(1.0, -1.0, 1.0);
	glEnd();
	//2
	glColor3f(1, 0, 1);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glNormal3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glNormal3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glNormal3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glEnd();
	//3
	glColor3f(1, 1, 0);
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glNormal3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glNormal3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glNormal3f(-1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glEnd();
	//4
	glColor3f(0, 1, 1);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glNormal3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glNormal3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glNormal3f(1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glEnd();
	//5
	glColor3f(0, 0, 1);
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glNormal3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glNormal3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glNormal3f(1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glEnd();
	//6 
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
	glNormal3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glNormal3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glNormal3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glNormal3f(-1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//float matDif[] = { 0.0f, 0.2f, 0.0f };
	float matAmb[] = { 0.2f, 0.2f, 0.2f };
	//float matSpec[] = { 0.6f, 0.6f, 0.6f };
	float matShininess = 0.1f * 128;
	//фоновый цвет материала
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
	//рассе€ный цвет материала
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif);
	//зеркальный цвет материала
	//glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	//коэф ‘онга дл€ бликов
	glMaterialf(GL_FRONT, GL_SHININESS, matShininess);

	//собственное свечение материала
	//float matEmi[] = { 1.0f, 0.0f, 0.0f, 0.0f};
	//glMaterialfv(GL_FRONT, GL_EMISSION, matEmi);



	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glRotatef(rot_x, 1, 0, 0);
	glRotatef(rot_y, 0, 1, 0);
	glRotatef(rot_z, 0, 0, 1);
	
	//куб с нормал€ми направленными к вершинам
	cube_normals_peaks();

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glPushMatrix();
	glTranslated(light_position[0], light_position[1], light_position[2]);


	glutSolidSphere(0.1, 5, 5);
	glPopMatrix();


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
	if (state)
	{
		mouseOldX = x;
		mouseOldY = y;
	}
}

void key(unsigned char key, int x, int y)
{
	if (key == 27 || key == 'q' || key == 'Q')		//quit 
		exit(0);
}



int main(int argc, char * argv[]) {
	glutInit(&argc, argv); //initialise glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);

	int	glWin = glutCreateWindow("OpenGL lab");  // create window

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	init();
	glutMainLoop();
	return 0;
}