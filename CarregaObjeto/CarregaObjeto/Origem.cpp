#include <GL\freeglut.h>
#include "CarregaObjeto.h"

const int LARGURA = 800, ALTURA = 600;
float ang = 0;
int FPS = 50;
int OBJECT;
string OBJECT_NAME = "cubo.obj";





Face getFace(string s, bool quad)
{
	
}

/*int loadObject(const char* objectName)
{
	vector<Coord3D>normal;
	vector<Coord3D>vertex;
	vector<string> lines;
	vector<Face> face;
	ifstream read;

	read.open(objectName);
	if (!read.is_open())
		cout << "Não foi possível iniciar o arquivo";

	while (read.good())
	{
		string line;
		getline(read, line);
		lines.push_back(line);
	}

	for (int i = 0; i < lines.size(); i++)
	{
		if (lines[i][0] == '#')
			continue;
		else if (lines[i][0] == 'v'&&lines[i][1] == ' ')
			vertex.push_back(getVertex(lines[i]));
		else if (lines[i][0] == 'v'&&lines[i][1] == 'n')
			normal.push_back(getNormal(lines[i]));
		else if (lines[i][0] == 'f')
		{
			if (count(lines[i].begin(), lines[i].end(), ' ') == 4)
				face.push_back(getFace(lines[i], true));
			else
				face.push_back(getFace(lines[i], false));
		}
	}

	int num = glGenLists(1);
	glNewList(num, GL_COMPILE);
	for (int i = 0; i < face.size(); i++)
	{
		if (face[i].Quad) 
		{
			glBegin(GL_QUADS);
			glNormal3f(normal[face[i].facenum - 1].x, normal[face[i].facenum - 1].y, normal[face[i].facenum - 1].z);
			glVertex3f(vertex[face[i].vertex[0] - 1].x, vertex[face[i].vertex[0] - 1].y, vertex[face[i].vertex[0] - 1].z);
			glVertex3f(vertex[face[i].vertex[1] - 1].x, vertex[face[i].vertex[1] - 1].y, vertex[face[i].vertex[1] - 1].z);
			glVertex3f(vertex[face[i].vertex[2] - 1].x, vertex[face[i].vertex[2] - 1].y, vertex[face[i].vertex[2] - 1].z);
			glVertex3f(vertex[face[i].vertex[3] - 1].x, vertex[face[i].vertex[3] - 1].y, vertex[face[i].vertex[3] - 1].z);
			glEnd();
		}
		else
		{
			glBegin(GL_QUADS);
			glNormal3f(normal[face[i].facenum - 1].x, normal[face[i].facenum - 1].y, normal[face[i].facenum - 1].z);
			glVertex3f(vertex[face[i].vertex[0] - 1].x, vertex[face[i].vertex[0] - 1].y, vertex[face[i].vertex[0] - 1].z);
			glVertex3f(vertex[face[i].vertex[1] - 1].x, vertex[face[i].vertex[1] - 1].y, vertex[face[i].vertex[1] - 1].z);
			glVertex3f(vertex[face[i].vertex[2] - 1].x, vertex[face[i].vertex[2] - 1].y, vertex[face[i].vertex[2] - 1].z);
			glEnd();
		}
	}
	glEndList();

	return num;
}*/

void desenha()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	float pos[] = {2, 2, 5, 1};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	glTranslatef(0, 0, -5);
	glRotatef(ang, 1, 1, 1);

	glCallList(OBJECT);

	glutSwapBuffers();
}

void inicia3D()
{
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (double)LARGURA/ALTURA, 1.0, 500);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float color[] = { 1, 1, 1, 1 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
	//OBJECT = loadObject("CuboMaterial.obj");
	OBJECT = LoadObject::load("monkey.obj");

}

void teclado(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: //Esc
		exit(0);

	}
}

void move(int valor)
{
	ang += 0.5;
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, move, 0);
}

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(LARGURA, ALTURA);
	glutCreateWindow("UFR - Blender");

	inicia3D();

	glutDisplayFunc(desenha);
	glutKeyboardFunc(teclado);
	glutTimerFunc(1000 / FPS, move, 0);
	glutMainLoop();
	return 0;
}
