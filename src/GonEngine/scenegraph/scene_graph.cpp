#include "GonEngine/scenegraph/scene_graph.hpp"

namespace Gon {

	SceneGraph::SceneGraph()
	{
		entt::entity entity{ m_registry.create() };


	}

	SceneGraph::~SceneGraph()
	{
	}

}