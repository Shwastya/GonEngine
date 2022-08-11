#pragma once
#include "GonEngine/platform/OpenGL/opengl_vao.hpp"
#include "GonEngine/geometries/geometry.hpp"

namespace Gon {

    class Quad final : public Geometry
    {
    public:
        Quad() = delete;
        Quad(const float size);

        virtual ~Quad();

        virtual void draw() override;

    private:
        u_ptr<VAO> m_vao;
    };
}

