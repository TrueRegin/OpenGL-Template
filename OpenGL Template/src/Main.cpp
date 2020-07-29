#include <glm\glm.hpp>
#include <glm\matrix.hpp>

#include "Config.h"
#include "Engine.h"
#include "ShaderManager.h"
#include "Globals.h"
#include "Texture2D.h"

int main() {
	GLFWwindow* window;
	init(c().WIDTH, c().HEIGHT, c().TITLE, window);
	if ((int)window < 0) return -1;

	{
		// Setting up the shader
		ShaderProgram DFT_SHADER("res/shaders/vertex.shader", "res/shaders/fragment.shader");
		Texture2D PLAYER_TEXTURE("res/images/sword.png");
		PLAYER_TEXTURE.Bind();
		DFT_SHADER.Bind();
		
		// Transforms for setting up the world view
		glm::mat4 modelMat = glm::mat4(1.0f);
		glm::mat4 viewMat = glm::mat4(1.0f);
		glm::mat4 projMat = glm::ortho(0.f, 640.f, 0.f, 480.f, -1.f, 1.f);
		glm::mat4 MVP_Mat = projMat * viewMat * modelMat;

		unsigned int vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		unsigned int vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
		glEnableVertexAttribArray(0);

		unsigned int tbo;
		glGenBuffers(1, &tbo);
		glBindBuffer(GL_ARRAY_BUFFER, tbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);


		// Getting the ImGUI IO
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setting Callbacks
		glfwSetKeyCallback(window, Input::key_callback);

		// Main program loop
		programLoop(window, [&DFT_SHADER, &PLAYER_TEXTURE, &window, &modelMat, &viewMat, &projMat, &MVP_Mat]() {
			
			// Player Code
			{
				x += sVel;
				y += fVel;
				modelMat = glm::translate(glm::mat4(1.0f), glm::vec3((float) x, (float) y, 0.0f));
				modelMat = glm::rotate(modelMat, glm::radians(rot), glm::vec3(0, 0, 1));
				MVP_Mat = projMat * viewMat * modelMat;
				DFT_SHADER.setUniform1i("tex", 0);
				DFT_SHADER.setUniformMat4("u_Project_View_Model_Matrix", MVP_Mat);

				// Drawing the Triangle
				glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (3 * sizeof(float)));
			}

			// ImGui Basic Menu
			ImGui::Begin("Default Window");
			ImGui::Text("You can edit this window in Main.cpp in the program loop, try experimenting with ImGUI");
			ImGui::End();

			// Key Stuff
			if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
				rot += 2.f;
			}
			if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
				rot -= 2.f;
			}

			// Window Resize Code
			glfwGetFramebufferSize(window, &new_display_w, &new_display_h);
			if (new_display_w != display_w || new_display_h != display_h) {
				display_w = new_display_w;
				display_h = new_display_h;
				glViewport(0, 0, display_w, display_h);
				projMat = glm::ortho(-display_w / 2.f, display_w / 2.f, -display_h / 2.f, display_h / 2.f, -1.f, 1.f);
			}
		});

		DFT_SHADER.Unbind();
		PLAYER_TEXTURE.Unbind();
	}

	glfwTerminate();
}