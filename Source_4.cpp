#include	<stdio.h>
#include	<math.h>
#include	<iostream>
#include	"glut.h"

#define M_PI           3.14159265358979323846  /* pi */

GLdouble eye_x = 2.0, eye_y = 2.0, eye_z = 2.0;
GLdouble rot_x = 0.0, rot_y = 0.0, rot_z = 0.0;

GLdouble light_x = 5.0, light_y = 0.0, light_z = 4.0;
GLdouble center_x = 0.0, center_y = 0.0, center_z = 0.0;


int			mouseOldX = 0;
int			mouseOldY = 0;

/////////////////////////////////////////////////////////////////////////////////

GLfloat light_position[] = { 3.0, 3.0, 3.0, 0.0 };

GLuint texture;


int Load_Texture(const char* path)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//float color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glGenerateMipmap(GL_TEXTURE_2D);
	//SOIL_load_image("texture.bmp")


	unsigned char *data; // текстура
	unsigned char header[54];

	int width, height; // ширина и высота изображения

	FILE *file;

	fopen_s(&file, path, "rb");

	if (file == NULL) return 0;

	if (fread(header, 1, 54, file) != 54) { // У нас проблемы, если не смогли прочитать 54 байта
		printf("Not a correct BMP file\n");
		return 0;
	}

	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	//выделение памяти под изображение
	data = (unsigned char *)malloc(width * height * 3);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	// BGR в RGB
	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];
		data[index] = R;
		data[index + 2] = B;

	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	return 1;
}


void init() {
	if(!Load_Texture("jupitermap.bmp"))
	{
		exit(0);
	}
	glClearColor(0.0, 0.0, 0.0, -1.0);
	glEnable(GL_DEPTH_TEST);

	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF,	20) ;

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);

	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

struct coord
{
	float x;
	float y;
	float z;
};

void Sphere_Coord(float lat, float longi, coord* cor)
{
	float alpha = 2 * M_PI * lat;
	float gamma = M_PI * longi;
	float x = cos(gamma) * cos(alpha);
	float y = cos(gamma) * sin(alpha);
	float z = sin(gamma);
	cor->x = x;
	cor->y = y;
	cor->z = z;
}

const int N = 20;
const int M = 20;

void sphere()
{
	glBegin(GL_QUADS);
	for (float i = 0; i < N; i++)
		for (float j = -M; j < M; j++)
		{
			coord p1;
			coord p2;
			coord p3;
			coord p4;

			Sphere_Coord(i / N, j / (2 * M), &p1);
			Sphere_Coord(i / N, (j + 1) / (2 * M), &p2);
			Sphere_Coord((i + 1) / N, j / (2 * M), &p4);
			Sphere_Coord((i + 1) / N, (j + 1) / (2 * M), &p3);

			float s = i;
			float t = j+M;

			glNormal3f(p1.x, p1.y, p1.z);
			glTexCoord2f(s / N, t / (2 * M));
			glVertex3f(p1.x, p1.y, p1.z);

			glNormal3f(p4.x, p4.y, p4.z);
			glTexCoord2f((s + 1) / N, t / (2 * M));
			glVertex3f(p4.x, p4.y, p4.z);

			glNormal3f(p3.x, p3.y, p3.z);
			glTexCoord2f((s + 1) / N, (t + 1) / (2 * M));
			glVertex3f(p3.x, p3.y, p3.z);

			glNormal3f(p2.x, p2.y, p2.z);
			glTexCoord2f(s / N, (t + 1) / (2 * M));
			glVertex3f(p2.x, p2.y, p2.z);
		}
	glEnd();
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotatef(rot_x, 1, 0, 0);
	glRotatef(rot_y, 0, 1, 0);
	glRotatef(rot_z, 0, 0, 1);
	
	sphere();
	
	
	glColor3f(1, 1, 1);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 2);
	glVertex3f(0, 1, 2);
	glVertex3f(1, 1, 2);
	glVertex3f(1, 0, 2);
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