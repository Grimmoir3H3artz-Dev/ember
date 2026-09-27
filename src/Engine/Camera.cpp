#include "Engine/Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <cmath>

namespace Ember {

namespace {
constexpr float kPitchLimit = 89.0f;
}

Camera::Camera()
{
    updateView();
}

void Camera::setPerspective(float fovDegrees, float aspect, float zNear, float zFar)
{
    m_proj = glm::perspective(glm::radians(fovDegrees), aspect, zNear, zFar);
}

void Camera::setPose(const glm::vec3& eye, float yawDegrees, float pitchDegrees)
{
    m_position = eye;
    m_yaw = yawDegrees;
    m_pitch = pitchDegrees;
    clampPitch();
    updateView();
}

void Camera::reset()
{
    setPose(m_defaultPosition, m_defaultYaw, m_defaultPitch);
}

void Camera::addYawPitch(float yawDegrees, float pitchDegrees)
{
    m_yaw += yawDegrees;
    m_pitch += pitchDegrees;
    clampPitch();
}

void Camera::moveLocal(const glm::vec3& localDelta)
{
    m_position += right() * localDelta.x;
    m_position += up() * localDelta.y;
    m_position += forward() * localDelta.z;
}

void Camera::updateView()
{
    m_view = glm::lookAt(m_position, m_position + forward(), up());
}

glm::vec3 Camera::forward() const
{
    const float yaw = glm::radians(m_yaw);
    const float pitch = glm::radians(m_pitch);
    const float cp = std::cos(pitch);
    return glm::normalize(glm::vec3{
        std::cos(yaw) * cp,
        std::sin(pitch),
        std::sin(yaw) * cp,
    });
}

glm::vec3 Camera::right() const
{
    return glm::normalize(glm::cross(forward(), up()));
}

void Camera::clampPitch()
{
    m_pitch = std::clamp(m_pitch, -kPitchLimit, kPitchLimit);
}

} // namespace Ember
