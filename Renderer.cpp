#include <iostream>
#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <fstream>
#include <sstream>

#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Object.h"
#include "Model.h"
#include "Input.h"


//Put your model file here
const std::string modelFile = "YOUR_NAME.fbx";
const float SPEED = 6.0f;
const float SENSITIVITY = 5.0f;

std::string readTextFile(const std::string &fileName);
int main()
{
    sf::Window window(sf::VideoMode(800, 800), "OpenGL hello world");
    // initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize glew\n";
        return -1;
    }
    Shader shader(readTextFile("vertex.glsl"), readTextFile("fragment.glsl"));

    // you should be loading your models through a file by replacing YOUR_SCENE on line 16 with the fbx file.
    Model model(modelFile);

    Camera camera(glm::vec3(0.0f, 0.0f, 2.0f));
    Input input(SENSITIVITY, SPEED);
    Object object(&model);
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
        input.handleKeyboard(camera, deltaTime);
        input.handleMouse(camera, window, deltaTime, isFirstMouse, lastMousePosition);

        // isFirstMouse gymnastics basically ensure that you can hold down mouse right and drag around to look

        glClear(GL_COLOR_BUFFER_BIT);

        // rendering portion
        shader.use();
        shader.setValue("projection", camera.getProjectionMatrix((float)window.getSize().x, (float)window.getSize().y));
        shader.setValue("view", camera.getViewMatrix());
        shader.setValue("color", glm::vec3(1.0f, 0.5f, 0.5f));
        object.draw(shader, glm::vec3(1.0f, 1.0f, 0.5f));
        window.display();
    }
    return 0;
}

std::string readTextFile(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "Failed to read file properly";
        return "";
    }

    std::stringstream ss{};
    ss << file.rdbuf();
    file.close();

    return ss.str();
}