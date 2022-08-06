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
	const glm::mat4& CameraOrthographic::getViewMatrix()  
	{ 
		updateViewMatrix();
		return m_viewMatrix; 
	}
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
	}
	void CameraOrthographic::setRotation(const float rotate)
	{
		m_rotation = rotate;
	}
	


	// Camera handlers
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	OrthoHandler::OrthoHandler(const float ratio, const OrthoHandler::Data& data)
		:	m_aspectRatio(ratio), m_speed(2.5f), m_rotSpeed(150.0f)			
	{		
		m_camera = make_u_ptr<CameraOrthographic>(data.Position);
		setData(data);

		// On switch from perspective ensure the correct capture mouse mode. 
		GonEngine::getGon().getPtrWindow().setCaptureMode(false);
	}
	void OrthoHandler::onUpdate(const DeltaTime dt)
	{
		if	(Input::isKeyPressed(GON_KEY_A))		
			m_camera->setPosition
			({ 
				m_data.Position.x -= m_speed * dt, m_data.Position.y, m_data.Position.z
			});		
		else if (Input::isKeyPressed(GON_KEY_D))		
			m_camera->setPosition
			({ 
				m_data.Position.x += m_speed * dt, m_data.Position.y, m_data.Position.z
			});		
		if	(Input::isKeyPressed(GON_KEY_W))
			m_camera->setPosition
			({ 
				m_data.Position.x, m_data.Position.y += m_speed * dt, m_data.Position.z
			});
		else if (Input::isKeyPressed(GON_KEY_S))
			m_camera->setPosition
			({ 
				m_data.Position.x, m_data.Position.y -= m_speed * dt, m_data.Position.z
			});

		if (m_data.EnableRotation)
		{
			if (Input::isKeyPressed(GON_KEY_Q))
			dynamic_cast<CameraOrthographic&>(*m_camera).setRotation
			(
				m_data.Rotate -= m_rotSpeed * dt
			);
			else if (Input::isKeyPressed(GON_KEY_E))
			dynamic_cast<CameraOrthographic&>(*m_camera).setRotation
			(
				m_data.Rotate += m_rotSpeed * dt
			);
		}
	}
	void OrthoHandler::onEvent(Event& e)
	{
		if (e.getEventType() == EventType::MouseScrolled)
			handleMouseScroll(dynamic_cast<OnMouseScrolled&>(e));

			
		if (m_enabled_prime_window && (e.getEventType() == EventType::WindowResize))
		{
			OnWindowResize& _e = dynamic_cast<OnWindowResize&>(e);
			m_aspectRatio = static_cast<float>(_e.GetWidth()) / static_cast<float>(_e.GetHeight());
		}
	}
	void OrthoHandler::setAspectRatio(const float aspectratio) { m_aspectRatio = aspectratio; }
	const float OrthoHandler::getAspectRatio() { return m_aspectRatio; }
	void OrthoHandler::updateProjectionMatrix()
	{		
		m_projectionMatrix = glm::ortho
		(
			-m_aspectRatio	* m_data.Zoom,
			m_aspectRatio	* m_data.Zoom,
			-m_data.Zoom,	m_data.Zoom,	
			m_near,			m_far
		);
	}
	const glm::mat4& OrthoHandler::getProjectionMatrix()
	{
		updateProjectionMatrix();
		return m_projectionMatrix;
	}
	const glm::mat4& OrthoHandler::getViewMatrix()
	{
		return m_camera->getViewMatrix();
	}
	void OrthoHandler::setData(const Data& data)
	{
		m_data = data;
		dynamic_cast<CameraOrthographic&>(*m_camera).setRotation(data.Rotate);
	}
	const bool OrthoHandler::handleMouseScroll(const OnMouseScrolled& e)
	{
		m_data.Zoom -= e.GetYOffset() * m_mouseSensitivity;
		m_speed = m_data.Zoom = std::max(m_data.Zoom, 0.25f);
		return false;
	}
}
