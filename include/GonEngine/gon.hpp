#pragma once
#include "GonEngine/nodes/nodes.hpp"
#include "GonEngine/nodes/n_imgui.hpp"

namespace gon {
	
	constexpr size_t k_default_reserve{ 10 };
	class SWindow;
	class Event;
	class Shader;
	class GonEngine	
	{
	public:
		GonEngine(const API api = API::OpenGL,
				  const std::string& name = "Gon Engine",
				  const int32_t width  = 1920,
				  const int32_t height = 1080,
				  const size_t reserve = k_default_reserve);

		virtual ~GonEngine();

		void run();

		static GonEngine& getGon();
		static double getTime();
		SWindow& getPtrWindow();

		void onEvent(Event& e);		
		
		void pushNode(u_ptr<NLayer> node);
		void pushOverNode(u_ptr<NLayer> overnode);
		
		
	private:
		const bool onCloseWindow();

	private: 
		u_ptr<SWindow> m_window;
		ImGuiNode* m_imgui;

		bool m_gon_is_running;
		NLayersManager m_layers;
		
		uint32_t m_VAO{0}, m_VBO{0}, m_EBO{0};
		s_ptr<Shader> m_shader;

	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
		static GonEngine* s_instance;
	};

	// predeclaracion para el entry-point
	// por parte de los proyectos cliente
	u_ptr<GonEngine> start_project();
}