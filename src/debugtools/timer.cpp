#include <timer.hpp>
#include <algorithm>
#include <thread>

void Instrumentor::beginSession(const std::string& name, const std::string& filepath)
{
	m_outputStream.open(filepath);
	writeHeader();
	m_currentSession = new InstrumentationSession{ name };
}

void Instrumentor::endSession()
{
	writeFooter();
	m_outputStream.close();
	delete m_currentSession;
	m_currentSession = nullptr;
	m_profileCount = 0;
}

void Instrumentor::writeProfile(const ProfileResult& result)
{
	if (m_profileCount++ > 0) m_outputStream << ",";

	std::string name = result.Name;
	std::replace(name.begin(), name.end(), '"', '\'');

	m_outputStream << "{";
	m_outputStream << "\"cat\":\"function\",";
	m_outputStream << "\"dur\":\"" << (result.End - result.Start) << "\",";
	m_outputStream << "\"name\":\"" << name << "\",";
	m_outputStream << "\"ph\":\"X\",";
	m_outputStream << "\"pid\":0,";
	m_outputStream << "\"tid\":" << result.ThreadID << ",";
	m_outputStream << "\"ts\":" << result.Start;
	m_outputStream << "}";

	m_outputStream.flush();
}

void Instrumentor::writeHeader()
{
	m_outputStream << "{\"otherData\": {},\"traceEvents\":[";
	m_outputStream.flush();
}

void Instrumentor::writeFooter()
{
	m_outputStream << "]}";
	m_outputStream.flush();
}

Instrumentor& Instrumentor::get()
{
	static Instrumentor instance;
	return instance;
}


Timer::Timer(const char* name)
	: m_name(name),
	  m_stopped(false),
	  m_startPoint(std::chrono::high_resolution_clock::now()) {}

Timer::~Timer() { if (!m_stopped) stop(); }

void Timer::stop()
{
	auto endPoint{ std::chrono::high_resolution_clock::now() };

	long long start
	{
		std::chrono::time_point_cast<std::chrono::microseconds>
		(m_startPoint).time_since_epoch().count()
	};
	long long end
	{
		std::chrono::time_point_cast<std::chrono::microseconds>
		(endPoint).time_since_epoch().count()
	};
	m_stopped = true;

	uint32_t threadID
	{ 
		static_cast<uint32_t>(std::hash<std::thread::id>{}(std::this_thread::get_id())) 
	};
	Instrumentor::get().writeProfile({m_name, start, end, threadID});

	//float duration{ (end - start) * 0.001f };
}




