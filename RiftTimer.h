#pragma once

#include <chrono>

class RiftTimer {
public:
	RiftTimer();
	float Mark();
	float Peek() const;
private:
	std::chrono::steady_clock::time_point last;
};