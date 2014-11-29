#include "InputSystem.h"

InputSystem::InputSystem()
{
	m_directInput = 0;
	m_keyboard = 0;
	m_mouse = 0;


}

InputSystem::InputSystem(const InputSystem& other)
{

}

InputSystem::~InputSystem()
{

}

bool InputSystem::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, int playerNumber)
{
	HRESULT result;

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	m_mouseX = 0;
	m_mouseY = 0;

	_controllerNum = playerNumber - 1;

	result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
        if(FAILED(result))
        {
                return false;
        }

	// Initialize the direct input interface for the keyboard.
        result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
        if(FAILED(result))
        {
                return false;
        }

        // Set the data format.  In this case since it is a keyboard we can use the predefined data format.
        result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
        if(FAILED(result))
        {
                return false;
        }

	  // Set the cooperative level of the keyboard to not share with other programs.
        result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
        if(FAILED(result))
        {
                return false;
        }

	  // Now acquire the keyboard.
        result = m_keyboard->Acquire();
        if(FAILED(result))
        {
                return false;
        }

      // Initialize the direct input interface for the mouse.
        result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
        if(FAILED(result))
        {
                return false;
        }

        // Set the data format for the mouse using the pre-defined mouse data format.
        result = m_mouse->SetDataFormat(&c_dfDIMouse);
        if(FAILED(result))
        {
                return false;
        }

	// Set the cooperative level of the mouse to share with other programs.
        result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
        if(FAILED(result))
        {
                return false;
        }

	// Acquire the mouse.
        result = m_mouse->Acquire();
        if(FAILED(result))
        {
                return false;
        }

        return true;
}
	
void InputSystem::Shutdown()
{
	if(m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = 0;
	}

	if(m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = 0;
	}

	if(m_directInput)
	{
		m_directInput->Release();
		m_directInput = 0;
	}

	return;
}

bool InputSystem::Frame()
{
	bool result;

	result = Readkeyboard();
	if(!result)
	{
		return false;
	}

	result = ReadMouse();
	if(!result)
	{
		return false;
	}

	ProcessInput();

	return true;
}

bool InputSystem::Readkeyboard()
{
	HRESULT result;

	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if(FAILED(result))
	{
		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		} 
		else
		{
			return false;
		}
	}

	return true;
}

bool InputSystem::ReadMouse()
{
HRESULT result;

        result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
        if(FAILED(result))
        {
                if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
                {
                        m_mouse->Acquire();
                }
                else
                {
                        return false;
                }
        }

        return true;	
}

void InputSystem::ProcessInput()
{
	        // Update the location of the mouse cursor based on the change of the mouse location during the frame.
        m_mouseX += m_mouseState.lX;
        m_mouseY += m_mouseState.lY;

        // Ensure the mouse location doesn't exceed the screen width or height.
        if(m_mouseX > m_screenWidth)  { m_mouseX = m_screenWidth; }
        if(m_mouseY > m_screenHeight) { m_mouseY = m_screenHeight; }
        
        return;
}

XINPUT_STATE InputSystem::GetState()
{
    // Zeroise the state
    ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

    // Get the state
    XInputGetState(_controllerNum, &_controllerState);

    return _controllerState;
}

bool InputSystem::IsConnected()
{
    // Zeroise the state
    ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

    // Get the state
    DWORD Result = XInputGetState(_controllerNum, &_controllerState);

    if(Result == ERROR_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void InputSystem::Vibrate(int leftVal, int rightVal)
{
    // Create a Vibraton State
    XINPUT_VIBRATION Vibration;

    // Zeroise the Vibration
    ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

    // Set the Vibration Values
    Vibration.wLeftMotorSpeed = leftVal;
    Vibration.wRightMotorSpeed = rightVal;

    // Vibrate the controller
    XInputSetState(_controllerNum, &Vibration);
}

bool InputSystem::IsEscapePressed()
{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
        if(m_keyboardState[DIK_ESCAPE] & 0x80)
        {
                return true;
        }

        return false;
}

void InputSystem::GetMouseLocation(int& mouseX, int& mouseY)
{
        mouseX = m_mouseX;
        mouseY = m_mouseY;
        return;
}