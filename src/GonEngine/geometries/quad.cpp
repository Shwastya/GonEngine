
#include "GonEngine/renderer/management/render_manager.hpp"
#include "GonEngine/renderer/calculate.hpp"
#include "GonEngine/geometries/quad.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"
#include <vector>

namespace Gon {

    Quad::Quad(const float size) // 6 face * 2 triangle * 3 vertices                  
        : m_vao(VAO::create(1))
    {
        const uint32_t nVertices{ 1 * 2 * 3 };

        const float half{ size / 2.0f };

        float positions[]
        {   
            half,  half, 0.0f,                                  
            half, -half, 0.0f,
           -half, -half, 0.0f,
           -half,  half, 0.0f 
        };
        float uvs[] 
        { 
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f 
        };
        float normals[] 
        { 
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f 
        };
        uint32_t indices[]{ 0, 3, 1, 1 , 3, 2 };

        std::array<float, 18> tangents{}, biTangents{};
        std::array<float, 84> vertices{};

        calculateTangents(positions, uvs, normals, tangents.data(), biTangents.data(), nVertices);

        uint32_t idx = 0, idxUvs = 0, idxVbo = 0;

        for (size_t i = 0; i < nVertices; i++)
        {
            vertices[idxVbo] = positions[idx];
            vertices[idxVbo + 1] = positions[idx + 1];
            vertices[idxVbo + 2] = positions[idx + 2];
            // uvs
            vertices[idxVbo + 3] = uvs[idxUvs];
            vertices[idxVbo + 4] = uvs[idxUvs + 1];
            idxUvs += 2;
            // normals
            vertices[idxVbo + 5] = normals[idx];
            vertices[idxVbo + 6] = normals[idx + 1];
            vertices[idxVbo + 7] = normals[idx + 2];
            // tangents
            vertices[idxVbo + 8] = tangents[idx];
            vertices[idxVbo + 9] = tangents[idx + 1];
            vertices[idxVbo + 10] = tangents[idx + 2];
            // bitangents
            vertices[idxVbo + 11] = biTangents[idx];
            vertices[idxVbo + 12] = biTangents[idx + 1];
            vertices[idxVbo + 13] = biTangents[idx + 2];
            idx += 3;
            idxVbo += 14;
        }

        u_ptr<VBO> vbo = VBO::create(vertices.data(), sizeof(float) * 84);
        vbo->setLayout
        ({
            {DataType::Float3, "aPos"},
            {DataType::Float2, "aUvs"},
            {DataType::Float3, "aNormal"},
            {DataType::Float3, "aTang"},
            {DataType::Float3, "aBitang"}
            });
        m_vao->takeVBO(vbo);
        u_ptr<EBO> ebo = EBO::create(indices, 6);
        m_vao->takeEBO(ebo);

        GON_TRACE("[CREATED] Quad from geometry.");
    }
    Quad::~Quad()
    {
        GON_TRACE("[DESTROYED] Quad from geometry.");
    }

    void Quad::draw()
    {
        m_vao->bind();
        RenderMan::Draw(6);
        m_vao->unbind();
    }
}
//#include "GonEngine/geometries/quad.hpp"
//#include "GonEngine/log.hpp"
//#include "GonEngine/memcfg/goncfg.h"
//
//namespace Gon {
//
//    Quad::Quad(const float size) :
//        Geometry
//        (
//            // 1 face * 2 triangle * 3 vertices
//            (1 * 2 * 3),    // m_nVertices
//            (1 * 2 * 3)     // m_nElements
//        )
//    {
//        GON_TRACE("[CREATED] Quad from geometry.");
//
//        // positions, uvs, normals, tangents, bitangents
//       // m_vert.init(84);
//        m_indices.init(m_nElements);
//
//        const float half = size / 2.0f;
//
//        float positions[]  
//        {   
//            half, half, 0.0f,                                  
//            half, -half, 0.0f,
//
//            -half, -half, 0.0f,
//            -half, half, 0.0f 
//        };
//
//        float uvs[] 
//        { 
//            1.0f, 1.0f,
//            1.0f, 0.0f,
//
//            0.0f, 0.0f,
//            0.0f, 1.0f 
//        };
//
//        float normals[] 
//        { 
//            0.0f, 0.0f, 1.0f,
//            0.0f, 0.0f, 1.0f,
//
//            0.0f, 0.0f, 1.0f,
//            0.0f, 0.0f, 1.0f 
//        };
//
//        uint32_t indices[]{ 0, 3, 1, 1 , 3, 2 };
//
//        setData(m_vert, positions, uvs, normals, false);
//        memcpy(m_indices.get(), indices, sizeof(indices));
//    }
//    Quad::~Quad()
//    {
//        GON_TRACE("[DESTROYED] Quad from geometry.");
//    }
//    const uint32_t Quad::size()
//    {       
//        return sizeof(m_vert);
//    }
//    const uint32_t* Quad::getIndices()
//    {
//        return m_indices.get();
//    }
//    const uint32_t Quad::nIndices()
//    {
//        return m_nElements;
//    }
//}