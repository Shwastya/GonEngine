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
	}

	// Node Stack Manager
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	NLayersManager::NLayersManager(const size_t reserve) : m_idxLast(0)
	{
		m_layers.reserve(reserve);
		GON_INFO("[CREATED] NLayersManager.");
	}
	NLayersManager::~NLayersManager()
	{
	}
	void NLayersManager::pushLayer(u_ptr<NLayer> layer)
	{
		GON_TRACE("[NLayer id:{0}] '{1}' pushed to the first half of the list.", layer->getId(), layer->getName());
		m_layers.emplace(m_layers.begin() + m_idxLast,std::move(layer));
		m_idxLast++;

	}
	void NLayersManager::pushOverLayer(u_ptr<NLayer> overLayer)
	{
		GON_TRACE("[NLayer id:{0}] '{1}' pushed to the second half of the list.", overLayer->getId(), overLayer->getName());
		m_layers.emplace_back(std::move(overLayer));
	}
	void NLayersManager::popLayer(u_ptr<NLayer> NLayer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), NLayer);

		if (it != m_layers.end())
		{
			GON_TRACE("[NLayer {0}] deleted.", m_idxLast);
			m_layers.erase(it);
			m_idxLast--;
		}
	}
	void NLayersManager::popOverLayer(u_ptr<NLayer> overNLayer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), overNLayer);

		if (it != m_layers.end())
		{
			GON_TRACE("[NLayer {0}] deleted.", m_layers.size());
			m_layers.erase(it);
		}
	}
	const NodeType NLayersManager::getType(int idx)
	{
		return m_layers[idx]->type();
	}
	std::vector<u_ptr<NLayer>>::iterator NLayersManager::begin()
	{
		return m_layers.begin();
	}
	std::vector<u_ptr<NLayer>>::iterator NLayersManager::end()
	{
		return m_layers.end();
	}
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

	//void Node::onUpdate(TimeStep dt)
	//{
	//	//GON_WARN("[Node] base-interface has triggering the 'onUpdate()' function");
	//}

	//void Node::onEvent(Event& e)
	//{
	//	//GON_WARN("[Node] base-interface has triggering the 'onEvent()' function");
	//}

	//void Node::onImguiRender()
	//{
	//	//GON_WARN("[Node] base-interface has triggering the 'onImguiRender()' function");
	//}

	

	

	

}