#include "Model.h"
#include "Mesh.h"
#include "Shader.h"

#include <string>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

Model::Model(const std::string &fileName)
{
    Assimp::Importer importer;
    // to get triangular faces only
    importer.ReadFile(fileName, aiProcess_Triangulate);
    const aiScene *scene = importer.GetScene();

    if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
    {
        std::cerr << "Failed to load file " << fileName << "\n";
        return;
    }

    processNode(scene->mRootNode, scene, glm::mat4(1.0f));
}

void Model::draw(Shader &shader, glm::mat4 transformation) const
{
    for (auto &mesh : meshes)
    {
        shader.setValue("model", mesh.transformation * transformation);
        mesh.draw();
    }
}

void Model::processNode(aiNode *node, const aiScene *scene, glm::mat4 parentTransformation)
{
    glm::mat4 transformation{};
    // terrifying hardcode to map assimp matrix to gl matrix. ripped off (obviously)

    transformation[0][0] = node->mTransformation.a1;
    transformation[1][0] = node->mTransformation.a2;
    transformation[2][0] = node->mTransformation.a3;
    transformation[3][0] = node->mTransformation.a4;
    transformation[0][1] = node->mTransformation.b1;
    transformation[1][1] = node->mTransformation.b2;
    transformation[2][1] = node->mTransformation.b3;
    transformation[3][1] = node->mTransformation.b4;
    transformation[0][2] = node->mTransformation.c1;
    transformation[1][2] = node->mTransformation.c2;
    transformation[2][2] = node->mTransformation.c3;
    transformation[3][2] = node->mTransformation.c4;
    transformation[0][3] = node->mTransformation.d1;
    transformation[1][3] = node->mTransformation.d2;
    transformation[2][3] = node->mTransformation.d3;
    transformation[3][3] = node->mTransformation.d4;

    transformation = parentTransformation * transformation;

    for (size_t i = 0; i < node->mNumChildren; i++)
    {
        Mesh mesh = processMesh(scene->mMeshes[i]);
        mesh.transformation = transformation;
        meshes.push_back(mesh);
    }
    for (size_t i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, transformation);
    }
}

Mesh Model::processMesh(aiMesh *mesh)
{
    std::vector<glm::vec3> vertices;
    std::vector<uint32_t> indices;
    for (size_t i = 0; i < mesh->mNumVertices; i++)
    {
        // aivec to glmvec :((((
        aiVector3D aivec = mesh->mVertices[i];
        vertices.push_back(glm::vec3(aivec.x, aivec.y, aivec.z));
    }
    for (size_t i = 0; i < mesh->mNumFaces; i++)
    {
        // aivec to glmvec :((((
        aiFace face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[i]);
        }
    }
    return Mesh(vertices, indices);
}
