#pragma once
#include <chrono>

class FrameTimer
{
public:
	FrameTimer();
	float deltaTime();
private:
	std::chrono::steady_clock::time_point last;
};