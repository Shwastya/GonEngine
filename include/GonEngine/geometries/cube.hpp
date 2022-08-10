#pragma once

#include "GonEngine/geometries/geometry.hpp"

namespace Gon {    

    class Cube final : public Geometry
    {
    public:
        Cube() = delete;
        Cube(const float size);

        virtual ~Cube();

        const uint32_t  size();

        const uint32_t* getIndices();
        const uint32_t  nIndices();

        const float* get() { return m_vert; };        

    private:
        
        uint32_t m_indices[36];
        float m_vert[504];
    };
}
