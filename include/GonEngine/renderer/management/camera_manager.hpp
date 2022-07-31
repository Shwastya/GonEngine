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

		struct DataGuard
		{
			glm::vec3 Position{ 0.0f, 0.0f, 0.0f };
			// both
			float AspectRatio	{ 1.0f };
			// ortho attributes
			float Zoom			{ 0.0f };
			float Rotate		{ 0.0f };
		};

		const u_ptr<Camera>& getCam();
		const s_ptr<CameraHandler>& handler();
		const glm::mat4& projectionMatrix();

		void initCam();
		void switchCam(const CamMode& mode);
		void takeSelectedCam() { switchCam(m_mode); };
		const CamMode getCamMode() { return m_mode; }		

	private:
		CamMode m_mode;
		s_ptr<CameraHandler> m_cameraHandler;
		DataGuard m_Dg;
	};

}