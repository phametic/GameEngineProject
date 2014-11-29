#ifndef INC_MATERIAL_H
#define INC_MATERIAL_H

#include "Vector4.h"

struct Material
{
	Vector4 ambient;
	Vector4 diffuse;
	Vector4 specular;
};

#endif