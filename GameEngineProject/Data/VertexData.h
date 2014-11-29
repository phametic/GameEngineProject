#ifndef INC_VERTEXDATA_H
#define INC_VERTEXDATA_H

#include "Vector3.h"
#include "Vector2.h"

class VertexData
{
public:
	Vector3 position;
	Vector2 texture;
	Vector3 normal;
	Vector3 tangent;
	Vector3 binormal;
};

#endif