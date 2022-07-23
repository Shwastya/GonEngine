#pragma once

#include "GonEngine/geometries/geometry.hpp"

namespace gon
{
    class Triangle final : public Geometry
    {
    public:
        Triangle();

        virtual ~Triangle();

        const uint32_t  size();
        const uint32_t* getIndices();
        const uint32_t  nIndices();

        virtual float* get() override { return m_vbo.get(); };



    private:        
        ScpUint32 m_indices;
    };
}
