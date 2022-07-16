#include "GonEngine/engine/nodes/nodes.hpp"
#include "GonEngine/engine/log.hpp"
#include "GonEngine/goncfg.h"


namespace gon
{
	// TimeStep
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	TimeStep::TimeStep(float time) :m_Time(time) {}
	TimeStep::operator float() const { return m_Time;}
	float TimeStep::Seconds() const	{ return m_Time; }
	float TimeStep::MilliSeconds() const { return m_Time * 1000.0f; }
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

#if defined (_NAME_TEST) && (_DEBUG) 
	#ifndef _INFO 
		#define _INFO node->getName()
	#endif
#else
	#ifndef _INFO 
		#define _INFO node->id(true)
	#endif
#endif

	// Node Stack Manager
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	NodeStack::NodeStack(const size_t reserve) : m_idxLast(0)
	{
		m_nodes.reserve(reserve);
		GON_INFO("[CREATED] NodeStack.");
	}
	NodeStack::~NodeStack()
	{
	}
	void NodeStack::pushNode(std::unique_ptr<Node> node)
	{
		GON_TRACE("[Node id:{0}] '{1}' pushed to the first half of the list.", node->getId(), node->getName());
		m_nodes.emplace(m_nodes.begin() + m_idxLast, std::move(node));		
		m_idxLast++;
		
	}
	void NodeStack::pushOverNode(std::unique_ptr<Node> overnode)
	{
		GON_TRACE("[Node id:{0}] '{1}' pushed to the second half of the list.", overnode->getId(), overnode->getName());
		m_nodes.emplace_back(std::move(overnode));		
	}
	void NodeStack::popNode(std::unique_ptr<Node> node)
	{
		auto it = std::find(m_nodes.begin(), m_nodes.end(), node);

		if (it != m_nodes.end())
		{
			GON_TRACE("[Node {0}] deleted.", m_idxLast);
			m_nodes.erase(it);
			m_idxLast--;
		}
	}
	void NodeStack::popOverNode(std::unique_ptr<Node> overnode)
	{
		auto it = std::find(m_nodes.begin(), m_nodes.end(), overnode);

		if (it != m_nodes.end())
		{
			GON_TRACE("[Node {0}] deleted.", m_nodes.size());
			m_nodes.erase(it);
		}
	}
	const NodeType NodeStack::getType(int idx)
	{
		return m_nodes[idx]->type();
	}
	std::vector<std::unique_ptr<Node>>::iterator NodeStack::begin()
	{
		return m_nodes.begin();
	}
	std::vector<std::unique_ptr<Node>>::iterator NodeStack::end()
	{
		return m_nodes.end();
	}
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

	void Node::onUpdate(TimeStep dt)
	{
	}

	void Node::onEvent(Event& e)
	{
	}

	const uint32_t Node::getId()
	{
		return m_id;
	}

	

}