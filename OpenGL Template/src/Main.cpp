#include "Config.h"
#include "Engine.h"
#include "ShaderManager.h"


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

		const float vertices[] = {
			0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
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

		programLoop(window, []() {
			glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (3 * sizeof(float)));
		});

		shader.Unbind();
	}

	glfwTerminate();
}