#include "Camera.hpp"
#include "Window.hpp"

Camera::Camera() : Node() {
    rotation.y = -90.0f;
    position.z = 10.0f;
}

void Camera::update() {
    double xpos, ypos;
    glfwGetCursorPos(Window::window, &xpos, &ypos);

    if (firstMouse) {
	lastMouse = glm::vec2(xpos, ypos);
	firstMouse = false;
    }

    float xoffset = xpos - lastMouse.x;
    float yoffset = lastMouse.y - ypos;

    lastMouse = glm::vec2(xpos, ypos);

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    // yaw / pitch
    rotation.y += xoffset;
    rotation.x += yoffset;

    if (rotation.x > 89.0f) rotation.x = 89.0f;
    if (rotation.x < -89.0f) rotation.x = -89.0f;

    updateWorldCoordinates();
    glm::vec3 worldRot = getWorldRotation();    
    glm::vec3 dir;
    dir.x = cos(glm::radians(worldRot.y)) * cos(glm::radians(worldRot.x));
    dir.y = sin(glm::radians(worldRot.x));
    dir.z = sin(glm::radians(worldRot.y)) * cos(glm::radians(worldRot.x));

    forward = glm::normalize(dir);
    right = glm::normalize(glm::cross(glm::normalize(dir), glm::vec3(0.0f, 1.0f, 0.0f)));

    if (glfwGetKey(Window::window, GLFW_KEY_W) == GLFW_PRESS) {
	position += forward * (speed * (float)Window::dt);
    } else if (glfwGetKey(Window::window, GLFW_KEY_S) == GLFW_PRESS) {
	position -= forward * (speed * (float)Window::dt);
    }

    if (glfwGetKey(Window::window, GLFW_KEY_D) == GLFW_PRESS) {
	position += right * (speed * (float)Window::dt);
    } else if (glfwGetKey(Window::window, GLFW_KEY_A) == GLFW_PRESS) {
	position -= right * (speed * (float)Window::dt);
    }
}
