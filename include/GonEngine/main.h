#pragma once

// Call for side project client -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
#include "GonEngine/memcfg/memory_tracking.hpp"
#include "GonEngine/events/events.hpp"
#include "GonEngine/input.hpp"
#include "GonEngine/gon.hpp"
#include <imgui.h>

// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

#if defined(GON_WIN64) || defined(GON_WIN32)
int main()
{
	GON_LOG_ON
	{
		Gon::u_ptr<Gon::GonEngine> App{Gon::start_project()};
		App->run();
	}	
	GON_LOG_OFF

	return 0;
}
#endif