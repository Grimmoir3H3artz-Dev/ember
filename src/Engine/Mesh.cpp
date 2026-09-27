#include "Engine/Mesh.hpp"

#include <glad/glad.h>

namespace Ember {

Mesh Mesh::makeColoredCube()
{
    // pos.xyz, color.rgb — 36 verts, no IBO yet (keep the first 3D path simple)
    const float vertices[] = {
        // front
        -0.5f, -0.5f,  0.5f,  0.90f, 0.32f, 0.28f,
         0.5f, -0.5f,  0.5f,  0.90f, 0.32f, 0.28f,
         0.5f,  0.5f,  0.5f,  0.95f, 0.55f, 0.30f,
        -0.5f, -0.5f,  0.5f,  0.90f, 0.32f, 0.28f,
         0.5f,  0.5f,  0.5f,  0.95f, 0.55f, 0.30f,
        -0.5f,  0.5f,  0.5f,  0.95f, 0.55f, 0.30f,
        // back
        -0.5f, -0.5f, -0.5f,  0.25f, 0.45f, 0.85f,
         0.5f,  0.5f, -0.5f,  0.35f, 0.65f, 0.95f,
         0.5f, -0.5f, -0.5f,  0.25f, 0.45f, 0.85f,
        -0.5f, -0.5f, -0.5f,  0.25f, 0.45f, 0.85f,
        -0.5f,  0.5f, -0.5f,  0.35f, 0.65f, 0.95f,
         0.5f,  0.5f, -0.5f,  0.35f, 0.65f, 0.95f,
        // left
        -0.5f, -0.5f, -0.5f,  0.30f, 0.75f, 0.50f,
        -0.5f, -0.5f,  0.5f,  0.30f, 0.75f, 0.50f,
        -0.5f,  0.5f,  0.5f,  0.55f, 0.90f, 0.45f,
        -0.5f, -0.5f, -0.5f,  0.30f, 0.75f, 0.50f,
        -0.5f,  0.5f,  0.5f,  0.55f, 0.90f, 0.45f,
        -0.5f,  0.5f, -0.5f,  0.55f, 0.90f, 0.45f,
        // right
         0.5f, -0.5f, -0.5f,  0.80f, 0.70f, 0.20f,
         0.5f,  0.5f,  0.5f,  0.95f, 0.85f, 0.30f,
         0.5f, -0.5f,  0.5f,  0.80f, 0.70f, 0.20f,
         0.5f, -0.5f, -0.5f,  0.80f, 0.70f, 0.20f,
         0.5f,  0.5f, -0.5f,  0.95f, 0.85f, 0.30f,
         0.5f,  0.5f,  0.5f,  0.95f, 0.85f, 0.30f,
        // top
        -0.5f,  0.5f, -0.5f,  0.85f, 0.85f, 0.90f,
        -0.5f,  0.5f,  0.5f,  0.85f, 0.85f, 0.90f,
         0.5f,  0.5f,  0.5f,  1.00f, 1.00f, 1.00f,
        -0.5f,  0.5f, -0.5f,  0.85f, 0.85f, 0.90f,
         0.5f,  0.5f,  0.5f,  1.00f, 1.00f, 1.00f,
         0.5f,  0.5f, -0.5f,  1.00f, 1.00f, 1.00f,
        // bottom
        -0.5f, -0.5f, -0.5f,  0.20f, 0.20f, 0.22f,
         0.5f, -0.5f,  0.5f,  0.35f, 0.35f, 0.38f,
        -0.5f, -0.5f,  0.5f,  0.20f, 0.20f, 0.22f,
        -0.5f, -0.5f, -0.5f,  0.20f, 0.20f, 0.22f,
         0.5f, -0.5f, -0.5f,  0.35f, 0.35f, 0.38f,
         0.5f, -0.5f,  0.5f,  0.35f, 0.35f, 0.38f,
    };

    Mesh mesh;
    glGenVertexArrays(1, &mesh.m_vao);
    glGenBuffers(1, &mesh.m_vbo);
    glBindVertexArray(mesh.m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          reinterpret_cast<void*>(3 * sizeof(float)));
    glBindVertexArray(0);
    mesh.m_vertexCount = 36;
    return mesh;
}

Mesh::~Mesh()
{
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
    , m_vertexCount(other.m_vertexCount)
{
    other.m_vao = 0;
    other.m_vbo = 0;
    other.m_vertexCount = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
    if (this != &other) {
        if (m_vbo) {
            glDeleteBuffers(1, &m_vbo);
        }
        if (m_vao) {
            glDeleteVertexArrays(1, &m_vao);
        }
        m_vao = other.m_vao;
        m_vbo = other.m_vbo;
        m_vertexCount = other.m_vertexCount;
        other.m_vao = 0;
        other.m_vbo = 0;
        other.m_vertexCount = 0;
    }
    return *this;
}

void Mesh::draw() const
{
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
    glBindVertexArray(0);
}

} // namespace Ember
