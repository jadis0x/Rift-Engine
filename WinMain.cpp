
#include "Window.h"
#include <exception>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Window wnd(800, 300, "Rift Engine");

	MSG msg;
	BOOL gResult;

	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (wnd.kbd.KeyIsPressed(VK_SPACE)) {
			MessageBoxA(nullptr, "caption", "", MB_OK);
		}
	}

	if (gResult == -1) {
		return -1;
	}

	return msg.wParam;
}
