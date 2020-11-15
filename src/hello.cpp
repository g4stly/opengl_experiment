#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_factory.h"
#include "texture.h"
#include "hello.h"
#include "cubev.h"

static Shader light_shader;
static Shader obj_shader;
static CubeV object;
static CubeV light;

Hello::Hello() : camera(0, 0, 9) {} 
Hello::~Hello() {} 

void Hello::load()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2, 0.2, 0.2, 1);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	/* load shaders */
	shader_factory.create_shader(&obj_shader,
		"src/shaders/object.vert",
		"src/shaders/object.frag"
	);

	shader_factory.create_shader(&light_shader,
		"src/shaders/object.vert",
		"src/shaders/light.frag"
	);

	shader_factory.link_programs();

	glm::vec3 lightPos = glm::vec3(3, 0, 2);
	glm::vec3 lightColor = glm::vec3(1, 1, 1);
	glm::vec3 objectColor = glm::vec3(1, .5, .3);
	
	obj_shader.use();
	obj_shader.set_vec3("lightColor", &lightColor[0]);
	obj_shader.set_vec3("objectColor", &objectColor[0]);
	obj_shader.set_vec3("lightPos", &lightPos[0]);

	light_shader.use();
	light_shader.set_vec3("lightColor", &lightColor[0]);


	/* load objects (generate buffers) */
	object.gen();
	light.gen();
	light.translate(lightPos);
	light.scale(glm::vec3(.2, .2, .2));
}

static float last_x = 400;
static float last_y = 300;
static float sensitivity = 0.001;
void Hello::update(float dt)
{
	double x, y;
	const float cameraSpeed = 20 * dt;
	glfwGetCursorPos(window, &x, &y);
	camera.rotate(
		(float)((x - last_x) * sensitivity),
		(float)((y - last_y) * sensitivity)
	);
	last_x = x;
	last_y = y;

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

	// rotate object
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		object.rotate((M_PI*.3)*dt, glm::vec3(0, 1, 0));
	}
}

void Hello::draw()
{

	glm::mat4 proj = glm::perspective(
		(float)(0.25*M_PI),
		800.0f / 600.0f, 
		0.1f, 200.0f);
	glm::mat4 view = camera.get_view();

	obj_shader.use();
	obj_shader.set_mat4("projection", glm::value_ptr(proj));
	obj_shader.set_mat4("view", glm::value_ptr(view));
	obj_shader.set_mat4("model", glm::value_ptr(object.model));
	glm::mat4 imodel = object.model;
	imodel = glm::inverse(imodel);
	obj_shader.set_mat4("imodel", glm::value_ptr(imodel));
	object.draw();

	light_shader.use();
	light_shader.set_mat4("projection", glm::value_ptr(proj));
	light_shader.set_mat4("view", glm::value_ptr(view));
	light_shader.set_mat4("model", glm::value_ptr(light.model));
	light.draw();

}

void Hello::free()
{
}
