#pragma once
#include "GonEngine/ECS/scene_graph.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"
#include <entt.hpp>

namespace Gon {

	class GameObject
	{
	public:
		GameObject() = default;
		GameObject(entt::entity wrap, SceneGraph* scene);
		GameObject(const GameObject& other) = default;

		~GameObject() { m_scene = nullptr; }

		template<typename T, typename... Args>
		T& addComponent(Args&&... args)
		{			
			return m_scene->m_registry.get_or_emplace<T>(m_gameObjectHandle, std::forward<Args>(args)...);			
		}

		template<typename T>
		T& getComponent()
		{			
			GON_ASSERT(hasComponent<T>(), "Not have component!");			
			return m_scene->m_registry.get<T>(m_gameObjectHandle);
		}

		template<typename T>
		bool hasComponent()
		{
			// se sustituyo en las nuevas versiones has por all_of 
			// tengo dudas de que esto funcione bien. Hay que revisar
			const bool result = m_scene->m_registry.all_of<T>(m_gameObjectHandle);
			return result;
		}

		template<typename T>
		void removeComponent()
		{
			if (!hasComponent<T>())	GON_WARN("Not have component to remove!");
			else m_scene->m_registry.remove<T>(m_gameObjectHandle);
		}

		operator bool() const		  { return m_gameObjectHandle != entt::null; }
		operator entt::entity() const { return m_gameObjectHandle; }
		operator uint32_t() const	  { return static_cast<uint32_t>(m_gameObjectHandle); }

		bool operator==(const GameObject& other) const {
			return m_gameObjectHandle == other.m_gameObjectHandle && m_scene == other.m_scene;
		}
		bool operator!=(const GameObject& other) const {
			return !(*this == other);
		}

	private:
		SceneGraph* m_scene { NULL };
		entt::entity m_gameObjectHandle { entt::null };
	};
}