#include <GonEngine/gon.h>

namespace gon {
	class GonEngine;

	class TestProject : public GonEngine
	{
	public:
		TestProject() {}
		~TestProject() {}
	};

	GonEngine* initProject()
	{
		return new TestProject();
	}
}

