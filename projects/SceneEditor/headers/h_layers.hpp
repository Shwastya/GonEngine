#pragma once
#define Gon_window_width  static_cast<float>(GonEngine::getGon().getPtrWindow().width())
#define Gon_window_height static_cast<float>(GonEngine::getGon().getPtrWindow().height())
#include "GonEngine/renderer/management/render_manager.hpp"
#include "GonEngine/renderer/management/camera_manager.hpp"
#include "GonEngine/renderer/management/shader_manager.hpp"
#include "GonEngine/platform/OpenGL/opengl_texture.hpp"
#include "GonEngine/platform/OpenGL/opengl_shader.hpp"
#include "GonEngine/platform/OpenGL/opengl_vao.hpp"
#include "GonEngine/gameobjects/gameobject.hpp"
#include "GonEngine/geometries/triangle.hpp"
#include "GonEngine/renderer/renderer.hpp"
#include "GonEngine/geometries/quad.hpp"
#include "GonEngine/geometries/cube.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "GonEngine/events/events.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include <glm/gtc/type_ptr.hpp>
#include "GonEngine/window.hpp"
#include "GonEngine/gon.hpp"
#include "GonEngine/log.hpp"
#include "GonEngine/log.hpp"
#include <glm/glm.hpp>
#include <imgui.h>







