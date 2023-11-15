#include "Input.h"
#include "Camera.h"
#include <SFML/Window.hpp>

Input::Input(float sensitivity, float speed)
    : sensitivity(sensitivity), speed(speed)
{
}

void Input::handleKeyboard(Camera &camera, float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        camera.setPosition(camera.getPosition() + (camera.getForward() * speed * deltaTime));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        camera.setPosition(camera.getPosition() - (camera.getRight() * speed * deltaTime));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        camera.setPosition(camera.getPosition() - (camera.getForward() * speed * deltaTime));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        camera.setPosition(camera.getPosition() + (camera.getRight() * speed * deltaTime));
    }
}
void Input::handleMouse(Camera &camera, sf::Window &window, float deltaTime, bool isFirstMouse, sf::Vector2i lastMousePosition)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (isFirstMouse)
        {
            lastMousePosition = sf::Mouse::getPosition(window);
            isFirstMouse = false;
            window.setMouseCursorVisible(false);
        }
        else
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            int xOffset = mousePos.x - lastMousePosition.x;
            int yOffset = lastMousePosition.y - mousePos.y;
            sf::Mouse::setPosition(lastMousePosition, window);

            camera.setYaw(camera.getYaw() + xOffset * sensitivity * deltaTime);
            camera.setPitch(camera.getPitch() + yOffset * sensitivity * deltaTime);
        }
    }
    else
    {
        isFirstMouse = true;
        window.setMouseCursorVisible(true);
    }
}
