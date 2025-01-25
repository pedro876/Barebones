#include "GL.h"

GL::GL()
{
	glfwInit();

	// Require OpenGL 3.3:
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Explicitly use the core-profile (no backwards compatible features required)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Mac Initialization:
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// CREATE WINDOW:
	window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		throw std::runtime_error("Failed to create GLFW window");
	}
	glfwMakeContextCurrent(window);

	// GLAD: LOAD ALL OPENGL FUNCTION POINTERS
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("Failed to initialize GLAD");
	}
}

GL::~GL()
{
	glfwTerminate();
}

bool GL::WindowShouldClose()
{
	return glfwWindowShouldClose(window);
}

void GL::BeginFrame()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GL::EndFrame()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}