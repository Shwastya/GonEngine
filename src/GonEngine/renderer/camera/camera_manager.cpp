#include "GonEngine/renderer/camera/camera_manager.hpp"
#include "GonEngine/renderer/camera/c_orthographic.hpp"
#include "GonEngine/renderer/camera/c_perspective.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"

namespace gon {
	CameraMan::CameraMan(const CamMode mode)
		: m_camera(nullptr), m_mode(mode), m_last_z(3.0f), m_last_rot(0.0f)
	{
		GON_WARN("Message from CameraMan: With the constructor 'CameraMan(const CamMode mode)' you have to start the camera with 'initCam(const glm::vec3& position)'.");
	}
	CameraMan::CameraMan(const CamMode mode, const glm::vec3& position)
		: m_camera(nullptr), m_mode(mode), m_last_z(3.0f), m_last_rot(0.0f)
	{
		initCam(position);
	}
	CameraMan::CameraMan(const CamMode mode, const float posx, const float posy, const float posz)
		: m_camera(nullptr), m_mode(mode), m_last_z(3.0f), m_last_rot(0.0f)
	{
		initCam(glm::vec3{posx, posy, posz });
	}
	CameraMan::~CameraMan()	{ GON_TRACE("[DESTROYED] CameraMan and current camera in use.");}

	void CameraMan::initCam(const glm::vec3& pos)
	{
		GON_TRACE("[CREATED] CameraMan.");
		switch (m_mode)
		{
		case CamMode::Ortho:
			m_camera = std::make_unique<Orthographic>(glm::vec3{ pos.x, pos.y, 0.0f });
			GON_INFO("Camera-Man is now using an orthographic camera.");
			break;
		case CamMode::Persp:
			m_camera = std::make_unique<Perspective>(pos);
			GON_INFO("Camera-Man is now using an perspective camera.");
			break;
		default:
			m_camera = std::make_unique<Perspective>(pos);
			GON_INFO("Camera-Man is now using an perspective camera.");
			break;
		}
	}

	void CameraMan::switchCam(const CamMode& mode) 
	{
		if (m_mode != mode)
		{		
			const glm::vec3 pos{ m_camera->getPosition() };
			m_camera.release();			
			
			switch (mode)
			{
			case CamMode::Ortho:
				GON_TRACE("[DESTROYED] perspective camera.");
				m_last_z = pos.z;
				m_camera = std::make_unique<Orthographic>(pos.x, pos.y, 0.0f, 1.0f, m_last_rot);
				m_mode = CamMode::Ortho;				
				GON_INFO("Camera-Man is now using an orthographic camera.");
				break;
			case CamMode::Persp:	
				GON_TRACE("[DESTROYED] Orthographic camera.");
				m_camera = std::make_unique<Perspective>(pos.x, pos.y, m_last_z);
				m_mode = CamMode::Persp;
				GON_INFO("Camera-Man is now using an perspective camera.");
				break;
			}
		}
	}
	
	void CameraMan::setRotation(const float rot)
	{
		if (m_mode != CamMode::Ortho)
		{
			GON_WARN("Set Rotation is a proprietary function of the orthographic camera.");

		}
		else
		{
			dynamic_cast<Orthographic&>(*m_camera).setRotation(rot);
			m_last_rot = rot;
		}
	}

	const std::pair<glm::mat4, glm::mat4> CameraMan::getViewProjectionMatrix() const
	{
		return m_camera->getViewProjectionMatrix();
	}
}

