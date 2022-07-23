#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/nodes/nodes.hpp"
#include "GonEngine/log.hpp"

namespace gon
{
	// TimeStep
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	TimeStep::TimeStep(float time) :m_Time(time) {}
	TimeStep::operator float() const { return m_Time; }
	float TimeStep::Seconds() const { return m_Time; }
	float TimeStep::MilliSeconds() const { return m_Time * 1000.0f; }


	// Node interfaz class
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	Node::Node(const NodeType ntype, const std::string& name)
		: m_nodeType(ntype), m_name(name)
	{
		static uint32_t id = 0;
		m_id = id++;
		GON_TRACE("[CREATED] Layer '{0}' id:{1}.",m_name, m_id);
	}

	// Node Stack Manager
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	NLayersManager::NLayersManager(const size_t reserve) : m_idxLast(0)
	{
		m_layers.reserve(reserve);
		GON_TRACE("[CREATED] Layers manager.");
	}
	NLayersManager::~NLayersManager()
	{
		GON_TRACE("[DESTROYED] Layers manager.");
	}
	void NLayersManager::pushLayer(u_ptr<Node> layer)
	{
		GON_INFO("[Layer id:{0}] '{1}' pushed to the first half of the list.", layer->getId(), layer->getName());
		m_layers.emplace(m_layers.begin() + m_idxLast,std::move(layer));
		m_idxLast++;

	}
	void NLayersManager::pushOverLayer(u_ptr<Node> overLayer)
	{
		GON_INFO("[Layer id:{0}] '{1}' pushed to the second half of the list.", overLayer->getId(), overLayer->getName());
		m_layers.emplace_back(std::move(overLayer));
	}
	void NLayersManager::popLayer(u_ptr<Node> NLayer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), NLayer);

		if (it != m_layers.end())
		{
			GON_TRACE("[Layer {0}] deleted.", m_idxLast);
			m_layers.erase(it);
			m_idxLast--;
		}
	}
	void NLayersManager::popOverLayer(u_ptr<Node> overNLayer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), overNLayer);

		if (it != m_layers.end())
		{
			GON_TRACE("[Layer {0}] deleted.", m_layers.size());
			m_layers.erase(it);
		}
	}
	const NodeType NLayersManager::getType(int idx)
	{
		return m_layers[idx]->getType();
	}
	std::vector<u_ptr<Node>>::iterator NLayersManager::begin()
	{
		return m_layers.begin();
	}
	std::vector<u_ptr<Node>>::iterator NLayersManager::end()
	{
		return m_layers.end();
	}
	Node::~Node()
	{
		GON_TRACE("[DESTROYED] Layer '{0}' id:{1}.", m_name, m_id);
	}
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
}