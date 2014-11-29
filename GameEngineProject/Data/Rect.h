#ifndef INC_RECT_H
#define INC_RECT_H

class Rect
{
public:
	Rect():x(0.0f), y(0.0f), width(0.0f), height(0.0f)
	{
	}
	Rect(float x,float y, float width, float height):x(x), y(y), width(width), height(height)
	{
	}

	float x, y, width, height;
};

#endif