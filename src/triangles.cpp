#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "triangles.h"

Triangles *Triangles::generate(
	const float *v,
	unsigned int v_sz,
	unsigned int stride)
{
	long f_sz = sizeof(*v);

	textures_len = v_sz;
	stride = stride * f_sz;

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, v_sz * f_sz, v, GL_STATIC_DRAW);

	/* only sets the position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, NULL);
	glEnableVertexAttribArray(0);

	generated = true;
	return this;
}

Triangles *Triangles::add_texture(unsigned int unit, const char *filename)
{
	Texture *t = (new Texture(GL_TEXTURE_2D))->load(filename);
	textures.insert(textures.begin()+unit, t);
	return this;
}

Triangles *Triangles::bind()
{
	GLenum target = GL_TEXTURE0;
	std::vector<Texture *>::size_type i;
	for (i = 0; i < textures.size(); i++) {
		textures[i]->bind(target + i);
	}
	glBindVertexArray(vao);
	return this;
}

void Triangles::draw()
{
	shader.set_mat4("model", glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, textures_len);
}

Triangles::Triangles()
{
	model = glm::mat4(1.0);
}

Triangles::~Triangles()
{
	if (generated) {
		glDeleteVertexArrays(1, &vao);
		glDeleteVertexArrays(1, &vbo);
	}
	std::vector<Texture *>::size_type i;
	for (i = 0; i < textures.size(); i++) {
		delete textures[i];
	}
}
