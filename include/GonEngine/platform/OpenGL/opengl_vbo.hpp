#pragma once
#include "GonEngine/renderer/vbo.hpp"


namespace gon {


	struct OpenglVBO : public VBO
	{
		OpenglVBO(float* vertices, const uint32_t size);
		virtual ~OpenglVBO();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void setLayout(const VBOLayout& layout) override { m_layout = layout; };
	
		virtual const VBOLayout& getLayout() const override { return m_layout; };

	private:
		uint32_t m_id_vbo;
		VBOLayout m_layout;
		
	}; 

	struct OpenglEBO : public EBO
	{

		OpenglEBO(const uint32_t* indices, const uint32_t nIndices);

		virtual ~OpenglEBO();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual const uint32_t nIndices() override;

	private:
		uint32_t m_id_ebo;
		const uint32_t m_nIndices;

	};

}