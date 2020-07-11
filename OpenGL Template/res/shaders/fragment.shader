#version 460 core

layout (location = 0) out vec4 color;

void main() {
	/* Sets the background color to gray with an alpha of 1.0f */
	color = vec4(0.5, 0.5, 0.5, 1.0);
}