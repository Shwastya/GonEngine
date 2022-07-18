#pragma once
#include "GonEngine/engine/nodes/nodes.hpp"
#include "GonEngine/engine/events/events.hpp"
#include "GonEngine/engine/nodes/n_imgui.hpp"

namespace gon {
	
	constexpr size_t k_default_reserve{ 10 };
	class SWindow;
	class Event;
	class GonEngine	
	{
	public:
		GonEngine(const std::string& name = "Gon Engine", 
			const size_t reserve = k_default_reserve);

		virtual ~GonEngine();

		void run();

		static GonEngine& getGon();
		static float getTime();
		SWindow& getPtrWindow();

		void onEvent(Event& e);		
		
		void pushNode(NLayer* node);
		void pushOverNode(NLayer *overnode);
		
		
	private:
		const bool onCloseWindow();

	private: 
		u_ptr<SWindow> m_window;
		ImGuiNode* m_imgui;

		bool m_gon_is_running;
		NLayersManager m_layers;
		


		static GonEngine* s_instance;
	};

	// predeclaracion para el entry-point
	// por parte de los proyectos cliente
	u_ptr<GonEngine> start_project();
}