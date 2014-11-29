#ifndef INC_GUIDATA_H
#define INC_GUIDATA_H

#include <string>

#include "Data\Rect.h"
#include "Data\Vector2.h"
#include "Data\Vector3.h"
#include "Data\Vector4.h"

typedef enum GuiElementType
{
	IMAGE,
	TEXT
};

struct GuiElementVertexData
{
	Vector2 position;
	Vector2 size;
	Vector4 color;
	Vector4 source;
};

struct GuiElement
{
	GuiElement() :
		Z(0.0f),
		Angle(0.0f),
		Scale(1.0f),
		Type(GuiElementType::IMAGE)
	{
	}

	Rect Source;
	Rect Destination;
	Vector4 Color;
	float Z;
	float Angle;
	float Scale;
	std::string Texture;
	GuiElementType Type;
};

struct GuiText
{
	GuiText()
	{
	}

	Rect Destination;
	Vector4 Color;
	std::string Font;
	std::string Text;
};

const int MaxElementsPerTexture = 512;

#endif