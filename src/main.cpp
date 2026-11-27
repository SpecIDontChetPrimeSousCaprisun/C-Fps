#include "Window.hpp"
#include "Model.hpp"
#include "Mesh.hpp"

int main() {
    if (Window::init() != 0) return 1;
    Mesh::init();

    Model* gun = new Model("models/Gun.obj");
    gun->setParent(Window::camera);
    gun->position.z = 50.0f;

    Window::mainLoop();

    return 0;
}
