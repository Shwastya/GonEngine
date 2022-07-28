#pragma once
#include "GonEngine/renderer/api_context.hpp"


namespace Gon
{

	const API APIContext::setAPI(const bool GetSet = false, const API api = API::OpenGL)
	{
		static API _API{ api };
		if (GetSet) _API = api;
		return _API;
	}

	const API APIContext::getAPI()
	{
		return setAPI(false);
	}

	
}