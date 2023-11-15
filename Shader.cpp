#include "Shader.h"
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

Shader::Shader(const std::string vertexCode, const std::string fragmentCode)
{
    const char *vertexShaderCode = vertexCode.c_str();
    const char *fragmentShaderCode = fragmentCode.c_str();
    // map and compile vertex and fragment shaders and check OK.
    size_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShader);

    int success{};
    char infoLog[1024]{};
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 1024, nullptr, infoLog);
        std::cerr << "Failed to compile shader. \n  InfoLog: \n"
                  << infoLog << '\n';
    }

    size_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 1024, nullptr, infoLog);
        std::cerr << "Failed to compile shader. \n  InfoLog: \n"
                  << infoLog << '\n';
    }

    // create program and actually link shaders together to pipeline
    program_id = glCreateProgram();
    glAttachShader(program_id, vertexShader);
    glAttachShader(program_id, fragmentShader);
    glLinkProgram(program_id);

    glGetProgramiv(program_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program_id, 1024, nullptr, infoLog);
        std::cerr << "Failed to link shaders. \n  InfoLog: \n"
                  << infoLog << '\n';
    }

    // delete individual shaders now that they are linked.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() const
{
    glUseProgram(program_id);
}

void Shader::setValue(const std::string &name, glm::vec3(values))
{
    glUniform3f(glGetUniformLocation(program_id, name.c_str()), values.x, values.y, values.z);
}
void Shader::setValue(const std::string &name, glm::mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
