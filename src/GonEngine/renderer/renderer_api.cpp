#pragma once
#include "GonEngine/window.hpp"
#include "GonEngine/renderer/renderer_api.hpp"
#include "GonEngine/log.hpp"
#include "GonEngine/memcfg/goncfg.h"

namespace gon 
{
	
	const API RendererApi::_API(const bool GetSet = false, const API api = API::OpenGL)
	{
		static API _API{ api };
		if (GetSet) _API = api;
		return _API;
	}	

	const API RendererApi::_API()
	{
		
		return _API(false);
	}
}