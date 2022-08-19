#include "GonEngine/events/events.hpp"
#include "GonEngine/ECS/scene_graph.hpp"
#include "GonEngine/ECS/game_object.hpp"
#include "GonEngine/renderer/deltatime.hpp"
#include "GonEngine/renderer/renderer.hpp"
#include "GonEngine/renderer/management/render_manager.hpp"
#include "GonEngine/platform/OpenGL/opengl_texture_cube_map.hpp"


namespace Gon {

	SkyBox::SkyBox() : Selected(0)
	{
		Cubemaps.reserve(2);
	}



	SceneGraph::~SceneGraph()
	{
		m_registry.clear();
	}
	void SceneGraph::pushSkyBox(const std::vector<std::string>& pathfile)
	{
		//u_ptr<CubeMapText> cubemap =  CubeMapText::create(pathfile, CubeMapText::Format::RGB);
		m_skyBox.Cubemaps.push_back(CubeMapText::create(pathfile, CubeMapText::Format::RGB));
	}


	void SceneGraph::onUpdate(const DeltaTime dt)
	{
		RenderMan::setEqualDepthTest();
		{
			Renderer::drawSkyBox(m_skyBox.Cubemaps[m_skyBox.Selected].get());
			//Renderer::drawRotateReflect3D({ -0.5f, 0.2f, -1.0f }, { 20.0f, 0.5f, 0.1f, 0.7f }, glm::vec3{ 1.0f }, m_cubemapText[m_switchSkybox].get(), m_cameraMan.getPosition());
		}
		RenderMan::setLessDepthTest();

		for (auto [entity, transform, mesh, filter] : m_registry.view<TransformComponent, MeshRendererComponent, MeshFilterComponent>().each())
		{
			Renderer::draw3D(filter, transform, mesh);
		}

		/*auto group { m_registry.group<TransformComponent>(entt::get<MeshRendererComponent>) };
		for (auto& entity : group)
		{
			auto& [transform, mesh] { group.get<TransformComponent, MeshRendererComponent>(entity) };			

			Renderer::draw3D(Geometry::Type::CUBE, transform, mesh);			
		}*/
	}

	void SceneGraph::onEvent(Event& e)
	{
		if (e.getEventType() == EventType::KeyPressed)
		{
			const auto& _e = dynamic_cast<OnKeyPressed&>(e);
			if (_e.getKeyCode() == KeyCode::F8)	m_skyBox.switching();
		}
	}


	

	GameObject SceneGraph::createEntity(const std::string& tagname, const glm::vec3 worldpos, const glm::vec3 rotate, const glm::vec3 scale)
	{
		GameObject entity{ m_registry.create(), this };
		entity.addComponent<TagComponent>(tagname.empty() ? "GameObject" : tagname);
		entity.addComponent<TransformComponent>(glm::vec3(worldpos));
		entity.getComponent<TransformComponent>().R = rotate;
		entity.getComponent<TransformComponent>().S = scale;
		return entity;
	}	


	
	void SkyBox::switching()
	{
		Selected = (Selected < Cubemaps.size() - 1) ? ++Selected : 0;
		GON_WARN("CubeMap size: {0}", Cubemaps.size());
		GON_WARN("SkyBox: {0}", Selected);
	}

}