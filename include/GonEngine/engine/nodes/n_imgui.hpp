#pragma once
#include "GonEngine/engine/nodes/nodes.hpp"


namespace gon
{
	class ImGuiLayer : public Node
	{
	public:
		// ImGuiLayer(const NodeType ntype = NodeType::Project);
#if defined (_NODE_NAMETEST) && (_DEBUG)	
		ImGuiLayer(const NodeType ntype, const std::string& name);
#endif
		~ImGuiLayer();

		virtual void onJoin()	  override;
		virtual void onQuit() override;

		void begin();
		void end();

		void setGonColorProfile();
	};
}