#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "application.h"
#include "shader_factory.h"
#include "texture.h"
#include "hello.h"
#include "cube.h"

class Toggle {
public:
	int key;
	bool value;
	bool pressed;
	void *user_data;
	void (*callback)(Toggle *t, void *);

	Toggle(int k, void (*cb)(Toggle *t, void *), void *ud) {
		key = k;
		value = true;
		callback = cb;
		user_data = ud;
		pressed = false;
	}

	void update(bool down) {
		if (pressed && !down) {
			pressed = false;
			value = !value;
			callback(this, user_data);
		} else if (!pressed && down) {
			pressed = true;
		}
	}
};

static void toggle_capture(Toggle *t, void *user_data)
{
	int mode = t->value ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
	glfwSetInputMode((GLFWwindow *)user_data, GLFW_CURSOR, mode);
}

static Toggle *capture;
static const float sensitivity = 0.001;
Hello::Hello() : camera(0, 0, 3) {} 
Hello::~Hello() {} 

static Cube skybox(0, 0, 0, 80);
static const char *const skybox_faces[] = {
	"textures/skybox/bkg1_right.png",
	"textures/skybox/bkg1_left.png",
	"textures/skybox/bkg1_top.png",
	"textures/skybox/bkg1_bot.png",
	"textures/skybox/bkg1_front.png",
	"textures/skybox/bkg1_back.png"
};

static Cube cube(0, 0, -5, 1);
static const char *const cube_faces[] = {
	"textures/skybox/red.png",
	"textures/skybox/cyan.png",
	"textures/skybox/blue.png",
	"textures/skybox/magenta.png",
	"textures/skybox/green.png",
	"textures/skybox/yellow.png"
};

void Hello::load()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2, 0.3, 0.3, 1);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	/* set toggle callbacks */
	capture = new Toggle(GLFW_KEY_ESCAPE, toggle_capture, window);

	/* load shaders */
	skybox.load_shader(&shader_factory);
	cube.load_shader(&shader_factory);

	shader_factory.link_programs();

	/* load textures */
	skybox.load_textures(skybox_faces);
	cube.load_textures(cube_faces);

	/* load objects (generate buffers) */
	skybox.generate();
	cube.generate();

}

static float r = .25;
static float last_x = 400, last_y = 300;
void Hello::update(float dt)
{
	double x, y;
	const float cameraSpeed = 50 * dt;
	if (capture->value) {
		glfwGetCursorPos(window, &x, &y);
		camera.rotate(
			(float)((x - last_x) * sensitivity),
			(float)((y - last_y) * sensitivity)
		);
		last_x = x;
		last_y = y;
	}

	capture->update(glfwGetKey(window, capture->key) == GLFW_PRESS);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.mv_fwrd(cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.mv_back(cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.mv_left(cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.mv_rght(cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		camera.mv_up(cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		camera.mv_down(cameraSpeed);
	}


	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, 1);
		return;
	}
}

void Hello::draw()
{
	/* set projection matrix */
	glm::mat4 proj = glm::perspective(
		(float)(r*M_PI),
		800.0f / 600.0f, 
		0.1f, 200.0f);
	skybox.shader.use();
	skybox.shader.set_mat4("projection", glm::value_ptr(proj));

	cube.shader.use();
	cube.shader.set_mat4("projection", glm::value_ptr(proj));

	glm::mat4 view;

	skybox.shader.use();
	view = glm::mat4(glm::mat3(camera.get_view()));
	skybox.shader.set_mat4("view", glm::value_ptr(view));
	skybox.bind()->draw();

	cube.shader.use();
	view = camera.get_view();
	cube.shader.set_mat4("view", glm::value_ptr(view));
	cube.bind()->draw();
}

void Hello::free()
{
	delete capture;
}
