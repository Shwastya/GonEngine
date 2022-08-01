#pragma once
#include "GonEngine/renderer/cameras/camera_orthographic.hpp"
#include "GonEngine/renderer/cameras/camera_perspective.hpp"
#include "GonEngine/memcfg/scp_ptr.hpp"
#include "GonEngine/events/events.hpp"

namespace Gon {

	enum class CamMode
	{
		Ortho = 0, Persp
	};	

	class CameraMan
	{
	public:			
		CameraMan(const CamMode mode, const float aspectRatio = 1.0f, const OrthoHandler::Data orthodata = OrthoHandler::Data(), PerspHandler::Data perpsdata = PerspHandler::Data());
		~CameraMan();

		const u_ptr<Camera>& getCam();
		const s_ptr<CameraHandler>& handler();
		const glm::mat4& projectionMatrix();

		void initCam(const OrthoHandler::Data& orthodata, PerspHandler::Data& persdata);
		void switchCam(const CamMode& mode);
		void takeSelectedCam() { switchCam(m_mode); };
		const CamMode getCamMode() { return m_mode; }		

	private:
		CamMode m_mode;
		OrthoHandler::Data m_orthoGuard;
		PerspHandler::Data m_perspGuard;
		s_ptr<CameraHandler> m_cameraHandler;		
		float m_aspectRatio;
	};

}