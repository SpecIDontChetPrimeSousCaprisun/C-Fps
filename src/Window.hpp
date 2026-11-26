#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Node.hpp"
#include "Camera.hpp"

class Window {
public:
    static int init();
    static void mainLoop();

    static GLFWwindow* window;
    static double dt;
    static double lastFrame;
    static int height;
    static int width;
    static Node* parent;
    static Camera camera;
private:
    static void frameBufferSizeCallback(GLFWwindow*, int newWidth, int newHeight);
};
