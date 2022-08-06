#include "GonEngine/headers/h_gonengine.hpp"

namespace Gon {	

	GonEngine* GonEngine::s_instance{ nullptr };

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
		m_UI.onQuit();		
		for (auto& Layers : (*m_layers_pile)) Layers->onQuit();
		Renderer::reset();
	}
	void GonEngine::initEngine(const API api, const std::string& name, const int32_t& width, const int32_t& height, const size_t& Layer_capacity)
	{
		m_window = SWindow::create({ name, api, width, height });
		m_window->setVsync(true);
		
		m_window->setCallBack(std::bind(&GonEngine::onEvent, this, std::placeholders::_1));
		m_game_loop[Minimized] = [&] { runOnWindowMinimized(); };
		m_game_loop[Maximized] = [&] { runOnWindowMaximized(); };

		m_gon_is_running = true;
		m_UI.onJoin();

		Renderer::init(true, true, true);
		m_layers_pile = make_u_ptr<LayersManager>(Layer_capacity);
		
	}
	void GonEngine::runOnWindowMaximized()
	{
		update();
		render();
	}

	void GonEngine::update()
	{
		
		for (auto& Layers : (*m_layers_pile))
		{
			Layers->onUpdate(m_dt);
		}		
	}

	void GonEngine::render()
	{
		m_UI.Begin();
		{
			for (auto& Layers : (*m_layers_pile))
			{
				Layers->onRender();
			}
		}
		m_UI.End();
	}

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
			

		// Layers loop to propagate events
		for (auto Layer = (*m_layers_pile).end(); Layer != (*m_layers_pile).begin();)
		{
			(*--Layer)->onEvent(e);
		}
	}
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	void GonEngine::pushLayer(u_ptr<Layer> Layer)
	{
		Layer->onJoin();
		m_layers_pile->pushLayer(std::move(Layer));		
	}
	void GonEngine::pushOverLayer(u_ptr<Layer> overLayer)
	{
		overLayer->onJoin();
		m_layers_pile->pushOverLayer(std::move(overLayer));		
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
			Renderer::onWindowResize(e.GetWidth(), e.GetHeight());		
		return false;
	}
}