#pragma once

#include <glm/glm.hpp>

namespace Ember {

class Camera {
public:
    Camera();

    void setPerspective(float fovDegrees, float aspect, float zNear, float zFar);

    void setPose(const glm::vec3& eye, float yawDegrees, float pitchDegrees);
    void reset();

    void addYawPitch(float yawDegrees, float pitchDegrees);
    void moveLocal(const glm::vec3& localDelta);

    void updateView();

    const glm::vec3& position() const { return m_position; }
    const glm::mat4& view() const { return m_view; }
    const glm::mat4& projection() const { return m_proj; }
    glm::mat4 viewProjection() const { return m_proj * m_view; }

    glm::vec3 forward() const;
    glm::vec3 right() const;
    glm::vec3 up() const { return {0.0f, 1.0f, 0.0f}; }

private:
    void clampPitch();

    glm::vec3 m_position{2.4f, 1.6f, 2.8f};
    float m_yaw = -132.0f;
    float m_pitch = -22.0f;

    glm::vec3 m_defaultPosition{2.4f, 1.6f, 2.8f};
    float m_defaultYaw = -132.0f;
    float m_defaultPitch = -22.0f;

    glm::mat4 m_view{1.0f};
    glm::mat4 m_proj{1.0f};
};

} // namespace Ember
