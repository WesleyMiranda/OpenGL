#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::string;

struct Coord3D
{
	float x;
	float y;
	float z;
	Coord3D();
	Coord3D(float x_, float y_, float z_);
};

struct Face
{
	bool Quad;
	int vertex[4];
	int facenum;
	Face(int num, int a, int b, int c, int d);
	Face(int num, int a, int b, int c);
};

class LoadObject
{
	int ID;
	vector<Coord3D>normal;
	vector<Coord3D>vertex;
	vector<Face> face;

	Coord3D getVertex(string s);
	Coord3D getNormal(string s);
	Face getFace(string s, bool quad);

	int load(const char* objectName);
};