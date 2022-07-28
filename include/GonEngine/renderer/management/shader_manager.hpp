#pragma once
#include "GonEngine/renderer/shader.hpp"
#include <array>


namespace Gon {

    enum IDShader
    {
        Basic1 = 0,
        Basic2
    };

    // The simplest idea now:
    // the engine will use a series of shaders in a static 
    // library loaded into memory with u_ptr array pointing to Shaders 
    // "In the future I could think of a better strategy" 
	class ShaderManager
	{
	public:
        ShaderManager();
        ~ShaderManager();

        ShaderManager(const ShaderManager&) = delete;
        ShaderManager(ShaderManager&&) = delete;
        ShaderManager& operator=(const ShaderManager&) = delete;
        ShaderManager& operator=(ShaderManager&&) = delete;

        const Shader* ShaderManager::operator[](const IDShader id) const
        {
            return m_storage[id].get();
        }

    private:
        std::array<u_ptr<Shader>, 2> m_storage;
	};


}