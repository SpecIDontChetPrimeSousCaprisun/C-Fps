#pragma once

#include "Node.hpp"
#include "Vertex.hpp"
#include "Shader.hpp"
#include "Material.hpp"

class Mesh : Node {
public:
    Mesh(Node* parent, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::string texPath);

    static void init();

    static Shader* shader;
protected:
    void update() override;
    void draw() override;
private:
    void sendMatrix();

    std::vector<unsigned int> indices;
    std::vector<Vertex> vertices;
    Material material;
    unsigned int VAO, VBO, EBO;
};
