#include "GonEngine/ECS/game_object.hpp"
namespace Gon
{
	GameObject::GameObject(entt::entity manager, SceneGraph* scene)
		: m_gameObjectHandle(manager), m_scene(scene) {  }
}



