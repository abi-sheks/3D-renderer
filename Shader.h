#pragma once
#include <glm/glm.hpp>
#include <string>

class Shader
{
public:
    Shader(const std::string vertexCode, const std::string fragmentCode);
    void use() const;
    void setValue(const std::string& name, glm::vec3 values);
    void setValue(const std::string& name, glm::mat4 value);

private:
    uint32_t program_id;
};