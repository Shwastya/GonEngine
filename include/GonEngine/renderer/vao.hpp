#pragma once
#include "GonEngine/renderer/vbo.hpp"

namespace Gon
{

	struct VAO // virtual table of dispatchs 
	{
		VAO() = default;
		virtual ~VAO() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void takeVBO(u_ptr<VBO>& _vbo) = 0;
		// EBO de momento solo tiene capacidad 1, no se cree necesario mas
		virtual void takeEBO(u_ptr<EBO>& _ebo) = 0;

		virtual const std::vector<u_ptr<VBO>>& getVBO() const = 0;
		//virtual const u_ptr<VBO>& getVBO() const = 0;
		virtual const u_ptr<EBO>& getEBO() const = 0;

		static u_ptr<VAO> create(const size_t reserve);
	};
}