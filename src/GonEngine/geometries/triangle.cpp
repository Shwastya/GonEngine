#include "GonEngine/geometries/triangle.hpp"
#include "GonEngine/log.hpp"
#include "GonEngine/memcfg/goncfg.h"

namespace Gon {

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
        //m_vert.init(42);
        m_indices.init(m_nElements);

        float positions[]
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

        setData(m_vert, positions, uvs, normals, true);
    }
    Triangle::~Triangle()
    {
        GON_TRACE("[DESTROYED] Triangle from geometry.");
    }
    const uint32_t Triangle::size()
    {        
        return sizeof(m_vert);
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