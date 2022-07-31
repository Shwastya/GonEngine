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

        const float* get() { return m_vert.get(); };

        // temporal
        const float* getRainbowColor();

    private:
        ScpUint32 m_indices;
        ScpFloat  m_vert;
    };
}
