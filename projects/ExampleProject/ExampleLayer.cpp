#include "ExampleLayer.hpp"
#include "GonEngine/events/events.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"
#include <imgui.h>

namespace gon 
{
	ExampleLayer::ExampleLayer(const NodeType ntype, const std::string& name)
	{
	}
	void ExampleLayer::onJoin()
	{
	}
	void ExampleLayer::onQuit()
	{
	}
	void ExampleLayer::onEvent(Event& e)
	{

		if (e.getEventType() == EventType::KeyPressed)
		{
			OnKeyPressed& _e = dynamic_cast<OnKeyPressed&>(e);

			if (_e.getKeyCode() == GON_KEY_A)
			{
				APP_INFO("This is an example of using onEvent");
			}
		}
		
	}
	void ExampleLayer::onUpdate(TimeStep dt)
	{
	}
	void ExampleLayer::onRender()
	{
		static bool show_demo_window = true;
		ImGui::ShowDemoWindow(&show_demo_window);
	}
}