#pragma once
#include "GonEngine/renderer/camera.hpp"

namespace Gon {

	constexpr float k_Yaw			= -90.0f;
	constexpr float k_Pitch			= 0.0f;	
	constexpr float k_FOV			= 45.0f;

	class Perspective : public Camera
	{
	public:
		Perspective(const glm::vec3& up, float yaw = k_Yaw, float pitch = k_Pitch);
		Perspective(float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f, float yaw = k_Yaw, float pitch = k_Pitch);
		
		virtual ~Perspective();
	
		virtual const glm::mat4& getViewMatrix()		const override;
		virtual const glm::mat4& getProjectionMatrix()	const override;

		virtual const glm::vec3& getPosition() override;
		virtual void setPosition(const glm::vec3& position) override;
		virtual void setRotation(const float rotate)		override;

		// non-virtual
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
		const float getFOV() { return m_fov; };
		float setFOV(const float fov) { m_fov = fov; }		

	private:
		void updateViewMatrix();
		void updateProjectionMatrix();
		void updateCameraVectors();
		

	private:
		glm::vec3 m_front, m_up, m_right, m_worldUp;
		float m_yaw, m_pitch;
		float m_fov;
		float m_near, m_far;		
	};




	// Camera handlers
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	class PerspHandler : public CameraHandler
	{
	public:
		PerspHandler(const glm::vec3& position, const float ratio, const bool rotation);
		virtual ~PerspHandler() = default;

		virtual void onUpdate(const DeltaTime dt) = 0;
		virtual void onEvent(Event& e) = 0;


	private:

		glm::vec3 m_position;
		bool m_enableRotation;
		float m_ratio, m_zoom;
		float m_rotation, m_speed;
	};
}