#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp" 
#include "sinks/stdout_color_sinks.h"


namespace Gon
{
	
	LogManager::LogManager()
	{
		m_log = std::make_unique<SpdLog>();
	}
	
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
		switch (type)
		{
		case LogType::LT_Spdlog:
			LogManager::p().get().engineLogger()->warn("Not implemented");
		break;
		case LogType::LT_Otherlog:
			LogManager::p().get().engineLogger()->warn("Not implemented");
		break;
		}

	}

	SpdLog::SpdLog() { init(); }

	// current Log implementation
	void SpdLog::init()
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
	std::shared_ptr<spdlog::logger>& SpdLog::engineLogger()
	{
		return m_engineLogger;
	}

	std::shared_ptr<spdlog::logger>& SpdLog::clientLogger()
	{
		return m_clientLogger;
	}


	void SpdLog::shutDown()
	{
		LogManager::p().get().engineLogger()->warn("Closing logging system, bye!");
		m_alive = false;
		m_clientLogger.reset();
		m_engineLogger.reset();
		spdlog::drop_all();
	}
	SpdLog::~SpdLog()
	{
		if (m_alive) shutDown();
	}
}

