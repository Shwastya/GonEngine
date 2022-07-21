#pragma once
#include "GonEngine/memcfg/scp_ptr.hpp"
#include <glm/glm.hpp>


namespace gon
{
    class Shader
    {
        
    public:

        Shader() = default;
        virtual ~Shader() = default;

        /*Shader(const Shader&) = default;
        Shader(Shader&&) = default;
        Shader& operator=(const Shader&) = default;
        Shader& operator=(Shader&&) = default;*/

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        // Overload set uniforms functions
        virtual void uniform(const char* name, int value) const = 0;
        virtual void uniform(const char* name, float value) const = 0;;
        virtual void uniform(const char* name, bool value) const = 0;
        virtual void uniform(const char* name, float value1, float value2) const = 0;
        virtual void uniform(const char* name, float value1, float value2, float value3) const = 0;
        virtual void uniform(const char* name, float value1, float value2, float value3, float value4) const = 0;
        virtual void uniform(const char* name, const glm::vec2& value) const = 0;
        virtual void uniform(const char* name, const glm::vec3& value) const = 0;
        virtual void uniform(const char* name, const glm::vec4& value) const = 0;
        virtual void uniform(const char* name, const glm::mat2& value) const = 0;
        virtual void uniform(const char* name, const glm::mat3& value) const = 0;
        virtual void uniform(const char* name, const glm::mat4& value) const = 0;

        //virtual const std::string& GetName() const = 0;

        static s_ptr<Shader> Create(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath = "none");
        //static s_ptr<Shader> Create(const std::string& GLSLFilePath);

    };
}