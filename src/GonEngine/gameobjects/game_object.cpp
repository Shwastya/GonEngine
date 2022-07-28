#include "GonEngine/gameobjects/gameobject.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"

namespace Gon
{
	// DeltaTime
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	DeltaTime::DeltaTime(float time) :m_Time(time) {}
	DeltaTime::operator float() const { return m_Time; }
	const float DeltaTime::Seconds() const { return m_Time; }
	const float DeltaTime::MilliSeconds() const { return m_Time * 1000.0f; }


	// Node interfaz class
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	GameObject::GameObject(const GOType ntype, const std::string& name)
		: m_gameObjectType(ntype), m_name(name)
	{
		static uint32_t id = 0;
		m_id = id++;
		GON_TRACE("[CREATED] GameObject '{0}' id: {1}.",m_name, m_id);
	}

	// Node Stack Manager
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	GameObjectsManager::GameObjectsManager(const size_t reserve_capacity) : m_idxLast(0)
	{
		m_gameObjects.reserve(reserve_capacity);
		GON_TRACE("[CREATED] GameObjects Manager. Capacity: {0}", m_gameObjects.capacity());
	}
	GameObjectsManager::~GameObjectsManager()
	{
		GON_TRACE("[DESTROYED] GameObjects manager.");
	}
	void GameObjectsManager::pushGameObject(u_ptr<GameObject> GObject)
	{
		GON_INFO("[GameObject id: {0}] '{1}' pushed to the first half of the list.", GObject->getId(), GObject->getName());
		m_gameObjects.emplace(m_gameObjects.begin() + m_idxLast,std::move(GObject));
		m_idxLast++;

	}
	void GameObjectsManager::pushOverGameObject(u_ptr<GameObject> overGObject)
	{
		GON_INFO("[GameObject id: {0}] '{1}' pushed to the second half of the list.", overGObject->getId(), overGObject->getName());
		m_gameObjects.emplace_back(std::move(overGObject));
	}
	void GameObjectsManager::popGameObject(u_ptr<GameObject> GObject)
	{
		auto it = std::find(m_gameObjects.begin(), m_gameObjects.end(), GObject);

		if (it != m_gameObjects.end())
		{
			GON_TRACE("[GameObject {0}] deleted.", m_idxLast);
			m_gameObjects.erase(it);
			m_idxLast--;
		}
	}
	void GameObjectsManager::popOverGameObject(u_ptr<GameObject> overGObject)
	{
		auto it = std::find(m_gameObjects.begin(), m_gameObjects.end(), overGObject);

		if (it != m_gameObjects.end())
		{
			GON_TRACE("[GameObject {0}] deleted.", m_gameObjects.size());
			m_gameObjects.erase(it);
		}
	}
	const GOType GameObjectsManager::getType(int idx)
	{
		return m_gameObjects[idx]->getType();
	}
	std::vector<u_ptr<GameObject>>::iterator GameObjectsManager::begin()
	{
		return m_gameObjects.begin();
	}
	std::vector<u_ptr<GameObject>>::iterator GameObjectsManager::end()
	{
		return m_gameObjects.end();
	}
	GameObject::~GameObject()
	{
		GON_TRACE("[DESTROYED] GameObject '{0}' id: {1}.", m_name, m_id);
	}
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
}