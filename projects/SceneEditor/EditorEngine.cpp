#include "EditorEngine.hpp"

namespace Gon {

	EditorEngine::EditorEngine() //: GonEngine(API::OpenGL, "Scene Editor", 1920, 1080, 15)
	{
		APP_WARN("Starting App: 'UI-Editor'");

		// Init and set
		GonEngine::getGon().initEngine
		(
			API::OpenGL, 
			"UI-Editor", 
			1920, 
			1080,
			2
		);

		pushLayer(make_u_ptr<EditorLayer>(NodeType::Project, "EditorLayer"));
		// pushLayer ....
		// pushLayer ....		
	}

	EditorEngine::~EditorEngine()
	{
		APP_WARN("Shutting down 'UI-Editor' app");
	}

	extern u_ptr<GonEngine> start_project()
	{
		return make_u_ptr<EditorEngine>();
	}
}