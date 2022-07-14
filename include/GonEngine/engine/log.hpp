#pragma once
#include <memory>
#include <spdlog.h>
#include <fmt/ostr.h> // for custom types log

/*
* NOTA:
* Si no se va a implementar distintas librerias para logging
* este polimorfismo me resultara inutil.
* 
*/

namespace gon
{
	struct VirtuaLog
	{
		virtual void init() = 0;

		virtual std::shared_ptr<spdlog::logger>& engineLogger() = 0;
		virtual std::shared_ptr<spdlog::logger>& clientLogger() = 0;

		virtual void shutDown() = 0;

		virtual ~VirtuaLog() = default;
	};

	struct Log : public VirtuaLog
	{
		Log() {	init(); }

		void init() override;

		std::shared_ptr<spdlog::logger>& engineLogger() override;		
		std::shared_ptr<spdlog::logger>& clientLogger() override;		

		virtual void shutDown() override;

		virtual ~Log();

	private:
		bool m_alive = false;
		std::shared_ptr<spdlog::logger> m_engineLogger;
		std::shared_ptr<spdlog::logger> m_clientLogger;
	};

	enum class LogType
	{
		LT_SPDLOG, LT_OTHERLOG
	};

	// Log Manager is a Singleton
	struct LogManager
	{
		~LogManager() = default;

		static LogManager& p();
		VirtuaLog& get();

		void switchLog(const LogType type);

	private:
		LogManager();

		// VirtuaLog* m_Log = nullptr;
		std::unique_ptr<VirtuaLog> m_log;
		LogType m_selected = LogType::LT_SPDLOG;
	};
}


