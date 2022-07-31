#pragma once
#include "GonEngine/renderer/camera.hpp"

namespace Gon {

	constexpr float k_Yaw			= -90.0f;
	constexpr float k_Pitch			= 0.0f;	
	constexpr float k_FOV			= 45.0f;

	class CameraPerspective : public Camera
	{
	public:

		CameraPerspective(const glm::vec3& position);
		virtual ~CameraPerspective();
	
		virtual const glm::mat4& getViewMatrix()			override;
		virtual void updateViewMatrix()					    override;

		virtual const glm::vec3& getPosition()				override;
		virtual void setPosition(const glm::vec3& position) override;
		virtual void setRotation(const float rotate)		override;

		void setUp(const glm::vec3& up)			{ m_up = up; }
		void setFront(const glm::vec3& front)	{ m_front = front; }
		glm::vec3 getFront()					{ return m_front; }


	private:
		glm::vec3 m_up, m_front;
	};




	// Camera handlers
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	class PerspectiveCameraHandler : public CameraHandler
	{
	public:
		PerspectiveCameraHandler(const glm::vec3& position, const float ratio);
		virtual ~PerspectiveCameraHandler() = default;

		virtual void onUpdate(const DeltaTime dt) override;
		virtual void onEvent(Event& e)			  override;

		virtual void setAspectRatio(const float aspectratio) override;
		virtual const float  getAspectRatio()                override;
		virtual void updateProjectionMatrix()				 override;

		virtual glm::mat4& getProjectionMatrix() override;		

		bool onMouseMoved(OnMouseMoved& e);

	private:	
		void updateCameraVectors();
		void handleMouseMovement(float xoffset, float yoffset, bool constrainPitch);
		void handleMouseScroll(const float yoffset);

	private:
		glm::vec3 m_position, m_front, m_right, m_worldUp;
		float m_aspectRatio;
		float m_yaw, m_pitch;
		float m_fov;
		float m_speed;
		float m_near, m_far;
		float m_mouseSentitivity;
		float m_firstMouse, m_lastX, m_lastY;
		float m_enableMouseDisplacement;
	};
}