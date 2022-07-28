#include "GonEngine/platform/OpenGL/opengl_shader.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <fstream>
#include <string>

#include <iostream>
#include <sstream>

namespace Gon
{



    OpenGLShader::OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
    {
        
        std::string vertexCode, fragmentCode, geometryCode;
        loadShader(vertexPath, &vertexCode);
        loadShader(fragmentPath, &fragmentCode);

        if (geometryPath != "none") 
        {
            loadShader(geometryPath, &geometryCode);
        }

        const char* vertexStr = vertexCode.c_str();
        const uint32_t vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexStr, nullptr);
        glCompileShader(vertex);
        checkErrors(vertex, Type::Vertex);

        const char* fragmentStr = fragmentCode.c_str();
        const uint32_t fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentStr, nullptr);
        glCompileShader(fragment);
        checkErrors(fragment, Type::Fragment);

        uint32_t geometry = 0;

        if (geometryPath != "none") 
        {
            const char* geometryStr = geometryCode.c_str();
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &geometryStr, nullptr);
            glCompileShader(geometry);
            checkErrors(geometry, Type::Geometry);
        }

        m_id = glCreateProgram();
        glAttachShader(m_id, vertex);
        glAttachShader(m_id, fragment);
        if (geometryPath != "none")
        {
            glAttachShader(m_id, geometry);
        }

        glLinkProgram(m_id);
        checkErrors(m_id, Type::Program);

        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if (geometryPath != "none")
        {
            glDeleteShader(geometry);
        }

        
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_id);
    }

    void OpenGLShader::bind() const
    {
        glUseProgram(m_id);
    }

    void OpenGLShader::unbind() const
    {
        glUseProgram(0);
    }

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
        else GON_ERROR("Error in load shader {0}", path);
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





   /* static GLenum TypeFormat(const std::string& T)
    {
        if (T == "V") return GL_VERTEX_SHADER;
        if (T == "F") return GL_FRAGMENT_SHADER;
        if (T == "G") return GL_GEOMETRY_SHADER;

        GON_ERROR("Unknow shader format!");

        return 0;
    }
    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
       
    {

        std::unordered_map<GLenum, std::string> src;
        src[GL_VERTEX_SHADER] = vertexPath;
        src[GL_FRAGMENT_SHADER] = fragmentPath;

        if (geometryPath != "0") src[GL_GEOMETRY_SHADER] = geometryPath;

        CompileShader(src);
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& GLSLFile)
        
    {
        std::string fileSrc = LoadShader(GLSLFile);
        std::unordered_map<GLenum, std::string> shaderSrcs = SplitGLSLFile(fileSrc);
        CompileShader(shaderSrcs);
    }


    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_id);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_id);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }*/

    //const std::string& OpenGLShader::GetName() const
    //{
    //    return m_Name;
    //}


    //std::unordered_map<GLenum, std::string> OpenGLShader::SplitGLSLFile(const std::string& GLSLSource)
    //{
    //    std::string vertexCode, fragmentCode;

    //    std::unordered_map<GLenum, std::string> shaderSrc;

    //    const char* token = "#TYPE";
    //    size_t tokenLenght = strlen(token);
    //    size_t pos = GLSLSource.find(token, 0);

    //    // La siguiente seccion de codigo habria que mejorar mucho la abstraccion
    //    // De momento, por las prisas, siendo funcional, lo dejo asi

    //    while (pos != std::string::npos)
    //    {
    //        size_t eol = GLSLSource.find_first_of("\r\n", pos);
    //        if (!(eol != std::string::npos)) GON_ERROR("Shader syntax error!");

    //        size_t begin = pos + tokenLenght + 1;
    //        std::string T = GLSLSource.substr(begin, eol - begin);

    //        size_t nextLinePos = GLSLSource.find_first_not_of("\r\n", eol);
    //        pos = GLSLSource.find(token, nextLinePos);

    //        shaderSrc[TypeFormat(T)] = GLSLSource.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? GLSLSource.size() - 1 : nextLinePos));
    //    }
    //    return shaderSrc;
    //}

    //void OpenGLShader::CompileShader(const std::unordered_map<GLenum, std::string>& srcs)
    //{
    //    uint32_t program = glCreateProgram();

    //    // standar array de 3 por si usaramos SHADER de GEOMETRIA
    //    std::array<GLenum, 3> IDShaders;

    //    m_Nshaders = 0;

    //    for (auto& value : srcs)
    //    {
    //        GLenum type = value.first;
    //        const std::string& src = value.second;

    //        const uint32_t shader = glCreateShader(type);
    //        const char* srcStr = src.c_str();

    //        glShaderSource(shader, 1, &srcStr, nullptr);
    //        glCompileShader(shader);
    //        CheckErrors(shader, Type::Shader);

    //        glAttachShader(program, shader);
    //        IDShaders[m_Nshaders] = (shader);
    //        ++m_Nshaders;
    //    }

    //    m_id = program;
    //    glLinkProgram(m_id);
    //    CheckErrors(m_id, Type::Program);

    //    for (int id = 0; id < m_Nshaders; ++id) glDeleteShader(id);
    //}


    //std::string OpenGLShader::LoadShader(const std::string& GLSLFilePath)
    //{
    //    GLSLFilePath;
    //    /*std::ifstream in(GLSLFilePath, std::ios::in | std::ios::binary);
    //    std::string result;

    //    if (in)
    //    {
    //        in.seekg(0, std::ios::end);
    //        result.resize(in.tellg());
    //        in.seekg(0, std::ios::beg);
    //        in.read(&result[0], result.size());
    //        in.close();
    //    }
    //    else GON_ERROR("Error in load GLSL File: {0}", GLSLFilePath);

    //    return result;*/

    //    return std::string();
    //}

    //void OpenGLShader::CheckErrors(uint32_t checkErrors, Type type)
    //{
    //    int success;
    //    char infoLog[512];
    //    if (type != Type::Program)
    //    {
    //        glGetShaderiv(checkErrors, GL_COMPILE_STATUS, &success);
    //        if (!success)
    //        {
    //            glGetShaderInfoLog(checkErrors, 512, nullptr, infoLog);
    //            glDeleteShader(checkErrors);

    //            GON_ERROR("{0}", infoLog);
    //            //GON_ASSERT(false, "Error Compiling Shader!");                
    //            return;
    //        }
    //    }
    //    else
    //    {
    //        glGetProgramiv(checkErrors, GL_LINK_STATUS, &success);
    //        if (!success)
    //        {
    //            glGetProgramInfoLog(checkErrors, 512, nullptr, infoLog);
    //            GON_ERROR("{0}", infoLog);
    //            //GON_ASSERT(false, "Error Linking Program!");
    //        }
    //    }
    //}

    //void OpenGLShader::Uniform(const char* name, int value) const
    //{
    //    glUniform1i(glGetUniformLocation(m_id, name), value);
    //}

    //void OpenGLShader::Uniform(const char* name, bool value) const
    //{
    //    glUniform1i(glGetUniformLocation(m_id, name), static_cast<int>(value));
    //}

    //void OpenGLShader::Uniform(const char* name, float value) const
    //{
    //    glUniform1f(glGetUniformLocation(m_id, name), value);
    //}

    //void OpenGLShader::Uniform(const char* name, float value1, float value2) const
    //{
    //    glUniform2f(glGetUniformLocation(m_id, name), value1, value2);
    //}

    //void OpenGLShader::Uniform(const char* name, float value1, float value2, float value3) const
    //{
    //    glUniform3f(glGetUniformLocation(m_id, name), value1, value2, value3);
    //}

    //void OpenGLShader::Uniform(const char* name, float value1, float value2, float value3, float value4) const
    //{
    //    glUniform4f(glGetUniformLocation(m_id, name), value1, value2, value3, value4);
    //}

    //void OpenGLShader::Uniform(const char* name, const glm::vec2& value) const
    //{
    //    glUniform2fv(glGetUniformLocation(m_id, name), 1, glm::value_ptr(value));
    //}

    //void OpenGLShader::Uniform(const char* name, const glm::vec3& value) const
    //{
    //    glUniform3fv(glGetUniformLocation(m_id, name), 1, glm::value_ptr(value));
    //}

    //void OpenGLShader::Uniform(const char* name, const glm::vec4& value) const
    //{
    //    glUniform4fv(glGetUniformLocation(m_id, name), 1, glm::value_ptr(value));
    //}

    //void OpenGLShader::Uniform(const char* name, const glm::mat2& value) const
    //{
    //    glUniformMatrix2fv(glGetUniformLocation(m_id, name), 1, GL_FALSE, glm::value_ptr(value));
    //}

    //void OpenGLShader::Uniform(const char* name, const glm::mat3& value) const
    //{
    //    glUniformMatrix3fv(glGetUniformLocation(m_id, name), 1, GL_FALSE, glm::value_ptr(value));
    //}

    //void OpenGLShader::Uniform(const char* name, const glm::mat4& value) const
    //{
    //    glUniformMatrix4fv(glGetUniformLocation(m_id, name), 1, GL_FALSE, glm::value_ptr(value));
    //}
}