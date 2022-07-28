#pragma once

#include "headers/h_layers.hpp"

namespace Gon {

	class EditorLayer : public GameObject
	{
	public:

		EditorLayer(const GOType ntype, const std::string& name);

		void onJoin() override;
		void onQuit() override;

		void onEvent(Event& e) override;
		void onUpdate(const DeltaTime dt) override;

		void onRender() override;

	private:

		u_ptr<VAO>					m_vao, m_vao2;
		u_ptr<Texture2D>			m_texture, m_alphaTexture;		

		ShaderManager   m_shader;
		SceneRenderer	m_render;
		CameraMan		m_cameraMan{ CameraMan(CamMode::Persp, 0.0f, 0.0f, 3.0f) };

	private:

		glm::vec3 m_quadColor{1.0f, 0.0f, 0.0f};
	};
}