#ifndef GRAPHICSYSTEMS_H
#define GRAPHICSYSTEMS_H

#include "D3DRenderer.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicSystems {

	public:
	GraphicSystems();
	GraphicSystems(const GraphicSystems&);
	~GraphicSystems();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

	bool Render();

	D3DRenderer* _D3D;

};

#endif