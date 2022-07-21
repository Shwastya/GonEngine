#pragma once

#include "GonEngine/geometries/geometry.hpp"

namespace gon
{
    class Triangle final : public Geometry
    {
    public:
        Triangle();

        virtual ~Triangle();

        const size_t sizeVbo();
        const uint32_t* getIndices();

        // TEMPORAL
        // ELIMINAR DESPUES DE PRUEBAS
        float* getPositions();

    private:        
        ScpUint32 m_indices;
    };
}
