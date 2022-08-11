#include "GonEngine/renderer/management/render_manager.hpp"
#include "GonEngine/geometries/skybox.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"
#include <vector>

namespace Gon {

    SkyBox::SkyBox() : m_vao(VAO::create(1))
    {
        float vertices[] = {
        	// positions          
        	-1.0f,  1.0f, -1.0f,
        	-1.0f, -1.0f, -1.0f,
        	 1.0f, -1.0f, -1.0f,
        	 1.0f, -1.0f, -1.0f,
        	 1.0f,  1.0f, -1.0f,
        	-1.0f,  1.0f, -1.0f,

        	-1.0f, -1.0f,  1.0f,
        	-1.0f, -1.0f, -1.0f,
        	-1.0f,  1.0f, -1.0f,
        	-1.0f,  1.0f, -1.0f,
        	-1.0f,  1.0f,  1.0f,
        	-1.0f, -1.0f,  1.0f,

        	 1.0f, -1.0f, -1.0f,
        	 1.0f, -1.0f,  1.0f,
        	 1.0f,  1.0f,  1.0f,
        	 1.0f,  1.0f,  1.0f,
        	 1.0f,  1.0f, -1.0f,
        	 1.0f, -1.0f, -1.0f,

        	-1.0f, -1.0f,  1.0f,
        	-1.0f,  1.0f,  1.0f,
        	 1.0f,  1.0f,  1.0f,
        	 1.0f,  1.0f,  1.0f,
        	 1.0f, -1.0f,  1.0f,
        	-1.0f, -1.0f,  1.0f,

        	-1.0f,  1.0f, -1.0f,
        	 1.0f,  1.0f, -1.0f,
        	 1.0f,  1.0f,  1.0f,
        	 1.0f,  1.0f,  1.0f,
        	-1.0f,  1.0f,  1.0f,
        	-1.0f,  1.0f, -1.0f,

        	-1.0f, -1.0f, -1.0f,
        	-1.0f, -1.0f,  1.0f,
        	 1.0f, -1.0f, -1.0f,
        	 1.0f, -1.0f, -1.0f,
        	-1.0f, -1.0f,  1.0f,
        	 1.0f, -1.0f,  1.0f
        };

        u_ptr<VBO> vbo = VBO::create(vertices, sizeof(vertices));
        vbo->setLayout({{DataType::Float3, "aPos"},});
        m_vao->takeVBO(vbo);

        GON_TRACE("[CREATED] SkyBox from geometry.");
    }
    SkyBox::~SkyBox()
    {
        GON_TRACE("[DESTROYED] Cube from geometry.");
    }

    void SkyBox::draw()
    {
        RenderMan::setFalseDepthMask();
        {
            m_vao->bind();
            RenderMan::DrawArrays(36);
            m_vao->unbind();
        }        
        RenderMan::setTrueDepthMask();
    }
}