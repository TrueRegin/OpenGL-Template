#include "Config.h"
#include "Engine.h"
#include "ShaderManager.h"
#include <glm\glm.hpp>
#include <glm\matrix.hpp>

int x = 0;
int y = 0;
int sVel = 0;
int fVel = 0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_W) {
			fVel = c().SPEED;
		}
		if (key == GLFW_KEY_S) {
			fVel = -c().SPEED;
		}

		if (key == GLFW_KEY_D) {
			sVel = c().SPEED;
		}
		if (key == GLFW_KEY_A) {
			sVel = -c().SPEED;
		}
	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_W && fVel > 0) {
			fVel = 0;
		}
		if (key == GLFW_KEY_S && fVel < 0) {
			fVel = 0;
		}

		if (key == GLFW_KEY_D && sVel > 0) {
			sVel = 0;
		}
		if (key == GLFW_KEY_A && sVel < 0) {
			sVel = 0;
		}
	}

}

int main() {
	GLFWwindow* window;
	init(c().WIDTH, c().HEIGHT, c().TITLE, window);
	if ((int)window < 0) return -1;

	{
		// Setting up the shader
		ShaderProgram shader("res/shaders/vertex.shader", "res/shaders/fragment.shader");
		shader.Bind();
		glm::mat4 projMat = glm::ortho(0.f, 640.f, 0.f, 480.f, -1.f, 1.f);
		glm::mat4 modelMat = glm::mat4(1.0f);
		modelMat = glm::translate(modelMat, glm::vec3(200.f, 100.f, 0.0f));
		shader.setUniformMat4("u_ProjMat", projMat);
		shader.setUniformMat4("u_ModelMat", modelMat);

		// Creating the gray "player" square
		const float vertices[] = {
			0.0f, 0.0f, 0.0f,
			100.0f, 0.0f, 0.0f,
			100.0f, 100.0f, 0.0f,
			100.0f, 100.0f, 0.0f,
			0.0f, 100.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
		};

		unsigned int vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		unsigned int vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
		glEnableVertexAttribArray(0);

		// Getting the ImGUI IO
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setting Callbacks
		glfwSetKeyCallback(window, key_callback);

		// Main program loop
		programLoop(window, [&shader, &modelMat]() {
			glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (3 * sizeof(float)));
			x += sVel;
			y += fVel;

			modelMat = glm::translate(glm::mat4(1.0f), glm::vec3((float) x, (float) y, 0.0f));
			shader.setUniformMat4("u_ModelMat", modelMat);

			ImGui::Begin("Default Window");
			ImGui::Text("You can edit this window in Main.cpp in the program loop, try experimenting with ImGUI");
			ImGui::End();
		});

		shader.Unbind();
	}

	glfwTerminate();
}