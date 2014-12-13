#ifndef GUISYSTEM_H
#define GUISYSTEM_H

#include <map>
#include <vector>
#include <string>

#include "D3DRenderer.h"
#include "InputSystem.h"
#include "IGUIElement.h"

typedef std::vector<GuiElement> GuiElementVector;
typedef std::map<std::string, int> GuiBatchingIndexMap;
typedef std::map<std::string, Vector2> TextureDimensionMap;
typedef std::vector<GuiText> GuiScreenTextVec;

class GUISystem
{
public:
	GUISystem();
	GUISystem(const GUISystem&);
	~GUISystem();

	bool Initialize(float screenWidth, float screenHeight);
	void Shutdown();
	bool Frame();
	void Update(float deltaTime);

	bool Render();

	void AddElement(GuiElement element, float textureWidth, float textureHeight);
	//void AddFont(std::string name, FontSheet sheet);
	void AddText(std::string text, std::string font, Vector2 pos, Vector4 color);

private:
	void DrawElementsUsingTexture(GuiElement element, GuiElementVertexData& data);
	Vector2 PointToNdc(int x, int y, float z);
	void BuildElementQuad(const GuiElement& element, GuiElementVertexData& v);
	void BuildTextElements(GuiText textData, GuiElementVertexData* data);

private:

	GuiElementVector _elements;
	GuiScreenTextVec _text;
	GuiBatchingIndexMap _batchMap;
	TextureDimensionMap _textureDimensions;

	D3DRenderer* _D3D;
	InputSystem* _Input;

	float _screenWidth;
	float _screenHeight;
};

#endif