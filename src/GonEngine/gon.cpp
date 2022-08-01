#include "GonEngine/headers/h_gonengine.hpp"

namespace Gon {	

	GonEngine* GonEngine::s_instance = nullptr;

	GonEngine::GonEngine()
		: m_gon_is_running(false),
		m_dt{ 0.0f }, 
		m_previus_frame_time(0.0f),
		m_if_window_maximized(1),
		m_gon_has_viewPort_control(true)
	{
		s_instance = this;		
	}

	GonEngine::~GonEngine()
	{
		GON_WARN("Shutting down Gon-Engine.");
		m_imgui->close();
	}
	void GonEngine::initEngine(const API api, const std::string& name, const int32_t& width, const int32_t& height, const size_t& gameobject_capacity)
	{
		m_window = SWindow::create({ name, api, width, height });
		m_window->setVsync(true);
	
		m_window->setCallBack(std::bind(&GonEngine::onEvent, this, std::placeholders::_1));
		m_game_loop[Minimized] = [this]() { this->runOnWindowMinimized(); };
		m_game_loop[Maximized] = [this]() { this->runOnWindowMaximized(); };

		m_gon_is_running = true;

		m_imgui = std::make_unique<ImguiLayerContext>();
		m_imgui->init();
		m_gameobjects_pile = std::make_unique<GameObjectsManager>(gameobject_capacity);
		
	}
	void GonEngine::runOnWindowMaximized()
	{
		m_imgui->begin();
		{
			for (auto& gameobjects : (*m_gameobjects_pile))
			{
				gameobjects->onUpdate(m_dt);
				gameobjects->onRender();
			}
		}
		m_imgui->end();
	}
	//void GonEngine::runOnWindowMinimized()

	void GonEngine::run()
	{
		
		while (m_gon_is_running)
		{
			m_game_loop[m_if_window_maximized]();

			m_window->swapBuffers();

			const float currentFrameTime{ (float)getTime() };
			m_dt = currentFrameTime - m_previus_frame_time;
			m_previus_frame_time = currentFrameTime;
		}
	}
	

	GonEngine& GonEngine::getGon()		{ return *s_instance; }
	SWindow& GonEngine::getPtrWindow()	{ return   *m_window; }
	const double GonEngine::getTime()
	{
		const double getTime{ glfwGetTime() };
		return getTime;
	}

	// onEvents functions
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	void GonEngine::onEvent(Event& e)
	{
		if (e.getEventType() == EventType::WindowClose)		  onWindowClose(dynamic_cast<OnWindowClose&>(e));
		else if (e.getEventType() == EventType::WindowResize) onWindowResize(dynamic_cast<OnWindowResize&>(e));
			

		// gameobjects loop to propagate events
		for (auto gameobject = (*m_gameobjects_pile).end(); gameobject != (*m_gameobjects_pile).begin();)
		{
			(*--gameobject)->onEvent(e);
		}
	}
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	void GonEngine::pushGameObject(u_ptr<GameObject> GObject)
	{
		GObject->onJoin();
		m_gameobjects_pile->pushGameObject(std::move(GObject));		
	}
	void GonEngine::pushOverGameObject(u_ptr<GameObject> overGObject)
	{
		overGObject->onJoin();
		m_gameobjects_pile->pushOverGameObject(std::move(overGObject));		
	}

	// Window events handlers
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	const bool GonEngine::onWindowClose(OnWindowClose& e)
	{
		m_gon_is_running = false;
		return true;
	}
	const bool GonEngine::onWindowResize(OnWindowResize& e)
	{
		m_if_window_maximized = static_cast<bool>(e.GetHeight());
		
		if (m_gon_has_viewPort_control)
			m_window->onWindowResize(0, 0, e.GetWidth(), e.GetHeight());
		
		return false;
	}
}