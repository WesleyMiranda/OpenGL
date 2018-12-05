#include <GL\freeglut>
#include <iostream>

using namespace std;

float cam_ang = 0, ang = 0;
float size = 5;
int LARGURA = 800, ALTURA = 600;
int FPS = 35;

void inicia3D();
void desenha();
void move(int v);
void desenhaCubo(float size);

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(LARGURA, ALTURA);

	inicia3D();

	glutDisplayFunc(desenha);
	glutTimerFunc(1000 / FPS, move, 0);
	//glutMouseFunc(criaPts);
	glutMainLoop();

	return 0;
}

void inicia3D()
{
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (double)LARGURA / ALTURA, 1.0, 500);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
}

void desenha()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0, 0, -10);
	desenhaCubo(size);
	glutSwapBuffers();

}

void desenhaCubo(float size)
{

	//frontal
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, size / 2);
	glEnd();
	//lateral direira
	glBegin(GL_QUADS);
	glColor3f(1, 1, 0);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(size / 2, size / 2, -size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();
	//Superior
	glBegin(GL_QUADS);
	glColor3f(1, 0, 1);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glEnd();
	//Inferior
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glEnd();
	//Lateral esquerda
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glEnd();
	//Traseira
	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
	glVertex3f(size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glEnd();
}

void move(int v)
{
	//Translação
	cam_ang += 1;
	glutPostRedisplay();
	glutTimerFunc(25, move, 0);

}


