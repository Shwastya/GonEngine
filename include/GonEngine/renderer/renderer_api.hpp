#pragma once


namespace gon {

	// API is defined en window.hpp
	// 
	enum class API;
	class RendererApi
	{
	public:		

		RendererApi() = default;
		virtual ~RendererApi() = default;

		RendererApi(const RendererApi&) = delete;
		RendererApi& operator=(const RendererApi&) = delete;

		RendererApi(RendererApi&&) noexcept = delete;
		RendererApi& operator=(RendererApi&&) noexcept = delete;

		// virtual interface 
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
		virtual void init()				= 0;

		virtual void clearColor(const float r, const float g, const float b, const float a)	= 0;
		virtual void clearBuffer()		= 0;
		virtual void clearColorBuffer()	= 0;
		virtual void clearDepthBuffer()	= 0;
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

		// non virtual
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*		
		const static API _API(const bool GetSet, const API api);
		const static API _API();
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
		
	};
}