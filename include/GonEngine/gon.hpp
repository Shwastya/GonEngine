#pragma once
#include "GonEngine/memcfg/scp_ptr.hpp"
#include "GonEngine/renderer/api_context.hpp"

namespace Gon {

	class	SWindow;	
	class	Event;
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

		
		GonEngine();

		GonEngine(const GonEngine&) = default;
		GonEngine& operator=(const GonEngine&) = default;

		GonEngine(GonEngine&&) noexcept = default;
		GonEngine& operator=(GonEngine&&) noexcept = default;

		virtual ~GonEngine();

		void initEngine(const API api, const std::string& name, const int32_t& width, const int32_t& height, const size_t& gameobject_capacity);
		
		void runOnWindowMaximized();	// implementamos luego de onwindowsResize = 0
		void runOnWindowMinimized();	// implementamos luego de onwindowsResize = 1
		
		void run();
		
		static GonEngine& getGon();		
		SWindow& getPtrWindow();
		static const double getTime();		

		void onEvent(Event& e);		

		void pushGameObject(u_ptr<GameObject> GObject);
		void pushOverGameObject(u_ptr<GameObject> overGOobject);

		//ProjectPropierties

	private:
		const bool onCloseWindow();

	private:
		bool  m_gon_is_running;
		uint8_t m_if_window_maximized;
		float m_dt; // DeltaTime
		float m_previusFrameTime;
		

		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
		u_ptr<SWindow>				m_window;
		u_ptr<ImguiLayerContext>	m_imgui;
		u_ptr<GameObjectsManager>	m_gameobjects_pile;
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

		std::function<void()> m_game_loop[2];
		
		

		static GonEngine* s_instance;
	};


	// entry-point forward declaration.
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	u_ptr<GonEngine> start_project();

}