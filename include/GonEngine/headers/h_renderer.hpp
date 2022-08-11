#pragma once
#include <glm/glm.hpp>  
#include "GonEngine/geometries/geometry.hpp"

namespace Gon
{
	#define current  s_storage->CurrentShader
	#define vector3	  const glm::vec3&
	#define vector4	  const glm::vec4&
	#define texture2D const Texture2D*
}