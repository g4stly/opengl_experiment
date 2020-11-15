#ifndef trianglesv_h_
#define trianglesv_h_

#include <glm/glm.hpp>

class TrianglesV {
protected:
	unsigned int vao;
	unsigned int vbo;
	unsigned int v_len;
public:
	glm::mat4 model;
	virtual void gen(
		const float *const v, 
		unsigned int vsz, 
		unsigned int stride);
	virtual void draw();
	virtual void translate(glm::vec3 vec);
	virtual void rotate(float r, glm::vec3 vec);
	virtual void scale(glm::vec3 vec);
	TrianglesV();
};


#endif
