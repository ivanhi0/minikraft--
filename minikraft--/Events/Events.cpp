// Capture keys 1

#include <string>
// OpenGL Enable
#define GLEW_STATIC
#include "../include/GLFW/glfw3.h"
#pragma comment(lib, "include/GLFW/glfw3.lib")
#pragma comment(lib, "include/GLFW/glfw3dll.lib")
#pragma comment(lib, "include/GLFW/glfw3_mt.lib")
#pragma comment(lib, "OpenGL32.lib")

#include "Events.h"

bool* Events::_keys;
unit* Events::_frames;
unit Events::_current = 0;
float Events::deltaX = 0.0f;
float Events::deltaY = 0.0f;
float Events::x = 0.0f;
float Events::y = 0.0f;
bool Events::_cursor_locked = false;
bool Events::_cursor_started = false;

#define _MOUSE_BUTTONS 1024

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	if (Events::_cursor_locked) {
		Events::deltaX += xpos - Events::x;
		Events::deltaX += xpos - Events::y;
	}
	else {
		Events::_cursor_started = true;
	}
	Events::x = xpos;
	Events::y = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) {
		Events::_keys[_MOUSE_BUTTONS + button] = true;
		Events::_frames[_MOUSE_BUTTONS + button] = Events::_current;
	}
	else if (action == GLFW_RELEASE) {
		Events::_keys[_MOUSE_BUTTONS + button] = false;
		Events::_frames[_MOUSE_BUTTONS + button] = Events::_current;
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {
		Events::_keys[key] = true;
		Events::_frames[key] = Events::_current;
	}
	else if (action == GLFW_RELEASE) {
		Events::_keys[key] = false;
		Events::_frames[key] = Events::_current;
	}
}

int Events::initialize() {
	GLFWwindow* window = Window::window;
	_keys = new bool[1032];
	_frames = new unit[1024];

	memset(_keys, false, 1032 * sizeof(bool));
	memset(_frames, 0, 1032 * sizeof(unit));

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	return 0;
}

bool Events::isPresed(int keycode) {
	if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
		return false;
	return _keys[keycode];
}

bool Events::justPressed(int keycode) {
	if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
		return false;
	return _keys[keycode] && _frames[keycode] == _current;
}

void Events::pullEvents() {
	_current++;
	deltaX = 0.0f;
	deltaY = 0.0f;
	glfwPollEvents();
}
