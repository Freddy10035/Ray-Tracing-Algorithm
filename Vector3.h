#ifndef _VECTOR3_H_
#define _VECTOR3_H_
class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float, float, float);
	Vector3(const Vector3&);

	void set(float, float, float);
	float size() const;
	Vector3 normal() const;   //normalization
	Vector3 scale(const Vector3&) const;
	Vector3 reflect(const Vector3&) const;
	Vector3 project(const Vector3&) const;

	bool operator==(const Vector3&);
	void operator=(const Vector3&);
	Vector3 operator+(const Vector3&) const;
	Vector3 operator-(const Vector3&) const;
	Vector3 operator*(float) const;
	float operator*(const Vector3&) const;
	Vector3 operator*=(float);
	Vector3 operator+=(const Vector3&);

};

#endif