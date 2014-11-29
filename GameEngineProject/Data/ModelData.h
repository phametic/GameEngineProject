#ifndef INC_MODELDATA_H
#define INC_MODELDATA_H

#include <vector>
#include <memory>

#include "VertexData.h"

typedef std::vector<VertexData> VertexDataVector;
typedef std::vector<unsigned int> IndicesVector;

class ModelData
{
public:
	void CalculateModelVectors();
	void CalculateTangentBinormal(VertexData, VertexData, VertexData, Vector3&, Vector3&);
	//void CalculateNormal(Vector3, Vector3, Vector3&);

	std::string name;
	VertexDataVector vertices;
	IndicesVector indices;
};

typedef std::shared_ptr<ModelData> ModelDataPtr;

#endif