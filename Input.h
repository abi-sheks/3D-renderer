#pragma once
#include "Camera.h"
#include <SFML/Window.hpp>

class Input
{
public:
    Input(float sensitivity, float speed);
    void handleKeyboard(Camera &camera, float deltaTime);
    void handleMouse(Camera &camera, sf::Window &window, float deltaTime, bool isFirstMouse, sf::Vector2i lastMousePosition);

private:
    float sensitivity;
    float speed;
};