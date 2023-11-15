#pragma once

#include <vector>
#include <glm/glm.hpp>

class Mesh {
    public:
        Mesh(std::vector<glm::vec3> vertices, std::vector<uint32_t> indices);
        void draw() const;

        //so that Object can apply this local transformation as well as Models transformation
        glm::mat4 transformation;
    private:
        std::vector<glm::vec3> vertices;
        std::vector<uint32_t> indices;
         
        uint32_t ebo, vao, vbo;
};