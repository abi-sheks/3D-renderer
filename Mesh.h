#pragma once

#include <vector>
#include <glm/glm.hpp>

class Mesh {
    public:
        Mesh(std::vector<glm::vec3> vertices, std::vector<uint32_t> indices);
        void draw() const;
    private:
        std::vector<glm::vec3> vertices;
        std::vector<uint32_t> indices;
         
        uint32_t ebo, vao, vbo;
};