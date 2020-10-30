#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STBI_ONLY_PNG
#define STBI_ONLY_JPEG
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "texture.h"
#include "util.h"

static bool flipped = false;
static const char *const load_fail = "Texture::load(%s): %s\n";
void Texture::load(const char *filename)
{
	if (!flipped) {
		stbi_set_flip_vertically_on_load(true);
		flipped = false;
	}
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char *data = stbi_load(filename, &width, &height, &nch, 4);
	if (!data) {
		die(load_fail, filename, "failed to load image");
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 
		0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}

void Texture::bind(GLenum target)
{
	glActiveTexture(target);
	glBindTexture(GL_TEXTURE_2D, id);
}
