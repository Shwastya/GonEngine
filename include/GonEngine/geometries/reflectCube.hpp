#pragma once
#include "GonEngine/platform/OpenGL/opengl_vao.hpp"
#include "GonEngine/geometries/geometry.hpp"

namespace Gon {

    class ReflectCube final : public Geometry
    {
    public:
        ReflectCube() = delete;
        ReflectCube(const float size);

        virtual ~ReflectCube();

        virtual void draw() override;

    private:
        u_ptr<VAO> m_vao;
    };
}
