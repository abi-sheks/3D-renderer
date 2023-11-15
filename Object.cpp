#include "Object.h"
#include "Model.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

Object::Object(const Model* model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : model(model), position(position), rotation(rotation), scale(scale)
{

}

void Object::draw(Shader& shader, glm::vec3 color) {
    shader.setValue("color", color);
    model->draw(shader, getTransformationMatrix());
}


glm::mat4 Object::getTransformationMatrix(){
    glm::mat4 tMatrix = glm::mat4(1.0f);

    //transformation calculation (order - scale, rotate, translate. (right to left matrix multiplication so bottom to top))
    tMatrix = glm::translate(tMatrix, position);
    //euler angle -> quaternion -> matrix
    tMatrix = tMatrix*glm::mat4_cast(glm::quat(glm::radians(rotation)));
    tMatrix = glm::scale(tMatrix, scale);

    return tMatrix;
}