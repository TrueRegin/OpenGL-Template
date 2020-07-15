#include "Engine.h"


void loadImGUI(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460 core");
}

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
int init(int width, int height, const char* title, GLFWwindow*& window) {
    // GLFW Init
    if (!glfwInit()) {
        std::cout << "GLFW load error, terminating!" << std::endl;
        return PROJ_GLFW_LOAD_ERROR;
    };
    // Creating the window
	window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cout << "GLFW window was not properly created during loadup, terminating!" << std::endl;
        return PROJ_NO_WINDOW_ERROR;
    }

    glfwWindowHint(GLFW_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwMakeContextCurrent(window);

    // Loading GLAD so we can access OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "ERROR: Failed to initialize OpenGL context" << std::endl;
        return PROJ_GLAD_LOAD_ERROR;
    }
    printf("OpenGL Version %d.%d loaded\n", GLVersion.major, GLVersion.minor);

    // Loading ImGUI so we can use its GUI system for debugging
    loadImGUI(window);

	return (int) window;
}

void programLoop(GLFWwindow* window, std::function<void()> const& loop) {
    while (!glfwWindowShouldClose(window)) {
        glClearColor(c().BG_COLOR.r, c().BG_COLOR.g, c().BG_COLOR.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        loop();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}