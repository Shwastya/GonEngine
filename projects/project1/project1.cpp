#pragma once
#include "GonEngine/engine/nodes/nodes.hpp"
#include <GonEngine/gon.h>
#include "GonEngine/engine/input.hpp"

#define ADD_NODE(x) pushNode(std::make_unique<TestNode>(x));

namespace gon {

	class TestNode : public Node
	{
	public:
		//TestNode(const NodeType ntype = NodeType::Project) : Node(ntype) {}
#if defined (_NODE_NAMETEST) && (_DEBUG)
		TestNode(const NodeType ntype = NodeType::Project, const std::string& name = "test")
			: Node(ntype, name)
		{}
#endif
		void onUpdate(TimeStep dt) override
		{
			auto [x, y] = Input::getMousePos();
			APP_INFO("{0},{1}", x, y);
		}

		void onEvent(Event& e) override
		{			
			if (m_nodeType == NodeType::Engine)
			
			{				
				if (e.getEventType() == EventType::MouseButtonPressed)
				{
					APP_WARN("ole! {0}", this->getId());
				}				
			}				
		}

		void onJoin() override
		{}
		void onQuit() override
		{}

	private:
		//Input m_input;
	};

	class Test : public GonEngine
	{
	public:
		
		Test() : GonEngine("Project1") 
		{
			pushNode(std::make_unique<TestNode>(NodeType::Project, "test1"));
			pushNode(std::make_unique<TestNode>(NodeType::None, "test2"));
			pushNode(std::make_unique<TestNode>(NodeType::Project, "test3"));
			pushNode(std::make_unique<TestNode>(NodeType::Engine, "testEngine"));
		};

		~Test() {};
	};

	extern std::unique_ptr<GonEngine> start_project()
	{
		return std::make_unique<Test>();
	}
}