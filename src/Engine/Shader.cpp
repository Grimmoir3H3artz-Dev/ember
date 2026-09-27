#include "Engine/Shader.hpp"
#include "Engine/File.hpp"

#include <glad/glad.h>

#include <iostream>
#include <stdexcept>
#include <vector>

namespace Ember {

Shader::Shader(std::string_view vertexPath, std::string_view fragmentPath)
{
    const std::string vertSrc = readTextFile(assetPath(vertexPath));
    const std::string fragSrc = readTextFile(assetPath(fragmentPath));

    const unsigned int vs = compile(GL_VERTEX_SHADER, vertSrc, std::string(vertexPath));
    const unsigned int fs = compile(GL_FRAGMENT_SHADER, fragSrc, std::string(fragmentPath));

    m_id = glCreateProgram();
    glAttachShader(m_id, vs);
    glAttachShader(m_id, fs);
    glLinkProgram(m_id);

    int ok = 0;
    glGetProgramiv(m_id, GL_LINK_STATUS, &ok);
    if (!ok) {
        int len = 0;
        glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &len);
        std::vector<char> log(static_cast<size_t>(len > 1 ? len : 1));
        glGetProgramInfoLog(m_id, len, nullptr, log.data());
        glDeleteShader(vs);
        glDeleteShader(fs);
        glDeleteProgram(m_id);
        m_id = 0;
        throw std::runtime_error(std::string("Shader link failed: ") + log.data());
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader()
{
    if (m_id) {
        glDeleteProgram(m_id);
    }
}

Shader::Shader(Shader&& other) noexcept : m_id(other.m_id)
{
    other.m_id = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept
{
    if (this != &other) {
        if (m_id) {
            glDeleteProgram(m_id);
        }
        m_id = other.m_id;
        other.m_id = 0;
    }
    return *this;
}

void Shader::bind() const
{
    glUseProgram(m_id);
}

void Shader::setMat4(const char* name, const glm::mat4& value) const
{
    const GLint loc = glGetUniformLocation(m_id, name);
    if (loc >= 0) {
        glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
    }
}

void Shader::setVec3(const char* name, const glm::vec3& value) const
{
    const GLint loc = glGetUniformLocation(m_id, name);
    if (loc >= 0) {
        glUniform3fv(loc, 1, &value[0]);
    }
}

void Shader::setInt(const char* name, int value) const
{
    const GLint loc = glGetUniformLocation(m_id, name);
    if (loc >= 0) {
        glUniform1i(loc, value);
    }
}

unsigned int Shader::compile(unsigned int type, const std::string& source, const std::string& label)
{
    const unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int ok = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        int len = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        std::vector<char> log(static_cast<size_t>(len > 1 ? len : 1));
        glGetShaderInfoLog(id, len, nullptr, log.data());
        glDeleteShader(id);
        throw std::runtime_error("Shader compile failed (" + label + "): " + log.data());
    }
    return id;
}

} // namespace Ember
