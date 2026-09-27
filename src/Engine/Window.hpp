#pragma once

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
    void pollEvents() const;
    void swapBuffers() const;
    void requestClose();

    int width() const { return m_width; }
    int height() const { return m_height; }
    float aspect() const;

    GLFWwindow* handle() const { return m_window; }

    bool keyDown(int glfwKey) const;

private:
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    GLFWwindow* m_window = nullptr;
    int m_width = 0;
    int m_height = 0;
};

} // namespace Ember
