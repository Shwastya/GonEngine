#include "GonEngine/renderer/management/render_manager.hpp"
#include "GonEngine/renderer/calculate.hpp"
#include "GonEngine/geometries/cube.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"
#include <vector>

namespace Gon {
    
    Cube::Cube(const float size) // 6 face * 2 triangle * 3 vertices                  
        : m_vao(VAO::create(1))        
    {
        const uint32_t nVertices{ 6 * 2 * 3 };        

        const float half { size / 2.0f };

        const float positions[] 
        {            
            -half, -half,  half, // front    
             half, -half,  half,
             half,  half,  half,
            -half,  half,  half,

             half, -half,  half, // right    
             half, -half, -half,
             half,  half, -half,
             half,  half,  half,

             half, -half, -half, // back    
            -half, -half, -half,
            -half,  half, -half,
             half,  half, -half,

            -half, -half, -half, // left      
            -half, -half,  half,
            -half,  half,  half,
            -half,  half, -half,

            -half, -half, -half, // bottom    
             half, -half, -half,
             half, -half,  half,
            -half, -half,  half,
            
            -half,  half,  half, // top    
             half,  half,  half,
             half,  half, -half,
            -half,  half, -half
        };
        const float uvs[]
        {
            0.0f, 0.0f, // front
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,

            0.0f, 0.0f, // right
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,

            0.0f, 0.0f, // back
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,

            0.0f, 0.0f, // left
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,

            0.0f, 0.0f, // bottom
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,

            0.0f, 0.0f, // top
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
        };
        const float normals[]
        {
            0.0f,  0.0f,  1.0f, // front
            0.0f,  0.0f,  1.0f,
            0.0f,  0.0f,  1.0f,
            0.0f,  0.0f,  1.0f,
                          
            1.0f,  0.0f,  0.0f, // right
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
                   
            0.0f,  0.0f, -1.0f, // back
            0.0f,  0.0f, -1.0f,
            0.0f,  0.0f, -1.0f,
            0.0f,  0.0f, -1.0f,
                   
           -1.0f,  0.0f,  0.0f, // left
           -1.0f,  0.0f,  0.0f,
           -1.0f,  0.0f,  0.0f,
           -1.0f,  0.0f,  0.0f,
                          
            0.0f, -1.0f,  0.0f, // bottom
            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,
                          
            0.0f,  1.0f,  0.0f, // top
            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f
        };
        const uint32_t indices[]
        {
             0,  1,  2,   0,  2,  3, // front
             4,  5,  6,   4,  6,  7, // right
             8,  9, 10,   8, 10, 11, // back
            12, 13, 14,  12, 14, 15, // left
            16, 17, 18,  16, 18, 19, // bottom
            20, 21, 22,  20, 22, 23  // top
        };       
        
        std::array<float, 108> tangents{}, biTangents{};
        std::array<float, 504> vertices{};

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

        u_ptr<VBO> vbo = VBO::create(vertices.data(), sizeof(float) * 504);
        vbo->setLayout
        ({
            {DataType::Float3, "aPos"},
            {DataType::Float2, "aUvs"},
            {DataType::Float3, "aNormal"},
            {DataType::Float3, "aTang"},
            {DataType::Float3, "aBitang"}
        });
        m_vao->takeVBO(vbo);
        u_ptr<EBO> ebo = EBO::create(indices, 36);
        m_vao->takeEBO(ebo);

        GON_TRACE("[CREATED] Cube from geometry.");        
    }
    Cube::~Cube()
    {
        GON_TRACE("[DESTROYED] Cube from geometry.");        
    }

    void Cube::draw()
    {
        m_vao->bind();
        RenderMan::Draw(36);
        m_vao->unbind();
    }
}