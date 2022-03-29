#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Scene.h"
#include "Objects.h"
#include "Rays.h"
#include "Vector3.h"
#include <glut.h>

using namespace std;

int width = 0;
int height = 0;
Scene* scene = new Scene();

void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float* pixels = new float[3 * width * height];

	Vector3 Camera(0.0f, 0.0f, -5.0f);
	Vector3 DatumPoint(-1.0f, -1.0f, 0.5f);
	Vector3 AddY(0.0f, 2.0f, 0.0f);
	Vector3 AddX(2.0f, 0.0f, 0.0f);

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			float RatioW = (float)w / width;
			float RatioH = (float)h / height;
			float py = (DatumPoint + (AddY * RatioH)).y;
			float px = (DatumPoint + (AddX * RatioW)).x;

			Vector3 PlanePoint(px, py, 0.5f);
			Ray ray(Camera, PlanePoint - Camera);
			ray.Shoot(scene->objects, scene->lights, 6);

			pixels[(h * width + w) * 3 + 0] = ray.color.x;
			pixels[(h * width + w) * 3 + 1] = ray.color.y;
			pixels[(h * width + w) * 3 + 2] = ray.color.z;
		}
	}

	glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);
	glFlush();

	delete[] pixels;
}

void InsertObjects(void)
{
	Light light1;
	light1.color.set(1.0f, 1.0f, 1.0f);
	light1.position.set(-50.0f, 100.0f, 5.0f);
	scene->AddLight(light1);

	Material green;
	green.ambient.set(0.0f, 0.0f, 0.0f);
	green.diffuse.set(0.1f, 0.35f, 0.1f);
	green.specular.set(0.45f, 0.55f, 0.45f);
	green.emittance.set(0.2f, 0.2f, 0.2f);
	green.shininess = 5;
	green.reflection = 0.5f;
	green.shininess = 30;

	Material gold;
	gold.ambient.set(0.247f, 0.2f, 0.075f);
	gold.diffuse.set(0.75f, 0.606f, 0.227f);
	gold.specular.set(0.628f, 0.556f, 0.366f);
	gold.shininess = 40;
	gold.reflection = 0.3f;
	gold.transmission = 0.0f;
	gold.RefractiveInd = 0.0f;

	Material floor;
	floor.ambient.set(0.05f, 0.05f, 0.05f);
	floor.diffuse.set(0.5f, 0.5f, 0.5f);
	floor.specular.set(0.7f, 0.7f, 0.7f);
	floor.shininess = 8;
	floor.reflection = 0.5f;
	floor.transmission = 0.0f;
	floor.RefractiveInd = 0.0f;

	Sphere* ball1 = new Sphere(Vector3(-0.3f, 0.5f, 8.0f), 1.0f);
	ball1->setMaterial(gold);
	scene->AddObject(ball1);

	Sphere* ball2 = new Sphere(Vector3(1.2f, -0.5f, 9.0f), 0.6f);
	ball2->setMaterial(green);
	scene->AddObject(ball2);

	Surface* surface1 = new Surface(Vector3(0.0f, -2.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), 100.0f, 100.0f);
	surface1->setMaterial(floor);
	scene->AddObject(surface1);
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	InsertObjects();
}

void resize(int w, int h)
{
	width = w;
	height = h;

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("CG_Assignment_RayTracing");
	init();
	glutReshapeFunc(resize);
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}
