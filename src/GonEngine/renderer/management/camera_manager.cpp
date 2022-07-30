#include "GonEngine/renderer/management/camera_manager.hpp"
#include "GonEngine/renderer/cameras/c_orthographic.hpp"
#include "GonEngine/renderer/cameras/c_perspective.hpp"

#include "GonEngine/input.hpp"

#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"

namespace Gon {
	CameraMan::CameraMan(const CamMode mode, const float aspectRatio)
		: m_cameraHandler(nullptr), m_mode(mode)
	{
		initCam(aspectRatio);
		GON_WARN("Message from CameraMan: With the constructor 'CameraMan(const CamMode mode)' you have to start the camera with 'initCam(const glm::vec3& position)'.");
	}
	CameraMan::~CameraMan()	{ GON_TRACE("[DESTROYED] CameraMan has dropped the camera.");}

	void CameraMan::initCam(const float aspectRatio)
	{
		GON_TRACE("[CREATED] CameraMan.");
		switch (m_mode)
		{
		case CamMode::Ortho:
			//m_camera = std::make_shared<Orthographic>();
			m_cameraHandler = std::make_shared<OrthoHandler>(glm::vec3{0.0f,0.0f,0.0f}, aspectRatio);
			GON_INFO("Camera-Man is now using an orthographic camera.");
			break;
		case CamMode::Persp:
			//m_camera = std::make_shared<Perspective>();
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
			m_cameraHandler.reset();
			
			switch (mode)
			{
			case CamMode::Ortho:
				//m_camera = std::make_shared<Orthographic>();
				m_cameraHandler = std::make_shared<OrthoHandler>(glm::vec3{0.0f,0.0f,0.0f});
				m_mode = CamMode::Ortho;				
				GON_INFO("Camera-Man is now using an orthographic camera.");
				break;
			case CamMode::Persp:	
				//m_camera = std::make_shared<Perspective>();
				m_mode = CamMode::Persp;
				GON_INFO("Camera-Man is now using an perspective camera.");
				break;
			}
		}
	}
	const u_ptr<Camera>& CameraMan::getCam() { return m_cameraHandler->get();  }
	const s_ptr<CameraHandler>& CameraMan::handler() { return m_cameraHandler; }	
}

