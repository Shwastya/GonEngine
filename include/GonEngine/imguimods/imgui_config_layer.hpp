#pragma once
namespace Gon {

	class ImguiLayerContext
	{
	public:		
		ImguiLayerContext()  = default;
		~ImguiLayerContext();
		void init();
		void begin();
		void onRender();
		void end();
		void close();
		void GonColors();
	};
}