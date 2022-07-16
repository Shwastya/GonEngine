#pragma once
#include "GonEngine/engine/nodes/nodes.hpp"
#include <GonEngine/gon.h>

#define ADD_NODE(x) pushNode(std::make_unique<TestNode>(x));

namespace gon {

	class TestNode : public Node
	{
	public:
		//TestNode(const NodeType ntype = NodeType::Project) : Node(ntype) {}
#if defined (_NAME_TEST) && (_DEBUG)
		TestNode(const NodeType ntype = NodeType::Project, const std::string& name = "test")
			: Node(ntype, name), m_nodeType(ntype), m_name(name)
		{}
#endif
		void onUpdate(TimeStep dt) override
		{
			//APP_INFO("[UPDATE] Test1 node");
		}

		void onEvent(Event& e) override
		{			
			if (m_nodeType == NodeType::None)
			
			{				
				if (e.getEventType() == EventType::MouseButtonPressed)
				{
					//APP_WARN("{0}", m_name);
				}											
			}				
		}

		void bind() override
		{}
		void unbind() override
		{}

	private:
#if defined (_NAME_TEST) && (_DEBUG)
		const std::string m_name{ "" };
#endif
		const NodeType m_nodeType{NodeType::Project};
		uint32_t count = 0;

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