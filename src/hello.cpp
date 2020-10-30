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

Hello::Hello() 
{

}

Hello::~Hello() 
{
}

static Shader s;
static Texture wall, face;
static unsigned int vao;
void Hello::load()
{
	glEnable(GL_DEPTH_TEST);
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
}

void Hello::update()
{
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

	glm::mat4 model = glm::mat4(1.0);
	model = glm::rotate(model, 
		-(float)(glfwGetTime()*M_PI/2), 
		glm::vec3(.5, 1, 0));
	s.set_mat4("model", glm::value_ptr(model));

	glm::mat4 view = glm::mat4(1.0);
	view = glm::translate(view, glm::vec3(0, 0, -2));
	s.set_mat4("view", glm::value_ptr(view));

	glm::mat4 proj = glm::perspective((float)(.5 * M_PI),
		800.0f / 600.0f, 0.1f, 100.0f);
	s.set_mat4("projection", glm::value_ptr(proj));

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, v_sz);
}

void Hello::free()
{
	glDeleteVertexArrays(1, &vao);
}
