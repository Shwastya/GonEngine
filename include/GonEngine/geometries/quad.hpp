#pragma once

#include "GonEngine/geometries/geometry.hpp"

namespace Gon {

    class Quad final : public Geometry
    {
    public:
        Quad() = delete;
        Quad(const float size);

        virtual ~Quad();

        const uint32_t  size();
        const uint32_t* getIndices();
        const uint32_t  nIndices();

        const float* get() { return m_vert.get(); };

    private:
        ScpUint32 m_indices;
        ScpFloat  m_vert;
    };
}
