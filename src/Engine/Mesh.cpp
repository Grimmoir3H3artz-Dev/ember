#include "Engine/Mesh.hpp"

#include <glad/glad.h>

#include <iterator>
#include <vector>

namespace Ember {

Mesh Mesh::makeColoredCube()
{
    return makeTexturedCube();
}

Mesh Mesh::makeTexturedCube()
{
    const float v[] = {
        -0.5f, -0.5f,  0.5f,  0, 0, 1,  0, 0,
         0.5f, -0.5f,  0.5f,  0, 0, 1,  1, 0,
         0.5f,  0.5f,  0.5f,  0, 0, 1,  1, 1,
        -0.5f,  0.5f,  0.5f,  0, 0, 1,  0, 1,
         0.5f, -0.5f, -0.5f,  0, 0,-1,  0, 0,
        -0.5f, -0.5f, -0.5f,  0, 0,-1,  1, 0,
        -0.5f,  0.5f, -0.5f,  0, 0,-1,  1, 1,
         0.5f,  0.5f, -0.5f,  0, 0,-1,  0, 1,
         0.5f, -0.5f,  0.5f,  1, 0, 0,  0, 0,
         0.5f, -0.5f, -0.5f,  1, 0, 0,  1, 0,
         0.5f,  0.5f, -0.5f,  1, 0, 0,  1, 1,
         0.5f,  0.5f,  0.5f,  1, 0, 0,  0, 1,
        -0.5f, -0.5f, -0.5f, -1, 0, 0,  0, 0,
        -0.5f, -0.5f,  0.5f, -1, 0, 0,  1, 0,
        -0.5f,  0.5f,  0.5f, -1, 0, 0,  1, 1,
        -0.5f,  0.5f, -0.5f, -1, 0, 0,  0, 1,
        -0.5f,  0.5f,  0.5f,  0, 1, 0,  0, 0,
         0.5f,  0.5f,  0.5f,  0, 1, 0,  1, 0,
         0.5f,  0.5f, -0.5f,  0, 1, 0,  1, 1,
        -0.5f,  0.5f, -0.5f,  0, 1, 0,  0, 1,
        -0.5f, -0.5f, -0.5f,  0,-1, 0,  0, 0,
         0.5f, -0.5f, -0.5f,  0,-1, 0,  1, 0,
         0.5f, -0.5f,  0.5f,  0,-1, 0,  1, 1,
        -0.5f, -0.5f,  0.5f,  0,-1, 0,  0, 1,
    };

    const unsigned int idx[] = {
         0,  1,  2,  0,  2,  3,
         4,  5,  6,  4,  6,  7,
         8,  9, 10,  8, 10, 11,
        12, 13, 14, 12, 14, 15,
        16, 17, 18, 16, 18, 19,
        20, 21, 22, 20, 22, 23,
    };

    return fromInterleaved(std::vector<float>(std::begin(v), std::end(v)),
                           std::vector<unsigned int>(std::begin(idx), std::end(idx)));
}

Mesh Mesh::fromInterleaved(const std::vector<float>& vertices,
                           const std::vector<unsigned int>& indices)
{
    Mesh mesh;
    glGenVertexArrays(1, &mesh.m_vao);
    glGenBuffers(1, &mesh.m_vbo);
    glGenBuffers(1, &mesh.m_ebo);
    glBindVertexArray(mesh.m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.m_vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(float)),
                 vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(indices.size() * sizeof(unsigned int)),
                 indices.data(), GL_STATIC_DRAW);

    const int stride = 8 * static_cast<int>(sizeof(float));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
                          reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,
                          reinterpret_cast<void*>(6 * sizeof(float)));
    glBindVertexArray(0);
    mesh.m_indexCount = static_cast<int>(indices.size());
    mesh.m_vertexCount = static_cast<int>(vertices.size() / 8);
    return mesh;
}

Mesh::~Mesh()
{
    if (m_ebo) {
        glDeleteBuffers(1, &m_ebo);
    }
    if (m_vbo) {
        glDeleteBuffers(1, &m_vbo);
    }
    if (m_vao) {
        glDeleteVertexArrays(1, &m_vao);
    }
}

Mesh::Mesh(Mesh&& other) noexcept
    : m_vao(other.m_vao)
    , m_vbo(other.m_vbo)
    , m_ebo(other.m_ebo)
    , m_indexCount(other.m_indexCount)
    , m_vertexCount(other.m_vertexCount)
{
    other.m_vao = other.m_vbo = other.m_ebo = 0;
    other.m_indexCount = other.m_vertexCount = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
    if (this != &other) {
        if (m_ebo) {
            glDeleteBuffers(1, &m_ebo);
        }
        if (m_vbo) {
            glDeleteBuffers(1, &m_vbo);
        }
        if (m_vao) {
            glDeleteVertexArrays(1, &m_vao);
        }
        m_vao = other.m_vao;
        m_vbo = other.m_vbo;
        m_ebo = other.m_ebo;
        m_indexCount = other.m_indexCount;
        m_vertexCount = other.m_vertexCount;
        other.m_vao = other.m_vbo = other.m_ebo = 0;
        other.m_indexCount = other.m_vertexCount = 0;
    }
    return *this;
}

void Mesh::draw() const
{
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

} // namespace Ember
