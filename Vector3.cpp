#include <cassert>
#include <cmath>
#include "Vector3.h"

Vector3::Vector3()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vector3::Vector3(float nx, float ny, float nz)
{
	this->x = nx;
	this->y = ny;
	this->z = nz;
}

Vector3::Vector3(const Vector3& a)
{
	this->x = a.x;
	this->y = a.y;
	this->z = a.z;
}

void Vector3::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vector3::size() const
{
	return sqrt((this->x) * (this->x) + (this->y) * (this->y) + (this->z) * (this->z));
}

Vector3 Vector3::normal() const
{
	return Vector3((this->x) / size(), (this->y) / size(), (this->z) / size());
}

Vector3 Vector3::scale(const Vector3& a) const
{
	return Vector3((this->x) * a.x, (this->y) * a.y, (this->z) * a.z);
}

Vector3 Vector3::reflect(const Vector3& a) const //R=I-2(I���N)N ��������
{
	return (*this) - (a * (a * (*this))) * 2.0f;
}

Vector3 Vector3::project(const Vector3& a) const  //��a��ͶӰ����a(N���a)\|a|^2
{
	return a * (((*this) * a) / (a.size() * a.size()));
}

void Vector3::operator=(const Vector3& a)
{
	(this->x) = a.x;
	(this->y) = a.y;
	(this->z) = a.z;
}

Vector3 Vector3::operator+(const Vector3& a) const
{
	return Vector3((this->x) + a.x, (this->y) + a.y, (this->z) + a.z);
}

Vector3 Vector3::operator-(const Vector3& a) const
{
	return Vector3((this->x) - a.x, (this->y) - a.y, (this->z) - a.z);
}

Vector3 Vector3::operator*(float s) const
{
	return Vector3((this->x) * s, (this->y) * s, (this->z) * s);
}

float Vector3::operator*(const Vector3& a) const
{
	return (this->x) * a.x + (this->y) * a.y + (this->z) * a.z;
}

Vector3 Vector3::operator*=(float s)
{
	(*this) = (*this) * s;
	return (*this);
}

Vector3 Vector3::operator+=(const Vector3& a)
{
	(*this) = (*this) + a;
	return (*this);
}

bool Vector3::operator==(const Vector3& a)
{
	return (this->x == a.x) && (this->y == a.y) && (this->z == a.z);
}
