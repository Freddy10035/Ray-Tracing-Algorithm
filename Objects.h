#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>

#include "Vector3.h"
#include "Rays.h"

using namespace std;

class Vector3;
class Ray;

struct Material
{
	Vector3 ambient;
	Vector3 diffuse;
	Vector3 specular;
	Vector3 emittance;
	float shininess;
	float reflection;
	float transmission;
	float RefractiveInd;
};

struct Collision {
	Material material;
	Vector3 point;
	Vector3 normal;
	float distance;
};

struct Light
{
	Vector3 position;
	Vector3 color;
};

class Object
{
public:
	Vector3 position;
	Vector3 color;
	Material material;

	Object();
	Object(const Vector3& pos);
	~Object();

	void setMaterial(const Material& mat);
	virtual Collision CollideRay(const Ray& ray) const = 0;
};

class Sphere : public Object
{
public:
	float radius;

	Sphere();
	Sphere(const Vector3& pos, float r);
	~Sphere();
	Collision CollideRay(const Ray& ray) const;

};

class Surface : public Object
{
public:
	Vector3 normal;
	float width;
	float height;

	Surface(const Vector3& point, const Vector3& norm, float x, float y);
	Collision CollideRay(const Ray& ray) const;
};

#endif