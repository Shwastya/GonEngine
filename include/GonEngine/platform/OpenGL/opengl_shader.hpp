#pragma once
#include "GonEngine/renderer/shader.hpp"


typedef unsigned int GLenum;

namespace Gon
{
    class OpenGLShader : public Shader
    {
        enum class Type {
            Vertex = 0,
            Fragment,
            Geometry,
            Program,
            Shader
        };

    public:
        OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath);
        OpenGLShader(const std::string& oneFilePath);

        OpenGLShader(const OpenGLShader&) = default;
        OpenGLShader(OpenGLShader&&) = default;
        OpenGLShader& operator=(const OpenGLShader&) = default;
        OpenGLShader& operator=(OpenGLShader&&) = default;

        virtual ~OpenGLShader();       

        virtual void bind()   const override;
        virtual void unbind() const override;

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
        struct ShaderSource
        {
            Type        m_type{};
            std::string m_code{};
        };
        GLenum getGLenumType(const Type type);
        std::string readFile(const std::string& oneFilePath);
        void splitFileCode(const std::string& source, ShaderSource* shaderSource);
        void loadShader(const std::string& path, std::string* code);
        void compileShader(const std::string& source, uint32_t& shaderType, const Type type);
        void createProgram(const uint32_t& vertex, const uint32_t& fragment, const uint32_t& geometry, const bool isGeometry);
        static void checkErrors(uint32_t shader, Type type);

    private:
        uint32_t m_id;
    };
}