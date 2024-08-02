#pragma once

#include "Window.h"
#include "RiftTimer.h"

class App {
public:
	App();
	// Master frame / message loop
	int Go();
private:
	void DoFrame();
private:
	Window wnd;
	RiftTimer timer;
};