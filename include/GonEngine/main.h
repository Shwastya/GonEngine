#pragma once

// Call for side project client -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
#include "GonEngine/renderer/api_context.hpp"
#include "GonEngine/events/events.hpp"
#include "GonEngine/memcfg/goncfg.h"
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
		Gon::u_ptr<Gon::GonEngine> projectApp{Gon::start_project()};
		projectApp->run();
	}
		GON_LOG_OFF
		return 0;
}

#endif