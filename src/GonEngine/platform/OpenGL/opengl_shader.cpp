#include "GonEngine/platform/OpenGL/opengl_shader.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include <glm/gtc/type_ptr.hpp>
#include "GonEngine/log.hpp"
#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <sstream>

namespace Gon {

    GLenum OpenGLShader::getGLenumType(const Type type)
    {
        switch (type)
        {
            case Type::Vertex:      return GL_VERTEX_SHADER;
            case Type::Fragment:    return GL_FRAGMENT_SHADER;
            case Type::Geometry:    return GL_GEOMETRY_SHADER;
        }
        return GL_PROGRAM;
    }    
    OpenGLShader::OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
    {
        const bool isGeometry{ static_cast<bool>(geometryPath.length()) };
        
        std::string vertexCode, fragmentCode, geometryCode;
        uint32_t vertex{ 0 }, fragment{ 0 }, geometry{ 0 };

        loadShader(vertexPath, &vertexCode);
        compileShader(vertexCode, vertex, Type::Vertex);

        loadShader(fragmentPath, &fragmentCode);
        compileShader(fragmentCode, fragment, Type::Fragment);

        if (geometryPath.length())
        {
            loadShader(geometryPath, &geometryCode);
            compileShader(geometryCode, geometry, Type::Geometry);
        }
        createProgram(vertex, fragment, geometry, isGeometry);      
    }    
    OpenGLShader::OpenGLShader(const std::string& oneFilePath)
    {
        std::string source{ OpenGLShader::readFile(oneFilePath) };
        ShaderSource shaderSource[3];
        splitFileCode(source, shaderSource);

        const bool isGeometry{ static_cast<bool>(shaderSource[2].m_code.length()) };
        uint32_t vertex{ 0 }, fragment{ 0 }, geometry{ 0 };

        compileShader(shaderSource[0].m_code, vertex,   shaderSource[0].m_type);
        compileShader(shaderSource[1].m_code, fragment, shaderSource[1].m_type);
        if (isGeometry)
            compileShader(shaderSource[2].m_code, geometry, shaderSource[2].m_type);
        createProgram(vertex, fragment, geometry, isGeometry);
    }
    OpenGLShader::~OpenGLShader()
    {
        GON_TRACE("[DESTROYED] Shader source id: {0}.", m_id);
        glDeleteProgram(m_id);
    }
    std::string OpenGLShader::readFile(const std::string& oneFilePath)
    {
        std::string result{};
        std::ifstream in(oneFilePath, std::ios::in, std::ios::binary);
        if (in)
        {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        }
        else GON_ERROR("Error in load shader {0}", oneFilePath);

        return result;
    }
    void OpenGLShader::splitFileCode(const std::string& source, ShaderSource* shaderSource)
    {
        const char* typeToken{ "#sourceToken" };
        uint8_t idx{ 0 };
        size_t pos{ source.find(typeToken, 0) };

        while (pos != std::string::npos)
        {
            size_t eol{ source.find_first_of("\r\n", pos) };
            GON_ASSERT(eol != std::string::npos, "Syntax Error");
            size_t begin{ pos + strlen(typeToken) + 1 };
            std::string type{ source.substr(begin, eol - begin) };
            GON_ASSERT(type == "Vertex" || type == "Fragment" || type == "pixel", "Invalid shader type token");

            size_t nextLinePos{ source.find_first_not_of("\r\n", eol) };
            pos = source.find(typeToken, nextLinePos);

            if (type == "Vertex") shaderSource[idx].m_type = Type::Vertex;
            else shaderSource[idx].m_type = (type == "Fragment") ? Type::Fragment : Type::Geometry; 

            shaderSource[idx].m_code = source.substr
            (
                nextLinePos, pos -
                (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos)
            );
            ++idx;
        }       
    }
    void OpenGLShader::compileShader(const std::string& source, uint32_t& shaderType, const Type type)
    {
        const char* sourceStr{ source.c_str() };
        shaderType = glCreateShader(getGLenumType(type));
        glShaderSource(shaderType, 1, &sourceStr, nullptr);
        glCompileShader(shaderType);
        checkErrors(shaderType, type);
    }
    void OpenGLShader::createProgram(const uint32_t& vertex, const uint32_t& fragment, const uint32_t& geometry, const bool isGeometry)
    {
        m_id = glCreateProgram();
        glAttachShader(m_id, vertex);
        glAttachShader(m_id, fragment);
        if (isGeometry) glAttachShader(m_id, geometry);
        glLinkProgram(m_id);
        checkErrors(m_id, Type::Program);
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if (isGeometry) glDeleteShader(geometry);
        GON_TRACE("[CREATED] Shader source id: {0}", m_id);
    }   
    void OpenGLShader::bind()   const { glUseProgram(m_id); }
    void OpenGLShader::unbind() const { glUseProgram(0);    }
    void OpenGLShader::loadShader(const std::string& path, std::string* code) 
    {
        std::ifstream file;
        file.open(path, std::ios_base::in);
        if (file) 
        {
            std::stringstream stream;
            stream << file.rdbuf();
            *code = stream.str();
            file.close();
        }
        else GON_ERROR("Error in load shader {0}.", path);
    }   
    void OpenGLShader::checkErrors(uint32_t shader, Type type) 
    {
        int success;
        char infoLog[512];
        if (type != Type::Program) 
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) 
            {
                glGetShaderInfoLog(shader, 512, nullptr, infoLog);
                GON_ERROR("Error Compiling Shader {0}", infoLog);                
            }
        }
        else 
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) 
            {
                glGetProgramInfoLog(shader, 512, nullptr, infoLog);
                GON_ERROR("Error Linking Program {0}", infoLog);
            }
        }
    }
    void OpenGLShader::uniform(const char* name, int value) const
    {
        glUniform1i(glGetUniformLocation(m_id, name), value);
    }
    void OpenGLShader::uniform(const char* name, bool value) const
    {
        glUniform1i(glGetUniformLocation(m_id, name), static_cast<int>(value));
    }
    void OpenGLShader::uniform(const char* name, float value) const
    {
        glUniform1f(glGetUniformLocation(m_id, name), value);
    }
    void OpenGLShader::uniform(const char* name, float value1, float value2) const
    {
        glUniform2f(glGetUniformLocation(m_id, name), value1, value2);
    }
    void OpenGLShader::uniform(const char* name, float value1, float value2, float value3) const
    {
        glUniform3f(glGetUniformLocation(m_id, name), value1, value2, value3);
    }
    void OpenGLShader::uniform(const char* name, float value1, float value2, float value3, float value4) const
    {
        glUniform4f(glGetUniformLocation(m_id, name), value1, value2, value3, value4);
    }
    void OpenGLShader::uniform(const char* name, const glm::vec2& value) const
    {
        glUniform2fv(glGetUniformLocation(m_id, name), 1, glm::value_ptr(value));
    }
    void OpenGLShader::uniform(const char* name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(m_id, name), 1, glm::value_ptr(value));
    }
    void OpenGLShader::uniform(const char* name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(m_id, name), 1, glm::value_ptr(value));
    }
    void OpenGLShader::uniform(const char* name, const glm::mat2& value) const
    {
        glUniformMatrix2fv(glGetUniformLocation(m_id, name), 1, GL_FALSE, glm::value_ptr(value));
    }
    void OpenGLShader::uniform(const char* name, const glm::mat3& value) const
    {        
        glUniformMatrix3fv(glGetUniformLocation(m_id, name), 1, GL_FALSE, glm::value_ptr(value));
    }
    void OpenGLShader::uniform(const char* name, const glm::mat4& value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_id, name), 1, GL_FALSE, glm::value_ptr(value));
    }
}