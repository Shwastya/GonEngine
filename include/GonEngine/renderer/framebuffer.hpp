#pragma once
#include "GonEngine/memcfg/scp_ptr.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <map>

namespace Gon
{
	enum class FBTextureFormat // Frame Buffer Texture Format
	{
		None = 0,
		// color
		RGBA8,
		RGB,
		REDINTEGER,
		// depth & stencil
		DEPTH24STENCIL8,
		DEPTHCOMPONENT24,
		// default
		Depth = DEPTHCOMPONENT24
	};

	// Frame Buffer Texture specification
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	struct FBTextureProps 
	{
		FBTextureProps() = default;
		FBTextureProps(FBTextureFormat format)
			: TextureFormat(format) 
		{}
		FBTextureFormat TextureFormat = FBTextureFormat::None;
	};

	struct FBPropCollection
	{
		FBPropCollection() = default;
		FBPropCollection(std::initializer_list<FBTextureProps> list)
			: Collection(list) 
		{}
		std::vector<FBTextureProps> Collection;
	};

	// Frame Buffer specifications
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	struct FBProps  
	{
		uint32_t Width;
		uint32_t Height;
		FBPropCollection List;
		uint32_t Samples = 1;
	};

	class FrameBuffer
	{
	public:

		virtual ~FrameBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void activeTexture(uint32_t idx) const = 0;

		virtual void resize(uint32_t W, uint32_t H) = 0;
		virtual int readPixel(uint32_t attachment, int x, int y) = 0;

		virtual uint32_t getFBOTexture(uint32_t idx = 0) const = 0;
		virtual uint32_t getDepthBuffer() const = 0;		 
		virtual const FBProps& getSpecification() const = 0;

		static u_ptr<FrameBuffer> create(const FBProps& spec);		
	};
}
