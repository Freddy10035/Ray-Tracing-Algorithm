#include <cmath>
#include "Vector3.h"
#include "Objects.h"
#include "Rays.h"

#define PI 3.1415926f

Object::Object()
{
	color.set(1.0f, 0.0f, 0.0f);
}

Object::Object(const Vector3& pos)
{
	position = pos;
	color.set(1.0f, 0.0f, 0.0f);
}

Object::~Object()
{
}

void Object::setMaterial(const Material& mat)
{
	material = mat;
}

Sphere::Sphere() : Object() {}

Sphere::Sphere(const Vector3& pos, float r) : Object(pos)
{
	radius = r;
}

Sphere::~Sphere()
{
}

bool approximately(float a, float b)
{
	return (fabs(a - b) < 0.0001f);
}

Collision Sphere::CollideRay(const Ray& ray) const
{
	Collision col;

	float dt = (position - ray.origin).size();

	if (approximately(dt, radius) && ray.InSphere) //if ray is inSphere
	{
		Vector3 half = (position - ray.origin).project(ray.direction);
		col.distance = half.size() * 2.0f;
		col.point = ray.origin + half * 2;
		col.normal = col.point - position;
		col.material = material;
		return col;
	}

	Vector3 originToCenter = position - ray.origin;

	float angle = acos(originToCenter.normal() * ray.direction.normal());
	angle = (angle / PI) * 180.0f;

	if (angle > 90.0f)
	{
		col.distance = -1.0f;
		return col;
	}
	float v = originToCenter * ray.direction;
	float disc = radius * radius - ((originToCenter * originToCenter) - v * v);
	if (disc < 0.0f)
	{
		col.distance = -1.0f;
		return col;
	}

	float d = sqrt(disc);
	col.point = ray.origin + (ray.direction * (v - d));
	col.distance = (col.point - ray.origin).size();
	col.material = material;
	col.normal = (col.point - position).normal();
	return col;
}

Surface::Surface(const Vector3& point, const Vector3& norm, float w, float h) : Object(point)
{
	normal = norm;
	width = w;
	height = h;
}

Collision Surface::CollideRay(const Ray& ray) const
{
	Collision col;
	float cosangle = ray.direction * normal;

	if (cosangle >= 0.0f)
	{
		col.distance = -1.0f;
		return col;
	}

	col.distance = (position - ray.origin) * normal / cosangle;
	col.point = ray.origin + (ray.direction * col.distance);

	if (width > 0.0f && height > 0.0f)
	{
		if (fabs((col.point - position).x) > width || fabs((col.point - position).y) > height)
		{
			col.distance = -1.0f;
			return col;
		}
	}
	col.material = material;
	col.normal = normal;
	return col;
}