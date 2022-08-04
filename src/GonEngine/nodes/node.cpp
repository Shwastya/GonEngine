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
}