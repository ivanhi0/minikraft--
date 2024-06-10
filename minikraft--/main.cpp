// Idk why

#include <iostream>

// OpenGL Enable
#define GLEW_STATIC
#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#pragma comment(lib, "include/GL/glew32s.lib")
#pragma comment(lib, "include/GLFW/glfw3.lib")
#pragma comment(lib, "include/GLFW/glfw3dll.lib")
#pragma comment(lib, "include/GLFW/glfw3_mt.lib")
#pragma comment(lib, "OpenGL32.lib")

#include "Window/Window.h"
#include "Events/Events.h"

using namespace std;

int width = 854;
int height = 480;

int main()
{
    //setlocale(LC_ALL, "en");
    Window::initialize(width, height, "Test Windows");
    Events::initialize();

    while (!Window::isShouldClose()) {
        Events::pullEvents();
        if (Events::justPressed(GLFW_KEY_ESCAPE)) {
            Window::setShouldClose(true);
        }
        Window::swapBuffers();
    }
    Window::terminate();

    return 0;
}