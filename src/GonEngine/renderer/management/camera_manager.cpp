#include "GonEngine/renderer/management/camera_manager.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/input.hpp"
#include "GonEngine/log.hpp"

namespace Gon {
	CameraMan::CameraMan(const CamMode mode, const float aspectRatio, const OrthoHandler::Data orthodata, PerspHandler::Data perpsdata)
		: m_cameraHandler(nullptr), m_mode(mode)
	{
		m_aspectRatio = aspectRatio;
		initCam(orthodata, perpsdata);
		GON_TRACE("[CREATED] CameraMan.");
	}
	CameraMan::~CameraMan()	{ GON_TRACE("[DESTROYED] CameraMan has dropped the camera.");}

	void CameraMan::initCam(const OrthoHandler::Data& orthodata, PerspHandler::Data& perpsdata)
	{		
		switch (m_mode)
		{
		case CamMode::Ortho:
			m_cameraHandler = std::make_shared<OrthoHandler>(m_aspectRatio, orthodata);
			GON_INFO("CameraMan is now using an orthographic camera.");
			break;
		case CamMode::Persp:
			m_cameraHandler = std::make_shared<PerspHandler>( m_aspectRatio, perpsdata);
			GON_INFO("CameraMan is now using an perspective camera.");
			break;
		default:
			//m_camera = std::make_shared<Perspective>();
			GON_INFO("CameraMan is now using an perspective camera.");
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
				GON_INFO("CameraMan is dropping the perspective camera. Switching data...");
				m_perspGuard = dynamic_cast<PerspHandler&>(*m_cameraHandler).getData();
				m_aspectRatio = m_cameraHandler->getAspectRatio();

				m_cameraHandler.reset();
				m_cameraHandler = std::make_shared<OrthoHandler>(m_aspectRatio, m_orthoGuard);
				m_mode = CamMode::Ortho;		
				GON_INFO("CameraMan is now using an orthographic camera.");
				break;

			case CamMode::Persp:
				GON_INFO("CameraMan is dropping the orthographic camera. Switching data...");
				m_orthoGuard = dynamic_cast<OrthoHandler&>(*m_cameraHandler).getData();
				m_aspectRatio = m_cameraHandler->getAspectRatio();

				m_cameraHandler.reset();			
				m_cameraHandler = std::make_shared<PerspHandler>(m_aspectRatio, m_perspGuard);
				m_mode = CamMode::Persp;				
				GON_INFO("CameraMan is now using an perspective camera.");
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

