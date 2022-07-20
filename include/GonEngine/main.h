
#pragma once

// Call for side project client -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/nodes/nodes.hpp"
#include "GonEngine/input.hpp"
#include "GonEngine/gon.hpp"
#include <imgui.h>
#include "GonEngine/log.hpp"

// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

#if defined(GON_WIN64) || defined(GON_WIN32)
	int main()
	{
		GON_LOG_ON
		{
			// Options:
			// 
			//	1. gon::API::OpenGL;
			//	2. gon::API::DirectX 
			//	3. gon::API::DirectX 
			//
			
			auto test = gon::start_project();
			test->run();		
		}		
		GON_LOG_OFF
		return 0;
	}
#endif
