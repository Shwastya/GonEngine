#include "GonEngine/geometries/cube.hpp"
#include "GonEngine/log.hpp"
#include "GonEngine/memcfg/goncfg.h"

namespace Gon {

    Cube::Cube(const float size) :
        Geometry
        (
            // 6 face * 2 triangle * 3 vertices
            (6 * 2 * 3),    // m_nVertices
            (6 * 2 * 3)     // m_nElements
        )
    {
        GON_TRACE("[CREATED] Cube from geometry.");

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

        float positions[] 
        {            
            -half, -half, half,     // front    
            half, -half, half,
            //half, half, half,

            //-half, -half, half,
            half, half, half,
            -half, half, half,

            half, -half, half,      // right    
            half, -half, -half,
            //half, half, -half,
            
            //half, -half, half,
            half, half, -half,
            half, half, half,

            half, -half, -half,     // back    
            -half, -half, -half,
           // -half, half, -half,

           // half, -half, -half,
            -half, half, -half,
            half, half, -half,

            -half, -half, -half,    // left      
            -half, -half, half,
            //-half, half, half,

           // -half, -half, -half,
            -half, half, half,
            -half, half, -half,

            -half, -half, -half,    // bottom    
            half, -half, -half,
           // half, -half, half,

           // -half, -half, -half,
            half, -half, half,
            -half, -half, half,
            
            -half, half, half,      // top    
            half, half, half,
           // half, half, -half,
            
           // -half, half, half,
            half, half, -half,
            -half, half, -half
        };

        float uvs[] 
        {
            0.0f, 0.0f,   // front
            1.0f, 0.0f,
            //1.0f, 1.0f,

            //0.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,

            0.0f, 0.0f,   // right
            1.0f, 0.0f,
           // 1.0f, 1.0f,

           // 0.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,

            0.0f, 0.0f,   // back
            1.0f, 0.0f,
           // 1.0f, 1.0f,

           // 0.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,

            0.0f, 0.0f,   // left
            1.0f, 0.0f,
           // 1.0f, 1.0f,

           // 0.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,

            0.0f, 0.0f,   // bottom
            1.0f, 0.0f,
          //  1.0f, 1.0f,

           // 0.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,

            0.0f, 0.0f,   // top
            1.0f, 0.0f,
            //1.0f, 1.0f,

           // 0.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
        };

        float normals[] 
        {
            0.0f, 0.0f, 1.0f,  // front
            0.0f, 0.0f, 1.0f,
           // 0.0f, 0.0f, 1.0f,

           // 0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,

            1.0f, 0.0f, 0.0f,  // right
            1.0f, 0.0f, 0.0f,
            //1.0f, 0.0f, 0.0f,

           // 1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,

            0.0f, 0.0f, -1.0f,  // back
            0.0f, 0.0f, -1.0f,
           // 0.0f, 0.0f, -1.0f,

           // 0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,

            -1.0f, 0.0f, 0.0f,  // left
            -1.0f, 0.0f, 0.0f,
            //-1.0f, 0.0f, 0.0f,

           // -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,

            0.0f, -1.0f, 0.0f,  // bottom
            0.0f, -1.0f, 0.0f,
           // 0.0f, -1.0f, 0.0f,

           // 0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,

            0.0f, 1.0f, 0.0f,   // top
            0.0f, 1.0f, 0.0f,
           // 0.0f, 1.0f, 0.0f,

           // 0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f
        };

        uint32_t indices[]
        {
            0, 1, 2,    0 ,2 ,3,
            4, 5, 6,    4, 6, 7,
            8, 9, 10,   8, 10, 11,
            12, 13, 14, 12, 14, 15,
            16, 17, 18, 16, 18, 19,
            20, 21, 22, 20, 22, 23
        };

        //uint32_t indices[]  
        //{ 
        //    0, 1, 2,    /**/  3,  4,  5,    // front
        //    6, 7, 8,    /**/  9, 10, 11,    // right
        //    12, 13, 14, /**/ 15, 16, 17,    // back
        //    18, 19, 20, /**/ 21, 22, 23,    // left
        //    24, 25, 26, /**/ 27, 28, 29,    // bottom
        //    30, 31, 32, /**/ 33, 34, 35     // top
        //};

        setData(m_vert.get(), positions, uvs, normals, false);
        memcpy(m_indices.get(), indices, sizeof(indices));
    }
    Cube::~Cube()
    {
        GON_TRACE("[DESTROYED] Cube from geometry.");
    }
    const uint32_t Cube::size()
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
    const uint32_t* Cube::getIndices()
    {
        return m_indices.get();
    }
    const uint32_t Cube::nIndices()
    {
        return m_nElements;
    }
    const float* Cube::getRainbowColor()
    {

        static float rainbowColor[]
        {
            1.0f, 0.0f, 0.0f,  // front
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            1.0f, 0.5f, 0.0f,

            1.0f, 0.0f, 0.0f,  // front
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.5,

            1.0f, 0.0f, 0.0f,  // front
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.5f, 1.0f,

            1.0f, 0.0f, 0.0f,  // front
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.5f, 1.0f, 0.0f,

            1.0f, 0.0f, 0.0f,  // front
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            1.0f, 0.5f, 0.5f,

            1.0f, 0.0f, 0.0f,  // front
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 1.0f,
        };
        return rainbowColor;

    }
}