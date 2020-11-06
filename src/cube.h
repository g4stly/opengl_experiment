#ifndef cube_h_
#define cube_h_

#include "shader_factory.h"
#include "triangles.h"

class Cube : public Triangles{
public:
	Cube *load_shader(ShaderFactory *f);
	Cube *load_textures(const char *const *faces);
	Cube *load_textures();
	Cube *generate();
	Cube(float x, float y, float z, float s);
	~Cube();
};

#endif
