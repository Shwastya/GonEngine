/* 
This engine is intended to run from C++17. 
The following code is for possible cross-platform portability and for core 
settings and configurations.
*/
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


// _______________________Logging Macros_______________________________________

#define	GON		gon::LogManager::p().get().engineLogger()
#define APP		gon::LogManager::p().get().clientLogger()

#if defined(_GON_LOG) // _GON_LOG_ is ON

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

		#define GON_LOG_ON GON_WARN("Welcome to the Gon-Engine logging!");
		#define GON_LOG_OFF	gon::LogManager::p().get().shutDown();
	#endif
#else // _GON_LOG_ is OFF	

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

	#define GON_LOG_ON	0;
	#define GON_LOG_OFF	0;

#endif // MH_LOG_SYSTEM

// asserts
#if defined(_GON_ASSERTS) // ASSERST or _GON_LOG is ON
	#ifndef _GON_LOG
		#define GON_ERROR(...) GON->error (__VA_ARGS__)
		#define APP_ERROR(...) APP->error (__VA_ARGS__)
		#define GON_TRACE(...) GON->trace (__VA_ARGS__)
		#define GON_LOG_ON GON_TRACE("Gon-Engine only logging with asserts!");
		#define GON_LOG_OFF	gon::LogManager::p().get().shutDown();
	#endif

	#ifndef _DEBUG		
		#define _BREAK_DEGUG ;
		#define GON_LOG_ON GON_TRACE("Gon-Engine logging with asserts only...");
		#define GON_LOG_OFF	gon::LogManager::p().get().shutDown();
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
// ----------------------------------------------------------------------------


