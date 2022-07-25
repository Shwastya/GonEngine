#include "EditorEngine.hpp"


namespace gon {

	EditorEngine::EditorEngine() : GonEngine(API::OpenGL, "Scene Editor", 1920, 1080, 15)
	{
		APP_WARN("Starting App: 'Scene-Editor'.");
		APP_TRACE("Pushing Nodes...");
		pushNode(std::make_unique<EditorLayer>(NodeType::Layer));
		// pushNode ....
		// pushNode ....
		
	}

	EditorEngine::~EditorEngine()
	{
		APP_WARN("Shutting down 'Scene-Editor' app.");
	}

	extern u_ptr<GonEngine> start_project()
	{
		return std::make_unique<EditorEngine>();
	}
}