#pragma once
#include "GonEngine/nodes/node.hpp"

namespace Gon {

	class ImGuiContext : public Node
	{
	public:
		ImGuiContext(const NodeType ntype, const std::string& name);
		virtual ~ImGuiContext();


		virtual void onJoin() override;
		virtual void onQuit() override;
		virtual void onRender() override;

		// Non virtual
		void Begin();
		void End();
		void GonColors();
	};
}