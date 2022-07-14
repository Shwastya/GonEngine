#pragma once

// set-config-preproces-etc.
#include "GonEngine/goncfg.h"
// Logging with spdlog
#include "GonEngine/engine/log.hpp"

namespace gon {

	class GonEngine
	{
	public:
		GonEngine();
		virtual ~GonEngine();

		void run();
	};

	// for project side instantiate
	GonEngine* initProject();

}