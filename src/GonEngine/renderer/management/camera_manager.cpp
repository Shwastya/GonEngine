#include "GonEngine/renderer/management/camera_manager.hpp"
#include "GonEngine/renderer/cameras/camera_orthographic.hpp"
#include "GonEngine/renderer/cameras/camera_perspective.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/input.hpp"
#include "GonEngine/log.hpp"

namespace Gon {
	CameraMan::CameraMan(const CamMode mode, const float aspectRatio, const OrthoHandler::Data orthodata, PerspHandler::Data perpsdata)
		: m_mode(mode), m_switchKey(Key::C)
	{
		m_cameraHandler[CamMode::Ortho] = std::make_shared<OrthoHandler>(aspectRatio, orthodata);
		m_cameraHandler[CamMode::Persp] = std::make_shared<PerspHandler>(aspectRatio, perpsdata);
		GON_TRACE("[CREATED] CameraMan (orhtographic and perspective)");
	}
	CameraMan::~CameraMan()	
	{ 
		GON_TRACE("[DESTROYED] CameraMan has dropped the camera");
	}
	void CameraMan::enablePrimeWindowResize()
	{	
		m_cameraHandler[m_mode]->enablePrimeWindowResize();
	}
	void CameraMan::disablePrimeWindowResize()
	{
		m_cameraHandler[m_mode]->disablePrimeWindowResize();
	}
	void CameraMan::refreshAspectRatio(const glm::vec2 viewport)
	{
		m_cameraHandler[m_mode]->setAspectRatio(viewport.x / viewport.y);
	}
	const u_ptr<Camera>& CameraMan::getCam() 
	{ 
		return m_cameraHandler[m_mode]->get(); 
	}
	const s_ptr<CameraHandler>& CameraMan::handler() 
	{
		return m_cameraHandler[m_mode];
	}

	const glm::mat4& CameraMan::View()
	{
		return m_cameraHandler[m_mode]->getViewMatrix();
	}

	const glm::mat4& CameraMan::Projection()
	{
		return m_cameraHandler[m_mode]->getProjectionMatrix();
	}

	void CameraMan::onEvent(Event& e)
	{
		handler()->onEvent(e);

		if (e.getEventType() == EventType::KeyPressed)
		{
			OnKeyPressed& _e = dynamic_cast<OnKeyPressed&>(e);

			if (_e.getKeyCode() == m_switchKey)
			{
				if (m_mode != CamMode::Ortho) switchCamMode(CamMode::Ortho);
				else switchCamMode(CamMode::Persp);
			}
		}
	}

}

