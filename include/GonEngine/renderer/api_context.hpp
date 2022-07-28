#pragma once

namespace Gon {	

	enum class API
	{
		None = 0,
		OpenGL,
		DirectX,
		Vulkan
	};

	class APIContext
	{
	public:

		APIContext() = default;
		virtual ~APIContext() = default;

		APIContext(const APIContext&) = delete;
		APIContext& operator=(const APIContext&) = delete;

		APIContext(APIContext&&) noexcept = delete;
		APIContext& operator=(APIContext&&) noexcept = delete;

		virtual void init() = 0;
		virtual void swapBuffers() = 0;

		// non virtual
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*		
		const static API setAPI(const bool GetSet, const API api);
		const static API getAPI();
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	};
}