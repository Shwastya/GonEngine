#include <GonEngine/main.h>
#include "GonEngine/geometries/triangle.hpp"

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
			
			if (e.getEventType() == EventType::KeyPressed)
			{
				OnKeyPressed& _e = dynamic_cast<OnKeyPressed&>(e);

				if (_e.getKeyCode() == GON_KEY_A)
				{
					Triangle triangle;
				}					
			}
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
	};

	class Test : public GonEngine
	{
	public:
		
		Test() : GonEngine(API::OpenGL, "project", 1920, 1080, 15) 
		{
			pushNode(std::make_unique<TestNode>(NodeType::Project));
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