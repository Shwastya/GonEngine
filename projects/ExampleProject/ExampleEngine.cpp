#include "ExampleEngine.hpp"


namespace gon {

	ExampleEngine::ExampleEngine() : GonEngine(API::OpenGL, "Example Template", 1920, 1080, 15)
	{
		APP_WARN("Starting App: 'Example-Template-Layer'.");
		APP_TRACE("Pushing Nodes...");
		pushNode(std::make_unique<ExampleLayer>(NodeType::Layer));
		// pushNode ....
		// pushNode ....
		
	}

	ExampleEngine::~ExampleEngine()
	{
		APP_WARN("Shutting down 'Example-Template-Layer' app.");
	}

	extern u_ptr<GonEngine> start_project()
	{
		return std::make_unique<ExampleEngine>();
	}
}