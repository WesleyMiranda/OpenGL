#include "CarregaObjeto.h"
#include <GL/freeglut.h>
#include <vector>

using namespace std;

Coord3D::Coord3D()
{
	x = 0;
	y = 0;
	z = 0;
}

Coord3D::Coord3D(float x_, float y_, float z_)
{
	x = x_;
	y = y_;
	z = z_;
}

Face::Face(int num, int a, int b, int c, int d)
{
	facenum = num;
	vertex[0] = a;
	vertex[1] = b;
	vertex[2] = c;
	vertex[3] = d;
	Quad = true;
}

Face::Face(int num, int a, int b, int c)
{
	facenum = num;
	vertex[0] = a;
	vertex[1] = b;
	vertex[2] = c;
	Quad = false;
}

Coord3D LoadObject::getVertex(string s)
{
	stringstream saved;
	float x, y, z;
	char c;

	saved << s;
	saved >> c >> x >> y >> z;

	Coord3D temp = Coord3D(x, y, z);

	return temp;
}
Coord3D LoadObject::getNormal(string s)
{
	stringstream saved;
	float x, y, z;
	string c;

	saved << s;
	saved >> c >> x >> y >> z;

	Coord3D temp = Coord3D(x, y, z);
	return temp;
}
Face LoadObject::getFace(string s, bool quad)
{
	int n, a, b, c, d;
	Face f = Face(0, 0, 0, 0);
	if (quad == true)
	{
		sscanf_s(s.c_str(), "f %d//%d %d//%d %d//%d %d//%d", &a, &n, &b, &n, &c, &n, &d, &n);
		f.vertex[0] = a;
		f.vertex[1] = b;
		f.vertex[2] = c;
		f.vertex[3] = d;
		f.facenum = n;
		f.Quad = quad;
	}

	else
	{
		sscanf_s(s.c_str(), "f %d//%d %d//%d %d//%d", &a, &n, &b, &n, &c, &n);
		f.vertex[0] = a;
		f.vertex[1] = b;
		f.vertex[2] = c;
		f.facenum = n;
		f.Quad = false;
	}
	return f;
}

int LoadObject::load(const char* objectName)
{
	vector<string> lines;
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
}