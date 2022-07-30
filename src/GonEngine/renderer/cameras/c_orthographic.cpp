#include "GonEngine/renderer/cameras/c_orthographic.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/input.hpp"
#include "GonEngine/log.hpp"


namespace Gon {

	Orthographic::Orthographic(const float left, const float right, const float bottom, const float top)
		: Camera(glm::mat4(1.0f), glm::ortho(left, right, bottom, top, k_zNear, k_zFar)),
		m_rotation(0.0f)
	{
		GON_TRACE("[CREATED] Orthographic camera");
	}

	Orthographic::~Orthographic() { GON_TRACE("[DESTROYED] Orthographic camera"); }

	const glm::mat4& Orthographic::getViewMatrix() const
	{
		return m_viewMatrix;
	}
	const glm::mat4& Orthographic::getProjectionMatrix() const
	{
		return m_projectionMatrix;
	}
	const glm::vec3& Orthographic::getPosition()
	{
		return m_position;
	}
	void Orthographic::setPosition(const glm::vec3& position)
	{
		m_position = position;
		Orthographic::updateViewMatrix();
	}
	void Orthographic::setRotation(const float rotate)
	{
		m_rotation = rotate;
		Orthographic::updateViewMatrix();
	}
	void Orthographic::updateViewMatrix()
	{
		const glm::mat4 transform{ glm::translate(glm::mat4(1.0f), m_position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1)) };
		m_viewMatrix = glm::inverse(transform);
	}	

	void Orthographic::updateProjectionMatrix(const float left, const float right, const float bottom, const float top)
	{
		m_projectionMatrix = glm::ortho(left, right, bottom, top, k_zNear, k_zFar);
	}





	// Camera handlers
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

	OrthoHandler::OrthoHandler(const glm::vec3& pos, const float ratio, const bool rotation)
		:	m_position(pos), m_aspectRatio(ratio),
			m_zoom(1.0f), 
			m_enableRotation(rotation),	
			m_rotate(0.0f), 
			m_speed(2.5f), m_rotSpeed(150.0f)
	{
		m_camera = std::make_unique<Orthographic>
		(
			-ratio * m_zoom,
			ratio  * m_zoom,
			-m_zoom,
			m_zoom
		);

		
	}
	void OrthoHandler::onUpdate(const DeltaTime dt)
	{
		if	(Input::isKeyPressed(GON_KEY_A))		
			m_camera->setPosition({ m_position.x -= m_speed * dt, m_position.y, m_position.z });		
		else if (Input::isKeyPressed(GON_KEY_D))		
			m_camera->setPosition({ m_position.x += m_speed * dt, m_position.y, m_position.z });		
		if	(Input::isKeyPressed(GON_KEY_W))
			m_camera->setPosition({ m_position.x, m_position.y += m_speed * dt, m_position.z });
		else if (Input::isKeyPressed(GON_KEY_S))
			m_camera->setPosition({ m_position.x, m_position.y -= m_speed * dt, m_position.z });

		if (m_enableRotation)
		{
			if (Input::isKeyPressed(GON_KEY_Q))
			{
				const float rot = m_rotate -= m_rotSpeed * dt;
				m_camera->setRotation(rot);
			}				
			else if (Input::isKeyPressed(GON_KEY_E))
			{
				const float rot = m_rotate += m_rotSpeed * dt;
				m_camera->setRotation(rot);
			}
		}
	}
	void OrthoHandler::onEvent(Event& e)
	{
		if (e.getEventType() == EventType::MouseScrolled)
		{
			OnMouseScrolled& _e = dynamic_cast<OnMouseScrolled&>(e);

			m_zoom -= _e.GetYOffset() * k_Sensitivity;			
			m_speed = m_zoom = std::max(m_zoom, 0.25f);
			updateApectRatio();
		}
		if (e.getEventType() == EventType::WindowResize)
		{
			OnWindowResize& _e = dynamic_cast<OnWindowResize&>(e);
			m_aspectRatio = static_cast<float>(_e.GetWidth()) / static_cast<float>(_e.GetHeight());
			updateApectRatio();			
		}
	}
	const void OrthoHandler::updateApectRatio() const
	{
		dynamic_cast<Orthographic&>(*m_camera).updateProjectionMatrix
		(
			-m_aspectRatio * m_zoom,
			m_aspectRatio * m_zoom,
			-m_zoom, m_zoom
		);
	}
}
