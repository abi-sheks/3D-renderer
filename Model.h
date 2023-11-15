#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include "Mesh.h"
#include "Shader.h"

class Model
{
    public:
    Model(const std::string& fileName);
    void draw(Shader& shader, glm::mat4 transformation) const;

    private:
    void processNode(aiNode* node, const aiScene* scene, glm::mat4 transformation);
    Mesh processMesh(aiMesh* mesh);
    std::vector<Mesh> meshes;
};