#pragma once
#include "GonEngine/renderer/shader.hpp"


typedef unsigned int GLenum;

namespace gon
{
    class OpenGLShader : public Shader
    {
        enum class Type {
            Vertex,
            Fragment,
            Geometry,
            Program,
            Shader
        };

    public:
        OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath);
        //OpenGLShader() = delete;
        //OpenGLShader(const std::string& GLSLFilePath);

        //OpenGLShader() = default;
        virtual ~OpenGLShader();

        //OpenGLShader(const OpenGLShader&) = default;
        //OpenGLShader(OpenGLShader&&) = default;
        //OpenGLShader& operator=(const OpenGLShader&) = default;
        //OpenGLShader& operator=(OpenGLShader&&) = default;

        virtual void bind()   const override;
        virtual void unbind() const override;

        //virtual const std::string& GetName() const override;

        // Overload set uniforms functions
        virtual void uniform(const char* name, int value) const override;
        virtual void uniform(const char* name, float value) const override;
        virtual void uniform(const char* name, bool value) const override;
        virtual void uniform(const char* name, float value1, float value2) const override;
        virtual void uniform(const char* name, float value1, float value2, float value3) const override;
        virtual void uniform(const char* name, float value1, float value2, float value3, float value4) const override;
        virtual void uniform(const char* name, const glm::vec2& value) const override;
        virtual void uniform(const char* name, const glm::vec3& value) const override;
        virtual void uniform(const char* name, const glm::vec4& value) const override;
        virtual void uniform(const char* name, const glm::mat2& value) const override;
        virtual void uniform(const char* name, const glm::mat3& value) const override;
        virtual void uniform(const char* name, const glm::mat4& value) const override;



    private:

        void loadShader(const std::string& path, std::string* code);
        static void checkErrors(uint32_t shader, Type type);

    private:
        uint32_t m_id;

    };
}