#pragma once
#include <chrono>
class Timer
{
public:
	float currentTime() {
		return std::chrono::duration<float>(std::chrono::steady_clock::now().time_since_epoch()).count();
	}
};

