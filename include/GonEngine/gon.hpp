#pragma once
#include "GonEngine/renderer/camera/camera_manager.hpp"

namespace gon {
	
	constexpr size_t k_default_reserve{ 10 };

	class SWindow;	class Event; class ImguiLayerContext; 	
	struct Node; class NLayersManager; class RenderManager;
	class Shader; struct VBO; struct EBO; struct VAO; 
	class CameraMan; 

	enum class API;

	class GonEngine
	{
	public:
		GonEngine() = default;
		GonEngine(const API api, const std::string& name, const int32_t width,
				  const int32_t height, const size_t reserve);

		GonEngine(const GonEngine&) = default;
		GonEngine& operator=(const GonEngine&) = default;

		GonEngine(GonEngine&&) noexcept = default;
		GonEngine& operator=(GonEngine&&) noexcept = default;

		virtual ~GonEngine();

		void run();

		static GonEngine& getGon();
		static double getTime();
		SWindow& getPtrWindow();

		void onEvent(Event& e);		
		
		void pushNode(u_ptr<Node> node);
		void pushOverNode(u_ptr<Node> overnode);		
		
	private:
		const bool onCloseWindow();
	private:
		bool m_gon_is_running;

	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
		u_ptr<SWindow>				m_window;
		u_ptr<ImguiLayerContext>	m_imgui;
		u_ptr<NLayersManager>		m_layers;

		u_ptr<VAO>					m_vao;
		u_ptr<Shader>				m_shader;

		u_ptr<RenderManager>		m_render;

		CameraMan m_cameraMan{ CameraMan(CamMode::Persp, 0.0f, 0.0f, 3.0f) };
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
		static GonEngine* s_instance;		
	};


	// entry-point forward declaration.
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	u_ptr<GonEngine> start_project();
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
}