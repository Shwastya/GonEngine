#pragma once
#include<functional>

namespace gon 
{
	class SWindow;
	class GonEngine
	{
	public:
		GonEngine(const std::string& name);
		virtual ~GonEngine();

		static GonEngine& ptr();

		void run();

	private:

		std::unique_ptr<SWindow> m_window;

		bool m_gonRunning{ true };
	};



	// predeclaracion para el entry-point
	// por parte de los proyectos cliente
	GonEngine* start_project();
}