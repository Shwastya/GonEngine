#include "GonEngine/geometries/triangle.hpp"
#include "GonEngine/log.hpp"
#include "GonEngine/memcfg/goncfg.h"
namespace gon
{
    Triangle::Triangle() : 
        Geometry
        (
            // 1 face * 1 triangle * 3 vertices
            (1 * 1 * 3),    // m_nVertices
            (1 * 1 * 3)     // m_nElements
        )        
    { 
        GON_TRACE("[CREATED] Triangle from geometry.");

        // positions, uvs, normals, tangents, bitangents
        const size_t totSize = N_V * 3 + N_V * 2 + N_V * 3 + N_V * 3 + N_V * 3;

        m_vbo.init(totSize);
        m_indices.init(sizeof(int32_t) * m_nElements);

        const float positions[]
        {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };        

        float uvs[]
        {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f
        };        

        float normals[]
        {
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f
        };

        for (uint32_t i = 0; i < 3; ++i) m_indices[i] = i;

        setData(positions, uvs, normals, true);
    }
    Triangle::~Triangle()
    {
        GON_TRACE("[DESTROYED] Triangle from geometry.");
    }
    const uint32_t Triangle::size()
    {
        const uint32_t vboSize
        {
            sizeof(float) * m_nVertices * 3 +
            sizeof(float) * m_nVertices * 2 +
            sizeof(float) * m_nVertices * 3 +
            sizeof(float) * m_nVertices * 3 +
            sizeof(float) * m_nVertices * 3
        };
        return vboSize;
    }
    const uint32_t* Triangle::getIndices()
    {
        return m_indices.get();
    }

    const uint32_t Triangle::nIndices()
    {
        return m_nElements;
    }
}