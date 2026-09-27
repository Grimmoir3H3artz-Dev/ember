#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Ember {

struct Transform {
    glm::vec3 position{0.0f};
    glm::vec3 rotationDeg{0.0f};
    glm::vec3 scale{1.0f};

    glm::mat4 matrix() const
    {
        glm::mat4 m{1.0f};
        m = glm::translate(m, position);
        m = glm::rotate(m, glm::radians(rotationDeg.y), {0.0f, 1.0f, 0.0f});
        m = glm::rotate(m, glm::radians(rotationDeg.x), {1.0f, 0.0f, 0.0f});
        m = glm::rotate(m, glm::radians(rotationDeg.z), {0.0f, 0.0f, 1.0f});
        m = glm::scale(m, scale);
        return m;
    }
};

} // namespace Ember
