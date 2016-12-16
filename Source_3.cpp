#include	<stdio.h>
#include	<stdlib.h>
#include	<iostream>
#include	<ctime>
#include	"glut.h"

#define M_PI           3.14159265358979323846  /* pi */

double RandInSection(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}


GLdouble eye_x = -7, eye_y = 0, eye_z = 0;
GLdouble rot_x = 0.0, rot_y = 0.0, rot_z = 0.0;
//GLdouble mov_x = 0.0, mov_y = 0.0, mov_z = 0.0;
GLdouble center_x = 0.0, center_y = 0.0, center_z = 0.0;

#define NumberOfTable 15
float randomBookAngles[NumberOfTable];
float randomBookX[NumberOfTable];
float randomBookY[NumberOfTable];
float randomPenAngles[NumberOfTable];
float randomPenX[NumberOfTable];
float randomPenY[NumberOfTable];
float randomTeaX[NumberOfTable];
float randomTeaY[NumberOfTable];
float randomTeaAngles[NumberOfTable];

//table
const float table_height = 4;
const float table_width = 10;
const float table_depth = 5;
//book
const float book_height = 0.5;
const float book_width = 2;
const float book_depth = 3;
//pen
double pen_radius = 1;
double pen_length = 7;


int			mouseOldX = 0;
int			mouseOldY = 0;

/////////////////////////////////////////////////////////////////////////////////

GLfloat light_position[] = { 5.0, 5.0, 5.0, 0.0 };

void init() {
	srand(time(NULL));
	glClearColor(0.0, 0.0, 0.0, -1.0);
	glEnable(GL_DEPTH_TEST);

	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	for (int i = 0; i < NumberOfTable; i++)
	{
		randomBookAngles[i] = rand() % 180;
		randomBookX[i] = -table_depth / 2 + book_depth / 2 + RandInSection(0, table_depth - book_depth);
		randomBookY[i] = RandInSection(book_depth / 2, table_width / 2 - book_width);
		randomPenAngles[i] = rand() % 360;
		randomPenX[i] = - RandInSection(0, table_depth / 2 - pen_length * 0.5 / 2) + pen_length * 0.2;
		randomPenY[i] = - RandInSection(0, table_width / 2 - pen_length * 0.5);
		randomTeaX[i] = RandInSection(0, table_depth / 2 - 0.5 / 2);;
		randomTeaY[i] = - RandInSection(table_depth / 2, table_width / 2 - 0.3);
		randomTeaAngles[i] = rand() % 360;
	}

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

void drawTable()
{
	float tabel_height = 4;
	float tabel_width = 10;
	float tabel_depth = 5;
	//крышка
	glPushMatrix();
	glColor3ub(138, 55, 0);
	glScalef(tabel_depth, tabel_width, 0.25);
	glutSolidCube(1);
	glPopMatrix();
	//ножки
	glPushMatrix();
	glColor3ub(138, 55, 0);
	glTranslatef(tabel_depth / 2 - 0.025 * tabel_width, tabel_width / 2 - 0.025 * tabel_width, -0.03125 * tabel_height - tabel_height / 2);
	glScalef(1, 1, 2 * tabel_height);
	glutSolidCube(0.5);
	glTranslatef(-tabel_depth + 0.5, 0, 0);
	glutSolidCube(0.5);
	glTranslatef(0, -tabel_width + 0.5, 0);
	glutSolidCube(0.5);
	glTranslatef(tabel_depth - 0.5, 0, 0);
	glutSolidCube(0.5);
	glPopMatrix();
}

void drawBook()
{
	float book_height = 0.5;
	float book_width = 2;
	float book_depth = 3;
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.5);
	glScalef(book_depth, book_width, book_height);
	glutSolidCube(1);
	glPopMatrix();
}

