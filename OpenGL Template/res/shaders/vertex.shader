#version 460 core

layout (location = 0) in vec3 i_pos;
layout (location = 1) in vec2 i_tex_coords;
uniform mat4 u_Project_View_Model_Matrix;

out vec2 texCoord;

void main() {
	gl_Position = u_Project_View_Model_Matrix * vec4(i_pos, 1.0);
	texCoord = i_tex_coords;
}