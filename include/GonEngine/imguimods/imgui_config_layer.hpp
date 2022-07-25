#pragma once

namespace gon {

	class ImguiLayerContext
	{
	public:
		
		ImguiLayerContext() = default;
		~ImguiLayerContext();

		void onJoin();

		void ImguiBegin();
		void OnRender();
		void ImguiEnd();

		void onQuit();

		void GonColors();
	};
}