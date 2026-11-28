#include "Window.hpp"
#include "Model.hpp"
#include "Mesh.hpp"

int main() {
    if (Window::init() != 0) return 1;
    Mesh::init();

    Model* gun = new Model("models/Gun.obj");
    gun->setParent(Window::camera);
    gun->position.z = -5.0f;
    gun->position.x = 2.0f;
    gun->position.y = -1.0f;

    Window::mainLoop();

    return 0;
}
