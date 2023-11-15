#include <iostream>
#include <SFML/Window.hpp>
#include <GL/glew.h>

#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"

const float SPEED = 6.0f;
const float SENSITIVITY = 5.0f;

int main()
{
    sf::Window window(sf::VideoMode(800, 800), "OpenGL hello world");

    // raw GLSL vertex and fragment shaders.
    const char *vertexShaderCode = "#version 330 core\n"
                                   "layout (location = 0) in vec3 pos;\n"
                                   "uniform mat4 projection;\n"
                                   "uniform mat4 view;\n"
                                   "void main() { gl_Position = projection*view*vec4(pos, 1.0);}\n";

    const char *fragmentShaderCode = "#version 330 core\n"
                                     "out vec4 FragColor;\n"
                                     "uniform vec3 color;\n"
                                     "void main() { FragColor = vec4(color, 1.0); }\n";

    // initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize glew\n";
        return -1;
    }
    Shader shader(vertexShaderCode, fragmentShaderCode);
    // creating mesh
    Mesh mesh({
                  glm::vec3(0.8f, 0.8f, 0.0f),
                  glm::vec3(0.8f, -0.8f, 0.0f),
                  glm::vec3(-0.8f, -0.8f, 0.0f),
                  glm::vec3(-0.8f, 0.8f, 0.0f),
              },
              {0, 1, 3, 1, 2, 3});

    Camera camera(glm::vec3(0.0f, 0.0f, 2.0f));

    uint32_t vao{}, vbo{}, ebo{};
    // gluint expects an unsigned int. for some reason uint32_t works, size_t doesnt.

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    bool isFirstMouse = true;
    sf::Vector2i lastMousePosition{};

    sf::Clock clock{};
    while (window.isOpen())
    {

        float deltaTime = clock.restart().asSeconds();
        sf::Event event{};

        // event loop
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::Resized)
            {
                glViewport(0, 0, window.getSize().x, window.getSize().y);
            }
        }

        // before rendering
        camera.updateDirectionVectors();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            camera.setPosition(camera.getPosition() + (camera.getForward() * SPEED * deltaTime));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            camera.setPosition(camera.getPosition() - (camera.getRight() * SPEED * deltaTime));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            camera.setPosition(camera.getPosition() - (camera.getForward() * SPEED * deltaTime));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            camera.setPosition(camera.getPosition() + (camera.getRight() * SPEED * deltaTime));
        }


        // isFirstMouse gymnastics basically ensure that you can hold down mouse right and drag around to look
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

                 camera.setYaw(camera.getYaw() + xOffset*SENSITIVITY*deltaTime);
                 camera.setPitch(camera.getPitch() + yOffset*SENSITIVITY*deltaTime);
            }
        }
        else
        {
            isFirstMouse = true;
            window.setMouseCursorVisible(true);
        }

        glClear(GL_COLOR_BUFFER_BIT);

        // rendering portion
        shader.use();
        shader.setValue("projection", camera.getProjectionMatrix(window.getSize().x, window.getSize().y));
        shader.setValue("view", camera.getViewMatrix());
        shader.setValue("color", glm::vec3(1.0f, 0.5f, 0.5f));
        mesh.draw();
        window.display();
    }
    return 0;
}