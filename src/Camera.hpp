#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include "Node.hpp"

class Camera : public Node {
public:
    Camera();

    glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 right = glm::vec3(-1.0f, 0.0f, 0.0f);
    glm::vec2 lastMouse = glm::vec2(0.0f, 0.0f);
    float speed = 10.0f;
    bool firstMouse = true;
    std::string mode = "free";

protected:
    void update() override;
};
