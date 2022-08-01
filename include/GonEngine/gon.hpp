#pragma once
#include "GonEngine/memcfg/scp_ptr.hpp"
#include "GonEngine/renderer/api_context.hpp"

namespace Gon {

	class	SWindow;	
	class	Event;
	struct  OnWindowClose;
	struct	OnWindowResize;
	class	ImguiLayerContext;  
	struct	GameObject; 
	class	GameObjectsManager; 
	class	RenderManager;	
	class	Shader; 
	struct	VAO; 
	class	CameraMan;	

	class GonEngine
	{
	public:

		enum WindowState 
		{
			Minimized = 0, 
			Maximized = 1
		};

		GonEngine();

		GonEngine(const GonEngine&) = default;
		GonEngine& operator=(const GonEngine&) = default;

		GonEngine(GonEngine&&) noexcept = default;
		GonEngine& operator=(GonEngine&&) noexcept = default;

		virtual ~GonEngine();

		void initEngine(const API api, const std::string& name, const int32_t& width, const int32_t& height, const size_t& gameobject_capacity);
		
		void runOnWindowMaximized();	
		void runOnWindowMinimized() {};
		
		void run();
		
		static GonEngine& getGon();		
		SWindow& getPtrWindow();
		static const double getTime();		

		void onEvent(Event& e);		

		void pushGameObject(u_ptr<GameObject> GObject);
		void pushOverGameObject(u_ptr<GameObject> overGOobject);

		// pensado para el uso de framebuffers en la parte del cliente
		// seguramente no sea necesario, plantear eliminarlo
		void disableGonViewPortControl() { m_gon_has_viewPort_control = false; }
		void enableGonViewPortControl()  { m_gon_has_viewPort_control = true;  }

	private:
		const bool onWindowClose(OnWindowClose& e);
		const bool onWindowResize(OnWindowResize& e);

	private:
		bool  m_gon_is_running;
		uint8_t m_if_window_maximized;
		float m_dt; // DeltaTime
		float m_previus_frame_time;
		

		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
		u_ptr<SWindow>				m_window;
		u_ptr<ImguiLayerContext>	m_imgui;
		u_ptr<GameObjectsManager>	m_gameobjects_pile;
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

		std::function<void()> m_game_loop[2];
		bool m_gon_has_viewPort_control;
		

		static GonEngine* s_instance;
	};


	// entry-point forward declaration.
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	u_ptr<GonEngine> start_project();

}