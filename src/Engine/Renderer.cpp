#include "Engine/Renderer.hpp"
#include "Engine/Window.hpp"

#include <glad/glad.h>

#include <iostream>

namespace Ember {

Renderer::Renderer(Window& window)
    : m_window(window)
    , m_shader("shaders/basic.vert", "shaders/basic.frag")
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glViewport(0, 0, window.width(), window.height());

    const char* vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
    const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    std::cout << "GL vendor   : " << (vendor ? vendor : "?") << '\n';
    std::cout << "GL renderer : " << (renderer ? renderer : "?") << '\n';
    std::cout << "GL version  : " << (version ? version : "?") << '\n';
}

void Renderer::beginFrame()
{
    glViewport(0, 0, m_window.width(), m_window.height());
    glClearColor(0.07f, 0.08f, 0.10f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_camera.setPerspective(60.0f, m_window.aspect(), 0.1f, 100.0f);
    m_shader.bind();
    m_shader.setMat4("uViewProj", m_camera.viewProjection());
}

void Renderer::draw(const Mesh& mesh, const glm::mat4& model)
{
    m_shader.setMat4("uModel", model);
    mesh.draw();
}

void Renderer::endFrame()
{
    m_window.swapBuffers();
}

} // namespace Ember
