/* 
This engine is intended to run from C++17. 
The following code is for possible cross-platform portability and for core 
settings and configurations.
Author. Suastia
*/
#pragma once

// Logging Off/On
#if 1 && defined(_DEBUG)
#ifndef _GON_LOG_
#define _GON_LOG_
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

#if defined(_GON_LOG_) // _GON_LOG_ is ON

#if defined(_DEBUG) // _GON_LOG_ is ON
	
	#define	GON		gon::LogManager::p().get().engineLogger()
	#define APP		gon::LogManager::p().get().clientLogger()		
	
	// CORE Logs
	#define GON_TRACE(...) GON->trace (__VA_ARGS__)
	#define GON_INFO(...)  GON->info  (__VA_ARGS__)
	#define GON_WARN(...)  GON->warn  (__VA_ARGS__)
	#define GON_ERROR(...) GON->error (__VA_ARGS__)
	#define GON_FATAL(...) GON->fatal (__VA_ARGS__)

	// CLIENT Logs
	#define APP_TRACE(...) APP->trace (__VA_ARGS__)
	#define APP_INFO(...)  APP->info  (__VA_ARGS__)
	#define APP_WARN(...)  APP->warn  (__VA_ARGS__)
	#define APP_ERROR(...) APP->error (__VA_ARGS__)
	#define APP_FATAL(...) APP->fatal (__VA_ARGS__)

	#define GON_LOG_ON GON_TRACE("Welcome to Gon-Engine!");
	#define GON_LOG_OFF	gon::LogManager::p().get().shutDown();
#endif

#else // _GON_LOG_ is OFF	

	// CORE Logs
	#define GON_TRACE(...) 
	#define GON_INFO(...)  
	#define GON_WARN(...)  
	#define GON_ERROR(...) 

	// CORE Client
	#define GON_TRACE(...)
	#define GON_INFO(...)  
	#define GON_WARN(...)  
	#define GON_ERROR(...) 
	#define GON_FATAL(...)

	#define GON_LOG_ON	0;
	#define GON_LOG_OFF	0;

#endif // MH_LOG_SYSTEM


// ----------------------------------------------------------------------------


