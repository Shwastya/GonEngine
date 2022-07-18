#include "GonEngine/engine/nodes/nodes.hpp"
#include "GonEngine/engine/log.hpp"
#include "GonEngine/goncfg.h"


namespace gon
{
	// TimeStep
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	TimeStep::TimeStep(float time) :m_Time(time) {}
	TimeStep::operator float() const { return m_Time; }
	float TimeStep::Seconds() const { return m_Time; }
	float TimeStep::MilliSeconds() const { return m_Time * 1000.0f; }
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-


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
	void NLayersManager::pushLayer(NLayer* NLayer)
	{
		GON_TRACE("[NLayer id:{0}] '{1}' pushed to the first half of the list.", NLayer->getId(), NLayer->getName());
		m_layers.emplace(m_layers.begin() + m_idxLast,NLayer);
		m_idxLast++;

	}
	void NLayersManager::pushOverLayer(NLayer* overNLayer)
	{
		GON_TRACE("[NLayer id:{0}] '{1}' pushed to the second half of the list.", overNLayer->getId(), overNLayer->getName());
		m_layers.emplace_back(overNLayer);
	}
	void NLayersManager::popLayer(NLayer* NLayer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), NLayer);

		if (it != m_layers.end())
		{
			GON_TRACE("[NLayer {0}] deleted.", m_idxLast);
			m_layers.erase(it);
			m_idxLast--;
		}
	}
	void NLayersManager::popOverLayer(NLayer* overNLayer)
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
	std::vector<NLayer*>::iterator NLayersManager::begin()
	{
		return m_layers.begin();
	}
	std::vector<NLayer*>::iterator NLayersManager::end()
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