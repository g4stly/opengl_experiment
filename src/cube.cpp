#include <iostream>
#include <glad/glad.h>
#include "cube_texture.h"
#include "cube.h"
#include "util.h"

static float vertices[] = {
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

Cube *Cube::load_shader(ShaderFactory *f)
{
	f->create_shader(&shader,
		"src/skybox.vert",
		"src/skybox.frag"
	);
	return this;
}

static const char *const df_faces[] = {
	"textures/skybox/a.png",
	"textures/skybox/b.png",
	"textures/skybox/c.png",
	"textures/skybox/d.png",
	"textures/skybox/e.png",
	"textures/skybox/f.png"
	/*
	"textures/skybox/bkg1_right.png",
	"textures/skybox/bkg1_left.png",
	"textures/skybox/bkg1_top.png",
	"textures/skybox/bkg1_bot.png",
	"textures/skybox/bkg1_front.png",
	"textures/skybox/bkg1_back.png"
	*/
};

Cube *Cube::load_textures()
{
	return load_textures(df_faces);
}

Cube *Cube::load_textures(const char *const *faces)
{
	CubeTexture *t = (new CubeTexture())->load(faces);
	textures.insert(textures.begin(), t);

	shader.use();
	shader.set_int("skybox", 0);
	return this;
}

Cube *Cube::generate()
{
	Triangles::generate(vertices, 36 * 3, 3);

	return this;
}

Cube::Cube(float x, float y, float z, float scale)
{
	model = glm::translate(model, glm::vec3(x, y, z));
	model = glm::scale(model, glm::vec3(scale, scale, scale));
}

Cube::~Cube()
{
}
