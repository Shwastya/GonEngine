#pragma once
#define Gon_window_width  static_cast<float>(GonEngine::getGon().getPtrWindow().width())
#define Gon_window_height static_cast<float>(GonEngine::getGon().getPtrWindow().height())
#include "GonEngine/renderer/management/render_manager.hpp" // quitar
#include "GonEngine/renderer/management/camera_manager.hpp" // quitar
#include "GonEngine/renderer/management/shader_manager.hpp" // quitar
#include "GonEngine/platform/OpenGL/opengl_texture.hpp" // quitar
#include "GonEngine/platform/OpenGL/opengl_shader.hpp" // quitar
#include "GonEngine/platform/OpenGL/opengl_vao.hpp"   // quitar
#include "GonEngine/geometries/triangle.hpp"  // quitar    
#include "GonEngine/renderer/renderer3D.hpp"
#include "GonEngine/geometries/quad.hpp" // quitar
#include "GonEngine/geometries/cube.hpp" // quitar
#include <glm/gtc/matrix_transform.hpp>  // quitar
#include "GonEngine/nodes/n_layer.hpp"
#include "GonEngine/events/events.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include <glm/gtc/type_ptr.hpp> // quitar
#include "GonEngine/window.hpp"
#include "GonEngine/gon.hpp"
#include "GonEngine/log.hpp"
#include "GonEngine/log.hpp"
#include <glm/glm.hpp>
#include <imgui.h>









