#pragma once
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <thread>

struct ProfileResult
{
	std::string Name;
	long long Start;
	long long End;
	uint32_t ThreadID;
};

struct InstrumentationSession
{
	std::string Name;
};

class Instrumentor
{
public:
	Instrumentor()
		: m_currentSession(nullptr), m_profileCount(0) 
	{}
	void beginSession(const std::string& name, const std::string& filepath = "result.json");
	void endSession();
	void writeProfile(const ProfileResult& result);
	void writeHeader();
	void writeFooter();
	static Instrumentor& get();
private:
	InstrumentationSession* m_currentSession;
	std::ofstream m_outputStream;
	int m_profileCount;
};


class Timer
{
public:
	Timer(const char* name);
	~Timer();
	
	void stop();
private:
	const char* m_name;
	std::chrono::time_point<std::chrono::steady_clock> m_startPoint;
	bool m_stopped;
};


struct TimingResultUI
{
	const char* Name;
	float Time;
};
template<typename Fn>
class UITimer
{
public:
	UITimer(const char* name, Fn&& func) 
		: 
		m_name(name),
		m_func(func),
		m_stop(false),
		m_startPoint(std::chrono::high_resolution_clock::now()) {}

	~UITimer() { if (!m_stop) stop(); }

	void stop()
	{
		auto endPoint{ std::chrono::high_resolution_clock::now() };

		long long start{ std::chrono::time_point_cast<std::chrono::microseconds>(m_startPoint).time_since_epoch().count() };
		long long end{ std::chrono::time_point_cast<std::chrono::microseconds>(endPoint).time_since_epoch().count() };

		m_stop = true;
		const float duration { (end - start) * 0.001f };
		m_func({ m_name, duration });
	}
private:	
	const char* m_name;
	Fn m_func;
	std::chrono::time_point<std::chrono::steady_clock> m_startPoint;
	bool m_stop;
};


