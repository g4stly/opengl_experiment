#ifndef triangles_h_
#define triangles_h_

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader_factory.h"
#include "texture.h"

class Triangles {
protected:
	bool generated;
	unsigned int vao;
	unsigned int vbo;


	unsigned int textures_len;
	std::vector<Texture *> textures;
	virtual Triangles *add_texture(unsigned int unit, const char *filename);
public:
	Shader shader;
	glm::mat4 model;
	virtual Triangles *load_shader(ShaderFactory *f) = 0;
	virtual Triangles *load_textures() = 0;
	virtual Triangles *generate(
		const float *v, 
		unsigned int v_sz, 
		unsigned int stride);
	virtual Triangles *bind();
	virtual void draw();
	Triangles();
	~Triangles();
};

#endif