void drawPen()
{
	glColor3f(0.6, 0.2, 0.0);
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	glColor3f(0.0, 0.5, 0.5);
	gluCylinder(quadratic, pen_radius, pen_radius, pen_length, 20, 10);
	glTranslated(0, 0, pen_length / 2 + 3.5 * pen_radius);
	glColor3f(0.0, 0.0, 0.0);
	glutSolidCone(pen_radius, pen_radius * 3, 20, 10);
	glTranslated(0, 0, -pen_length / 2 - 3.5 * pen_radius);
	glutSolidSphere(1, 20, 10);
}

void drawAll(int i)
{
	glPushMatrix();
	drawTable();
	glPushMatrix();
	glTranslated(randomBookX[i], randomBookY[i], book_height / 2 + 0.03125 * table_height);
	glRotatef(randomBookAngles[i], 0, 0, 1);
	drawBook();
	glPopMatrix();
	glPushMatrix();
	glTranslated(randomPenX[i], randomPenY[i], pen_radius * 0.1 + 0.03125 * table_height);
	glRotatef(90, 0, 1, 0);
	glRotatef(randomPenAngles[i], 1, 0, 0);
	glScalef(0.1, 0.1, 0.2);
	drawPen();
	glPopMatrix();
	glTranslated(randomTeaX[i], randomTeaY[i], 0.75 + 0.03125 * table_height);
	glRotatef(90, 1, 0, 0);
	glRotatef(randomTeaAngles[i], 0, -1, 0);
	glColor3ub(211, 222, 60);
	glutSolidTeapot(1);
	glPopMatrix();
}

void drawScene()
{
	for (int width = 0; width < 3; width++)
	{
		for (int height = 0; height < 5; height++)
		{
			glPushMatrix();
			glTranslatef(-height * 10, width * 15, 0);
			drawAll(width * 5 + height);
			glPopMatrix();
		}
	}
	// пол
	glColor3ub(127, 0, 127);
	glTranslatef(0, 0, -table_height);
	glBegin(GL_QUADS);
	glVertex3f(10, -10, 0);
	glVertex3f(-50, -10, 0);
	glVertex3f(-50, 40, 0);
	glVertex3f(10, 40, 0);
	glEnd();
	// стены
	glColor3ub(127, 127, 127);
	glBegin(GL_QUADS);
	glVertex3f(10, -10, 0);
	glVertex3f(-50, -10, 0);
	glVertex3f(-50, -10, table_height * 3);
	glVertex3f(10, -10, table_height * 3);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(10, 40, 0);
	glVertex3f(-50, 40, 0);
	glVertex3f(-50, 40, table_height * 3);
	glVertex3f(10, 40, table_height * 3);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(10, 40, 0);
	glVertex3f(10, -10, 0);
	glVertex3f(10, -10, table_height * 3);
	glVertex3f(10, 40, table_height * 3);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-50, 40, 0);
	glVertex3f(-50, -10, 0);
	glVertex3f(-50, -10, table_height * 3);
	glVertex3f(-50, 40, table_height * 3);
	glEnd();
	// Доска
	glTranslatef(0, 0, 4);
	glColor3ub(0, 255, 120);
	glBegin(GL_QUADS);
	glVertex3f(-49, 30, 0);
	glVertex3f(-49, 0, 0);
	glVertex3f(-49, 0, table_height * 2);
	glVertex3f(-49, 30, table_height * 2);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float mat_dif[] = { 0.2f, 0.2f , 0.0f };
	float mat_amb[] = { 0.2f, 0.2f , 0.2f };
	float mat_spec[] = { 0.6f, 0.6f , 0.6f };
	float mat_shininess = 0.1f * 128;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);


	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glPushMatrix();
	drawScene();
	glPopMatrix();
	glTranslatef(-100, 0, 0);
	glRotatef(180, 0, 0, 1);
	glScaled(1, -1, 1);
	drawScene();

	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1, 150.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	center_x = eye_x + eye_x * sin(rot_z) * cos(rot_y);
	center_y = eye_y + eye_x * sin(rot_z) * sin(rot_y);
	center_z = eye_z + eye_x * cos(rot_z);
	gluLookAt(eye_x, eye_y, eye_z,	// eye
		center_x, center_y, center_z,				// center
		0.0, 0.0, 1.0);		// up
}

