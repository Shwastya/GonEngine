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

        const float* get() { return m_vert.get(); };



    private:        
        ScpUint32 m_indices;
        ScpFloat  m_vert;
    };
}
