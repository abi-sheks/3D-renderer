#pragma once

#include <glm/glm.hpp>
#include "Model.h"
#include "Shader.h"

class Object
{
public:
    Object(const Model* model, glm::vec3 position = {}, glm::vec3 rotation = {}, glm::vec3 scale = glm::vec3(1.0f));
    void draw(Shader& shader, glm::vec3 color);
    glm::mat4 getTransformationMatrix();
    const Model* model;
    glm::vec3 position, rotation, scale;
private:
};