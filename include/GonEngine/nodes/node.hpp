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

	static const std::string NodeTypeToString(const NodeType nodetype)
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
		virtual void onRender() = 0;

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



