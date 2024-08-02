#include "RiftTimer.h"

using namespace std::chrono;

RiftTimer::RiftTimer()
{
	last = steady_clock::now();
}

float RiftTimer::Mark()
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}

float RiftTimer::Peek() const
{
	return duration<float>(steady_clock::now() - last).count();
}
