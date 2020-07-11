#version 460 core

layout (location = 0) in vec3 pos;
uniform mat4 u_ProjMat;
uniform mat4 u_ModelMat;
//uniform mat4 u_ViewMat;

void main() {
	gl_Position = u_ProjMat * u_ModelMat * vec4(pos, 1.0);
}