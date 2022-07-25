#pragma once

#include "GonEngine/nodes/nodes.hpp"

namespace gon {

	

	class EditorLayer : public Node
	{
	public:

		EditorLayer(const NodeType ntype = NodeType::Project, const std::string& name = "Scene Editor");

		void onJoin() override;
		void onQuit() override;

		void onEvent(Event& e) override;
		void onUpdate(TimeStep dt) override;
		void onRender() override;
	};
}