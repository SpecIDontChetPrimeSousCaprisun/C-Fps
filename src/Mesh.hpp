#pragma once

#include "Node.hpp"
#include "Vertex.hpp"

class Mesh : Node {
public:
    Mesh(Node* parent, std::vector<Vertex> vertices, std::vector<unsigned int> indices);
private:
    unsigned int VAO, VBO, EBO;
};
