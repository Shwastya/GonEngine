#pragma once
#define gonWindowWidth  static_cast<float>(GonEngine::getGon().getPtrWindow().width())
#define gonWindowHeight static_cast<float>(GonEngine::getGon().getPtrWindow().height())

#include "GonEngine/platform/OpenGL/opengl_framebuffer.hpp"
#include "GonEngine/renderer/management/render_manager.hpp" 
#include "GonEngine/renderer/management/camera_manager.hpp" 
#include "GonEngine/platform/OpenGL/opengl_texture.hpp"
#include "GonEngine/imguimods/dockspace_layer.hpp"
#include "GonEngine/geometries/triangle.hpp"  
#include "GonEngine/renderer/renderer3D.hpp"
#include "GonEngine/geometries/quad.hpp" 
#include "GonEngine/geometries/cube.hpp"
#include "GonEngine/nodes/n_layer.hpp"
#include "GonEngine/events/events.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include <glm/gtc/type_ptr.inl>
#include "GonEngine/window.hpp"
#include "GonEngine/gon.hpp"
#include "GonEngine/log.hpp"
#include "GonEngine/log.hpp"
#include <glm/glm.hpp>
#include <imgui.h>

#if defined(GON_TIMER_PROFILE)
	#pragma warning( disable : 4456 )
#endif





