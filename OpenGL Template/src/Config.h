#pragma once

#include <glm\vec3.hpp>
#include <unordered_map>

struct Config {
	const int WIDTH;
	const int HEIGHT;
	const char* TITLE = "OpenGL Template";
	const char* VERTEX_START_STRING = "$vertex";
	const char* FRAGMENT_START_STRING = "$fragment";

	const glm::vec3 BG_COLOR = {1.0f, 0.3f, 0.2f};
};

Config& c();