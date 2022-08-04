#pragma once
#include "GonEngine/renderer/management/shader_manager.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"

namespace Gon {

	ShaderManager::ShaderManager()
		: m_storage
	({
		Shader::create("../assets/shaders/basic.glsl"),	// Basic1
	})
	{
		GON_TRACE("[CREATED] ShaderManager: Archived Shaders");
	}

	ShaderManager::~ShaderManager()
	{
		GON_TRACE("[DESTROYED] ShaderManager");
	}		
}