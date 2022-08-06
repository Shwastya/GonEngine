#pragma once

#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"
#include "GonEngine/gon.hpp"
#include <memory_tracking.hpp>
#include <timer.hpp>

#if defined(GON_WIN64) || defined(GON_WIN32)
int main()
{
	GON_LOG_ON;
	{		
		Gon::u_ptr<Gon::GonEngine> App{Gon::start_project()};

		App->run();		
	}	
	GON_LOG_OFF;
	
	return 0;
}
#endif