#pragma once
#include "GonEngine/nodes/node.hpp"

namespace Gon {		
	
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-	
	class Event;

	struct Layer : public Node
	{
		Layer(const NodeType ntype, const std::string& name);

		Layer(const Layer&) = delete;
		Layer& operator=(const Layer&) = delete;

		Layer(Layer&&) noexcept = delete;
		Layer& operator=(Layer&&) noexcept = delete;
		virtual ~Layer();

		virtual void onJoin() = 0;
		virtual void onQuit() = 0;	

		virtual void onEvent(Event& e) = 0;

		virtual void onUpdate(const DeltaTime dt) = 0;
		virtual void onRender() = 0;
	};

	class LayersManager
	{
	public:
		LayersManager(const size_t reserve);
		virtual ~LayersManager();

		void pushLayer(u_ptr<Layer> G_object);
		void pushOverLayer(u_ptr<Layer> over_G_object);

		void popLayer(u_ptr<Layer> G_object);
		void popOverLayer(u_ptr<Layer> over_G_object);

		const NodeType getType(int idx);

		std::vector<u_ptr<Layer>>::iterator begin();
		std::vector<u_ptr<Layer>>::iterator end();

	private:
		std::vector<u_ptr<Layer>> m_Layers;
		uint32_t m_idxLast{ 0 };
	};
}
