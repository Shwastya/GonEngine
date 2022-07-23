#pragma once

#include "GonEngine/renderer/vao.hpp"

namespace gon {

	class OpenglVAO : public VAO
	{
	public:

		
		OpenglVAO(const size_t reserve);
		virtual ~OpenglVAO();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void takeVBO(u_ptr<VBO>& _vbo) override;
		virtual void takeEBO(u_ptr<EBO>& _ebo) override;

		//virtual const std::vector<u_ptr<VBO>>& getVBO() const override { return  m_vbo_vec; }
		virtual const u_ptr<VBO>& getVBO() const override { return m_vbo; }
		virtual const u_ptr<EBO>& getEBO() const override { return m_ebo; }
		

	private:

		// using std::shared_ptr<Type>
		uint32_t m_id_vao;
		//std::vector<u_ptr<VBO>> m_vbo_vec;
		//u_ptr<VBO> m_vbo_vec;
		u_ptr<VBO> m_vbo;
		u_ptr<EBO> m_ebo;
		

	};

}