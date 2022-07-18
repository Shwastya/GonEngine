#pragma once
#include "GonEngine/engine/nodes/nodes.hpp"
#include <GonEngine/gon.h>
#include "GonEngine/engine/input.hpp"
#include <imgui.h>


#define ADD_NODE(x) pushNode(std::make_unique<TestNode>(x));

namespace gon {

	class TestNode : public NLayer
	{
	public:
		

		TestNode(const NodeType ntype = NodeType::Project, const std::string& name = "test")
			: NLayer(ntype, name)
		{}

		void onJoin() override
		{}
		void onQuit() override
		{}

		void onEvent(Event& e) override
		{
			/*if (m_nodeType == NodeType::Engine)

			{
				if (e.getEventType() == EventType::MouseButtonPressed)
				{
					APP_WARN("ole! {0}", this->getId());
				}
			}	*/
		}

		void onUpdate(TimeStep dt) override
		{
			/*auto [x, y] = Input::getMousePos();
			APP_INFO("{0},{1}", x, y);*/
		}

		

		void onRender() override
		{
			ImGui::Begin("Test");
			ImGui::Text("Hello world!");
			ImGui::End();
		}

		
		

	private:
		//Input m_input;
	};

	class Test : public GonEngine
	{
	public:
		
		Test() : GonEngine("Project1") 
		{
			pushNode(new TestNode(NodeType::Project));
			//pushNode(new TestNode(NodeType::None));
			//pushNode(new TestNode(NodeType::Project));
			//pushNode(new TestNode(NodeType::Engine));
		};

		~Test() {};
	};

	extern u_ptr<GonEngine> start_project()
	{
		return std::make_unique<Test>();
	}
}