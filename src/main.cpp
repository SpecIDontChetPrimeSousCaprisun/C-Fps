#include "Window.hpp"
#include "Model.hpp"

int main() {
    if (Window::init() != 0) return 1;

    new Model("models/Gun.obj");

    Window::mainLoop();

    return 0;
}
