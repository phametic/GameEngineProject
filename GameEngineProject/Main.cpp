// include the basic windows header file
#include "engine.h"

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{

	Engine* engine;
	bool result;

	engine = new Engine;
	if (!engine)
	{
		return 0;
	}
    
	result = engine->Initialize();
	if (result)
	{
		engine->Run();
	}

    return 0;
}

