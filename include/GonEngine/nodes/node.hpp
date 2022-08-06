#pragma once
#include "GonEngine/memcfg/scp_ptr.hpp"
#include "GonEngine/renderer/deltatime.hpp"
#include <string>

namespace Gon {

	enum class NodeType
	{
		None = 0,
		Layer,
		Project,
		Engine,
		ImGui,
		Object
	};

	

	class Event;
	struct Node
	{
		Node(const NodeType ntype, const std::string& name);

		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;

		Node(Node&&) noexcept = delete;
		Node& operator=(Node&&) noexcept = delete;
		virtual ~Node() = default;

		virtual void onJoin()	= 0;
		virtual void onQuit()	= 0;

		// Non virtual
		const std::string NodeTypeToString(const NodeType nodetype);
		
			
		

	public:
		const uint32_t		getId()	  { return m_id; };
		const NodeType		getType() { return m_nodeType; };
		const std::string&	getName() { return m_name; }

	protected:
		const NodeType m_nodeType{ NodeType::None };
		const std::string m_name;
		uint32_t m_id;

	};
}



