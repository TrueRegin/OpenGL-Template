#version 460 core

// Output Variables
layout (location = 0) out vec4 color;

// Input Variables from the Vertex Shader
in vec2 texCoord;

// Uniform Variables
uniform sampler2D tex;

void main() {
	vec4 texColor = texture(tex, texCoord);
	if (texColor.a == 0.0f) {
		discard;
	}

	/* Sets the background color of the "player" to a sword texture */
	color = texColor;
}