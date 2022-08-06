#pragma once
#include "GonEngine/renderer/camera.hpp"
#include "GonEngine/renderer/cameras/camera_orthographic.hpp"
#include "GonEngine/renderer/cameras/camera_perspective.hpp"
#include "GonEngine/memcfg/scp_ptr.hpp"
#include "GonEngine/events/events.hpp"

namespace Gon {

	enum CamMode
	{
		Ortho = 0, 
		Persp
	};	

	class CameraMan
	{
	public:			
		CameraMan(const CamMode mode, const float aspectRatio = 1.0f, const OrthoHandler::Data orthodata = OrthoHandler::Data(), PerspHandler::Data perpsdata = PerspHandler::Data());
		~CameraMan();

		const u_ptr<Camera>& getCam();
		const s_ptr<CameraHandler>& handler();

		const glm::mat4& View();
		const glm::mat4& Projection();

		void onEvent(Event& e);

		void setKeySwitch(const Key newkey)			{ m_switchKey = newkey; }
		void switchCamMode(const CamMode mode)		{ m_mode = mode; }

		void enablePrimeWindowResize();
		void disablePrimeWindowResize();

		void refreshAspectRatio(const glm::vec2 viewport);

		const CamMode  getCamMode()  { return m_mode; }

	private:
		s_ptr<CameraHandler> m_cameraHandler[2];

		CamMode	 m_mode;
		Key m_switchKey;		
	};
}