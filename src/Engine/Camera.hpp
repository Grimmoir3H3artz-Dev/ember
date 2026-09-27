#pragma once

#include <glm/glm.hpp>

namespace Ember {

class Camera {
public:
    void setPerspective(float fovDegrees, float aspect, float zNear, float zFar);
    void lookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up);

    const glm::mat4& view() const { return m_view; }
    const glm::mat4& projection() const { return m_proj; }
    glm::mat4 viewProjection() const { return m_proj * m_view; }

private:
    glm::mat4 m_view{1.0f};
    glm::mat4 m_proj{1.0f};
};

} // namespace Ember
