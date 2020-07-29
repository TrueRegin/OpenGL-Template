#pragma once
// Position, Velocity, Acceleration, Rotation
// NOTE: Move to the Player class later
int x = 0;
int y = 0;
int sVel = 0;
int fVel = 0;

float rot = 0.0f;

// Width
int display_w = 0, display_h = 0;
int new_display_w = 0, new_display_h = 0;

// Square Vertex Data
const float vertices[] = {
	0.0f, 0.0f, 0.0f,
	100.0f, 0.0f, 0.0f,
	100.0f, 100.0f, 0.0f,
	100.0f, 100.0f, 0.0f,
	0.0f, 100.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
};
float texCoords[] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f
};

// Input Callback Functions
namespace Input {
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	//void mouse_button_callback();
	//void mouse_position_callback();
	//void mouse_scroll_callback();

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (action == GLFW_PRESS) {
			if (key == GLFW_KEY_W) { fVel = c().SPEED; }
			if (key == GLFW_KEY_S) { fVel = -c().SPEED; }

			if (key == GLFW_KEY_D) { sVel = c().SPEED; }
			if (key == GLFW_KEY_A) { sVel = -c().SPEED; }
		}
		if (action == GLFW_RELEASE) {
			if (key == GLFW_KEY_W && fVel > 0) { fVel = 0; }
			if (key == GLFW_KEY_S && fVel < 0) { fVel = 0; }

			if (key == GLFW_KEY_D && sVel > 0) { sVel = 0; }
			if (key == GLFW_KEY_A && sVel < 0) { sVel = 0; }
		}
	}
};


//void mouse_button_callback();
