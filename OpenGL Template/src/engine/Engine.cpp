#include "Engine.h"

/**

@param width Width of the created window
@param height Height of the created window
@param title Title of the window

@returns new GLFWwindow* as an int or a negative integer corresponding to an error with the render
	Possible error return values:
		PROJ_GLFW_LOAD_ERROR
		PROJ_NO_WINDOW_ERROR
		PROJ_GLAD_LOAD_ERROR
*/
int init(int width, int height, const char* title) {
    GLFWwindow* window;

	if (!glfwInit()) return PROJ_GLFW_LOAD_ERROR;
	window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        return PROJ_NO_WINDOW_ERROR;
    }

    glfwWindowHint(GLFW_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "ERROR: Failed to initialize OpenGL context" << std::endl;
        return PROJ_GLAD_LOAD_ERROR;
    }
    printf("OpenGL Version %d.%d loaded\n", GLVersion.major, GLVersion.minor);

	return (int) window;
}

void programLoop(GLFWwindow* window, std::function<void()> const& loop) {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(c().BG_COLOR.r, c().BG_COLOR.g, c().BG_COLOR.b, 1.0f);
        loop();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}