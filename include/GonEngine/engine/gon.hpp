#pragma once
#include "GonEngine/engine/nodes/nodes.hpp"
#include "GonEngine/engine/events/events.hpp"
#include <functional>


namespace gon {

	class SWindow;
	class Event;
	class GonEngine
	{
	public:
		GonEngine(const std::string& name, const size_t reserve = 10);
		virtual ~GonEngine();

		void run();

		static GonEngine* getGon();
		static float getTime();
		SWindow* getWindow();

		void onEvent(Event& e);		
		
		void pushNode(std::unique_ptr<Node> node);
		void pushOverNode(std::unique_ptr<Node> overnode);
		

	private:
		const bool onCloseWindow();

	private: 
		std::unique_ptr<SWindow> m_window;
		bool m_gon_is_running;
		NodeStack m_nodes;

		static GonEngine* s_instance;
	};

	// predeclaracion para el entry-point
	// por parte de los proyectos cliente
	std::unique_ptr<GonEngine> start_project();
	//GonEngine* start_project();
}