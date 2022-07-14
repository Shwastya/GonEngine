#include "GonEngine/engine/log.hpp"
#include "sinks/stdout_color_sinks.h"

namespace gon
{
	// Logmanager implementation
	LogManager::LogManager()
	{
		//m_Log = new Log();
		m_log = std::make_unique<Log>();
	}

	// encapsulado con unique m_Log, no necesita destructor.
	/*LogManager::~LogManager()
	{
		delete m_Log;
	}*/

	// Return Singleton instance
	LogManager& LogManager::p()
	{
		static LogManager instance;
		return instance;
	}

	SLog& LogManager::get()
	{
		return *m_log;
	}

	void LogManager::switchLog(const LogType type)
	{
		// for future logging 
		// switching implementations 
	}

	Log::Log() { init(); }

	// current Log implementation
	void Log::init()
	{
		/* STRING FORMAT EXAMPLES: */
		// %^ - Start color range (can be used only once)
		// %T - ISO 8601 time format (HH::MM::SS)
		// %n - Logger's name
		// %v - The actual text to log
		// %$ - End color range   (can be use only once)

		// MORE: https://github.com/gabime/spdlog/wiki/3.-Custom-formatting

		spdlog::set_pattern("%^[%T] %n: %v%$");

		/* LEVEL ENUM */

		//	trace    = SPDLOG_LEVEL_TRACE,
		//	debug    = SPDLOG_LEVEL_DEBUG,
		//	info     = SPDLOG_LEVEL_INFO,
		//	warn     = SPDLOG_LEVEL_WARN,
		//	err      = SPDLOG_LEVEL_ERROR,
		//	critical = SPDLOG_LEVEL_CRITICAL,
		//	off      = SPDLOG_LEVEL_OFF,
		//	n_levels

		m_engineLogger = spdlog::stdout_color_mt("GON");
		m_engineLogger->set_level(spdlog::level::trace);

		m_clientLogger = spdlog::stdout_color_mt("APP");
		m_clientLogger->set_level(spdlog::level::trace);

		m_alive = true;
	}
	std::shared_ptr<spdlog::logger>& Log::engineLogger()
	{
		return m_engineLogger;
	}

	std::shared_ptr<spdlog::logger>& Log::clientLogger()
	{
		return m_clientLogger;
	}


	void Log::shutDown()
	{
		LogManager::p().get().engineLogger()->info("[DESTROYING] spdlog.");
		m_alive = false;
		m_clientLogger.reset();
		m_engineLogger.reset();
		spdlog::drop_all();
	}
	Log::~Log()
	{
		if (m_alive) shutDown();
	}
}

