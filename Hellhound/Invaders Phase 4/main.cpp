#include <Windows.h>

#include "GameController.h"
#include "Graphics.h"
#include "Level_Loading.h"
#include "Starfield.h"

Graphics* graphics;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (uMsg == WM_DESTROY) {
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow) {
	srand(time(NULL));
	WNDCLASSEX windowClass;
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.lpszClassName = "MainWindow";
	windowClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowClass);

	//We want the main window to be SCREENWIDTHxSCREENHEIGHT not including the menu and border, this adjusts the size to that
	RECT rect = { 0, 0, WINDOWWIDTH, SCREENHEIGHT };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", GAMETITLE, WS_OVERLAPPEDWINDOW, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);

	if (!windowHandle) return -1;

	graphics = new Graphics();

	Level_Game::Init(graphics);

	if (!graphics->Init(windowHandle)) {
		delete graphics;
		return -1;
	}

	ShowWindow(windowHandle, nCmdShow);

	//MSG message;

	//GetMessage checks the queue and then waits until there is a message
	//while (GetMessage(&message, NULL, 0, 0)) {
	//	DispatchMessage(&message);
	//}

	//PeekMessage checks the message queue and if there is a message allows Dispatch
	//OTHERWISE it returns control to the program

	MSG message;
	message.message = WM_NULL;

	starfield sf = starfield(SCREENWIDTH, SCREENHEIGHT, graphics);
	GameController::LoadInitialLevel(new Level_Loading());
	Sleep(160);

	while (message.message != WM_QUIT) {
		//Can put windowHandle for the 2nd option
		//NULL is any message passed to any windows owned by this thread
		//Windowshandle will limit messages to the current window only
		//Options 3 and 4 can filter out (read the last keyboard or mouse message for ex.)
		//Last option is what you want to happen to the message (We want it removed)

		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			DispatchMessage(&message);
		}
		else {
			//UPDATE
			sf.updateStarfield();
			GameController::Update();
			graphics->BeginDraw();
			sf.render();
			GameController::Render();
			graphics->EndDraw();
		}
	}

	return 0;
}