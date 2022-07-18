#pragma once
#include "GonEngine/engine/nodes/nodes.hpp"


namespace gon
{
	class ImGuiNode : public Node
	{
	public:
		
		ImGuiNode(const NodeType ntype = NodeType::ImGui, const std::string& name = "imgui-layer");

		~ImGuiNode();

		virtual void onJoin() override;

		void beginRender();
		virtual void onRender() override;
		void closeRender();

		virtual void onQuit() override;

		void setColorGonDefault();
	};
}