void motion(int x, int y)
{
	//std::cout << x << " " << y << std::endl;
	rot_z -= ((mouseOldY - y) * 360.0f) / 50000.0f;
	rot_y += ((mouseOldX - x) * 360.0f) / 50000.0f;
	
	if (rot_y > 2*M_PI)
		rot_y -= 2*M_PI;

	if (rot_y < -2*M_PI)
		rot_y += 2*M_PI;

	if (rot_z > 2*M_PI)
		rot_z -= 2*M_PI;

	if (rot_z < -2*M_PI)
		rot_z += 2*M_PI;
	
	mouseOldX = x;
	mouseOldY = y;
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	center_x = eye_x + eye_x * sin(rot_z) * cos(rot_y);
	center_y = eye_y + eye_x * sin(rot_z) * sin(rot_y);
	center_z = eye_z + eye_x * cos(rot_z);
	gluLookAt(eye_x, eye_y, eye_z,	// eye
		center_x, center_y, center_z,				// center
		0.0, 0.0, 1.0);		// up
	
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
		mouseOldX = x;
		mouseOldY = y;
}

void key(unsigned char key, int x, int y)
{
	if (key == 27 || key == 'q' || key == 'Q')		//quit requested
		exit(0);
	if (key == 'w')
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		double step_x = (eye_x - center_x) *0.1;
		double step_y = step_x * (center_y - eye_y) / (eye_x - center_x);
		double step_z = step_x * (center_z - eye_z) / (eye_x - center_x);
		center_x -= step_x;
		eye_x -= step_x;
		center_y += step_y;
		eye_y += step_y;
		center_z += step_z;
		eye_z += step_z;
		gluLookAt(eye_x, eye_y, eye_z,	// eye
			center_x, center_y, center_z,				// center
			0.0, 0.0, 1.0);		// up

		glutPostRedisplay();
	}
	if (key == 's')
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		double step_x = -(eye_x - center_x) *0.1;
		double step_y = step_x * (center_y - eye_y) / (eye_x - center_x);
		double step_z = step_x * (center_z - eye_z) / (eye_x - center_x);
		center_x -= step_x;
		eye_x -= step_x;
		center_y += step_y;
		eye_y += step_y;
		center_z += step_z;
		eye_z += step_z;
		gluLookAt(eye_x, eye_y, eye_z,	// eye
			center_x, center_y, center_z,				// center
			0.0, 0.0, 1.0);		// up

		glutPostRedisplay();
	}
	if (key == 'a')
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		center_x -= (center_y - eye_y) * 0.1;
		eye_x -= (center_y - eye_y) * 0.1;
		center_y += (center_x - eye_x) * 0.1;
		eye_y += (center_x - eye_x) * 0.1;
		//center_z += step_z;
		//eye_z += step_z;
		gluLookAt(eye_x, eye_y, eye_z,	// eye
			center_x, center_y, center_z,				// center
			0.0, 0.0, 1.0);		// up

		glutPostRedisplay();
	}
	if (key == 'd')
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		center_x += (center_y - eye_y) * 0.1;
		eye_x += (center_y - eye_y) * 0.1;
		center_y -= (center_x - eye_x) * 0.1;
		eye_y -= (center_x - eye_x) * 0.1;
		//center_z -= (center_x - eye_x) * 0.1;
		//eye_z -= (center_x - eye_x) * 0.1;
		gluLookAt(eye_x, eye_y, eye_z,	// eye
			center_x, center_y, center_z,				// center
			0.0, 0.0, 1.0);		// up

		glutPostRedisplay();
	}
}



int main(int argc, char * argv[]) {
	glutInit(&argc, argv); //initialise glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL lab");  // create window
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	//glutPassiveMotionFunc(motion);
	glutMotionFunc(motion);
	init();
	glutMainLoop();
	return 0;
}