#pragma once
#include "GonEngine/renderer/camera.hpp"

namespace Gon {

	class CameraPerspective : public Camera
	{	
	public:

		CameraPerspective(const glm::vec3& position);
		virtual ~CameraPerspective();
	
		virtual const glm::mat4& getViewMatrix()			override;
		virtual void updateViewMatrix()					    override;

		virtual const glm::vec3& getPosition()				override;
		virtual void setPosition(const glm::vec3& position) override;

		void setUp(const glm::vec3& up)			{ m_up = up; }
		void setFront(const glm::vec3& front)	{ m_front = front; }
		glm::vec3 getFront()					{ return m_front; }


	private:
		glm::vec3 m_up, m_front;
	};




	// Camera handlers
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	class PerspHandler : public CameraHandler
	{
	public:

		struct Data
		{
			glm::vec3   Position{ glm::vec3{ 0.0f, 0.0f, 3.0f} };
			glm::vec3	Front	{};
			glm::vec3	Right	{};
			float		Yaw		{ -90.0f };
			float		Pitch	{ 0.0f };
			float		Fov		{ 45.0f };
		};

	public:
		PerspHandler(const float ratio, const PerspHandler::Data& data = PerspHandler::Data());
		virtual ~PerspHandler() = default;

		virtual void onUpdate(const DeltaTime dt)			 override;
		virtual void onEvent(Event& e)						 override;

		virtual void setAspectRatio(const float aspectratio) override;
		virtual const float  getAspectRatio()                override;
		virtual void updateProjectionMatrix()				 override;

		virtual const glm::mat4& getProjectionMatrix()		 override;
		virtual const glm::mat4& getViewMatrix()			 override;

		virtual void enablePrimeWindowResize()  override { m_enabled_prime_window = true; }
		virtual void disablePrimeWindowResize() override { m_enabled_prime_window = false; }
	
		virtual const glm::vec3& getPosition() { return m_camera->getPosition(); };

	private:
		bool onMouseMoved(OnMouseMoved& e);
		const Data getData() { return m_data; }
		void  setData(const Data& data);	
		void updateCameraVectors();
		void handleMouseMovement(float xoffset, float yoffset, bool constrainPitch);
		void handleMouseScroll(const float yoffset);

	private:
		Data m_data;
		glm::vec3 m_worldUp;
		float m_aspectRatio;
		float m_speed,m_near, m_far;
		float m_firstMouse, m_lastX, m_lastY;
		float m_enableMouseDisplacement;
	};
}