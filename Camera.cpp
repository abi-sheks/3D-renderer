#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

const glm::vec3 Camera::worldUp{0.0f, 1.0f, 0.0f};

Camera::Camera(glm::vec3 position, float yaw, float pitch, float fov)
    : position(position), yaw(yaw), pitch(pitch), fov(fov), forward(), right(), up()
{
}

glm::mat4 Camera::getProjectionMatrix(float width, float height)
{
    return glm::perspective(glm::radians(fov), width / height, 0.1f, 100.0f);
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, position + forward, up);
}

void Camera::updateDirectionVectors()
{
    forward =
        glm::normalize(
            glm::vec3(
                glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch)),
                glm::sin(glm::radians(pitch)),
                glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch))));
    right = glm::normalize(glm::cross(forward, worldUp));
    up = glm::normalize(glm::cross(right, forward));
}