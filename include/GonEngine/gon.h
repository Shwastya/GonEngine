// Entry Point (main projects)
#pragma once

// Call for side project client
#include "GonEngine/engine/gon.hpp"
// Logging with spdlog
#include "GonEngine/engine/log.hpp"
#include "GonEngine/goncfg.h"

#if defined(GON_WIN64) || defined(GON_WIN32)
	int main(int argc, char** argv)
	{
		GON_LOG_ON
		{
			auto test = gon::start_project();
			test->run();		
		}		
		GON_LOG_OFF
		return 0;
	}
#endif
