#include "GUISystem.h"

GUISystem::GUISystem()
{

}

GUISystem::GUISystem(const GUISystem&)
{

}

GUISystem::~GUISystem()
{

}

Vector2 GUISystem::PointToNdc(int x, int y, float z)
{
	Vector2 point;

	point.x = 2.0f * (float)x / _screenWidth - 1.0f;
	point.y = 1.0f - 2.0f * (float)y / _screenHeight;

	return point;
}

void GUISystem::BuildElementQuad(const GuiElement& element, GuiElementVertexData& v)
{
	const Rect& dest = element.Destination;
	const Rect& src = element.Source;
	Vector2 textureDimensions = _textureDimensions[element.Texture];

	v.position = PointToNdc(dest.x, dest.y, element.Z);
	v.size = Vector2(dest.width / _screenWidth * 2.0f, dest.height / _screenHeight * 2.0f);
	v.color = element.Color;

	v.source = Vector4(src.x / textureDimensions.x, src.height / textureDimensions.y, src.width / textureDimensions.x, src.y / textureDimensions.y);
}

bool GUISystem::Render()
{
	int size = _elements.size();
	int i = 0;
	for (; i < size; i++)
	{
		/*GuiElementVertexData* data = _D3D->GuiGetVertData();

		GuiElement element = _elements[i];
		DrawElementsUsingTexture(element, data[0]);

		_D3D->GuiReleaseVertData();

		_D3D->DrawIndexed(1, 0, 0, 3, element.Texture);*/
	}

	size = _text.size();
	int y = 0;
	for (; y < size; y++)
	{
		/*GuiElementVertexData* data = _renderer->GuiGetVertData();

		GuiText text = _text[y];
		BuildTextElements(text, data);

		_renderer->GuiReleaseVertData();

		int length = text.Text.length();
		_renderer->DrawIndexed(length, 0, 0, 3, text.Font);*/
	}

	_text.clear();

	return true;
}

void GUISystem::AddElement(GuiElement element, float textureWidth, float textureHeight)
{
	int index = -1;
	std::string texture = element.Texture;

	_textureDimensions[texture].x = textureWidth;
	_textureDimensions[texture].y = textureHeight;

	_elements.push_back(element);
}

void GUISystem::AddText(std::string text, std::string font, Vector2 pos, Vector4 color)
{
	GuiText guiText;
	guiText.Color = color;
	guiText.Destination = Rect(pos.x, pos.y, 0.0f, 0.0f);
	guiText.Font = font;
	guiText.Text = text;

	_text.push_back(guiText);
}

bool GUISystem::Initialize(float screenWidth, float screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	return true;
}

void GUISystem::Shutdown()
{
	_elements.clear();
	_batchMap.clear();
}