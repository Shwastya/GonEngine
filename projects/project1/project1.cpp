#include <GonEngine/gon.h>
#pragma once

namespace gon {

	class TestProject : public GonEngine
	{
	public:
		
		TestProject() : GonEngine("Project1") {  };

		~TestProject() {};
	};

	extern GonEngine* start_project()
	{
		return new TestProject();
	}
}



