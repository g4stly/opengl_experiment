#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "application.h"
#include "shader_factory.h"
#include "texture.h"
#include "hello.h"

static int v_sz = 36;
static float vertices[] = {
	// front
	 0.5,  0.5,  0.5,  1.0, 0.0, 0.0,  1.0, 1.0,
	-0.5,  0.5,  0.5,  1.0, 1.0, 0.0,  0.0, 1.0,
	-0.5, -0.5,  0.5,  0.0, 1.0, 0.0,  0.0, 0.0,

	 0.5,  0.5,  0.5,  1.0, 0.0, 0.0,  1.0, 1.0,
	 0.5, -0.5,  0.5,  0.0, 0.0, 1.0,  1.0, 0.0,
	-0.5, -0.5,  0.5,  0.0, 1.0, 0.0,  0.0, 0.0,

	// back
	 0.5,  0.5, -0.5,  1.0, 1.0, 0.0,  0.0, 1.0,
	-0.5,  0.5, -0.5,  1.0, 0.0, 0.0,  1.0, 1.0,
	-0.5, -0.5, -0.5,  0.0, 0.0, 1.0,  1.0, 0.0,

	 0.5,  0.5, -0.5,  1.0, 1.0, 0.0,  0.0, 1.0,
	 0.5, -0.5, -0.5,  0.0, 1.0, 0.0,  0.0, 0.0,
	-0.5, -0.5, -0.5,  0.0, 0.0, 1.0,  1.0, 0.0,
	
	// left
	-0.5,  0.5,  0.5,  1.0, 0.0, 0.0,  1.0, 1.0,
	-0.5,  0.5, -0.5,  1.0, 1.0, 0.0,  0.0, 1.0,
	-0.5, -0.5, -0.5,  0.0, 1.0, 0.0,  0.0, 0.0,

	-0.5,  0.5,  0.5,  1.0, 0.0, 0.0,  1.0, 1.0,
	-0.5, -0.5,  0.5,  0.0, 0.0, 1.0,  1.0, 0.0,
	-0.5, -0.5, -0.5,  0.0, 1.0, 0.0,  0.0, 0.0,

	// right
	 0.5,  0.5,  0.5,  1.0, 1.0, 0.0,  0.0, 1.0,
	 0.5, -0.5,  0.5,  0.0, 1.0, 0.0,  0.0, 0.0,
	 0.5, -0.5, -0.5,  0.0, 0.0, 1.0,  1.0, 0.0,

	 0.5,  0.5,  0.5,  1.0, 1.0, 0.0,  0.0, 1.0,
	 0.5,  0.5, -0.5,  1.0, 0.0, 0.0,  1.0, 1.0,
	 0.5, -0.5, -0.5,  0.0, 0.0, 1.0,  1.0, 0.0,

	// top
	 0.5,  0.5, -0.5,  1.0, 0.0, 0.0,  1.0, 1.0,
	-0.5,  0.5, -0.5,  1.0, 1.0, 0.0,  0.0, 1.0,
	-0.5,  0.5,  0.5,  0.0, 1.0, 0.0,  0.0, 0.0,

	 0.5,  0.5, -0.5,  1.0, 0.0, 0.0,  1.0, 1.0,
	 0.5,  0.5,  0.5,  0.0, 0.0, 1.0,  1.0, 0.0,
	-0.5,  0.5,  0.5,  0.0, 1.0, 0.0,  0.0, 0.0,

	// bottom
	 0.5, -0.5, -0.5,  1.0, 0.0, 0.0,  1.0, 1.0,
	 0.5, -0.5,  0.5,  1.0, 1.0, 0.0,  0.0, 1.0,
	-0.5, -0.5,  0.5,  0.0, 1.0, 0.0,  0.0, 0.0,

	 0.5, -0.5, -0.5,  1.0, 0.0, 0.0,  1.0, 1.0,
	-0.5, -0.5, -0.5,  0.0, 0.0, 1.0,  1.0, 0.0,
	-0.5, -0.5,  0.5,  0.0, 1.0, 0.0,  0.0, 0.0

};

glm::vec3 positions[] = {
	glm::vec3( 0.0,  0.0,  0.0),
	glm::vec3( 2.3,  1.9, -7.0),
	glm::vec3(-1.9,  0.9, -8.2),
	glm::vec3( 3.0, -1.4, -0.8),
	glm::vec3(-0.6,  1.0, -11.0),
	glm::vec3(-4.0, -0.4, -1.0),
	glm::vec3(-2.0, -0.0, -7.8),
	glm::vec3( 2.3, -0.3, -4.3),
	glm::vec3(-2.0, -1.0, -3.8),
	glm::vec3(-0.2, -1.2, -0.3),
	glm::vec3( 1.1,  1.0, -12.0)
};

static void create_rect(unsigned int *vao, float *v, int v_len)
{
	void *offset;
	unsigned int vbo;
	long vunit = sizeof(*v);
	int stride = 8 * vunit;

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, vao);

	glBindVertexArray(*vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vunit * v_len, v, GL_STATIC_DRAW);

	offset = NULL;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(0);

	offset = (void *)(vunit * 3);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(1);

	offset = (void *)(vunit * 6);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(2);
}

const float sensitivity = 0.005;
Hello::Hello() : camera(0, 0, 3) {} 
Hello::~Hello() {} 

static Shader s;
static Texture wall, face;
static unsigned int vao;
void Hello::load()
{
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	create_rect(&vao, vertices, 8 * v_sz);

	wall.load("wood.jpg");
	face.load("face.png");

	shader_factory.create_shader(
		&s, "src/shader.vert", "src/shader.frag"
	);
	shader_factory.link_programs();

	s.use();
	s.set_int("tex_wall", 0);
	s.set_int("tex_face", 1);
	glm::mat4 proj = glm::perspective(
		(float)(.25*M_PI),
		800.0f / 600.0f, 
		0.1f, 100.0f);
	s.set_mat4("projection", glm::value_ptr(proj));
}

static float last_x = 400, last_y = 300;
void Hello::update(float dt)
{
	double x, y;
	const float cameraSpeed = 4.5 * dt;
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
}

void Hello::draw()
{
	wall.bind(GL_TEXTURE0);
	face.bind(GL_TEXTURE1);

	s.use();

	glm::mat4 view = camera.get_view();
	s.set_mat4("view", glm::value_ptr(view));

	glBindVertexArray(vao);
	for (int i = 0; i < 11; i++) {
		glm::mat4 model = glm::mat4(1.0);
		model = glm::translate(model, positions[i]);
		float r = 20.0 * (i+1) * glfwGetTime();
		model = glm::rotate(model, 
			glm::radians(r),
			glm::vec3(1, .3, .5));
		s.set_mat4("model", glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, v_sz);
	}
}

void Hello::free()
{
	glDeleteVertexArrays(1, &vao);
}
