
// This engine is intended to run from C++17. 
// The following code is for possible cross-platform portability and for core 
// settings and configurations.

#pragma once
// Logging: Off/On->(only in debug)
#if 1 && defined(_DEBUG)
	#ifndef _GON_LOG
	#define _GON_LOG
	#endif
#endif
// Asserts: off/on->(0|1 v _GON_LOG)
#if 0 || defined(_GON_LOG)
	#ifndef _GON_ASSERTS
	#define _GON_ASSERTS
	#endif
#endif

// timer profiling system off/on(0|1)
#define GON_TIMER_PROFILE 1



#if defined(_WIN64)
/* Microsoft Windows (64-bit) */
	#ifndef GON_WIN64
	#define GON_WIN64
	#endif
#elif defined(_WIN32)
	#ifndef GON_WIN32
	#define GON_WIN32
	#endif
/* Microsoft Windows (32-bit) */
#elif defined(__linux__)
/* Linux  */
	#ifndef GON_LINUX
	#define GON_LINUX
	#endif
#else
	#error Platform not supported!
#endif


#if defined(_GON_LOG) // _GON_LOG_ is ON

	#define	GON		Gon::LogManager::p().get().engineLogger()
	#define APP		Gon::LogManager::p().get().clientLogger()
	#define GON_OFF Gon::LogManager::p().get().shutDown()

	#if defined(_DEBUG) // _GON_LOG_ is ON			
		
		

		// CORE Logs
		#define GON_TRACE(...) GON->trace (__VA_ARGS__)
		#define GON_INFO(...)  GON->info  (__VA_ARGS__)
		#define GON_WARN(...)  GON->warn  (__VA_ARGS__)
		#define GON_ERROR(...) GON->error (__VA_ARGS__)

		// CLIENT Logs
		#define APP_TRACE(...) APP->trace (__VA_ARGS__)
		#define APP_INFO(...)  APP->info  (__VA_ARGS__)
		#define APP_WARN(...)  APP->warn  (__VA_ARGS__)
		#define APP_ERROR(...) APP->error (__VA_ARGS__)		
		
		#define MEMORY_USAGE() printfMemoryUsage()

		#define GON_LOG_ON GON_WARN("Welcome to the Gon-Engine logging!") 
		#define GON_LOG_OFF	GON_OFF; MEMORY_USAGE()

			

	#endif
#else // _GON_LOG_ is OFF	
	
	#define MEMORY_USAGE()

	// CORE Logs
	#define GON_TRACE(...) 
	#define GON_INFO(...)  
	#define GON_WARN(...)  
	#define GON_ERROR(...) 

	// CORE Client
	#define APP_TRACE(...)
	#define APP_INFO(...)  
	#define APP_WARN(...)  
	#define APP_ERROR(...) 

	#define GON_LOG_ON
	#define GON_LOG_OFF

#endif // MH_LOG_SYSTEM

// asserts
#if defined(_GON_ASSERTS) // ASSERST or _GON_LOG is ON

#define	GON		Gon::LogManager::p().get().engineLogger()
#define APP		Gon::LogManager::p().get().clientLogger()

	#ifndef _GON_LOG
		#define GON_ERROR(...) GON->error (__VA_ARGS__)
		#define APP_ERROR(...) APP->error (__VA_ARGS__)
		#define GON_TRACE(...) GON->trace (__VA_ARGS__)
		#define GON_LOG_ON GON_TRACE("Gon-Engine only logging with asserts!");
		#define GON_LOG_OFF	Gon::LogManager::p().get().shutDown();
	#endif

	#ifndef _DEBUG		
		#define _BREAK_DEGUG ;
		#define GON_LOG_ON GON_TRACE("Gon-Engine logging with asserts only...");
		#define GON_LOG_OFF	Gon::LogManager::p().get().shutDown();
	#else
		#ifndef _BREAK_DEGUG
			#define _BREAK_DEGUG __debugbreak();
		#endif
	#endif // !(_DEBUG))

	#define APP_ASSERT(x, ...) { if(!(x)) {APP_ERROR("[ASSERTION FAILED]: {0}", __VA_ARGS__); _BREAK_DEGUG}}
	#define GON_ASSERT(x, ...) { if(!(x)) {GON_ERROR("[ASSERTION FAILED]: {0}", __VA_ARGS__); _BREAK_DEGUG}}
#else
	#define GON_ASSERT(...) 
	#define APP_ASSERT(...)
#endif

#if defined(_DEBUG) // _GON_LOG_ is ON	
	#if GON_TIMER_PROFILE
#include <timer.hpp>
		// works for save json file for chrome visual profile

		#define GON_TIMER_BEGIN(name, filepath) Instrumentor::get().beginSession(name, filepath)
		#define GON_TIMER_END() Instrumentor::get().endSession()
		#define GON_TIMER_SCOPE(name) Timer timer##__LINE__;
		#define GON_TIMER_FUNCT() GON_TIMER_SCOPE(__FUNCSIG__)
		
		// works for show in ImGui screen		
		#define GON_UI_TIMING(n) UITimer timer##__LINE__(n, [&](TimingResultUI results) { m_timingResult.push_back(results); })
		#define GON_UI_UPDATE void timerUpdate(){ static float time{ 0.0f };if (time < 0.5f){	m_UITimingRender.clear();m_UITimingRender = m_timingResult;}m_timingResult.clear();time += 0.1f;if (time > 6.0f) time = 0.0f; }		
		#define GON_UI_RENDER void timerRender(){ for (auto& result : m_UITimingRender)	{ char label[50]{ " %.4f ms.  " }; strcat_s(label, result.Name); ImGui::Text(label, result.Time);}}
		#define GON_UI_TIMING_VECS_DEFS GON_UI_UPDATE GON_UI_RENDER std::vector<TimingResultUI> m_timingResult;std::vector<TimingResultUI> m_UITimingRender
		#define GON_UI_TIMING_SHOW_RESULTS(n) ImGui::Begin(n); { timerUpdate();	timerRender(); } ImGui::End();
	#else
		#define GON_TIMER_BEGIN(name, filepath)
		#define GON_TIMER_END()
		#define GON_TIMER_SCOPE(name)
		#define GON_TIMER_FUNCT()
		
		#define GON_UI_TIMING(n)
		#define GON_UI_TIMING_VECS_DEFS
		#define GON_UI_TIMING_SHOW_RESULTS(n)
		

	#endif
#else
	#define GON_TIMER_BEGIN(name, filepath)
	#define GON_TIMER_END()
	#define GON_TIMER_SCOPE(name)
	#define GON_TIMER_FUNCT()

	#define GON_UI_TIMING(n)
	#define GON_UI_TIMING_VECS_DEFS
	#define GON_UI_TIMING_SHOW_RESULTS(n)
#endif
// ----------------------------------------------------------------------------


