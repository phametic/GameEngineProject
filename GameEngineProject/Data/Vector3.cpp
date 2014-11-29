#include "Vector3.h"

Vector3 Vector3::Normalize(Vector3 in)
{
	float u = sqrt(in.x * in.x + in.y * in.y + in.z * in.z);
	Vector3 out = Vector3(in.x / u, in.y / u, in.z / u);

	return out;
}

Vector3 operator+(const Vector3 &vec1, const Vector3 &vec2)
{
	return Vector3(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

Vector3 operator+=(const Vector3 &vec1, const Vector3 &vec2)
{
	return Vector3(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

Vector3 operator-(const Vector3 &vec1, const Vector3 &vec2)
{
	return Vector3(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}

Vector3 operator/(const Vector3 &vec1, const float num)
{
	return Vector3(vec1.x / num, vec1.y / num, vec1.z / num);
}

Vector3 operator*(const Vector3 &vec1, unsigned long num)
{
	return Vector3(vec1.x * num, vec1.y * num, vec1.z * num);
}

Vector3 operator*(const Vector3 &vec1, const float num)
{
	return Vector3(vec1.x * num, vec1.y * num, vec1.z * num);
}