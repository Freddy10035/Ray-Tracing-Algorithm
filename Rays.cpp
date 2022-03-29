#include <cmath>
#include <list>
#include <glut.h>
#include "Vector3.h"
#include "Rays.h"
#include "Objects.h"

using namespace std;

Ray::Ray(const Vector3& o, const Vector3& d)
{
	origin = o;
	direction = d.normal();
	depth = 0;
	distance = 0.0f;
	color = Vector3(0.0f, 0.0f, 0.0f);
	RefractionRatio = 1.0f;
	InSphere = false;
}

Ray::Ray(const Vector3& o, const Vector3& d, int n)
{
	origin = o;
	direction = d.normal();
	depth = n;
	distance = 0.0f;
	color = Vector3(0.0f, 0.0f, 0.0f);
	RefractionRatio = 1.0f;
	InSphere = false;
}

Ray::~Ray()
{
}

bool CompareDistance(const Collision& col1, const Collision& col2)
{
	return col1.distance < col2.distance;
}

Collision Ray::GetCollision(const list<Object*>& scene)
{
	Collision FirstCol;
	list<Collision> collisions;

	list<Object*>::const_iterator itr = scene.begin();
	for (; itr != scene.end(); itr++)
	{
		Collision col = (*itr)->CollideRay((*this));
		if (col.distance != -1.0f)
			collisions.push_back(col);
	}
	//no collision
	if (collisions.size() == 0)
	{
		FirstCol.distance = -1.0f;
		return FirstCol;
	}
	//tell which one is the first to collide according to the distance
	collisions.sort(CompareDistance);
	return *(collisions.begin());
}

Vector3 Ray::Shoot(const list<Object*>& scene, const list<Light>& lights, int depth)
{
	Collision col = GetCollision(scene);
	// get FirstCollison
	if (col.distance > 0.0f)
	{
		// emittance 
		color += col.material.emittance;
		list<Light>::const_iterator itr = lights.begin();
		for (; itr != lights.end(); itr++)
		{
			// Ambient
			color += (col.material.ambient).scale((*itr).color);
			Vector3 ToLight = ((*itr).position - col.point).normal();
			Ray ColToLight(col.point, ToLight);
			bool arrive = ColToLight.CanArrive(scene, (*itr));
			if (arrive) { continue; }
			else
			{
				// Diffuse 
				float normAngle = ToLight * col.normal;
				color += (col.material.diffuse).scale((*itr).color) * normAngle;
				// Specular 
				float specAngle = (ToLight + (direction * -1.0f)).normal() * col.normal;
				if (specAngle > 0.0f)
					color += col.material.specular.scale((*itr).color) * pow(specAngle, col.material.shininess);
			}
		}
		if (depth > 0)
		{
			if (col.material.reflection > 0.0f && !InSphere) //reflection
			{
				Vector3 dir = direction.reflect(col.normal).normal();
				Ray reflect(col.point, dir);
				reflect.InSphere = false;
				Vector3 reflectColor = reflect.Shoot(scene, lights, depth - 1);
				color += reflectColor * col.material.reflection;
			}

			if (col.material.transmission > 0.0f)   //refraction
			{
				float tmp1 = (direction * col.normal) * -1.0f;
				float n = RefractionRatio / (RefractionRatio == 1.0f ? col.material.RefractiveInd : 1.0f);
				float tmp2 = sqrt(1 - pow(n, 2) * (1 - pow(tmp1, 2)));

				Vector3 norm = (InSphere ? col.normal * -1.0f : col.normal);
				Vector3 dir = (direction * n) + (norm * (n * tmp1 - tmp2));
				Ray refract(col.point, dir);

				refract.InSphere = !InSphere;
				refract.RefractionRatio = col.material.RefractiveInd;

				Vector3 refractColor = refract.Shoot(scene, lights, depth - 1);
				color += refractColor * col.material.transmission;
				color *= 0.5f;
			}
		}
		return color;
	}
	color.set(0.0f, 0.0f, 0.0f);
	return color;
}

bool Ray::CanArrive(const list<Object*>& scene, const Light& light)
{
	Collision col = GetCollision(scene);
	if (col.distance == -1.0f)
	{
		return false;
	}
	if ((light.position - origin).size() > col.distance)
	{
		return true;
	}
	return false;
}