#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#include <XInput.h>

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "XInput.lib")

class InputSystem
{

public:
	InputSystem();
	InputSystem(const InputSystem&);
	~InputSystem();

	bool Initialize(HINSTANCE, HWND, int, int, int);
	void Shutdown();

	bool Frame();

	bool IsEscapePressed();
	void GetMouseLocation(int&, int&);

		XINPUT_STATE GetState();
    bool IsConnected();
    void Vibrate(int leftVal = 0, int rightVal = 0);

private:
	bool Readkeyboard();
	bool ReadMouse();
	bool ReadGamepad();
	void ProcessInput();

	 IDirectInput8* m_directInput;
     IDirectInputDevice8* m_keyboard;
     IDirectInputDevice8* m_mouse;

	unsigned char m_keyboardState[256];
    DIMOUSESTATE m_mouseState;

    int m_screenWidth, m_screenHeight;
    int m_mouseX, m_mouseY;

	XINPUT_STATE _controllerState;
    int _controllerNum;

};

#endif