#ifndef INC_VECTOR2_H
#define INC_VECTOR2_H

class Vector2
{
public:
	Vector2():x(0.0f),y(0.0f)
	{
	}
	Vector2(float x,float y):x(x),y(y)
	{
	}

	float x,y;
};

Vector2 operator+(const Vector2 &vec1, const Vector2 &vec2);

#endif