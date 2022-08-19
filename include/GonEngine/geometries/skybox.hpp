#pragma once
#include "GonEngine/platform/OpenGL/opengl_vao.hpp"
#include "GonEngine/geometries/geometry.hpp"

namespace Gon {

    class CubeMap: public Geometry
    {
    public:
        CubeMap();
        virtual ~CubeMap();

        virtual void draw() override;

    private:
        u_ptr<VAO> m_vao;
    };
}
