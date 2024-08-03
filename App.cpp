#include "App.h"
#include <sstream>

App::App() : wnd(800, 600, "[DirectX 11] Rift Engine"){}

int App::Go()
{
	while (true) {
		// Process all messages pending, but to not block
		if (const auto ecode = Window::ProcessMessages()) {

			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}

		DoFrame();

		// Wait for messages or timeout to prevent high CPU usage
		MsgWaitForMultipleObjects(0, nullptr, FALSE, 1, QS_ALLEVENTS);
	}
}

void App::DoFrame()
{
	const float c = sin(timer.Peek() / 2.0f + 0.5f);
	wnd.Gfx().ClearBuffer(c, c, 1.0f);
	wnd.Gfx().EndFrame();
}
