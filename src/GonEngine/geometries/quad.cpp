#include "GonEngine/geometries/quad.hpp"
#include "GonEngine/log.hpp"
#include "GonEngine/memcfg/goncfg.h"

namespace Gon {

    Quad::Quad(const float size) :
        Geometry
        (
            // 1 face * 2 triangle * 3 vertices
            (1 * 2 * 3),    // m_nVertices
            (1 * 2 * 3)     // m_nElements
        )
    {
        GON_TRACE("[CREATED] Quad from geometry.");

        // positions, uvs, normals, tangents, bitangents
        const size_t totSize =
            (m_nVertices * 3) +
            (m_nVertices * 2) +
            (m_nVertices * 3) +
            (m_nVertices * 3) +
            (m_nVertices * 3);

        m_vert.init(totSize);
        m_indices.init(m_nElements);

        const float half = size / 2.0f;

        float positions[] = 
        {   
            //upper right triangle
            half, half, 0.0f,                                  
            half, -half, 0.0f,
            -half, half, 0.0f,
            //lower left triangle
            half, -half, 0.0f,   
            -half, half, 0.0f,
            -half, -half, 0.0f 
        };

        float uvs[] = 
        { 
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,

            1.0f, 0.0f,
            0.0f, 1.0f,
            0.0f, 0.0f 
        };

        float normals[] = 
        { 
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,

            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f 
        };

        uint32_t indices[] = { 0, 2, 1, 3 , 4, 5 };

        setData(m_vert.get(), positions, uvs, normals, false);
        memcpy(m_indices.get(), indices, sizeof(indices));
    }
    Quad::~Quad()
    {
        GON_TRACE("[DESTROYED] Quad from geometry.");
    }
    const uint32_t Quad::size()
    {
        const uint32_t vboSize
        {
            (sizeof(float) * m_nVertices * 3) +
            (sizeof(float) * m_nVertices * 2) +
            (sizeof(float) * m_nVertices * 3) +
            (sizeof(float) * m_nVertices * 3) +
            (sizeof(float) * m_nVertices * 3)
        };
        return vboSize;
    }
    const uint32_t* Quad::getIndices()
    {
        return m_indices.get();
    }
    const uint32_t Quad::nIndices()
    {
        return m_nElements;
    }
}