#pragma once
#include "GonEngine/renderer/cameras/camera.hpp"
#include "GonEngine/memcfg/scp_ptr.hpp"


namespace Gon {


	enum class CamMode 
	{
		Ortho = 0, Persp
	};

	class CameraMan
	{
	public:			
		CameraMan(const CamMode mode);
		CameraMan(const CamMode mode, const glm::vec3& position);
		CameraMan(const CamMode mode, const float posx, const float posy, const float posz);
		~CameraMan();

		void initCam(const glm::vec3& position);
		void switchCam(const CamMode& mode);
		void takeSelectedCam() { switchCam(m_mode); };
		const CamMode getCamMode() { return m_mode; }

		// Only in orthographic camera mode.
		void setRotation(const float rot);

		const std::pair<glm::mat4, glm::mat4> getViewProjectionMatrix() const;

		const glm::vec3& getPosition() { return m_camera->getPosition(); };
		void setPosition(const glm::vec3& position) { m_camera->setPosition(position); };

		// we need to share the camera with renderers
		const s_ptr<Camera>& getCam();

		

	private:
		CamMode m_mode;
		s_ptr<Camera> m_camera;
		float m_last_z, m_last_rot;
	};

}