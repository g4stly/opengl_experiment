#include <iostream>
#include <glad/glad.h>
#include "application.h"
#include "shader_factory.h"
#include "hello.h"

static unsigned int vao;
static float vertices[] = {
	-0.5, 0.5, 0.0,
	0.5, 0.5, 0.0,
	0.0, -0.5, 0.0
};

Hello::Hello() 
{

}

Hello::~Hello() 
{
}

static Shader s;
void Hello::load()
{
	unsigned int vbo;

	shader_factory.create_shader(&s, "src/shader.vert", "src/shader.frag");
	shader_factory.link_programs();

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, 
		vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);
}

void Hello::update()
{
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, 1);
	}
}

void Hello::draw()
{
	s.use();
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
