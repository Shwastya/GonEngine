#pragma once
#if 1
	#define _NODE_NAMETEST
#endif
#include <vector>
#include <iostream>


namespace gon
{
	enum class NodeType
	{
		None = 0,
		Project,
		Engine,
		ImGui,
		Object
	};

	struct TimeStep
	{
		TimeStep(float time = 0.0f);
		operator float() const;
		float Seconds() const;
		float MilliSeconds() const;
	private:
		float m_Time;
	};
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-	
	class Event;
	struct Node
	{
		//Node(const NodeType ntype = NodeType::Project) :m_nodeType(ntype) 
		//{
		//	static uint32_t id = 0;
		//	m_id = id++;
		//};
#if defined (_NODE_NAMETEST) && (_DEBUG) 
		Node(const NodeType ntype = NodeType::Project, const std::string& name = "")
			: m_nodeType(ntype), m_name(name)
		{
			static uint32_t id = 0;
			m_id = id++;			
		};
#endif
		virtual ~Node() = default;

		virtual void onJoin() = 0;
		virtual void onQuit() = 0;

		virtual void onUpdate(TimeStep dt);
		virtual void onEvent(Event& e);
		virtual void onImGuiUpdate() {};

		const uint32_t getId();

		const NodeType type() { return m_nodeType; };		

#if defined (_NODE_NAMETEST) && (_DEBUG) 
		const std::string& getName() const { return m_name; }
	protected:
		std::string m_name{ "" };		
#endif
	protected:
		const NodeType m_nodeType{ NodeType::None };
		uint32_t m_id{ 0 };
	};
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	class NodeStack
	{
	public:
		NodeStack(const size_t reserve);
		virtual ~NodeStack();

		void pushNode(std::unique_ptr<Node> node);
		void pushOverNode(std::unique_ptr<Node> overnode);

		void popNode(std::unique_ptr<Node> node);
		void popOverNode(std::unique_ptr<Node> overnode);

		const NodeType getType(int idx);

		std::vector<std::unique_ptr<Node>>::iterator begin();
		std::vector<std::unique_ptr<Node>>::iterator end();

	private:
		std::vector<std::unique_ptr<Node>> m_nodes;
		uint32_t m_idxLast{ 0 };
	};
}
