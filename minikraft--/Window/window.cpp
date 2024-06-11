// Create window 1

#include <iostream>

// OpenGL Enable
#include "../include/GL/glew.h"
#include "../include/GLFW/glfw3.h"
#pragma comment(lib, "include/GL/glew32s.lib")
#pragma comment(lib, "include/GLFW/glfw3.lib")
#pragma comment(lib, "include/GLFW/glfw3dll.lib")
#pragma comment(lib, "include/GLFW/glfw3_mt.lib")
#pragma comment(lib, "OpenGL32.lib")

#include "Window.h"

using namespace std;

GLFWwindow* Window::window;
int Window::initialize(int width, int height, const char* title) {
    // Init window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Check window created
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr) {
        cerr << "F*** HOW Window not created\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // If GLEW inited?
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cerr << "GLEW not inited\n";
        return -1;
    }
    glViewport(0, 0, width, height);

    return 0;
}

bool Window::isShouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::setShouldClose(bool flag) {
    glfwSetWindowShouldClose(window, flag);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

void Window::terminate() {
    glfwTerminate();
}