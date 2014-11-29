#ifndef INC_VECTOR4_H
#define INC_VECTOR4_H

class Vector4
{
public:
	Vector4():x(0.0f),y(0.0f),z(0.0f),w(0.0)
	{
	}
	Vector4(float x,float y,float z, float w):x(x),y(y),z(z),w(w)
	{
	}

	float x,y,z,w;
};

#endif