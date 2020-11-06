#ifndef texture_h_
#define texture_h_

#include <glad/glad.h>

class Texture
{
public:
	GLenum type;
	unsigned int id;
	int width, height, nch;
	virtual Texture *load(const char *filename);
	virtual Texture *bind(GLenum target);
	Texture(GLenum type);
	virtual ~Texture();
};


#endif
