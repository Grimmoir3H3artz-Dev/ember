#pragma once

#include <glm/glm.hpp>
#include <string>

struct GLFWwindow;

namespace Ember {

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool shouldClose() const;
    void pollEvents();
    void swapBuffers() const;
    void requestClose();

    int width() const { return m_width; }
    int height() const { return m_height; }
    float aspect() const;

    GLFWwindow* handle() const { return m_window; }

    bool keyDown(int glfwKey) const;
    bool mouseDown(int glfwButton) const;
    glm::vec2 consumeCursorDelta();
    float consumeScrollY();
    bool looking() const { return m_looking; }

private:
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
    static void cursorPosCallback(GLFWwindow* window, double x, double y);
    static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

    GLFWwindow* m_window = nullptr;
    int m_width = 0;
    int m_height = 0;

    bool m_looking = false;
    bool m_cursorPrimed = false;
    double m_lastX = 0.0;
    double m_lastY = 0.0;
    glm::vec2 m_cursorDelta{0.0f};
    float m_scrollY = 0.0f;
};

} // namespace Ember
