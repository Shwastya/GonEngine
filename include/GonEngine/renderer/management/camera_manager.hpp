#pragma once

#include "GonEngine/renderer/camera.hpp"
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
		CameraMan(const CamMode mode, const float aspectRatio = 1.0f);
		~CameraMan();

		const u_ptr<Camera>& getCam();
		const s_ptr<CameraHandler>& handler();

		void initCam(const float aspectRatio);
		void switchCam(const CamMode& mode);
		void takeSelectedCam() { switchCam(m_mode); };
		const CamMode getCamMode() { return m_mode; }		

	private:
		CamMode m_mode;
		s_ptr<CameraHandler> m_cameraHandler;
	};

}