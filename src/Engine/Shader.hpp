#pragma once

#include <glm/glm.hpp>
#include <string>
#include <string_view>

namespace Ember {

class Shader {
public:
    Shader() = default;
    Shader(std::string_view vertexPath, std::string_view fragmentPath);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    void bind() const;
    void setMat4(const char* name, const glm::mat4& value) const;
    unsigned int id() const { return m_id; }

private:
    static unsigned int compile(unsigned int type, const std::string& source, const std::string& label);

    unsigned int m_id = 0;
};

} // namespace Ember
