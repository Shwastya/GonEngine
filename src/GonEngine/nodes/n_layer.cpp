#include "GonEngine/nodes/n_layer.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"

namespace Gon
{
	// Node interfaz class
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	Layer::Layer(const NodeType ntype, const std::string& name)
		: Node(ntype, name)
	{		
		GON_TRACE("[CREATED] Layer: (Type: {0}) > (Name: {1}) > (Id: {2})", NodeTypeToString(m_nodeType), m_name, m_id);
	}
	Layer::~Layer()
	{
		GON_TRACE("[DESTROYED] Layer: (Type: {0}) > (Name: {1}) > (Id: {2})", NodeTypeToString(m_nodeType), m_name, m_id);
	}
	// Node Stack Manager
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	LayersManager::LayersManager(const size_t reserve_capacity) : m_idxLast(0)
	{
		m_Layers.reserve(reserve_capacity);
		GON_TRACE("[CREATED] LayerManager: Capacity = {0}", m_Layers.capacity());
	}
	LayersManager::~LayersManager()
	{
		GON_TRACE("[DESTROYED] LayerManager");
	}
	void LayersManager::pushLayer(u_ptr<Layer> Layer)
	{
		GON_INFO("[Layer id: {0}] '{1}' pushed to the first half of the list", Layer->getId(), Layer->getName());
		m_Layers.emplace(m_Layers.begin() + m_idxLast,std::move(Layer));
		m_idxLast++;

	}
	void LayersManager::pushOverLayer(u_ptr<Layer> overLayer)
	{
		GON_INFO("[Layer id: {0}] '{1}' pushed to the second half of the list", overLayer->getId(), overLayer->getName());
		m_Layers.emplace_back(std::move(overLayer));
	}
	void LayersManager::popLayer(u_ptr<Layer> Layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), Layer);

		if (it != m_Layers.end())
		{
			GON_TRACE("[Layer {0}] deleted", m_idxLast);
			m_Layers.erase(it);
			m_idxLast--;
		}
	}
	void LayersManager::popOverLayer(u_ptr<Layer> overLayer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overLayer);

		if (it != m_Layers.end())
		{
			GON_TRACE("[Layer {0}] deleted", m_Layers.size());
			m_Layers.erase(it);
		}
	}
	const NodeType LayersManager::getType(int idx)
	{
		return m_Layers[idx]->getType();
	}
	std::vector<u_ptr<Layer>>::iterator LayersManager::begin()
	{
		return m_Layers.begin();
	}
	std::vector<u_ptr<Layer>>::iterator LayersManager::end()
	{
		return m_Layers.end();
	}
	
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
}