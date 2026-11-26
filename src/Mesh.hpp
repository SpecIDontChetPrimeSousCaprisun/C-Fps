#pragma once

#include "Node.hpp"
#include "Vertex.hpp"
#include "Shader.hpp"

class Mesh : Node {
public:
    Mesh(Node* parent, std::vector<Vertex> vertices, std::vector<unsigned int> indices);

    static void init();

    static Shader* shader;
protected:
    void update() override;
    void draw() override;
private:
    void sendMatrix();

    std::vector<unsigned int> indices;
    std::vector<Vertex> vertices;
    unsigned int VAO, VBO, EBO;
};
