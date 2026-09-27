#include "Engine/Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Ember {

void Camera::setPerspective(float fovDegrees, float aspect, float zNear, float zFar)
{
    m_proj = glm::perspective(glm::radians(fovDegrees), aspect, zNear, zFar);
}

void Camera::lookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up)
{
    m_view = glm::lookAt(eye, target, up);
}

} // namespace Ember
