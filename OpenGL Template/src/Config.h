#pragma once

#include <glm\vec3.hpp>
#include <unordered_map>

struct Config {
	const int WIDTH;
	const int HEIGHT;
	const char* TITLE;
	const char* VERTEX_START_STRING;
	const char* FRAGMENT_START_STRING;
	const glm::vec3 BG_COLOR;
	const float SPEED;

	Config()
	: 
		WIDTH(640),
		HEIGHT(480), 
		TITLE("OpenGL Template"), 
		VERTEX_START_STRING("$vertex"), 
		FRAGMENT_START_STRING("$fragment"), 
		BG_COLOR({1.0f, 0.3f, 0.5f}), 
		SPEED(5)
	{}
};

const Config& c();