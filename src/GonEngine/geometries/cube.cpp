#include "GonEngine/geometries/cube.hpp"
#include "GonEngine/log.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include <vector>
namespace Gon {

    Cube::Cube(const float size) :
        Geometry
        (
            // 6 face * 2 triangle * 3 vertices
            (6 * 2 * 3),    // m_nVertices
            (6 * 2 * 3)     // m_nElements
        )
    {
        m_vao = VAO::create(1);
        GON_TRACE("[CREATED] Cube from geometry.");

        // positions, uvs, normals, tangents, bitangents
       // m_vert.init(504);
       // m_indices.init(m_nElements);

        const float half = size / 2.0f;

        float positions[] 
        {            
            -half, -half,  half,     // front    
             half, -half,  half,
             half,  half,  half,
            -half,  half,  half,

             half, -half,  half,      // right    
             half, -half, -half,
             half,  half, -half,
             half,  half,  half,

             half, -half, -half,     // back    
            -half, -half, -half,
            -half,  half, -half,
             half,  half, -half,

            -half, -half, -half,    // left      
            -half, -half,  half,
            -half,  half,  half,
            -half,  half, -half,

            -half, -half, -half,    // bottom    
             half, -half, -half,
             half, -half,  half,
            -half, -half,  half,
            
            -half, half,  half,      // top    
             half, half,  half,
             half, half, -half,
            -half, half, -half
        };

        float uvs[] 
        {
            0.0f, 0.0f,   // front
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,

            0.0f, 0.0f,   // right
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,

            0.0f, 0.0f,   // back
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,

            0.0f, 0.0f,   // left
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,

            0.0f, 0.0f,   // bottom
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,

            0.0f, 0.0f,   // top
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
        };

        float normals[] 
        {
            0.0f, 0.0f, 1.0f,  // front
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,

            1.0f, 0.0f, 0.0f,  // right
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,

            0.0f, 0.0f, -1.0f,  // back
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,

            -1.0f, 0.0f, 0.0f,  // left
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,

            0.0f, -1.0f, 0.0f,  // bottom
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,

            0.0f, 1.0f, 0.0f,   // top
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f
        };

        uint32_t indices[]
        {
             0,  1,  2,   0,  2,  3,    // front
             4,  5,  6,   4,  6,  7,    // right
             8,  9, 10,   8, 10, 11,    // back
            12, 13, 14,  12, 14, 15,    // left
            16, 17, 18,  16, 18, 19,    // bottom
            20, 21, 22,  20, 22, 23     // top
        };            
        setData(m_vert, positions, uvs, normals, false);
        memcpy(m_indices, indices, sizeof(indices));
    }
    Cube::~Cube()
    {
        GON_TRACE("[DESTROYED] Cube from geometry.");
    }
    const uint32_t Cube::size()
    {        
        return sizeof(m_vert);
    }
    const uint32_t* Cube::getIndices()
    {
        return m_indices;
    }
    const uint32_t Cube::nIndices()
    {
        return m_nElements;
    }
}