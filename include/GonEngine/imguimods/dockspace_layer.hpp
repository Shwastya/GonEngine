#pragma once
#include "GonEngine/nodes/node.hpp"
#include <imgui.h>

namespace Gon {

	class ImGuiDockSpace : public Node
	{
	public:
		ImGuiDockSpace(const NodeType ntype, const std::string& name);
		virtual ~ImGuiDockSpace();

		virtual void onJoin() override;
		virtual void onQuit() override;

		void Begin();
		void End();

	private:

		struct MenuLayout
		{
			char* FullscreenMenuItem { "Fullscreen mode" };
			bool  IsFullScreen{ false };
		};	

		MenuLayout m_menu;
	
	};
}