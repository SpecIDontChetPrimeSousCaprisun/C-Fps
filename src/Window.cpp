#include <iostream>

#include "Window.hpp"

GLFWwindow* Window::window = nullptr;
int Window::width = 1600;
int Window::height = 1200;
double Window::dt = 0;
double Window::lastFrame = 0;
Node* Window::parent = new Node();
Camera Window::camera;
DirLight Window::dirLight;

void Window::frameBufferSizeCallback(GLFWwindow*, int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
    glViewport(0, 0, width, height);
} 

int Window::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    window = glfwCreateWindow(width, height, "3dgame", NULL, NULL);
    if (window == NULL) {
	std::cout << "Failed to create GLFW window" << std::endl;
	glfwTerminate();
	return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	std::cout << "Failed to initialize GLAD" << std::endl;
	return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_FRAMEBUFFER_SRGB);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    dirLight.position = glm::vec3(-2.0f, -1.0f, -1.0f);
    dirLight.ambient = glm::vec3(0.274509804f);
    dirLight.diffuse = glm::vec3(0.588235294f, 0.588235294f, 0.392156863f);
    dirLight.specular = glm::vec3(1.0f, 1.0f, 1.0f);

    return 0;
}

void Window::mainLoop() {
    while(!glfwWindowShouldClose(window)) {
	glfwPollEvents();    

	double currentFrame = glfwGetTime();
	dt = currentFrame - lastFrame;
	lastFrame = currentFrame;

	if (dt > 0.1) {
	    dt = 0.1;
	}

	glClearColor(0.0f, 0.717647059f, 0.921568627f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera.update();
	parent->updateChildren();
	parent->drawChildren();

	glfwSwapBuffers(window);
    }
}
