#ifndef _SCENE_H_
#define _SCENE_H_

#include <list>
#include "Objects.h"
#include "Vector3.h"
#include <glut.h>

using namespace std;
class Scene
{
public:
	list<Object*> objects;
	list<Light> lights;

	Scene() {}

	Scene(const list<Object*>& sceneObjects)
	{
		objects = sceneObjects;
	}

	~Scene()
	{
		list<Object*>::iterator itr = objects.begin();
		for (; itr != objects.end(); itr++)
		{
			delete (*itr);
		}
	}

	void AddObject(Object* newObject)
	{
		objects.push_back(newObject);
	}

	void AddLight(const Light& newLight)
	{
		lights.push_back(newLight);
	}
};
#endif