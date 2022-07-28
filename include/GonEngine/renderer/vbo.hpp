#pragma once
#include "GonEngine/memcfg/scp_ptr.hpp"
#include "GonEngine/renderer/vbo_layout.hpp"

namespace Gon {

	// Vertex Buffer Object
	struct VBO
	{
	
		VBO() = default;
		virtual ~VBO() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setLayout(const VBOLayout& layout) = 0;
		virtual const VBOLayout& getLayout() const = 0;

		static u_ptr<VBO> create(const float* vertices, const uint32_t size);

	};

	// Element Buffer Object
	struct EBO
	{
		EBO() = default;
		virtual ~EBO() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const uint32_t nIndices() = 0;



		static u_ptr<EBO> create(const uint32_t* indices, const uint32_t nIndices);

	};
}