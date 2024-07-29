
#include "Window.h"
#include <exception>
#include <sstream>

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

		while (!wnd.mouse.IsEmpty()) {
			const auto e = wnd.mouse.Read();

			switch (e->GetType()) {
			case Mouse::Event::Type::Leave:
				wnd.SetTitle("gone!");
				break;
			case Mouse::Event::Type::Move:
				std::ostringstream oss;
				oss << "Mouse Position: (" << e->GetPosX() << "," << e->GetPosY() << ")";
				wnd.SetTitle(oss.str());
			}
		}
	}

	if (gResult == -1) {
		return -1;
	}

	return msg.wParam;
}
