#pragma once
#include "GonEngine/renderer/cameras/camera.hpp"

namespace Gon {

	constexpr float k_Yaw			= -90.0f;
	constexpr float k_Pitch			= 0.0f;
	constexpr float k_Speed			= 2.5f;
	constexpr float k_Sensitivity	= 0.1f;
	constexpr float k_FOV			= 45.0f;

	class Perspective : public Camera
	{
	public:
		Perspective() = default;
		Perspective(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = k_Yaw, float pitch = k_Pitch);
		Perspective(float posX, float posY, float posZ, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f, float yaw = k_Yaw, float pitch = k_Pitch);
		
		~Perspective();
	
		virtual const std::pair<glm::mat4, glm::mat4> getViewProjectionMatrix() const override;	

		virtual const glm::vec3& getPosition() override { return m_position;  };
		virtual void setPosition(const glm::vec3& position) override { m_position = position; };

		virtual void handleKeyboard(const Movement direction, const float dt) override {};
		virtual void handleMouseMovement(const float xoffset, const float yoffset, const bool constrainPitch = true) override {};
		virtual void handleMouseScroll(float yoffset) override {};

		//virtual void setRotation(const float rot) override { rot; };

		// non-virtual
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
		const float getFOV() { return m_fov; };
		float setFOV(const float fov) { m_fov = fov; }

	private:
		virtual void updateCameraVectors();

	private:
		glm::vec3 m_front, m_up, m_right, m_worldUp;
		float m_yaw, m_pitch;
		float m_fov;
		float m_near, m_far;

		
	};
}