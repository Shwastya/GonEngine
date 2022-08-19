#pragma once
#include "GonEngine/ECS/components.hpp"
#include "GonEngine/memcfg/scp_ptr.hpp"
#include <entt.hpp>

namespace Gon {

	// Forward declarations
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	struct DeltaTime;
	class  Event;
	class  GameObject;
	class  CubeMapText;
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	
	struct SkyBox
	{
		SkyBox();
		~SkyBox() = default;

		void switching();

		int8_t Selected;
		std::vector<u_ptr<CubeMapText>>  Cubemaps;
		
	};

	class SceneGraph
	{
	public:
		SceneGraph() = default;
		~SceneGraph();

		void pushSkyBox(const std::vector<std::string>& pathfile);

		void onUpdate(const DeltaTime dt);
		void onEvent(Event& e);

		GameObject createEntity(const std::string& tagname = "", const glm::vec3 worldpos = glm::vec3(0.0f), const glm::vec3 rotate = glm::vec3(1.0f), const glm::vec3 scale = glm::vec3(1.0f));

	private:

		SkyBox m_skyBox;
		entt::registry m_registry;

		friend class GameObject;
	};
}