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
		glm::vec3{ 0.0f, 0.0f, 3.0f} , // Position
		glm::vec3{}, glm::vec3{}	 , // Front & Right
		{ -90.0f }					 , // Yaw				
		{ 0.0f   }					 , // Pitch			
		{ 45.0f  }					 , // Fov
	};

	class EditorLayer : public Layer
	{
	public:		

		EditorLayer(const NodeType ntype, const std::string& name);
		~EditorLayer();

		void onJoin() override;
		void onQuit() override;

		void onEvent(Event& e) override;
		void onUpdate(const DeltaTime dt) override;

		void onRender() override;

	private:	

		u_ptr<Texture2D>	m_texture[4];
		u_ptr<CubeMapText>  m_cubemapText;
		s_ptr<CameraMan>	m_cameraMan;
		u_ptr<FrameBuffer>  m_frameBuffer;

		ImGuiDockSpace m_dock_space{ ImGuiDockSpace(NodeType::ImGui, "DockSpace-Layer") };
		glm::vec2 m_viewPort{ 0.0f, 0.0f };
	
		bool m_windowFocused{ false };
		bool m_windowHovered{ false };

		GON_UI_TIMING_VECS_DEFS;
	};
}