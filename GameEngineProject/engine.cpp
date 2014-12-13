#include "engine.h"

Engine::Engine()
{
	_Graphics = 0;
	_Input = 0;
}

Engine::Engine(const Engine& other)
{
}

Engine::~Engine()
{
}

bool Engine::Initialize()
{
	int screenWidth, screenHeight;
	bool result;

	screenWidth = SCREEN_WIDTH;
	screenHeight = SCREEN_HEIGHT;


	InitializeWindows(screenWidth, screenHeight);

	_Input = new InputSystem;
	if(!_Input)
	{
		return false;
	}
	result = _Input->Initialize(hInstance, hWnd, screenWidth, screenHeight, 1);
	if(!result)
	{
		MessageBox(hWnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	_Graphics = new GraphicSystems;
	if (!_Graphics)
	{
		return false;
	}
	result = _Graphics->Initialize(screenWidth, screenHeight, hWnd);
	if (!result)
	{
		return false;
	}
	_GUI = new GUISystem;
	if(!_GUI)
	{
		return false;
	}
	result = _GUI->Initialize(screenWidth, screenHeight);

	_Sound = new SoundSystem;
	if(!_Sound)
	{
		return false;
	}
	result = _Sound->Initialize();

	_Sound->createSound(&soundSample, "Assets/music.mp3");
	_Sound->playSound(soundSample, true);

	return true;
}

void Engine::Run()
{

	MSG msg;
	bool done, result;

	// clear out the window class for use
    ZeroMemory(&msg, sizeof(MSG));

	done = false;
	 // Enter the infinite message loop
    while(!done)
    {
        // Check to see if any messages are waiting in the queue
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // translate keystroke messages into the right format
            TranslateMessage(&msg);

            // send the message to the WindowProc function
            DispatchMessage(&msg);
        }
		// check to see if it's time to quit
            if(msg.message == WM_QUIT) {
                done = true;
			}
        else
        {
			result = Frame();
			if(!result)
			{
				MessageBox(hWnd, L"Frame Processing Failed", L"Error", MB_OK);
				done = true;
			}
        }
			if(_Input->IsEscapePressed() == true)
                {
                        done = true;
                }
			if(_Input->IsConnected())
			{
				if(_Input->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
				{
					_Input->Vibrate(65535, 0);
				}
				 if(_Input->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
				{
					_Input->Vibrate(0, 65535);
				}

				if(_Input->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
				{
					_Input->Vibrate(65535, 65535);
				}

				if(_Input->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
				{
					_Input->Vibrate();
				}

				if(_Input->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
				{
					break;
				}
			
			}
    }

	return;
}

bool Engine::Frame()
{
	bool result;

	result = _Graphics->Render();
	if(!result)
	{
		return false;

	}

	result = _Input->Frame();
	if(!result)
	{
		return false;
	}

	return true;
}

LRESULT CALLBACK Engine::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch(umsg)
	{
		// Any other messages send to the default message handler as our application won't make use of them.
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}

void Engine::Shutdown()
{
	if (_Graphics)
	{
		_Graphics->Shutdown();
		delete _Graphics;
		_Graphics = 0;
	}

	if(_Input)
	{
		_Input->Shutdown();
		delete _Input;
		_Input = 0;
	}

	_Sound->releaseSound(soundSample);

	UnregisterClass(applicationName, hInstance);
	hInstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}

void Engine::InitializeWindows(int& screenWidth, int& screenHeight)
{
    // this struct holds information for the window class
    WNDCLASSEX wc;

	ApplicationHandle = this;

	applicationName = L"Engine";

	hInstance = GetModuleHandle(NULL);

	 // fill in the struct with the needed information
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursorFromFile(L"cursor.cur");
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// register the window class
    RegisterClassEx(&wc);

	screenWidth = 800;
	screenHeight = 600;

    // calculate the size of the client area
    RECT wr = {0, 0, screenWidth, screenHeight};    // set the size, but not the position
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size


	// create the window and use the result as the handle
    hWnd = CreateWindowEx(WS_EX_APPWINDOW,
                          applicationName,    // name of the window class
                          applicationName,    // title of the window
                          WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,    // window style
                          300,    // x-position of the window
                          300,    // y-position of the window
						  SCREEN_WIDTH,    // width of the window
                          SCREEN_HEIGHT,    // height of the window
                          NULL,    // we have no parent window, NULL
                          NULL,    // we aren't using menus, NULL
                          hInstance,    // application handle
                          NULL);    // used with multiple windows, NULL

	 // display the window on the screen
    ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

	return;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch(message)
    {
        case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
    }

    // Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}