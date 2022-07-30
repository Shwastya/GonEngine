#pragma once
#include "GonEngine/memcfg/scp_ptr.hpp"
#include "GonEngine/renderer/deltatime.hpp"

namespace Gon {	

	// GameObject type
	enum class GOType
	{
		None = 0,
		Layer,
		Project,
		Engine,
		ImGui,
		Object
	};
	
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-	
	class Event;
	struct GameObject
	{
		GameObject(const GOType ntype, const std::string& name);

		GameObject(const GameObject&) = delete;
		GameObject& operator=(const GameObject&) = delete;

		GameObject(GameObject&&) noexcept = delete;
		GameObject& operator=(GameObject&&) noexcept = delete;
		virtual ~GameObject();

		virtual void onJoin() = 0;
		virtual void onQuit() = 0;	

		virtual void onEvent(Event& e) = 0;
		virtual void onUpdate(const DeltaTime dt) = 0;

		virtual void onRender() = 0;

		const uint32_t getId() { return m_id; };
		const GOType getType() { return m_gameObjectType; };
		const std::string& getName() const { return m_name; }

	protected:
		const GOType m_gameObjectType{ GOType::None };
		const std::string m_name;
		uint32_t m_id;

	};

	class GameObjectsManager
	{
	public:
		GameObjectsManager(const size_t reserve);
		virtual ~GameObjectsManager();

		void pushGameObject(u_ptr<GameObject> G_object);
		void pushOverGameObject(u_ptr<GameObject> over_G_object);

		void popGameObject(u_ptr<GameObject> G_object);
		void popOverGameObject(u_ptr<GameObject> over_G_object);

		const GOType getType(int idx);

		std::vector<u_ptr<GameObject>>::iterator begin();
		std::vector<u_ptr<GameObject>>::iterator end();

	private:
		std::vector<u_ptr<GameObject>> m_gameObjects;
		uint32_t m_idxLast{ 0 };
	};
}
