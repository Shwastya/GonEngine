#pragma once

#include "GonEngine/nodes/nodes.hpp"

namespace gon {

	

	class ExampleLayer : public Node
	{
	public:

		ExampleLayer(const NodeType ntype = NodeType::Project, const std::string& name = "Example-Layer");

		void onJoin() override;
		void onQuit() override;

		void onEvent(Event& e) override;
		void onUpdate(TimeStep dt) override;
		void onRender() override;
	};
}