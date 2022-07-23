#pragma once
#include <GonEngine/memcfg/scp_ptr.hpp>

namespace gon {

	class Event;

	struct TimeStep
	{
		TimeStep(float time = 0.0f);
		operator float() const;
		float Seconds() const;
		float MilliSeconds() const;
	private:
		float m_Time;
	};

	enum class NodeType
	{
		None = 0,
		Layer,
		Project,
		Engine,
		ImGui,
		Object
	};

	
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-	
	
	struct Node
	{
		Node(const NodeType ntype = NodeType::None, const std::string& name = "noname");

		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;

		Node(Node&&) noexcept = delete;
		Node& operator=(Node&&) noexcept = delete;
		virtual ~Node();

		virtual void onJoin() = 0;
		virtual void onQuit() = 0;	

		virtual void onEvent(Event& e) = 0;
		virtual void onUpdate(TimeStep dt) = 0;

		virtual void onRender() = 0;

		inline const uint32_t getId() { return m_id; };
		inline const NodeType getType() { return m_nodeType; };
		inline  const std::string& getName() const { return m_name; }

	protected:
		const NodeType m_nodeType{ NodeType::None };
		const std::string m_name;
		uint32_t m_id;

	};




	/*struct NLayer : public Node
	{		
		NLayer(const NodeType ntype = NodeType::Layer, const std::string& name = "noname")
			: Node(ntype, name)
		{};

		virtual ~NLayer() = default;

		virtual void onJoin() override = 0;
		virtual void onQuit() override = 0;

		virtual void onEvent(Event& e) = 0;
		virtual void onUpdate(TimeStep dt) = 0;

		virtual void onRender() override = 0;
	};*/
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	class NLayersManager
	{
	public:
		NLayersManager(const size_t reserve);
		virtual ~NLayersManager();

		void pushLayer(u_ptr<Node> node);
		void pushOverLayer(u_ptr<Node> overnode);

		void popLayer(u_ptr<Node> node);
		void popOverLayer(u_ptr<Node> overnode);

		const NodeType getType(int idx);

		std::vector<u_ptr<Node>>::iterator begin();
		std::vector<u_ptr<Node>>::iterator end();

	private:
		std::vector<u_ptr<Node>> m_layers;
		uint32_t m_idxLast{ 0 };
	};
}
