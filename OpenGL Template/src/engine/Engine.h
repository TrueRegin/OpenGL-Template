#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <functional>

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include "Config.h"

enum { PROJ_GLFW_LOAD_ERROR = -1, PROJ_NO_WINDOW_ERROR = -2, PROJ_GLAD_LOAD_ERROR = -3 };

int init(int width, int height, const char* title, GLFWwindow*& window);
void programLoop(GLFWwindow* window, std::function<void()> const& loop);