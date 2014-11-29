#include "ModelData.h"

void ModelData::CalculateModelVectors()
{
	int faceCount, i, index;
	VertexData vertex1, vertex2, vertex3;
	Vector3 tangent, binormal, normal;


	faceCount = indices.size() / 3;

	index = 0;

	for(i=0; i<faceCount; i++)
	{
		vertex1 = vertices[indices[index]];
		index++;

		vertex2 = vertices[indices[index]];
		index++;

		vertex3 = vertices[indices[index]];
		index++;

		CalculateTangentBinormal(vertex1, vertex2, vertex3, tangent, binormal);


		vertices[indices[index-1]].tangent = tangent;
		vertices[indices[index-1]].binormal = binormal;

		vertices[indices[index-2]].tangent = tangent;
		vertices[indices[index-2]].binormal = binormal;

		vertices[indices[index-3]].tangent = tangent;
		vertices[indices[index-3]].binormal = binormal;
	}

	return;
}

void ModelData::CalculateTangentBinormal(VertexData vertex1, VertexData vertex2, VertexData vertex3,
					  Vector3& tangent, Vector3& binormal)
{
	float vector1[3], vector2[3];
	float tuVector[2], tvVector[2];
	float den;
	float length;

	vector1[0] = vertex2.position.x - vertex1.position.x;
	vector1[1] = vertex2.position.y - vertex1.position.y;
	vector1[2] = vertex2.position.z - vertex1.position.z;

	vector2[0] = vertex3.position.x - vertex1.position.x;
	vector2[1] = vertex3.position.y - vertex1.position.y;
	vector2[2] = vertex3.position.z - vertex1.position.z;

	tuVector[0] = vertex2.texture.x - vertex1.texture.x;
	tvVector[0] = vertex2.texture.y - vertex1.texture.y;

	tuVector[1] = vertex3.texture.x - vertex1.texture.x;
	tvVector[1] = vertex3.texture.y - vertex1.texture.y;

	den = 1.0f / (tuVector[0] * tvVector[1] - tuVector[1] * tvVector[0]);

	tangent.x = (tvVector[1] * vector1[0] - tvVector[0] * vector2[0]) * den;
	tangent.y = (tvVector[1] * vector1[1] - tvVector[0] * vector2[1]) * den;
	tangent.z = (tvVector[1] * vector1[2] - tvVector[0] * vector2[2]) * den;

	binormal.x = (tuVector[0] * vector2[0] - tuVector[1] * vector1[0]) * den;
	binormal.y = (tuVector[0] * vector2[1] - tuVector[1] * vector1[1]) * den;
	binormal.z = (tuVector[0] * vector2[2] - tuVector[1] * vector1[2]) * den;

	length = sqrt((tangent.x * tangent.x) + (tangent.y * tangent.y) + (tangent.z * tangent.z));
			
	tangent.x = tangent.x / length;
	tangent.y = tangent.y / length;
	tangent.z = tangent.z / length;

	length = sqrt((binormal.x * binormal.x) + (binormal.y * binormal.y) + (binormal.z * binormal.z));
			
	binormal.x = binormal.x / length;
	binormal.y = binormal.y / length;
	binormal.z = binormal.z / length;

	return;
}