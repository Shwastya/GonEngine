#pragma once
#include "GonEngine/platform/OpenGL/opengl_vao.hpp"
#include "GonEngine/geometries/geometry.hpp"

namespace Gon {

    class SkyBox : public Geometry
    {
    public:
        SkyBox();
        virtual ~SkyBox();

        virtual void draw() override;

    private:
        u_ptr<VAO> m_vao;
    };
}
