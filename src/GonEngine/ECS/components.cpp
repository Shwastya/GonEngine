#pragma once
#include "GonEngine/ECS/components.hpp"



namespace Gon {

	// TagComponent
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	TagComponent::TagComponent(const std::string& tag) 
		: Tag(tag){}	

	// TransformComponent
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	TransformComponent::TransformComponent(const glm::vec3& translation)
		: T(translation) {}
	TransformComponent::operator glm::mat4& () { setTransform();  return Model; }
	TransformComponent::operator const glm::mat4& () { setTransform();  return Model; };
	TransformComponent::operator const glm::mat4& () const { return Model; }	

	// MeshRendererComponent
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
	MeshRendererComponent::MeshRendererComponent(const std::string& path, Texture2D::Format format)
		:Albedo(Texture2D::create(path, format)) {}
	MeshRendererComponent::operator Texture2D* () { return Albedo.get(); }
	MeshRendererComponent::operator const Texture2D* () const { return Albedo.get(); }	

	// MeshFilterComponent
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
	MeshFilterComponent::MeshFilterComponent(const Geometry::Type filter)
		: Filter(filter) {}
	MeshFilterComponent::operator Geometry::Type& () { return Filter; }
	MeshFilterComponent::operator const Geometry::Type& () const { return Filter; }
}