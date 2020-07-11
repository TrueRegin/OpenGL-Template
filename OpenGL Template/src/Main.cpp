#include "Config.h"
#include "Engine.h"
#include "ShaderManager.h"
#include <glm\glm.hpp>
#include <glm\matrix.hpp>

int x = 0;
int y = 0;
int velX = 0;
int velY = 0;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_D) {
		velX = c().SPEED;
	}
	if (key == GLFW_KEY_A) {
		velX = -c().SPEED;
	}

	if (key == GLFW_KEY_W) {
		velY = c().SPEED;
	}
	if (key == GLFW_KEY_S) {
		velY = -c().SPEED;
	}

	//if (action == GLFW_RELEASE) {
	//	printf("Key Release!");
	//	if (key == GLFW_KEY_W && velY > 0) {
	//		velY = 0;
	//	}
	//	else if (key == GLFW_KEY_S && velY < 0) {
	//		velY = 0;
	//	}

	//	if (key == GLFW_KEY_D && velX > 0) {
	//		velX = 0;
	//	}
	//	else if (key == GLFW_KEY_A && velX < 0) {
	//		velX = 0;
	//	}
	//}
}

int main() {
	GLFWwindow* window = (GLFWwindow*) init(c().WIDTH, c().HEIGHT, c().TITLE);
	switch ((int)window)
	{
	case PROJ_NO_WINDOW_ERROR:
		std::cout << "GLFW window was not properly created during loadup, terminating!" << std::endl;
		return -1;
	case PROJ_GLFW_LOAD_ERROR:
		std::cout << "GLFW load error, terminating!" << std::endl;
		return -1;
	case PROJ_GLAD_LOAD_ERROR:
		std::cout << "GLAD load error, terminating" << std::endl;
		return -1;
	}

	{
		ShaderProgram shader("res/shaders/vertex.shader", "res/shaders/fragment.shader");
		shader.Bind();
		glm::mat4 projMat = glm::ortho(0.f, 640.f, 0.f, 480.f, -1.f, 1.f);
		glm::mat4 modelMat = glm::mat4(1.0f);
		modelMat = glm::translate(modelMat, glm::vec3(200.f, 100.f, 0.0f));
		shader.setUniformMat4fv("u_ProjMat", projMat);
		shader.setUniformMat4fv("u_ModelMat", modelMat);

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

		glfwSetKeyCallback(window, keyCallback);
		programLoop(window, [&shader, &modelMat]() {
			glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (3 * sizeof(float)));
			x += velX;
			y += velY;
			modelMat = glm::translate(glm::mat4(1.0f), glm::vec3((float) x, (float) y, 0.0f));
			shader.setUniformMat4fv("u_ModelMat", modelMat);
		});

		shader.Unbind();
	}

	glfwTerminate();
}