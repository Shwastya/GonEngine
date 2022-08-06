#include "GonEngine/nodes/node.hpp"

namespace Gon
{
	// Node interfaz class
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	Node::Node(const NodeType ntype, const std::string& name)
		: m_nodeType(ntype), 
		  m_name(name)
	{
		static uint32_t id = 0;
		m_id = id++;
	}
	const std::string Node::NodeTypeToString(const NodeType nodetype)
	{
		switch (nodetype)
		{
			case NodeType::Layer:	return "Layer";
			case NodeType::Project: return "Project";
			case NodeType::Engine:  return "Engine";
			case NodeType::ImGui:	return "ImGui";
			case NodeType::Object:	return "GameObject";
			default: return "None";
		}
	}
}