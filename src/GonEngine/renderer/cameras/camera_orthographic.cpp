#include "GonEngine/renderer/cameras/camera_orthographic.hpp"
#include "GonEngine/platform/windows_window.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/input.hpp"
#include "GonEngine/log.hpp"
#include "GonEngine/gon.hpp"


namespace Gon {

	CameraOrthographic::CameraOrthographic(const glm::vec3& position)
		: Camera(position), m_rotation(0.0f)
	{	
		GON_TRACE("[CREATED] Orthographic camera");	
		CameraOrthographic::updateViewMatrix();
	}
	CameraOrthographic::~CameraOrthographic() 
	{ 
		GON_TRACE("[DESTROYED] Orthographic camera"); 
	}
	const glm::mat4& CameraOrthographic::getViewMatrix()  { return m_viewMatrix; }
	void CameraOrthographic::updateViewMatrix() 
	{
		const glm::mat4 transform
		{
			glm::translate(glm::mat4(1.0f), m_position) *
			glm::rotate(glm::mat4(1.0f),
			glm::radians(m_rotation),
			glm::vec3(0, 0, 1))
		};
		m_viewMatrix = glm::inverse(transform);
	}
	const glm::vec3& CameraOrthographic::getPosition() { return m_position;	}
	void CameraOrthographic::setPosition(const glm::vec3& position)
	{
		m_position = position;
		CameraOrthographic::updateViewMatrix();
	}
	void CameraOrthographic::setRotation(const float rotate)
	{
		m_rotation = rotate;
		CameraOrthographic::updateViewMatrix();
	}
	


	// Camera handlers
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	OrthographicCameraHandler::OrthographicCameraHandler(const glm::vec3& pos, const float ratio, const bool rotation)
		:	m_position(pos), 
			m_aspectRatio(ratio),
			m_zoom(1.0f), 
			m_enableRotation(rotation),	
			m_speed(2.5f),
			m_rotate(0.0f), m_rotSpeed(150.0f)			
	{
		m_camera = std::make_unique<CameraOrthographic>(pos);
		OrthographicCameraHandler::updateProjectionMatrix();
	}
	void OrthographicCameraHandler::onUpdate(const DeltaTime dt)
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
	void OrthographicCameraHandler::onEvent(Event& e)
	{
		if (e.getEventType() == EventType::MouseScrolled)
		{
			OnMouseScrolled& _e = dynamic_cast<OnMouseScrolled&>(e);

			m_zoom -= _e.GetYOffset() * k_Sensitivity;			
			m_speed = m_zoom = std::max(m_zoom, 0.25f);
			OrthographicCameraHandler::updateProjectionMatrix();
		}
		if (e.getEventType() == EventType::WindowResize)
		{
			OnWindowResize& _e = dynamic_cast<OnWindowResize&>(e);
			m_aspectRatio = static_cast<float>(_e.GetWidth()) / static_cast<float>(_e.GetHeight());
			OrthographicCameraHandler::updateProjectionMatrix();
		}
	}
	void OrthographicCameraHandler::setAspectRatio(const float aspectratio) { m_aspectRatio = aspectratio; }
	const float OrthographicCameraHandler::getAspectRatio() {	return m_aspectRatio; }
	void OrthographicCameraHandler::updateProjectionMatrix()
	{		
		m_projectionMatrix = glm::ortho
		(
			-m_aspectRatio * m_zoom,
			m_aspectRatio * m_zoom,
			-m_zoom,
			m_zoom, m_near, m_far
		);
	}
	glm::mat4& OrthographicCameraHandler::getProjectionMatrix()
	{
		return m_projectionMatrix;
	}	
}
