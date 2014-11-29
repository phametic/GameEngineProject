#ifndef INC_INSTANCEDATA_H
#define INC_INSTANCEDATA_H

#include "Matrix.h"

class InstanceData
{
public:
	Matrix worldMatrix;
	unsigned int textureID;
	unsigned int tessellationFactor;
};

#endif