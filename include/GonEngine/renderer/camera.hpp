#pragma once
#include "GonEngine/renderer/deltatime.hpp"
#include "GonEngine/memcfg/scp_ptr.hpp"
#include "GonEngine/events/events.hpp"
#include <glm/glm.hpp>
#include <utility>

namespace Gon {

	class Camera
	{
	public:

		Camera(const glm::vec3& position) : m_position(position), m_viewMatrix(1.0f) {}

		virtual ~Camera() = default;
	
		virtual const glm::mat4& getViewMatrix()		  = 0;
		virtual void updateViewMatrix()					  = 0;

		virtual const glm::vec3& getPosition()				= 0;
		virtual void setPosition(const glm::vec3& position) = 0;

	protected:
		glm::vec3 m_position;
		glm::mat4 m_viewMatrix;
	};

	// Camera handlers
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	class CameraHandler 
	{
	public:
		CameraHandler() 
			: m_projectionMatrix(1.0f), 
			  m_near(-1.0f), 
			  m_far(1.0f),
			  m_mouseSensitivity(0.1f) 
		{}
		virtual ~CameraHandler() = default;

		virtual void onUpdate(const DeltaTime dt) = 0;
		virtual void onEvent(Event& e) = 0;

		virtual void setAspectRatio(const float aspectratio) = 0;
		virtual const float  getAspectRatio()				 = 0;
		virtual void updateProjectionMatrix()				 = 0;

		virtual const glm::mat4& getProjectionMatrix()		 = 0;
		virtual const glm::mat4& getViewMatrix()			 = 0;
		
		virtual void enablePrimeWindowResize()				 = 0;
		virtual void disablePrimeWindowResize()				 = 0;

		const u_ptr<Camera>& get() { return m_camera; }

	protected:
		glm::mat4 m_projectionMatrix;
		float m_near, m_far, m_mouseSensitivity;
		u_ptr<Camera> m_camera;
		bool m_enabled_prime_window{ true };
	};

}
