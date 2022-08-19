#include "GonEngine/renderer/management/render_manager.hpp"
#include "GonEngine/renderer/calculate.hpp"
#include "GonEngine/geometries/reflectCube.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"
#include <vector>

namespace Gon {

    ReflectCube::ReflectCube(const float size) // 6 face * 2 triangle * 3 vertices                  
        : m_vao(VAO::create(1))
    {
        const float half{ size / 2.0f };

        float vertices[]
        {
            -half, -half,  half,   0.0f,  0.0f,  1.0f, 
             half, -half,  half,   0.0f,  0.0f,  1.0f,
             half,  half,  half,   0.0f,  0.0f,  1.0f,
                                      
            -half, -half,  half,   0.0f,  0.0f,  1.0f,
             half,  half,  half,   0.0f,  0.0f,  1.0f,
            -half,  half,  half,   0.0f,  0.0f,  1.0f,
                                      
             half, -half,  half,   1.0f,  0.0f,  0.0f, 
             half, -half, -half,   1.0f,  0.0f,  0.0f,
             half,  half, -half,   1.0f,  0.0f,  0.0f,
                                      
             half, -half,  half,   1.0f,  0.0f,  0.0f,
             half,  half, -half,   1.0f,  0.0f,  0.0f,
             half,  half,  half,   1.0f,  0.0f,  0.0f,
                                 
             half, -half, -half,   0.0f,  0.0f, -1.0f, 
            -half, -half, -half,   0.0f,  0.0f, -1.0f,
            -half,  half, -half,   0.0f,  0.0f, -1.0f,
                                 
             half, -half, -half,   0.0f,  0.0f, -1.0f,
            -half,  half, -half,   0.0f,  0.0f, -1.0f,
             half,  half, -half,   0.0f,  0.0f, -1.0f,
                                 
            -half, -half, -half,  -1.0f,  0.0f,  0.0f, 
            -half, -half,  half,  -1.0f,  0.0f,  0.0f,
            -half,  half,  half,  -1.0f,  0.0f,  0.0f,
                                      
            -half, -half, -half,  -1.0f,  0.0f,  0.0f,
            -half,  half,  half,  -1.0f,  0.0f,  0.0f,
            -half,  half, -half,  -1.0f,  0.0f,  0.0f,
                                      
            -half, -half, -half,   0.0f, -1.0f,  0.0f, 
             half, -half, -half,   0.0f, -1.0f,  0.0f,
             half, -half,  half,   0.0f, -1.0f,  0.0f,
                                      
            -half, -half, -half,   0.0f, -1.0f,  0.0f,
             half, -half,  half,   0.0f, -1.0f,  0.0f,
            -half, -half,  half,   0.0f, -1.0f,  0.0f,
                                      
            -half,  half,  half,   0.0f,  1.0f,  0.0f, 
             half,  half,  half,   0.0f,  1.0f,  0.0f,
             half,  half, -half,   0.0f,  1.0f,  0.0f,
                                      
            -half,  half,  half,   0.0f,  1.0f,  0.0f,
             half,  half, -half,   0.0f,  1.0f,  0.0f,
            -half,  half, -half,   0.0f,  1.0f,  0.0f
        }; 

        u_ptr<VBO> vbo = VBO::create(vertices, sizeof(vertices));
        vbo->setLayout
        ({
            {DataType::Float3, "aPos"},
            {DataType::Float3, "aNormal"},
         });
        m_vao->takeVBO(vbo);

        GON_TRACE("[CREATED] ReflectCube from geometry.");
    }
    ReflectCube::~ReflectCube()
    {
        GON_TRACE("[DESTROYED] ReflectCube from geometry.");
    }
    void ReflectCube::draw()
    {
        m_vao->bind();
        RenderMan::DrawArrays(36);
        m_vao->unbind();
    }
}