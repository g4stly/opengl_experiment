#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "trianglesv.h"

void TrianglesV::gen(
	const float *const v, 
	unsigned int vsz, 
	unsigned int stride)
{
	unsigned int floatsz = sizeof(float);
	stride = stride * floatsz;
	v_len = vsz;

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	GLenum target = GL_ARRAY_BUFFER;
	glBindBuffer(target, vbo);
	glBufferData(target, vsz * floatsz, v, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
	glEnableVertexAttribArray(0);
}

void TrianglesV::draw()
{
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, v_len);
}

void TrianglesV::scale(glm::vec3 vec)
{
	model = glm::scale(model, vec);
}

void TrianglesV::translate(glm::vec3 vec)
{
	model = glm::translate(model, vec);
}

void TrianglesV::rotate(float r, glm::vec3 vec)
{
	model = glm::rotate(model, r, vec);
}

TrianglesV::TrianglesV()
{
	model = glm::mat4(1.0);
}
