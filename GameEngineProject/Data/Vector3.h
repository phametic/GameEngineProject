#ifndef INC_VECTOR3_H
#define INC_VECTOR3_H

#include <math.h>

class Vector3 
{
public:
	Vector3():x(0.0f),y(0.0f),z(0.0f)
	{
	}
	Vector3(float x,float y,float z):x(x),y(y),z(z)
	{
	}

	static Vector3 Normalize(Vector3);

	float x,y,z;
};

Vector3 operator+(const Vector3 &vec1, const Vector3 &vec2);
Vector3 operator+=(const Vector3 &vec1, const Vector3 &vec2);
Vector3 operator-(const Vector3 &vec1, const Vector3 &vec2);
Vector3 operator/(const Vector3 &vec1, const float num);
Vector3 operator*(const Vector3 &vec1, unsigned long num);
Vector3 operator*(const Vector3 &vec1, const float num);

#endif