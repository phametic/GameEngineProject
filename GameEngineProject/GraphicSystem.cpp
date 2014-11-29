#include "GraphicSystems.h"

GraphicSystems::GraphicSystems()
{
	_D3D = 0;
}


GraphicSystems::GraphicSystems(const GraphicSystems& other)
{
}


GraphicSystems::~GraphicSystems()
{
}

bool GraphicSystems::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	// Create the Direct3D object.
	_D3D = new D3DRenderer;
	if(!_D3D)
	{
		return false;
	}
	// Initialize the Direct3D object.
	result = _D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicSystems::Shutdown() {
	if(_D3D)
	{
		_D3D->Shutdown();
		delete _D3D;
		_D3D = 0;
	}
	return;
}

bool GraphicSystems::Frame()
{
	bool result;

	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}

bool GraphicSystems::Render()
{
	_D3D->BeginScene(0.0f, 0.2f, 0.4f, 1.0f);

	_D3D->EndScene();

	return true;
}