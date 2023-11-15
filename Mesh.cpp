#include "Mesh.h"
#include <GL/glew.h>

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<uint32_t> indices) 
:vertices(vertices), indices(indices), vao(), vbo(), ebo()
{
    glGenBuffers(1, &ebo);
    glGenBuffers(1, &vbo);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //need size in bytes, not number of elements in vec3 array. .data() as we need cstyle arrays.
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        //need size in bytes, not number of elements in vec3 array

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0,
     3, //as we have a vector3 for vertices
      GL_FLOAT,
      GL_FALSE,
      3*(sizeof(float)), //the step to reach next vector in array (as we have vec3)
      nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::draw() const {
        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}