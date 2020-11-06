#include <stb_image.h>
#include "cube_texture.h"
#include "util.h"

static const char * const load_fail = "CubeTexture::load(%s): %s\n";

CubeTexture::CubeTexture() : Texture(GL_TEXTURE_CUBE_MAP)
{
}

CubeTexture *CubeTexture::load(const char *const *filenames)
{
	glGenTextures(1, &id);
	glBindTexture(type, id);
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	for (int i = 0; i < 6; i++) {
		unsigned char *data = stbi_load(filenames[i], &width, &height, &nch, 4);
		if (!data) {
			die(load_fail, filenames[i], "failed to load image");
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0, GL_RGB, width, height, 
			0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}

	return this;
}
