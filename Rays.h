#ifndef _RAYS_H_
#define _RAYS_H_
#define MAX_RECURSE_DEPTH 6

#include <list>
#include "Objects.h"

class Object;
class Sphere;
struct Light;
struct Collision;

using namespace std;

class Ray
{
private:
	int depth;

public:
	Vector3 origin;
	Vector3 direction;
	Vector3 color;
	float distance;
	float RefractionRatio;
	bool InSphere;

	Ray(const Vector3& o, const Vector3& d);
	Ray(const Vector3& o, const Vector3& d, int n);
	~Ray();

	Collision GetCollision(const list<Object*>& scene);
	Vector3 Shoot(const list<Object*>& scene, const list<Light>& lights, int depth);
	bool CanArrive(const list<Object*>& scene, const Light& light);
};

#endif