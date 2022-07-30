#pragma once
#include "GonEngine/renderer/deltatime.hpp"
#include "GonEngine/memcfg/scp_ptr.hpp"
#include "GonEngine/events/events.hpp"
#include <glm/glm.hpp>
#include <utility>

namespace Gon {

	constexpr float k_Speed = 2.5f;
	constexpr float k_Sensitivity = 0.1f;

	class Camera
	{
	public:

		Camera() = default;

		Camera(const glm::mat4 viewmatrix, const glm::mat4 projmatrix)
			:	m_viewMatrix(viewmatrix), 
				m_projectionMatrix(projmatrix),
				m_position(0.0f)
		{}

		virtual ~Camera() = default;
	
		virtual const glm::mat4& getViewMatrix()		const = 0;
		virtual const glm::mat4& getProjectionMatrix()	const = 0;

		virtual const glm::vec3& getPosition()				= 0;
		virtual void setPosition(const glm::vec3& position) = 0;
		virtual void setRotation(const float rotate)		= 0;

	protected:

		glm::vec3 m_position;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;
	};





	// Camera handlers
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	class CameraHandler 
	{
	public:
		CameraHandler() = default;
		virtual ~CameraHandler() = default;

		virtual void onUpdate(const DeltaTime dt) = 0;
		virtual void onEvent(Event& e) = 0;	

		const u_ptr<Camera>& get() { return m_camera; }

	protected:
		u_ptr<Camera> m_camera;
	};

}
