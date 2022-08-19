#pragma once
#include "GonEngine/renderer/management/shader_manager.hpp"
#include "GonEngine/platform/OpenGL/opengl_shader.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"

namespace Gon {

	ShaderManager::ShaderManager()
		: m_storage
	({
		Shader::create("../assets/shaders/color/basic.glsl"),	// Basic1
		Shader::create("../assets/shaders/text/basic.glsl"),
		Shader::create("../assets/shaders/text/SkyBox.glsl"),
		Shader::create("../assets/shaders/text/Reflection.glsl")

	})
	{
		GON_TRACE("[CREATED] ShaderManager: Archived Shaders");
	}
	ShaderManager::~ShaderManager()
	{
		GON_TRACE("[DESTROYED] ShaderManager");		
	}
}