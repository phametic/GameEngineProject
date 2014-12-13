#ifndef _ENGINE_H_
#define _ENGINE_H_

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include "GraphicSystems.h"
#include "InputSystem.h"
#include "GUISystem.h"
#include "SoundSystem.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

class Engine {

public:

	Engine();
	Engine(const Engine&);
	~Engine();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	LPCWSTR applicationName;
	HINSTANCE hInstance;
	HWND hWnd;
	void InitializeWindows(int&, int&);
	bool Frame();

	GraphicSystems* _Graphics;
	InputSystem* _Input;
	GUISystem* _GUI;
	SoundSystem* _Sound;

	SoundClass soundSample;
};

	// the WindowProc function prototype
	static LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
	//LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static Engine* ApplicationHandle = 0;

#endif