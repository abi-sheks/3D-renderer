#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
    static const glm::vec3 worldUp;
    Camera(glm::vec3 position, float yaw = -90.0f, float pitch = 0.0f, float fov = 60.0f);

    glm::mat4 getProjectionMatrix(float width, float height);
    glm::mat4 getViewMatrix();
    void updateDirectionVectors();
    glm::vec3 getForward() {return forward;}
    glm::vec3 getUp() {return up;}
    glm::vec3 getRight() {return right;}
    glm::vec3 getPosition() {return position;}
    float getYaw() {return yaw;}
    float getPitch() {return pitch;}
    float getFov() {return fov;}
    void setYaw(float newYaw) {yaw = newYaw;}
    void setFov(float newFov) {fov = newFov;}
    void setPitch(float newPitch) {pitch = newPitch;}
    void setPosition(glm::vec3 newPosition) {position = newPosition;}
private:
    glm::vec3 position;
    glm::vec3 forward, up, right;
    float yaw, pitch, fov;
};