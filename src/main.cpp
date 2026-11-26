#include "Window.hpp"
#include "Model.hpp"
#include "Mesh.hpp"

int main() {
    if (Window::init() != 0) return 1;
    Mesh::init();

    new Model("models/Gun.obj");

    Window::mainLoop();

    return 0;
}
