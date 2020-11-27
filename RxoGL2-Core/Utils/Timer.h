#pragma once
#include <iostream>
#include <chrono>
class Timer
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
public:
	Timer() { m_StartTimePoint = std::chrono::high_resolution_clock::now(); }
	~Timer() { Stop(); }
	void Stop()
	{
		auto endTimePoint = std::chrono::high_resolution_clock::now();
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
		auto duration = end - start;
		double ms = duration * 0.001;
		std::cout << duration << "us (" << ms << "ms)\n";
	}
};