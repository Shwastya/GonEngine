#pragma once
#include "GonEngine/platform/OpenGL/opengl_vao.hpp"
#include "GonEngine/geometries/geometry.hpp"

namespace Gon {    

    class Cube final : public Geometry
    {
    public:
        Cube() = delete;
        Cube(const float size);

        virtual ~Cube();

        virtual void draw() override;   

    private:
        u_ptr<VAO> m_vao;      
    };
}
