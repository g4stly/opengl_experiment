#include <cstdlib>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "application.h"
#include "util.h"

static const char *const app_create_win = "Application::create_window(): %s\n";
static const char *const create_win_fail = "failed to create window";
static const char *const glad_init_fail = "failed to initialize glad";


static void terminate_glfw(int status, void *usr_data)
{
	glfwTerminate();
}

static void glfw_error_callback(int status, const char *message)
{
	std::cerr << "GLFW(" << status << "): " << message << std::endl;
}

static void resize_callback(GLFWwindow *w, int width, int height)
{
	glViewport(0, 0, width, height);
}

Application::Application()
{
}

Application::~Application()
{
}

Application *Application::init(int arg, char **argv)
{
	glfwInit();
	on_exit(terminate_glfw, NULL);
	glfwSetErrorCallback(glfw_error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	return this;
}

Application *Application::set_title(const char *title)
{
	this->title = title;
	return this;
}

Application *Application::create_window(int w, int h)
{
	if (!(window = glfwCreateWindow(w, h, title, NULL, NULL))) {
		die(app_create_win, create_win_fail);
	}

	glfwSetFramebufferSizeCallback(window, resize_callback);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		die(app_create_win, glad_init_fail);
	}

	load();
	
	return this;
}

int Application::execute()
{
	while (!glfwWindowShouldClose(window)) {
		update();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	free();
	return 0;
}
