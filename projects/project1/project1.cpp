#include <GonEngine/main.h>

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
			e;
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
			dt;
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