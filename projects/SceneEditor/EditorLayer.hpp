#pragma once

#include "headers/h_layers.hpp"

namespace Gon {

	constexpr OrthoHandler::Data k_orthoData
	{
		glm::vec3{ 0.0f, 0.0f, 0.0f} , // Position
		{ 1.0f }					 , // Zoom
		{ 0.0f }					 , // Rotate
		{ true }					 , // EnableRotation
	}; 
	constexpr PerspHandler::Data k_perspData
	{
		glm::vec3{ 0.0f, 0.0f, 2.5f} , // Position
		glm::vec3{}, glm::vec3{}	 , // Front & Right
		{ -90.0f }					 , // Yaw				
		{ 0.0f   }					 , // Pitch			
		{ 45.0f  }					 , // Fov
	};

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

		u_ptr<VAO>			m_vao, m_vao2;
		u_ptr<Texture2D>	m_texture, m_alphaTexture;	
		s_ptr<CameraMan>	m_cameraMan;		

		ShaderManager		m_shader;
		SceneRenderer		m_render;
		 

	private:
		glm::vec3 m_quadColor{1.0f, 0.0f, 0.0f};
	};
}