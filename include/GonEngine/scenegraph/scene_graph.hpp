#pragma once
#include <entt.hpp>

namespace Gon {

	class SceneGraph
	{
	public:
		SceneGraph();
		~SceneGraph();

	private:
		entt::registry m_registry;
	};
}