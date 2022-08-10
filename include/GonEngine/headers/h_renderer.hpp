#pragma once
#include <glm/glm.hpp>  

#define current  s_storage->CurrentShader
#define SHADER	 s_storage->Shader
#define VAObj	 s_storage->Vao

#define MODEL	 s_storage->Model
#define VIEW	 s_storage->View
#define PROJ	 s_storage->Proj

#define VEC3	 const glm::vec3&
#define VEC4	 const glm::vec4&
#define Texture	 const Texture2D*
#define Color	 const glm::vec4&