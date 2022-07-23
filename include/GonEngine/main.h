#pragma once

// Call for side project client -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
#include "GonEngine/renderer/api_context.hpp"
#include "GonEngine/events/events.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/nodes/nodes.hpp"
#include "GonEngine/input.hpp"
#include "GonEngine/gon.hpp"
#include "GonEngine/log.hpp"
#include <imgui.h>

// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

#if defined(GON_WIN64) || defined(GON_WIN32)

	int main()
	{
		GON_LOG_ON
		{
			gon::u_ptr<gon::GonEngine>test{gon::start_project()};
			test->run();		
		}		
		GON_LOG_OFF
		return 0;
	}

#endif
