#pragma once

struct GLFWwindow;

namespace Ember {

class Ui {
public:
    explicit Ui(GLFWwindow* window);
    ~Ui();

    Ui(const Ui&) = delete;
    Ui& operator=(const Ui&) = delete;

    void beginFrame();
    void endFrame();

private:
    bool m_ready = false;
};

} // namespace Ember
