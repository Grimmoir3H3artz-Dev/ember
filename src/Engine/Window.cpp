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
    glfwSetCursorPosCallback(m_window, cursorPosCallback);
    glfwSetScrollCallback(m_window, scrollCallback);

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

void Window::pollEvents()
{
    glfwPollEvents();

    const bool wantLook = mouseDown(GLFW_MOUSE_BUTTON_RIGHT);
    if (wantLook && !m_looking) {
        m_looking = true;
        m_cursorPrimed = false;
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else if (!wantLook && m_looking) {
        m_looking = false;
        m_cursorPrimed = false;
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
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

bool Window::mouseDown(int glfwButton) const
{
    return glfwGetMouseButton(m_window, glfwButton) == GLFW_PRESS;
}

glm::vec2 Window::consumeCursorDelta()
{
    const glm::vec2 d = m_looking ? m_cursorDelta : glm::vec2(0.0f);
    m_cursorDelta = {0.0f, 0.0f};
    return d;
}

float Window::consumeScrollY()
{
    const float y = m_scrollY;
    m_scrollY = 0.0f;
    return y;
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

void Window::cursorPosCallback(GLFWwindow* window, double x, double y)
{
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (!self || !self->m_looking) {
        return;
    }
    if (!self->m_cursorPrimed) {
        self->m_lastX = x;
        self->m_lastY = y;
        self->m_cursorPrimed = true;
        return;
    }
    self->m_cursorDelta.x += static_cast<float>(x - self->m_lastX);
    self->m_cursorDelta.y += static_cast<float>(y - self->m_lastY);
    self->m_lastX = x;
    self->m_lastY = y;
}

void Window::scrollCallback(GLFWwindow* window, double /*xOffset*/, double yOffset)
{
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (!self) {
        return;
    }
    self->m_scrollY += static_cast<float>(yOffset);
}

} // namespace Ember
