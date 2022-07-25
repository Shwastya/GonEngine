#include "EditorLayer.hpp"
#include "GonEngine/events/events.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"
#include <imgui.h>

namespace gon 
{
	EditorLayer::EditorLayer(const NodeType ntype, const std::string& name)
	{
	}
	void EditorLayer::onJoin()
	{
	}
	void EditorLayer::onQuit()
	{
	}
	void EditorLayer::onEvent(Event& e)
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
	void EditorLayer::onUpdate(TimeStep dt)
	{
	}
	void EditorLayer::onRender()
	{
		static bool show_demo_window = true;
		ImGui::ShowDemoWindow(&show_demo_window);
	}
}