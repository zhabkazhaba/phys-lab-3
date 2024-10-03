#include "window.h"

int main() {
    Window* window_ptr;
    window_ptr = Window::initializeWindow();
    window_ptr->runWindow();
    return 0;
}
