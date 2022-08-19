#pragma once
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "GonEngine/geometries/geometry.hpp"
#include "GonEngine/platform/OpenGL/opengl_texture.hpp"

namespace Gon {	
	
	struct TagComponent
	{
		std::string Tag{};

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag);
	};

	struct TransformComponent
	{
		glm::vec3 T	{ glm::vec3(0.0f, 0.0f, 0.0f) };
		glm::vec3 R { glm::vec3(0.0f, 0.0f, 0.0f) };
		glm::vec3 S { glm::vec3(1.0f, 1.0f, 1.0f) };

		glm::mat4 Model { glm::mat4(1.0f) };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation = glm::vec3(0.0f, 0.0f, 0.0f));

		void setTransform()
		{
			Model = glm::mat4(1.0f);
			Model = glm::translate(Model, T);
			Model = Model * glm::toMat4(glm::quat(R));
			Model = glm::scale(Model, S);
		}

		operator glm::mat4& ();
		operator const glm::mat4& ();
		operator const glm::mat4& () const;
	};	

	struct MeshRendererComponent
	{
		s_ptr<Texture2D> Albedo;

		MeshRendererComponent() = default;
		MeshRendererComponent(const MeshRendererComponent&) = default;
		MeshRendererComponent(const std::string& path, Texture2D::Format format);

		operator Texture2D* ();
		operator const Texture2D* () const;
	};

	struct MeshFilterComponent
	{
		Geometry::Type Filter{ Geometry::Type::NONE };

		MeshFilterComponent() = default;
		MeshFilterComponent(const MeshFilterComponent&) = default;
		MeshFilterComponent(const Geometry::Type filter);

		operator Geometry::Type& ();
		operator const Geometry::Type& () const;

	};
}