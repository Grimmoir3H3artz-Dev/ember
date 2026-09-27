#include "Engine/Window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

namespace Ember {

Window::Window(int width, int height, const std::string& title)
    : m_width(width)
    , m_height(height)
{
    if (!glfwInit()) {
        throw std::runtime_error("glfwInit failed");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window (need OpenGL 4.6 core)");
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);

    auto load = [](void* /*user*/, const char* name) -> void* {
        return reinterpret_cast<void*>(glfwGetProcAddress(name));
    };
    if (!gladLoadGLLoader(load, nullptr)) {
        throw std::runtime_error("Failed to load OpenGL functions");
    }

    glfwGetFramebufferSize(m_window, &m_width, &m_height);
}

Window::~Window()
{
    if (m_window) {
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(m_window) == GLFW_TRUE;
}

void Window::pollEvents() const
{
    glfwPollEvents();
}

void Window::swapBuffers() const
{
    glfwSwapBuffers(m_window);
}

void Window::requestClose()
{
    glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}

float Window::aspect() const
{
    return m_height == 0 ? 1.0f : static_cast<float>(m_width) / static_cast<float>(m_height);
}

bool Window::keyDown(int glfwKey) const
{
    return glfwGetKey(m_window, glfwKey) == GLFW_PRESS;
}

void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (!self) {
        return;
    }
    self->m_width = width;
    self->m_height = height;
    glViewport(0, 0, width, height);
}

} // namespace Ember
