#include "GonEngine/renderer/management/camera_manager.hpp"
#include "GonEngine/renderer/cameras/camera_orthographic.hpp"
#include "GonEngine/renderer/cameras/camera_perspective.hpp"

#include "GonEngine/input.hpp"

#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"

namespace Gon {
	CameraMan::CameraMan(const CamMode mode, const float aspectRatio)
		: m_cameraHandler(nullptr), m_mode(mode)
	{
		m_Dg.AspectRatio = aspectRatio;
		initCam();
		GON_TRACE("[CREATED] CameraMan.");
	}
	CameraMan::~CameraMan()	{ GON_TRACE("[DESTROYED] CameraMan has dropped the camera.");}

	void CameraMan::initCam()
	{		
		switch (m_mode)
		{
		case CamMode::Ortho:
			m_cameraHandler = std::make_shared<OrthographicCameraHandler>(glm::vec3{ 0.0f, 0.0f, 0.0f }, m_Dg.AspectRatio);
			GON_INFO("Camera-Man is now using an orthographic camera.");
			break;
		case CamMode::Persp:
			m_cameraHandler = std::make_shared<PerspectiveCameraHandler>(glm::vec3{ 0.0f, 0.0f, 3.0f }, m_Dg.AspectRatio);
			GON_INFO("Camera-Man is now using an perspective camera.");
			break;
		default:
			//m_camera = std::make_shared<Perspective>();
			GON_INFO("Camera-Man is now using an perspective camera.");
			break;
		}
	}

	void CameraMan::switchCam(const CamMode& mode) 
	{
		if (m_mode != mode)
		{			
			switch (mode)
			{
			case CamMode::Ortho:
				GON_INFO("Camera-Man is dropping the perspective camera. Saving data...");
				m_Dg.Position = m_cameraHandler->get()->getPosition();
				m_cameraHandler.reset();
				m_cameraHandler = std::make_shared<OrthographicCameraHandler>(glm::vec3{m_Dg.Position.x, m_Dg.Position.y, 0.0f}, m_Dg.AspectRatio);			
				m_mode = CamMode::Ortho;				
				GON_INFO("Camera-Man is now using an orthographic camera.");
				break;

			case CamMode::Persp:
				GON_INFO("Camera-Man is dropping the orthographic camera. Saving data...");
				m_Dg.Position.x = m_cameraHandler->get()->getPosition().x;
				m_Dg.Position.y = m_cameraHandler->get()->getPosition().y;
				m_cameraHandler.reset();			
				m_cameraHandler = std::make_shared<PerspectiveCameraHandler>(m_Dg.Position, m_Dg.AspectRatio);
				m_mode = CamMode::Persp;
				GON_INFO("Camera-Man is now using an perspective camera.");
				break;
			}
		}
	}
	const u_ptr<Camera>& CameraMan::getCam() { return m_cameraHandler->get();  }
	const s_ptr<CameraHandler>& CameraMan::handler() { return m_cameraHandler; }
	const glm::mat4& CameraMan::projectionMatrix()
	{
		return m_cameraHandler->getProjectionMatrix();
	}

}

