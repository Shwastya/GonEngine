#pragma once

namespace gon {

	class ImguiLayerSet
	{
	public:
		
		ImguiLayerSet() = default;
		~ImguiLayerSet();

		void onJoin();

		void ImguiBegin();
		void OnRender();
		void ImguiEnd();

		void onQuit();

		void GonColors();
	};
}