#include <glad/glad.h>

#include "Mesh.hpp"
#include "Window.hpp"

Shader* Mesh::shader;

void Mesh::init() {
    Mesh::shader = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
}

Mesh::Mesh(
    Node* parent,
    std::vector<Vertex> vertices,
    std::vector<unsigned int> indices,
    std::string texPath
) : Node(parent), indices(indices), vertices(vertices) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
  
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), 
                 &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    glBindVertexArray(0);

    material.diffuse.gen(texPath);
    material.specular.gen(texPath);

    setParent(Window::parent);
}

void Mesh::update() {

}

void Mesh::draw() {
    glUseProgram(shader->program);    

    sendMatrix();

    shader->setMaterial("material", material);
    shader->setDirLight("dirLight", Window::dirLight);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::sendMatrix() {
    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 view = glm::lookAt(
	Window::camera.position,
	Window::camera.position + Window::camera.forward,
	glm::vec3(0.0f, 1.0f, 0.0f)
    );

    /*glm::vec3 worldRotation = getWorldRotation();

    model = glm::translate(model, getWorldPosition());
    model = glm::rotate(model, glm::radians(worldRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(worldRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(worldRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, size);*/

    glm::mat4 projection = glm::perspective(
	glm::radians(70.0f),
	(float)Window::width / (float)Window::height,
	0.1f,
	100.0f
    );

    shader->setMatrix("model", model);
    shader->setMatrix("view", view);
    shader->setMatrix("projection", projection);
}
